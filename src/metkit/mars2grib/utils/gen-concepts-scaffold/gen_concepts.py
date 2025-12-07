#!/usr/bin/env python3
"""
Generate concept scaffolding (enum/encoding/info/umbrella headers) from a YAML
specification of concepts and their types.

Usage:
    python gen_concepts.py concepts.yaml output_dir

YAML format:

concepts:
  analysis:
    - default
  composition:
    - chem
    - aerosol
    - default
  ...
"""

import sys
import os
import re
from pathlib import Path

try:
    import yaml
except ImportError:
    print("This script requires PyYAML (pip install pyyaml).", file=sys.stderr)
    sys.exit(1)


# ---------------------------------------------------------------------
# Naming helpers
# ---------------------------------------------------------------------

def split_words(name: str):
    """Split identifiers like 'shapeOfTheEarth', 'spectral_complex', 'on-demand'
    into logical word tokens."""
    # Replace non-alnum with spaces
    s = re.sub(r'[^0-9A-Za-z]+', ' ', name)
    # Insert spaces between lower->upper and letter->digit / digit->letter
    s = re.sub(r'([a-z0-9])([A-Z])', r'\1 \2', s)
    s = re.sub(r'([A-Za-z])([0-9])', r'\1 \2', s)
    s = re.sub(r'([0-9])([A-Za-z])', r'\1 \2', s)
    parts = [p for p in s.split() if p]
    return parts


def to_kebab(name: str) -> str:
    return "-".join(p.lower() for p in split_words(name))


def to_snake(name: str) -> str:
    return "_".join(p.lower() for p in split_words(name))


def to_camel(name: str) -> str:
    """PascalCase from any form."""
    return "".join(p[0].upper() + p[1:] for p in split_words(name))


def type_to_enum_name(type_name: str) -> str:
    """Convert a type string (e.g. 'spectral_complex', 'onDemandExtremesDT')
    into an enum identifier (e.g. 'SpectralComplex', 'OnDemandExtremesDT')."""
    parts = split_words(type_name)
    if not parts:
        return "Default"
    return "".join(p[0].upper() + p[1:] for p in parts)


# ---------------------------------------------------------------------
# Generators for each header
# ---------------------------------------------------------------------

def generate_enum_header(concept: str, types: list[str]) -> str:
    base_snake = to_snake(concept)
    concept_camel = to_camel(concept)
    enum_name = f"{concept_camel}Type"
    list_name = f"{concept_camel}List"
    func_name = f"{base_snake}TypeName"

    # Enum entries
    enum_entries = []
    for i, t in enumerate(types):
        enum_id = type_to_enum_name(t)
        if i == 0:
            enum_entries.append(f"    {enum_id} = 0")
        else:
            enum_entries.append(f"    {enum_id}")
    enum_body = ",\n".join(enum_entries)

    # ValueList entries
    vl_entries = [
        f"    {enum_name}::{type_to_enum_name(t)}"
        for t in types
    ]
    vl_body = ",\n".join(vl_entries)

    # DEF lines
    def_lines = []
    for t in types:
        enum_id = type_to_enum_name(t)
        def_lines.append(
            f"    DEF({enum_name}::{enum_id}, \"{t}\");"
        )
    def_block = "\n".join(def_lines)

    return f"""#pragma once

#include <string>
#include <string_view>
#include <vector>
#include <cstdint>
#include <iostream>

#include "../concept_core.h"

// ======================================================
// ENUM OF VARIANTS FOR THIS CONCEPT
// ======================================================
enum class {enum_name} : int {{
{enum_body}
}};

// ======================================================
// COMPILE-TIME TYPELIST
// ======================================================
using {list_name} = ValueList<
{vl_body}
>;

// ======================================================
// VARIANT -> STRING MAPPING
// ======================================================
template<{enum_name} T>
constexpr std::string_view {func_name}();

#define DEF(T,NAME) \\
    template<> constexpr std::string_view {func_name}<T>() {{ return NAME; }}

{def_block}

#undef DEF
"""


def generate_encoding_header(concept: str) -> str:
    base_snake = to_snake(concept)
    concept_camel = to_camel(concept)
    enum_name = f"{concept_camel}Type"
    applicable_name = f"{base_snake}Applicable"
    func_name = f"{base_snake}TypeName"
    op_name = f"{concept_camel}Op"

    return f"""#pragma once

#include <string>
#include <string_view>
#include <iostream>

#include "../concept_core.h"
#include "{base_snake}_enum.h"

// ======================================================
// DEFAULT APPLICABILITY (user will override manually)
// ======================================================
constexpr bool {applicable_name}(int Stage, int Section, {enum_name} Variant)
{{
    return false;
}}

// ======================================================
// MAIN OPERATION
// ======================================================
template<
    int Stage, int Section,
    {enum_name} Variant,
    class MarsDict_t,
    class GeoDict_t,
    class ParDict_t,
    class OptDict_t,
    class OutDict_t
>
uint8_t {op_name}(
    const MarsDict_t&  mars,
    const GeoDict_t&   geo,
    const ParDict_t&   par,
    const OptDict_t&   opt,
    OutDict_t&         out)
{{
    std::cout << "[Concept {concept_camel}] Op called: "
              << "Stage="   << Stage
              << ", Section=" << Section
              << ", Variant=" << std::string({func_name}<Variant>())
              << std::endl;
    return 0;
}}
"""


def generate_info_header(concept: str) -> str:
    base_snake = to_snake(concept)
    concept_camel = to_camel(concept)
    enum_name = f"{concept_camel}Type"
    info_name = f"{concept_camel}ConceptInfo"
    applicable_name = f"{base_snake}Applicable"
    func_name = f"{base_snake}TypeName"
    op_name = f"{concept_camel}Op"

    # use the original concept key as the "name" string
    concept_string_name = concept

    return f"""#pragma once

#include <string>
#include <string_view>

#include "../concept_core.h"
#include "{base_snake}_enum.h"
#include "{base_snake}_encoding.h"

// ======================================================
// ConceptInfo
// ======================================================
struct {info_name}
{{
    static constexpr const char* name = "{concept_string_name}";

    template<
        int Stage, int Sec,
        {enum_name} Variant,
        class MarsDict_t,
        class GeoDict_t,
        class ParDict_t,
        class OptDict_t,
        class OutDict_t
    >
    static constexpr Fn<
        MarsDict_t,
        GeoDict_t,
        ParDict_t,
        OptDict_t,
        OutDict_t
    > entry()
    {{
        if constexpr ( {applicable_name}(Stage, Sec, Variant) ) {{
            return &{op_name}<
                Stage, Sec, Variant,
                MarsDict_t,
                GeoDict_t,
                ParDict_t,
                OptDict_t,
                OutDict_t
            >;
        }} else {{
            return nullptr;
        }}
    }}

    template<auto Variant>
    static std::string_view variantName()
    {{
        return std::string_view(
            {func_name}<
                static_cast<{enum_name}>(Variant)
            >()
        );
    }}
}};
"""


def generate_umbrella_header(concept: str) -> str:
    base_snake = to_snake(concept)
    return f"""#pragma once

#include "{base_snake}_enum.h"
#include "{base_snake}_encoding.h"
#include "{base_snake}_info.h"
"""


# ---------------------------------------------------------------------
# Main
# ---------------------------------------------------------------------

def main(argv: list[str]) -> int:
    if len(argv) != 3:
        print(f"Usage: {argv[0]} concepts.yaml output_dir", file=sys.stderr)
        return 1

    yaml_path = Path(argv[1])
    out_dir = Path(argv[2])

    if not yaml_path.is_file():
        print(f"YAML file not found: {yaml_path}", file=sys.stderr)
        return 1

    with yaml_path.open("r", encoding="utf-8") as f:
        data = yaml.safe_load(f)

    concepts = data.get("concepts", {})
    if not isinstance(concepts, dict):
        print("YAML must contain a top-level 'concepts' mapping.", file=sys.stderr)
        return 1

    out_dir.mkdir(parents=True, exist_ok=True)

    for concept, types in concepts.items():
        if not isinstance(types, list) or not types:
            print(f"Concept '{concept}' has no types list or is empty.", file=sys.stderr)
            continue

        dir_name = to_kebab(concept)
        concept_dir = out_dir / dir_name
        concept_dir.mkdir(parents=True, exist_ok=True)

        enum_code = generate_enum_header(concept, types)
        encoding_code = generate_encoding_header(concept)
        info_code = generate_info_header(concept)
        umbrella_code = generate_umbrella_header(concept)

        base_snake = to_snake(concept)

        (concept_dir / f"{base_snake}_enum.h").write_text(enum_code, encoding="utf-8")
        (concept_dir / f"{base_snake}_encoding.h").write_text(encoding_code, encoding="utf-8")
        (concept_dir / f"{base_snake}_info.h").write_text(info_code, encoding="utf-8")
        (concept_dir / f"{base_snake}.h").write_text(umbrella_code, encoding="utf-8")

    return 0


if __name__ == "__main__":
    raise SystemExit(main(sys.argv))
