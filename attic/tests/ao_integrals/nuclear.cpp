#include "property_types/ao_integrals/nuclear.hpp"
#include "tests/test_property_type.hpp"

using namespace property_types::ao_integrals;

TEST_CASE("Nuclear") {
    test_property_type<Nuclear<double>>({"molecule", "bra", "ket"},
                                        {"(m|Z_A/r_iA|n)"});
}