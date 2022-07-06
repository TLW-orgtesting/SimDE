#include "../test_property_type.hpp"
#include "simde/orbital_spaces/auxiliary_basis_set.hpp"

TEST_CASE("AuxiliaryBasisSet") {
    test_property_type<simde::AuxiliaryBasisSet>({"AtomicBasisSet"},
                                                 {"AuxiliaryBasisSet"});
}