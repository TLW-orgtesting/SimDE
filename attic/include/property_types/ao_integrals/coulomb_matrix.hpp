#pragma once
#include "property_types/ao_integrals/detail_/make_key.hpp"
#include "property_types/ao_integrals/detail_/type_traits.hpp"
#include "property_types/ao_integrals/n_center.hpp"
#include "property_types/types.hpp"
#include <sde/property_type/property_type.hpp>

namespace property_types {

/** @brief The property type for modules that build the Coulomb matrix, which is
 *  canonically denoted @f$\mathbf{J}@f$.
 *
 *  While the canonical algorithms for building @f$\mathbf{J}@f$ and
 *  @f$\mathbf{K}@f$ usually have them being built together to avoid recomputing
 *  integrals, modern algorithms often build the two by relying on very
 *  different procedures. This property type is for modules that build
 *  @f$\mathbf{J}@f$. The same module may also build @f$\mathbf{K}@f$, in which
 *  case it should register itself as satisfying both property types and rely
 *  on memoization for "computing" @f$\mathbf{K}@f$.
 *
 *  @tparam ElementType The type of the elements in the returned tensor.
 *  @tparam OrbitalType The type of the input orbital space
 */
template<typename ElementType = double,
         typename OrbitalType = type::orbital_space_t<ElementType>,
         typename BaseType    = ao_integrals::TwoCenter<ElementType>>
DECLARE_DERIVED_TEMPLATED_PROPERTY_TYPE(CoulombMatrix_, BaseType, ElementType,
                                        OrbitalType, BaseType);

//-----------------------------Implementations----------------------------------

template<typename ElementType, typename OrbitalType, typename BaseType>
TEMPLATED_PROPERTY_TYPE_INPUTS(CoulombMatrix_, ElementType, OrbitalType,
                               BaseType) {
    auto rv = sde::declare_input()
                .add_field<const type::molecule&>("Molecule")
                .add_field<const OrbitalType&>("Molecular Orbitals");
    rv["Molecule"].set_description("The molecular system");
    rv["Molecular Orbitals"].set_description("The molecular orbitals");
    return rv;
}

template<typename ElementType, typename OrbitalType, typename BaseType>
TEMPLATED_PROPERTY_TYPE_RESULTS(CoulombMatrix_, ElementType, OrbitalType,
                                BaseType) {
    using my_type      = CoulombMatrix_<ElementType, OrbitalType>;
    using traits       = ao_integrals::detail_::NCenterTraits<BaseType>;
    using element_type = typename traits::element_type;
    using space_type   = typename traits::space_type;
    using tensor_type  = typename space_type::overlap_type;
    const auto key     = ao_integrals::detail_::make_key<my_type>("j");
    auto rv            = sde::declare_result().add_field<tensor_type>(key);
    rv[key].set_description("The computed Coulomb matrix");
    return rv;
}

template<typename ElementType = double,
         typename OrbitalType = type::orbital_space_t<ElementType>>
using CoulombMatrix = CoulombMatrix_<ElementType, OrbitalType,
                                     ao_integrals::TwoCenter<ElementType>>;

template<typename ElementType = double,
         typename OrbitalType = type::orbital_space_t<ElementType>>
using SparseCoulombMatrix =
  CoulombMatrix_<ElementType, OrbitalType,
                 ao_integrals::SparseTwoCenter<ElementType>>;

extern template class CoulombMatrix_<double>;
extern template class CoulombMatrix_<double, type::derived_space_t<double>>;
extern template class CoulombMatrix_<double, type::canonical_space_t<double>>;
extern template class CoulombMatrix_<float>;
extern template class CoulombMatrix_<float, type::derived_space_t<float>>;
extern template class CoulombMatrix_<float, type::canonical_space_t<float>>;

} // namespace property_types
