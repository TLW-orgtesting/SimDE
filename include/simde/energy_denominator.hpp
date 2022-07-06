#pragma once
#include "simde/types.hpp"
#include <pluginplay/property_type/property_type.hpp>

namespace simde {
/** @brief The property type for modules that compute an orbital energy
 *  denominator.
 *
 *  As defined this class is suitable for use with pair theories.
 *
 *  @tparam OccType The type of the occupied orbital space.
 *  @tparam VirtType The type of the virtual orbital space.
 */
template<typename OccType, typename VirtType>
DECLARE_TEMPLATED_PROPERTY_TYPE(EnergyDenominator, OccType, VirtType);

template<typename OccType, typename VirtType>
TEMPLATED_PROPERTY_TYPE_INPUTS(EnergyDenominator, OccType, VirtType) {
    auto rv = pluginplay::declare_input()
                .add_field<const OccType&>("Occupieds")
                .template add_field<const VirtType&>("Virtuals");
    return rv;
}

template<typename OccType, typename VirtType>
TEMPLATED_PROPERTY_TYPE_RESULTS(EnergyDenominator, OccType, VirtType) {
    using tensor_type = std::decay_t<decltype(std::declval<VirtType>().C())>;
    auto rv           = pluginplay::declare_result().add_field<tensor_type>(
      "-1/(e_a + e_b - e_i - e_j)");
    return rv;
}

/// Type of an energy denominator that uses canonical orbitals
using CanonicalEnergyDenominator =
  EnergyDenominator<type::canonical_space, type::canonical_space>;

/// Type of energy denominator which uses tensor of tensors
using LocalEnergyDenominator =
  EnergyDenominator<type::independent_space, type::canonical_tot_space>;

} // namespace simde
