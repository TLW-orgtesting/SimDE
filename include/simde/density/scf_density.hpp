#pragma once
#include "simde/types.hpp"
#include <pluginplay/pluginplay.hpp>

namespace simde {

/** @brief API for modules which create densities from occupied orbitals.
 *
 *  Modules which satisfy the `SCFDensity` property type effectively
 *  have an API: `simde::type::el_density (const canonical_space&)`.
 *  For example, the `SCF::Density` will compute the density by contracting
 *  the occupied orbitals together.
 */
DECLARE_PROPERTY_TYPE(SCFDensity);

PROPERTY_TYPE_INPUTS(SCFDensity) {
    using simde::type::canonical_space;
    auto rv =
      pluginplay::declare_input().add_field<const canonical_space&>("Phi0");
    return rv;
}

PROPERTY_TYPE_RESULTS(SCFDensity) {
    using simde::type::el_density;
    auto rv = pluginplay::declare_result().add_field<el_density>("Density");
    return rv;
}

} // namespace simde