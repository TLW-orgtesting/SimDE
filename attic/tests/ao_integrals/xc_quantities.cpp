#include "property_types/ao_integrals/xc_quantities.hpp"
#include "tests/test_property_type.hpp"

TEST_CASE("PureXCQuantities") {
    test_property_type<property_types::PureXCQuantities<>>(
      {"Molecule", "Molecular Orbitals", "Bra", "Ket", "Derivative"},
      {"VXC Matrix", "EXC Energy"});
}
TEST_CASE("HybridXCQuantities") {
    test_property_type<property_types::HybridXCQuantities<>>(
      {"Molecule", "Molecular Orbitals", "Bra", "Ket", "Derivative"},
      {"VXC Matrix", "EXC Energy", "xEXX"});
}
