#include "property_types/ao_integrals/f12/x.hpp"
#include "property_types/types.hpp"
#include "tests/test_property_type.hpp"

using namespace property_types;
using namespace ao_integrals::f12;

TEST_CASE("F12 X value") {
    using mo_type = type::canonical_space_t<double>;
    test_property_type<X<mo_type, mo_type>>(
      {"Molecular system", "Orbital space for occupied orbitals",
       "Orbital space for virtual orbitals"},
      {"X"});
}