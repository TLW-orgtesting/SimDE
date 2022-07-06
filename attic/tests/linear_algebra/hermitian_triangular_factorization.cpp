#include "simde/linear_algebra/hermitian_triangular_factorization.hpp"
#include "tests/test_property_type.hpp"

TEST_CASE("BunchKaufman") {
    test_property_type<property_types::BunchKaufmanFactorization<double>>(
      {"Input Matrix", "Triangle"}, {"Bunch Kaufman Factor", "D"});
}
