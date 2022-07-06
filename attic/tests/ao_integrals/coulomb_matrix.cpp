#include "property_types/ao_integrals/coulomb_matrix.hpp"
#include "tests/test_property_type.hpp"

TEST_CASE("CoulombMatrix") {
    test_property_type<property_types::CoulombMatrix<>>(
      {"Molecule", "Molecular Orbitals", "bra", "ket"}, {"(m|j|n)"});
}
