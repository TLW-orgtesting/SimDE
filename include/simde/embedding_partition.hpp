#pragma once
#include "simde/types.hpp"
#include <pluginplay/property_type/property_type.hpp>

namespace simde {

/** @brief Property type for modules that can partition the density into
 * active and environment parts
 *
 *  @tparam ElementType the type of the elements in the basis set
 *  @tparam OrbitalType the type of the input and output orbital spaces
 */
template<typename OrbitalType>
DECLARE_TEMPLATED_PROPERTY_TYPE(EmbedPartition, OrbitalType);

//-------------------------------Implementations--------------------------------
template<typename OrbitalType>
TEMPLATED_PROPERTY_TYPE_INPUTS(EmbedPartition, OrbitalType) {
    auto rv =
      pluginplay::declare_input()
        .add_field<const type::molecule&>("Molecule")
        .add_field<const type::ao_space&>("Basis Set")
        .template add_field<const std::vector<type::size>&>("Active Atoms")
        .template add_field<const OrbitalType&>("Initial Orbitals");
    rv["Molecule"].set_description("The molecule associated with the density");
    rv["Basis Set"].set_description("The basis set used for the density");
    rv["Active Atoms"].set_description("The list of active atoms");
    rv["Initial Orbitals"].set_description("The initial orbital space");
    return rv;
}

template<typename OrbitalType>
TEMPLATED_PROPERTY_TYPE_RESULTS(EmbedPartition, OrbitalType) {
    auto rv = pluginplay::declare_result()
                .template add_field<OrbitalType>("Active Orbitals")
                .template add_field<OrbitalType>("Environment Orbitals");
    rv["Active Orbitals"].set_description("The active orbital space");
    rv["Environment Orbitals"].set_description("The environment orbital space");
    return rv;
}

extern template class EmbedPartition<type::derived_space>;
extern template class EmbedPartition<type::canonical_space>;

} // namespace simde
