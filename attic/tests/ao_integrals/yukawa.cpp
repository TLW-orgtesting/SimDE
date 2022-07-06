#include "property_types/ao_integrals/yukawa.hpp"
#include "tests/test_property_type.hpp"

using namespace property_types::ao_integrals;

TEST_CASE("Yukawa2C") {
    test_property_type<Yukawa2C<double>>({"STG Exponent", "bra", "ket"},
                                         {"(m|exp(-ar_12)/r_12|n)"});
}

TEST_CASE("Yukawa3C") {
    test_property_type<Yukawa3C<double>>(
      {"STG Exponent", "bra", "ket 1", "ket 2"}, {"(m|exp(-ar_12)/r_12|nl)"});
}

TEST_CASE("Yukawa4C") {
    test_property_type<Yukawa4C<double>>(
      {"STG Exponent", "bra 1", "bra 2", "ket 1", "ket 2"},
      {"(mn|exp(-ar_12)/r_12|ls)"});
}