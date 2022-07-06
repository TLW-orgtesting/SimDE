#include "simde/linear_algebra/positive_definite_triangular_factorization.hpp"
#include "tests/test_property_type.hpp"

TEST_CASE("Cholesky") {
    test_property_type<property_types::CholeskyFactorization<double>>(
      {"Input Matrix", "Triangle"}, {"Cholesky Factor"});
}
