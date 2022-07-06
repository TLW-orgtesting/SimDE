#pragma once
#include "simde/types.hpp"
#include <pluginplay/property_type/property_type.hpp>

namespace simde {

/**
 * @brief The property type for modules that calculate atomic charges.
 */
DECLARE_PROPERTY_TYPE(AtomicCharges);

//---------------------------Implementations------------------------------------
PROPERTY_TYPE_INPUTS(AtomicCharges) {
    auto rv = pluginplay::declare_input()
                .add_field<const type::molecule&>("Molecule")
                .add_field<const type::el_density&>("Density");
    rv["Molecule"].set_description("The molecular system");
    rv["Density"].set_description("The electronic density");
    return rv;
}

PROPERTY_TYPE_RESULTS(AtomicCharges) {
    auto rv =
      pluginplay::declare_result().add_field<type::tensor>("Partial Charges");
    rv["Partial Charges"].set_description("The calculated partial charges");
    return rv;
}

} // namespace simde
