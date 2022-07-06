#include "property_types/ao_integrals/electron_repulsion.hpp"
#include "property_types/transformed.hpp"
#include "tests/test_property_type.hpp"

using namespace property_types;

TEMPLATE_TEST_CASE("Transformed<ERI2c>", "", double, float) {
    using pt = Transformed<ao_integrals::ERI2C<TestType>>;

    test_property_type<pt>({"final bra", "final ket", "bra", "ket"},
                           {"(m|r_12|n)"});
}

TEMPLATE_TEST_CASE("Transformed<ERI3c>", "", double, float) {
    using pt = Transformed<ao_integrals::ERI3C<TestType>>;

    test_property_type<pt>(
      {"final bra", "final ket 1", "final ket 2", "bra", "ket 1", "ket 2"},
      {"(m|r_12|nl)"});
}

TEMPLATE_TEST_CASE("Transformed<ERI4c>", "", double, float) {
    using pt = Transformed<ao_integrals::ERI4C<TestType>>;

    test_property_type<pt>({"final bra 1", "final bra 2", "final ket 1",
                            "final ket 2", "bra 1", "bra 2", "ket 1", "ket 2"},
                           {"(mn|r_12|ls)"});
}