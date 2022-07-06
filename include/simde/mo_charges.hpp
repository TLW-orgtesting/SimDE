#pragma once
#include "simde/types.hpp"
#include <pluginplay/property_type/property_type.hpp>

namespace simde {

/**
 * @brief The property type for modules that calculate MO charges.
 *
 * @tparam ElementType The type of the elements in the returned tensor
 * @tparam OrbitalType The type of the input molecular orbitals
 */
template<typename OrbitalType>
DECLARE_TEMPLATED_PROPERTY_TYPE(MOCharges, OrbitalType);

template<typename OrbitalType>
TEMPLATED_PROPERTY_TYPE_INPUTS(MOCharges, OrbitalType) {
    auto rv = pluginplay::declare_input().add_field<const OrbitalType&>(
      "Molecular Orbitals");
    rv["Molecular Orbitals"].set_description("The molecular orbitals");
    return rv;
}

template<typename OrbitalType>
TEMPLATED_PROPERTY_TYPE_RESULTS(MOCharges, OrbitalType) {
    auto rv =
      pluginplay::declare_result().add_field<type::tensor>("MO Charges");
    rv["MO Charges"].set_description("The calculated MO charge densities");
    return rv;
}

extern template class MOCharges<type::derived_space>;
extern template class MOCharges<type::canonical_space>;

} // namespace simde
