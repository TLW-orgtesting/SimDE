#include "simde/connectivity.hpp"
#include "test_property_type.hpp"

TEST_CASE("Connectivity") {
    test_property_type<simde::Connectivity>({"Molecule"},
                                            {"Connectivity Table"});
}
