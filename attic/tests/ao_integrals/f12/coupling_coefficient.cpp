#include "property_types/ao_integrals/f12/coupling_coefficient.hpp"
#include "property_types/types.hpp"
#include "tests/test_property_type.hpp"

using namespace property_types;
using namespace ao_integrals::f12;

TEST_CASE("F12 C value") {
    using mo_type = type::canonical_space_t<double>;
    test_property_type<CouplingCoefficient<mo_type, mo_type>>(
      {"Molecular system", "Occupied Orbital Space", "Virtual Orbital Space"},
      {"C"});
}