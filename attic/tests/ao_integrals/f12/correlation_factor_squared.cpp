#include "property_types/ao_integrals/f12/correlation_factor_squared.hpp"
#include "tests/test_property_type.hpp"

using namespace property_types::ao_integrals::f12;

TEST_CASE("Correlation Factor Squared 2C") {
    test_property_type<CorrelationFactorSquared2C<double>>(
      {"bra", "ket"}, {"(m|f_12^2(r_12)|n)"});
}

TEST_CASE("Correlation Factor Squared 3C") {
    test_property_type<CorrelationFactorSquared3C<double>>(
      {"bra", "ket 1", "ket 2"}, {"(m|f_12^2(r_12)|nl)"});
}

TEST_CASE("Correlation Factor Squared 4C") {
    test_property_type<CorrelationFactorSquared4C<double>>(
      {"bra 1", "bra 2", "ket 1", "ket 2"}, {"(mn|f_12^2(r_12)|ls)"});
}