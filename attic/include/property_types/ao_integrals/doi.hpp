#pragma once
#include "property_types/ao_integrals/detail_/make_key.hpp"
#include "property_types/ao_integrals/n_center.hpp"
#include "property_types/types.hpp"
#include <sde/property_type/property_type.hpp>

namespace property_types::ao_integrals {

/**
 * @brief The property type for modules that build tensors filled with
 * differential overlap integrals in the AO basis set.
 *
 * @tparam ElementType The type of the element in the tensor. Defaults to
 *                     `double`.
 *
 * @note DOI inherits from TwoCenter since that's what controls the input
 *       fields; however, DOI is actually a four-center quantity. The type
 *       traits in type_traits.hpp are configured to reflect the four-centered
 *       nature of the DOI.
 */
template<typename ElementType = double>
DECLARE_DERIVED_TEMPLATED_PROPERTY_TYPE(DOI, TwoCenter<ElementType>,
                                        ElementType);

template<typename ElementType>
TEMPLATED_PROPERTY_TYPE_INPUTS(DOI, ElementType) {
    return sde::declare_input();
}

template<typename ElementType>
TEMPLATED_PROPERTY_TYPE_RESULTS(DOI, ElementType) {
    using tensor_type = type::tensor<ElementType>;
    using my_type     = DOI<ElementType>;
    using four_center = FourCenter<ElementType>;

    // N.B. DOIs are actually four-centered, but the inputs are two-centered
    return sde::declare_result().add_field<tensor_type>(
      detail_::make_key<four_center>("delta(r-r')"));
}

extern template class DOI<double>;
extern template class DOI<float>;

} // namespace property_types::ao_integrals
