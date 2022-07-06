#include "simde/linear_algebra/lu.hpp"
#include "tests/test_property_type.hpp"

TEST_CASE("LU") {
    test_property_type<property_types::LUFactorization<double>>(
      {"Input Matrix"}, {"L", "U"});
}
