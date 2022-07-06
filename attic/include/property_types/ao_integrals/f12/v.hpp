#pragma once
#include <sde/property_type/property_type.hpp>

namespace property_types::ao_integrals::f12 {

template<typename OccType, typename VirtType>
DECLARE_TEMPLATED_PROPERTY_TYPE(V, OccType, VirtType);

template<typename OccType, typename VirtType>
TEMPLATED_PROPERTY_TYPE_INPUTS(V, OccType, VirtType) {
    auto rv =
      sde::declare_input()
        .add_field<const OccType&>("Orbital space for occupied orbitals")
        .template add_field<const VirtType&>(
          "Orbital space for virtual orbitals");
    return rv;
}

template<typename OccType, typename VirtType>
TEMPLATED_PROPERTY_TYPE_RESULTS(V, OccType, VirtType) {
    using tensor_type = std::decay_t<decltype(std::declval<OccType>().C())>;
    using scalar_type = typename tensor_type::scalar_type;
    auto rv           = sde::declare_result().add_field<scalar_type>("V");
    return rv;
}
} // namespace property_types::ao_integrals::f12