#include "property_types/ao_integrals/ao_integrals.hpp"
#include "tests/test_property_type.hpp"

using namespace property_types::ao_integrals;

TEMPLATE_TEST_CASE("EMultipole", "", double, float) {
    test_property_type<EMultipole<TestType, 0>>({"origin", "bra", "ket"},
                                                {"(m|r**0|n)"});
}

TEMPLATE_TEST_CASE("EDipole", "", double, float) {
    test_property_type<EDipole<TestType>>({"origin", "bra", "ket"},
                                          {"(m|r**1|n)"});
}

TEMPLATE_TEST_CASE("EQuadrupole", "", double, float) {
    test_property_type<EQuadrupole<TestType>>({"origin", "bra", "ket"},
                                              {"(m|r**2|n)"});
}

TEMPLATE_TEST_CASE("EOctopole", "", double, float) {
    test_property_type<EOctopole<TestType>>({"origin", "bra", "ket"},
                                            {"(m|r**3|n)"});
}