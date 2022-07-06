#include "../test_property_type.hpp"
#include "simde/orbital_spaces/orbital_spaces.hpp"

using namespace simde;

TEST_CASE("LocalizedOrbitals") {
    test_property_type<LocalizedOrbitals<type::canonical_space>>(
      {"Orbitals"}, {"Local Orbitals"});
}
