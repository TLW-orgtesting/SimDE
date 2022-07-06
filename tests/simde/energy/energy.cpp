#include "../test_property_type.hpp"
#include "simde/energy/energy_class.hpp"

using namespace simde;

TEST_CASE("Energy") { test_property_type<Energy>({"system"}, {"Energy"}); }
