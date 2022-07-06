#include "property_types/ao_integrals/doi.hpp"
#include "tests/test_property_type.hpp"

using namespace property_types::ao_integrals;

TEST_CASE("DOI") {
    test_property_type<DOI<>>({"bra", "ket"}, {"(mn|delta(r-r')|ls)"});
}