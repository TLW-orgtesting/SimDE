#include "test_property_type.hpp"
#include <property_types/update_mos.hpp>

TEST_CASE("UpdateMOs") {
    test_property_type<property_types::UpdateMOs<>>(
      {"Molecule", "Basis Set", "Fock Matrix", "Previous Molecular Orbitals"},
      {"Molecular Orbitals"});
}
