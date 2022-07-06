#pragma once
#include "simde/types.hpp"
#include <pluginplay/pluginplay.hpp>

namespace simde {

DECLARE_PROPERTY_TYPE(MolecularTopology);

PROPERTY_TYPE_INPUTS(MolecularTopology) {
    using mol_input_t = const type::molecule&;
    auto rv = pluginplay::declare_input().add_field<mol_input_t>("Molecule");
    rv.at("Molecule")
      .set_description("Molecular system whose topology is being determined");
    return rv;
}

PROPERTY_TYPE_RESULTS(MolecularTopology) {
    using topology_t = type::topology;
    auto rv = pluginplay::declare_result().add_field<topology_t>("Topology");
    rv.at("Topology").set_description("Topology of input molecule");
    return rv;
}

} // namespace simde
