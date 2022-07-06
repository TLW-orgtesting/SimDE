#include "property_types/ao_integrals/core_hamiltonian.hpp"
#include "tests/test_property_type.hpp"

TEST_CASE("CoreHamiltonian") {
    test_property_type<property_types::CoreHamiltonian<>>(
      {"Molecule", "bra", "ket"}, {"(m|h|n)"});
}
