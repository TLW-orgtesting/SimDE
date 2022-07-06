#pragma once
#include "property_types/ao_integrals/type_traits.hpp"
#include "property_types/types.hpp"
#include <sde/property_type/property_type.hpp>

namespace property_types {

template<typename SpaceType, typename BaseType>
DECLARE_DERIVED_TEMPLATED_PROPERTY_TYPE(Transformed_, BaseType, SpaceType,
                                        BaseType);

template<typename SpaceType, typename BaseType>
TEMPLATED_PROPERTY_TYPE_INPUTS(Transformed_, SpaceType, BaseType) {
    using orb_space_t = const SpaceType&;

    if constexpr(ao_integrals::n_centers_v<BaseType> == 2) {
        return sde::declare_input()
          .add_field<orb_space_t>("final bra")
          .template add_field<orb_space_t>("final ket");
    } else if constexpr(ao_integrals::n_centers_v<BaseType> == 3) {
        return sde::declare_input()
          .add_field<orb_space_t>("final bra")
          .template add_field<orb_space_t>("final ket 1")
          .template add_field<orb_space_t>("final ket 2");
    } else if constexpr(ao_integrals::n_centers_v<BaseType> == 4) {
        return sde::declare_input()
          .add_field<orb_space_t>("final bra 1")
          .template add_field<orb_space_t>("final bra 2")
          .template add_field<orb_space_t>("final ket 1")
          .template add_field<orb_space_t>("final ket 2");
    } else {
        static_assert(
          ao_integrals::n_centers_v<BaseType>, // Will be false if we get here
          "Type does not inherit from TwoCenter, ThreeCenter, or FourCenter");
    }
}

template<typename SpaceType, typename BaseType>
TEMPLATED_PROPERTY_TYPE_RESULTS(Transformed_, SpaceType, BaseType) {
    return sde::declare_result();
}

template<typename BaseType>
using Transformed = Transformed_<type::orbital_space_t<double>, BaseType>;

template<typename BaseType>
using SparseTransformed = Transformed_<type::sparse_space_t<double>, BaseType>;

} // namespace property_types