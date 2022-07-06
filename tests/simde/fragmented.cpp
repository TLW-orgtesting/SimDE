#include "simde/fragmented.hpp"
#include "simde/types.hpp"
#include "test_property_type.hpp"

using namespace simde;

using tuple = std::tuple<type::molecule>;

TEMPLATE_LIST_TEST_CASE("Fragmented", "", tuple) {
    using T = TestType;
    test_property_type<Fragmented<T>>({"Object to Fragment"},
                                      {"Fragmented Object"});
}
