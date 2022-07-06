#include "simde/atomic_charges.hpp"
#include "test_property_type.hpp"

TEST_CASE("AtomicCharges") {
    test_property_type<simde::AtomicCharges>({"Molecule", "Density"},
                                             {"Partial Charges"});
}
