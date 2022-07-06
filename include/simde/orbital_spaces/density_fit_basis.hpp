#pragma once
#include "simde/types.hpp"
#include <pluginplay/property_type/property_type.hpp>

namespace simde {

/** @brief API for modules that compute density fitting coefficients
 */
DECLARE_PROPERTY_TYPE(DensityFitBasis);

PROPERTY_TYPE_INPUTS(DensityFitBasis) {
    auto rv = pluginplay::declare_input()
                .add_field<const type::ao_space&>("Aux Basis")
                .add_field<const type::el_el_coulomb&>("Coulomb Operator");
    rv["Aux Basis"].set_description("The auxilliary basis set");
    rv["Coulomb Operator"].set_description("A Coulomb Operator");
    return rv;
}

PROPERTY_TYPE_RESULTS(DensityFitBasis) {
    auto rv = pluginplay::declare_result().add_field<type::derived_space>("DF");
    rv["DF"].set_description("The density fitting space");
    return rv;
}

} // namespace simde
