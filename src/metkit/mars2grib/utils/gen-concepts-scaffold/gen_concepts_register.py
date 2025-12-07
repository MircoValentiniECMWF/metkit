#!/usr/bin/env python3

import sys
from pathlib import Path
import re

try:
    import yaml
except ImportError:
    print("Missing PyYAML. Install with: pip install pyyaml", file=sys.stderr)
    sys.exit(1)


# ---------------------------------------------------------------------------
# Naming helpers — IDENTICI allo script di scaffolding
# ---------------------------------------------------------------------------

def split_words(name: str):
    s = re.sub(r'[^0-9A-Za-z]+', ' ', name)
    s = re.sub(r'([a-z0-9])([A-Z])', r'\1 \2', s)
    return [p for p in s.split() if p]


def to_kebab(name: str) -> str:
    return "-".join(p.lower() for p in split_words(name))


def to_snake(name: str) -> str:
    return "_".join(p.lower() for p in split_words(name))


def to_camel(name: str) -> str:
    return "".join(p.capitalize() for p in split_words(name))


# ---------------------------------------------------------------------------
# Registry header generator
# ---------------------------------------------------------------------------

def generate_registry_header(concept_names, singleton: bool) -> str:

    # ---- includes (path + umbrella header)
    includes = []
    for c in concept_names:
        kebab = to_kebab(c)
        snake = to_snake(c)
        includes.append(f'#include "{kebab}/{snake}.h"')

    include_block = "\n".join(includes)

    # ---- RegisterVariants lines
    register_lines = []
    for c in concept_names:
        camel = to_camel(c)
        register_lines.append(
f"""    RegisterVariants<{camel}ConceptInfo, {camel}List,
                     MarsDict_t,GeoDict_t,ParDict_t,OptDict_t,OutDict_t>::run(registry);"""
        )

    register_block = "\n\n".join(register_lines)

    # ---- factory / singleton switch
    if not singleton:
        factory = f"""
// ======================================================
// make_concept_registry()  (NON-SINGLETON)
// ======================================================
template<
    class MarsDict_t,
    class GeoDict_t,
    class ParDict_t,
    class OptDict_t,
    class OutDict_t
>
ConceptRegistry<
    MarsDict_t, GeoDict_t, ParDict_t, OptDict_t, OutDict_t
>
make_concept_registry()
{{
    using Registry = ConceptRegistry<
        MarsDict_t, GeoDict_t, ParDict_t, OptDict_t, OutDict_t>;

    Registry registry;

{register_block}

    return registry;
}}
"""
    else:
        factory = f"""
// ======================================================
// concept_registry_instance()  (SINGLETON)
// ======================================================
template<
    class MarsDict_t,
    class GeoDict_t,
    class ParDict_t,
    class OptDict_t,
    class OutDict_t
>
ConceptRegistry<
    MarsDict_t, GeoDict_t, ParDict_t, OptDict_t, OutDict_t
>&
concept_registry_instance()
{{
    static auto instance =
        make_concept_registry<
            MarsDict_t, GeoDict_t, ParDict_t, OptDict_t, OutDict_t>();

    return instance;
}}
"""

    return f"""#pragma once

#include <map>
#include <string>
#include <array>
#include <utility>

#include "concept_core.h"

{include_block}

// ======================================================
// Registry: (concept, variantName) -> table [NUM_STAGES x NUM_SECTIONS]
// ======================================================
template<
    class MarsDict_t,
    class GeoDict_t,
    class ParDict_t,
    class OptDict_t,
    class OutDict_t
>
struct ConceptRegistry
{{
    using FnPtr =
        uint8_t(*)(const MarsDict_t&,
                   const GeoDict_t&,
                   const ParDict_t&,
                   const OptDict_t&,
                   OutDict_t&);

    using Table = std::array<std::array<FnPtr, NUM_SECTIONS>, NUM_STAGES>;

    std::map<std::pair<std::string_view,std::string_view>, Table> map;

    void add( const std::string_view& conceptName,
              const std::string_view& variantName,
              Table table)
    {{
        map.emplace(
            std::make_pair(conceptName, variantName),
            std::move(table)
        );
    }}
}};

{factory}
"""


# ---------------------------------------------------------------------------
# Main
# ---------------------------------------------------------------------------

def main(argv):

    if len(argv) != 4:
        print("Usage:")
        print("  gen_concept_registry.py concepts.yaml output.h [singleton|nonsingleton]")
        return 1

    yaml_path = Path(argv[1])
    out_path  = Path(argv[2])
    mode      = argv[3].lower()

    if mode not in ("singleton", "nonsingleton"):
        print("Mode must be: singleton | nonsingleton")
        return 1

    with yaml_path.open("r", encoding="utf-8") as f:
        data = yaml.safe_load(f)

    concepts = data.get("concepts")
    if not isinstance(concepts, dict):
        print("YAML must contain 'concepts:' mapping")
        return 1

    concept_names = list(concepts.keys())

    header = generate_registry_header(
        concept_names,
        singleton = (mode == "singleton")
    )

    out_path.write_text(header, encoding="utf-8")
    print(f"Generated registry header: {out_path}")
    print(f"Mode: {mode}")

    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv))
