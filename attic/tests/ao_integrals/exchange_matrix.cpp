#include "property_types/ao_integrals/exchange_matrix.hpp"
#include "tests/test_property_type.hpp"

TEST_CASE("ExchangeMatrix") {
    test_property_type<property_types::ExchangeMatrix<>>(
      {"Molecule", "Molecular Orbitals", "bra", "ket"}, {"(m|k|n)"});
}
