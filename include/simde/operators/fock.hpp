#pragma once
#include "simde/types.hpp"
#include <pluginplay/pluginplay.hpp>

namespace simde {

DECLARE_PROPERTY_TYPE(FockOp);

PROPERTY_TYPE_INPUTS(FockOp) {
    using ham          = const type::els_hamiltonian&;
    using density_type = const type::el_density&;

    auto rv = pluginplay::declare_input()
                .add_field<ham>("Electronic Hamiltonian")
                .template add_field<density_type>("One Electron Density");
    return rv;
}

PROPERTY_TYPE_RESULTS(FockOp) {
    return pluginplay::declare_result().add_field<type::fock>("Fock operator");
}

} // namespace simde
