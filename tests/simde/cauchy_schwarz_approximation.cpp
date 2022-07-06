#include "simde/cauchy_schwarz_approximation.hpp"
#include "test_property_type.hpp"

TEST_CASE("CauchySchwarz") {
    test_property_type<simde::ShellNorms>({"Basis1", "Basis2"},
                                          {"Screening Matrix"});
}
