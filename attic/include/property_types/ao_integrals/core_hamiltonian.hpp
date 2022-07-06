#pragma once
#include "property_types/ao_integrals/detail_/make_key.hpp"
#include "property_types/ao_integrals/detail_/type_traits.hpp"
#include "property_types/ao_integrals/n_center.hpp"
#include "property_types/types.hpp"
#include <sde/property_type/property_type.hpp>

namespace property_types {

/**
 * @brief The property type for modules that build the core Hamiltonian in the
 *        AO basis set.
 *
 * @tparam ElementType The type of the elements in the returned tensor
 */
template<typename ElementType = double,
         typename BaseType    = ao_integrals::TwoCenter<ElementType>>
DECLARE_DERIVED_TEMPLATED_PROPERTY_TYPE(CoreHamiltonian_, BaseType, ElementType,
                                        BaseType);

//---------------------------Implementations------------------------------------
template<typename ElementType, typename BaseType>
TEMPLATED_PROPERTY_TYPE_INPUTS(CoreHamiltonian_, ElementType, BaseType) {
    auto rv = sde::declare_input().add_field<const type::molecule&>("Molecule");
    rv["Molecule"].set_description("The molecular system");
    return rv;
}

template<typename ElementType, typename BaseType>
TEMPLATED_PROPERTY_TYPE_RESULTS(CoreHamiltonian_, ElementType, BaseType) {
    using my_type      = CoreHamiltonian_<ElementType, BaseType>;
    using traits       = ao_integrals::detail_::NCenterTraits<BaseType>;
    using element_type = typename traits::element_type;
    using space_type   = typename traits::space_type;
    using tensor_type  = typename space_type::overlap_type;
    auto key           = ao_integrals::detail_::make_key<my_type>("h");
    auto rv            = sde::declare_result().add_field<tensor_type>(key);
    rv[key].set_description("The computed Core Hamiltonian");
    return rv;
}

template<typename ElementType = double>
using CoreHamiltonian =
  CoreHamiltonian_<ElementType, ao_integrals::TwoCenter<ElementType>>;

template<typename ElementType = double>
using SparseCoreHamiltonian =
  CoreHamiltonian_<ElementType, ao_integrals::SparseTwoCenter<ElementType>>;

extern template class CoreHamiltonian_<double>;
extern template class CoreHamiltonian_<float>;

} // namespace property_types
