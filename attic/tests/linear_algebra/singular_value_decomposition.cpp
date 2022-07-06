#include "simde/linear_algebra/singular_value_decomposition.hpp"
#include "tests/test_property_type.hpp"

TEST_CASE("SingularValueDecomposition") {
    test_property_type<property_types::SingularValueDecomposition<>>(
      {"Matrix"}, {"S", "U", "V"});
}
