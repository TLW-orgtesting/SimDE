#pragma once
#include "property_types/ao_integrals/detail_/make_key.hpp"
#include "property_types/ao_integrals/n_center.hpp"
#include "property_types/types.hpp"
#include <sde/property_type/property_type.hpp>

namespace property_types {

/** @brief The property type for modules that build Fock matrices in the AO
 *  basis set.
 *
 *  The Fock matrix (or Kohn-Sham matrix for DFT) is an effective one-electron
 *  potential. Modules that satisfy this property type are capable of computing
 *  the Fock matrix in the AO basis set.
 *
 *  @tparam ElementType The type of the elements in the returned tensor.
 *  @tparam OrbitalType The type of the input orbital space
 */
template<typename ElementType, typename OrbitalType, typename BaseType>
DECLARE_DERIVED_TEMPLATED_PROPERTY_TYPE(FockMatrix_, BaseType, ElementType,
                                        OrbitalType, BaseType);

//-------------------------------------Implementations--------------------------

template<typename ElementType, typename OrbitalType, typename BaseType>
TEMPLATED_PROPERTY_TYPE_INPUTS(FockMatrix_, ElementType, OrbitalType,
                               BaseType) {
    auto rv = sde::declare_input()
                .add_field<const type::molecule&>("Molecule")
                .add_field<const OrbitalType&>("Molecular Orbitals");
    rv["Molecule"].set_description("The molecular system");
    rv["Molecular Orbitals"].set_description("The molecular orbitals");
    return rv;
}

template<typename ElementType, typename OrbitalType, typename BaseType>
TEMPLATED_PROPERTY_TYPE_RESULTS(FockMatrix_, ElementType, OrbitalType,
                                BaseType) {
    using my_type     = FockMatrix_<ElementType, OrbitalType, BaseType>;
    using tensor_type = std::decay_t<decltype(std::declval<OrbitalType>().C())>;
    auto key          = ao_integrals::detail_::make_key<my_type>("f");
    auto rv           = sde::declare_result().add_field<tensor_type>(key);
    rv[key].set_description("The computed Fock Matrix");
    return rv;
}

template<typename ElementType, typename OrbitalType>
using FockMatrix =
  FockMatrix_<ElementType, OrbitalType, ao_integrals::TwoCenter<ElementType>>;

template<typename ElementType, typename OrbitalType>
using SparseFockMatrix =
  FockMatrix_<ElementType, OrbitalType,
              ao_integrals::SparseTwoCenter<ElementType>>;

extern template class FockMatrix_<double, type::derived_space_t<double>,
                                  ao_integrals::TwoCenter<double>>;
extern template class FockMatrix_<float, type::derived_space_t<float>,
                                  ao_integrals::TwoCenter<float>>;

} // namespace property_types
