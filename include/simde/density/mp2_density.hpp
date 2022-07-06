#pragma once
#include <pluginplay/pluginplay.hpp>

namespace simde {

template<typename OccType, typename VirtType>
DECLARE_TEMPLATED_PROPERTY_TYPE(MP2Density, OccType, VirtType);

template<typename OccType, typename VirtType>
TEMPLATED_PROPERTY_TYPE_INPUTS(MP2Density, OccType, VirtType) {
    auto rv = pluginplay::declare_input()
                .add_field<const OccType&>("occupied space")
                .template add_field<const VirtType&>("virtual space");
    return rv;
}

template<typename OccType, typename VirtType>
TEMPLATED_PROPERTY_TYPE_RESULTS(MP2Density, OccType, VirtType) {
    using tensor_type = std::decay_t<decltype(std::declval<OccType>().C())>;
    auto rv = pluginplay::declare_result().add_field<tensor_type>("D");
    return rv;
}

} // namespace simde
