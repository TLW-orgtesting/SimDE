#pragma once

namespace simde {

template<typename OccType, typename VirtType>
DECLARE_TEMPLATED_PROPERTY_TYPE(DoublesResidual, OccType, VirtType);

template<typename OccType, typename VirtType>
TEMPLATED_PROPERTY_TYPE_INPUTS(DoublesResidual, OccType, VirtType) {
    using tensor_type = std::decay_t<decltype(std::declval<VirtType>().C())>;

    auto rv = pluginplay::declare_input()
                .add_field<const type::molecule&>("Molecule")
                .template add_field<const OccType&>("occupied space")
                .template add_field<const VirtType&>("virtual space")
                .template add_field<const tensor_type&>("amplitudes");
    return rv;
}

template<typename OccType, typename VirtType>
TEMPLATED_PROPERTY_TYPE_RESULTS(DoublesResidual, OccType, VirtType) {
    using tensor_type = std::decay_t<decltype(std::declval<VirtType>().C())>;
    auto rv = pluginplay::declare_result().add_field<tensor_type>("R");
    return rv;
}

} // namespace simde
