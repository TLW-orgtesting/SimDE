#include "simde/linear_algebra/matrix_inverse.hpp"
#include "tests/test_property_type.hpp"

TEST_CASE("MatrixInverse") {
    test_property_type<property_types::MatrixInverse<double>>({"Input Matrix"},
                                                              {"Inverse"});
}
