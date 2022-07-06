#include "simde/ao_integrals/df_coefficients.hpp"
#include "test_property_type.hpp"

TEST_CASE("DFCoefficients") {
    test_property_type<property_types::DFCoefficients<>>({"bra", "ket"},
                                                         {"(m|l|n)"});
}
