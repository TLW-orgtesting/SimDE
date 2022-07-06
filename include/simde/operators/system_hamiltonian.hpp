#pragma once
#include "simde/types.hpp"
#include <pluginplay/pluginplay.hpp>

namespace simde {

DECLARE_PROPERTY_TYPE(SystemHamiltonian);

PROPERTY_TYPE_INPUTS(SystemHamiltonian) {
    using system = const type::chemical_system&;
    auto rv = pluginplay::declare_input().add_field<system>("Chemical System");
    return rv;
}

PROPERTY_TYPE_RESULTS(SystemHamiltonian) {
    return pluginplay::declare_result().add_field<type::hamiltonian>(
      "Hamiltonian");
}

} // namespace simde
