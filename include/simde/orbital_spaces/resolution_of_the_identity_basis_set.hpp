#pragma once
#include "simde/types.hpp"
#include <pluginplay/property_type/property_type.hpp>

namespace simde {

/** @brief Property type for the RIBS in F12 theories.
 *
 *  This should not be confused with the auxiliary basis set used in density
 *  fitting or to form the CABS in F12.
 */
template<typename ORBSType, typename CABSType>
DECLARE_TEMPLATED_PROPERTY_TYPE(ResolutionOfTheIdentityBasisSet, ORBSType,
                                CABSType);

template<typename ORBSType, typename CABSType>
TEMPLATED_PROPERTY_TYPE_INPUTS(ResolutionOfTheIdentityBasisSet, ORBSType,
                               CABSType) {
    auto rv = pluginplay::declare_input()
                .add_field<const ORBSType&>("orbital space")
                .template add_field<const CABSType&>("cabs space");
    return rv;
}

template<typename ORBSType, typename CABSType>
TEMPLATED_PROPERTY_TYPE_RESULTS(ResolutionOfTheIdentityBasisSet, ORBSType,
                                CABSType) {
    auto rv = pluginplay::declare_result().add_field<CABSType>("RIBS");
    return rv;
}

using RIBS =
  ResolutionOfTheIdentityBasisSet<type::derived_space, type::derived_space>;

} // namespace simde
