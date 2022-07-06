#pragma once
#include "property_types/types.hpp"
#include <sde/property_type/property_type.hpp>

namespace property_types::ao_integrals::f12 {

template<typename OccType, typename VirtType>
DECLARE_TEMPLATED_PROPERTY_TYPE(B, OccType, VirtType);

template<typename OccType, typename VirtType>
TEMPLATED_PROPERTY_TYPE_INPUTS(B, OccType, VirtType) {
    auto rv = sde::declare_input()
                .add_field<const type::molecule&>("Molecular system")
                .template add_field<const OccType&>(
                  "Orbital space for occupied orbitals")
                .template add_field<const VirtType&>(
                  "Orbital space for virtual orbitals");
    return rv;
}

template<typename OccType, typename VirtType>
TEMPLATED_PROPERTY_TYPE_RESULTS(B, OccType, VirtType) {
    using tensor_type = std::decay_t<decltype(std::declval<OccType>().C())>;
    using scalar_type = typename tensor_type::scalar_type;
    auto rv           = sde::declare_result().add_field<scalar_type>("B");
    return rv;
}

} // namespace property_types::ao_integrals::f12