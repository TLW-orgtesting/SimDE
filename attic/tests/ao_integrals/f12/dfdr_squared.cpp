#include "property_types/ao_integrals/f12/dfdr_squared.hpp"
#include "tests/test_property_type.hpp"

using namespace property_types::ao_integrals::f12;

TEST_CASE("dfdr Squared 2C") {
    test_property_type<dfdrSquared2C<double>>({"bra", "ket"},
                                              {"(m|[f_12, [T, f_12]]|n)"});
}

TEST_CASE("dfdr Squared 3C") {
    test_property_type<dfdrSquared3C<double>>({"bra", "ket 1", "ket 2"},
                                              {"(m|[f_12, [T, f_12]]|nl)"});
}

TEST_CASE("dfdr Squared 4C") {
    test_property_type<dfdrSquared4C<double>>(
      {"bra 1", "bra 2", "ket 1", "ket 2"}, {"(mn|[f_12, [T, f_12]]|ls)"});
}