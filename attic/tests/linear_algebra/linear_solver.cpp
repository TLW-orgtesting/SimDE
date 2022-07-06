#include "simde/linear_algebra/linear_solver.hpp"
#include "tests/test_property_type.hpp"

TEST_CASE("LinearSolver") {
    test_property_type<property_types::LinearSolver<double, double, double>>(
      {"LHS", "RHS"}, {"Solution"});
}
