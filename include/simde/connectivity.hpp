#pragma once
#include "simde/types.hpp"
#include <pluginplay/pluginplay.hpp>

namespace simde {

DECLARE_PROPERTY_TYPE(Connectivity);

PROPERTY_TYPE_INPUTS(Connectivity) {
    using mol_input_t = const type::molecule&;
    auto rv = pluginplay::declare_input().add_field<mol_input_t>("Molecule");
    rv.at("Molecule")
      .set_description("The molecule whose bonds are being assigned.");
    return rv;
}

PROPERTY_TYPE_RESULTS(Connectivity) {
    using table_t = type::connectivity_table;
    auto rv =
      pluginplay::declare_result().add_field<table_t>("Connectivity Table");
    rv.at("Connectivity Table")
      .set_description("Connectivity of the input molecule.");
    return rv;
}

} // namespace simde
