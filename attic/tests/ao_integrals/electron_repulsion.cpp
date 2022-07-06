#include "property_types/ao_integrals/electron_repulsion.hpp"
#include "tests/test_property_type.hpp"

using namespace property_types::ao_integrals;

TEST_CASE("ERI2C") {
    test_property_type<ERI2C<double>>({"bra", "ket"}, {"(m|r_12|n)"});
}

TEST_CASE("ERI3C") {
    test_property_type<ERI3C<double>>({"bra", "ket 1", "ket 2"},
                                      {"(m|r_12|nl)"});
}

TEST_CASE("ERI4C") {
    test_property_type<ERI4C<double>>({"bra 1", "bra 2", "ket 1", "ket 2"},
                                      {"(mn|r_12|ls)"});
}