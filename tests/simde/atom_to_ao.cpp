#include "simde/atom_to_ao.hpp"
#include "test_property_type.hpp"

TEST_CASE("AtomToCenter") {
    test_property_type<simde::AtomToAO>({"Molecule", "Orbital Basis"},
                                        {"Atom to Center map"});
}