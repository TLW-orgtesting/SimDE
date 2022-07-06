#pragma once
#include "property_types/ao_integrals/detail_/make_key.hpp"
#include "property_types/ao_integrals/n_center.hpp"
#include "property_types/types.hpp"
#include <sde/property_type/property_type.hpp>

namespace property_types {

/**
 * @brief The property type for modules that build the density-fitting
 * coefficients for computing the J and K matrices using 3C ERIs.
 *
 * @tparam ElementType The type of the elements in the returned tensor
 */
template<typename ElementType = double>
DECLARE_DERIVED_TEMPLATED_PROPERTY_TYPE(DFCoefficients,
                                        ao_integrals::TwoCenter<ElementType>,
                                        ElementType);

//---------------------------Implementations------------------------------------
template<typename ElementType>
TEMPLATED_PROPERTY_TYPE_INPUTS(DFCoefficients, ElementType) {
    return sde::declare_input();
}

template<typename ElementType>
TEMPLATED_PROPERTY_TYPE_RESULTS(DFCoefficients, ElementType) {
    using my_type     = DFCoefficients<ElementType>;
    using tensor_type = type::tensor<ElementType>;
    auto key          = ao_integrals::detail_::make_key<my_type>("l");
    auto rv           = sde::declare_result().add_field<tensor_type>(key);
    rv[key].set_description("The computed DF coefficients");
    return rv;
}

extern template class DFCoefficients<double>;
extern template class DFCoefficients<float>;

} // namespace property_types
