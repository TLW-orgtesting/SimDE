#pragma once
#include "simde/types.hpp"
#include <pluginplay/property_type/property_type.hpp>

namespace simde {

/** @brief The property type for modules that compute energies and energy
 *         derivatives of molecular systems.
 *
 *  Arguably one of the most important quantities in electronic structure theory
 *  is the energy of the system. Modules that are capable of computing the
 *  energy of a molecular system satisfy the Energy property type.
 *
 *  @tparam ElementType The type of the elements in the tensors.
 */
DECLARE_PROPERTY_TYPE(Energy);

//-------------------------------Implementations--------------------------------
PROPERTY_TYPE_INPUTS(Energy) {
    using chem_sys_t = const type::chemical_system&;
    auto rv = pluginplay::declare_input().add_field<chem_sys_t>("system");
    rv["system"].set_description("The molecular system");
    return rv;
}

PROPERTY_TYPE_RESULTS(Energy) {
    auto rv = pluginplay::declare_result().add_field<double>("Energy");
    rv["Energy"].set_description("The computed energy");
    return rv;
}

} // namespace simde
