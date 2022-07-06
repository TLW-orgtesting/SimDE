#pragma once
#include <pluginplay/pluginplay.hpp>

namespace simde {

template<typename InputOrbitals, typename OutputOrbitals>
DECLARE_TEMPLATED_PROPERTY_TYPE(PAOs, InputOrbitals, OutputOrbitals);

template<typename InputOrbitals, typename OutputOrbitals>
TEMPLATED_PROPERTY_TYPE_INPUTS(PAOs, InputOrbitals, OutputOrbitals) {
    auto rv =
      pluginplay::declare_input().add_field<const InputOrbitals&>("Orbitals");
    return rv;
}

template<typename InputOrbitals, typename OutputOrbitals>
TEMPLATED_PROPERTY_TYPE_RESULTS(PAOs, InputOrbitals, OutputOrbitals) {
    auto rv = pluginplay::declare_result().add_field<OutputOrbitals>("PAOs");
    return rv;
}

using paos = PAOs<type::derived_space, type::derived_space>;

} // namespace simde
