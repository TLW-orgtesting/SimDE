#include "../test_property_type.hpp"
#include "simde/orbital_spaces/orbital_spaces.hpp"

using namespace simde;

TEST_CASE("DensityFitBasis") {
    using pt = DensityFitBasis;
    test_property_type<pt>({"Aux Basis", "Coulomb Operator"}, {"DF"});
}