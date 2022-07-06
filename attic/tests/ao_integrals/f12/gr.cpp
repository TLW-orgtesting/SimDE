#include "property_types/ao_integrals/f12/gr.hpp"
#include "tests/test_property_type.hpp"

using namespace property_types::ao_integrals::f12;

TEST_CASE("GR 2C") {
    test_property_type<GR2C<double>>({"bra", "ket"}, {"(m|f_12(r_12)/r_12|n)"});
}

TEST_CASE("GR 3C") {
    test_property_type<GR3C<double>>({"bra", "ket 1", "ket 2"},
                                     {"(m|f_12(r_12)/r_12|nl)"});
}

TEST_CASE("GR 4C") {
    test_property_type<GR4C<double>>({"bra 1", "bra 2", "ket 1", "ket 2"},
                                     {"(mn|f_12(r_12)/r_12|ls)"});
}