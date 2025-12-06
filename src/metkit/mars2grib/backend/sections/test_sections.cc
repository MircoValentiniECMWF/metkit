#include "sections-recipes.h"


int main()
{
    // Example usage
    uint16_t sectionId = 4;
    uint16_t templateId = 1;

    const std::optional<ConceptList> concepts = search(sectionId, templateId);
    if (concepts) {
        for (const auto& concept : *concepts) {
            if (concept.type) {
                printf("Concept: %.*s, Type: %.*s\n",
                       (int)concept.name.size(), concept.name.data(),
                       (int)concept.type->size(), concept.type->data());
            } else {
                printf("Concept: %.*s, Type: null\n",
                       (int)concept.name.size(), concept.name.data());
            }
        }
    } else {
        printf("No recipe found for Section %d, Template %d\n", sectionId, templateId);
    }

    return 0;
}