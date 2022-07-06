#include "simde/topology.hpp"
#include "test_property_type.hpp"

TEST_CASE("Topology") {
    test_property_type<simde::MolecularTopology>({"Molecule"}, {"Topology"});
}
