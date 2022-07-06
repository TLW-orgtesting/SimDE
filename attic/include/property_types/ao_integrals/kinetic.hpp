#pragma once
#include "property_types/ao_integrals/detail_/make_key.hpp"
#include "property_types/ao_integrals/n_center.hpp"
#include "property_types/types.hpp"
#include <sde/property_type/property_type.hpp>

namespace property_types::ao_integrals {

/**
 * @brief The property type for modules that build tensors filled with electron
 * kinetic energy integrals in the AO basis set.
 *
 * @tparam ElementType The type of the element in the tensor. Defaults to
 *                     `double`.
 */
template<typename ElementType = double>
DECLARE_DERIVED_TEMPLATED_PROPERTY_TYPE(Kinetic, TwoCenter<ElementType>,
                                        ElementType);

template<typename ElementType>
TEMPLATED_PROPERTY_TYPE_INPUTS(Kinetic, ElementType) {
    return sde::declare_input();
}

template<typename ElementType>
TEMPLATED_PROPERTY_TYPE_RESULTS(Kinetic, ElementType) {
    using tensor_type = type::tensor<ElementType>;
    using my_type     = Kinetic<ElementType>;

    return sde::declare_result().add_field<tensor_type>(
      detail_::make_key<my_type>("T"));
}

extern template class Kinetic<double>;
extern template class Kinetic<float>;

} // namespace property_types::ao_integrals
