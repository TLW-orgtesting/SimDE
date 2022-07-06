#include "property_types/ao_integrals/kinetic.hpp"
#include "tests/test_property_type.hpp"

using namespace property_types::ao_integrals;

TEST_CASE("Kinetic") {
    test_property_type<Kinetic<double>>({"bra", "ket"}, {"(m|T|n)"});
}