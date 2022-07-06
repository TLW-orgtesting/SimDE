#pragma once
#include "property_types/types.hpp"
#include <sde/property_type/property_type.hpp>

namespace property_types::ao_integrals::f12 {

template<typename OccType, typename VirtType>
DECLARE_TEMPLATED_PROPERTY_TYPE(CouplingCoefficient, OccType, VirtType);

template<typename OccType, typename VirtType>
TEMPLATED_PROPERTY_TYPE_INPUTS(CouplingCoefficient, OccType, VirtType) {
    auto rv = sde::declare_input()
                .add_field<const type::molecule&>("Molecular system")
                .template add_field<const OccType&>("Occupied Orbital Space")
                .template add_field<const VirtType&>("Virtual Orbital Space");
    return rv;
}

template<typename OccType, typename VirtType>
TEMPLATED_PROPERTY_TYPE_RESULTS(CouplingCoefficient, OccType, VirtType) {
    using tensor_type = std::decay_t<decltype(std::declval<VirtType>().C())>;
    auto rv           = sde::declare_result().add_field<tensor_type>("C");
    return rv;
}

} // namespace property_types::ao_integrals::f12