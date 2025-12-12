#include "metkit/mars2grib/backend/concepts/concept_registry.h"

#include <iostream>
#include <string>

// Dummy types A,B,C,D
struct A { template<class T> T get(const std::string&) const { return {}; } };
struct B { };
struct C { template<class T> T get(const std::string&) const { return {}; } };
struct D { template<class T> void set(const std::string&, const T&) {} };
struct E { template<class T> void set(const std::string&, const T&) {} };

int main()
{
    using namespace metkit::mars2grib::backend::cnpts;
    using Registry = ConceptRegistry<A,B,C,D,E>;

    Registry registry = make_concept_registry<A,B,C,D,E>();

    A aa;
    B bb;
    C cc;
    D dd;
    E ee;

    // Loop su tutti i typeOfLevel e stampa la tabella
    for (const auto& [ key, table ] : registry.map )
    {
        const auto& [ conceptName, conceptKind ] = key;
        std::cout << "=================================================================================================================================" << std::endl;
        std::cout << "Concept: type:"       << conceptName
                  << ", variant:" << conceptKind << "\n";

        for (int stage = 0; stage < NUM_STAGES; ++stage) {
            for (int sec = 0; sec < NUM_SECTIONS; ++sec) {
                bool assigned = (table[stage][sec] != nullptr);
                std::cout << "  stage "   << stage
                          << ", section " << sec
                          << ": " << (assigned ? "yes" : "no")
                          << std::endl;
                if (assigned) table[stage][sec](aa, bb, cc, dd, ee); // chiamata dummy

            }
        }
        std::cout << std::endl;

    }

    std::cout << "Map size: " << registry.map.size() << std::endl;

    return 0;
}
