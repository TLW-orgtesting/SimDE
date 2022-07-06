#include "property_types/ao_integrals/fock_matrix.hpp"
#include "tests/test_property_type.hpp"

using namespace property_types;

TEMPLATE_TEST_CASE("FockMatrix", "", double, float) {
    using pt = FockMatrix<TestType, type::derived_space_t<TestType>>;
    test_property_type<pt>({"Molecule", "Molecular Orbitals", "bra", "ket"},
                           {"(m|f|n)"});
}
