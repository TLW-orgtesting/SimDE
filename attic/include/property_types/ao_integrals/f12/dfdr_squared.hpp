#pragma once
#include "property_types/ao_integrals/detail_/macros.hpp"
#include "property_types/ao_integrals/detail_/make_key.hpp"
#include "property_types/ao_integrals/type_traits.hpp"
#include "property_types/types.hpp"
#include <sde/property_type/property_type.hpp>

namespace property_types::ao_integrals::f12 {

/** @brief This is the property type for the quantity usually denoted as
 *         @f$\left|\bigtriangledown f_{12}(r_{12})\right|^2@f$ in f12 theory.
 *
 *  The @f$B@f$ term of F12 involves a double commutator of the correlation
 *  factor with the electronic kinetic energy. The commutators reduce to:
 *  @f$\left|\bigtriangledown f_{12}(r_{12})\right|^2@f$.
 */
template<typename BaseType>
DECLARE_DERIVED_TEMPLATED_PROPERTY_TYPE(dfdrSquared, BaseType, BaseType);

template<typename BaseType>
TEMPLATED_PROPERTY_TYPE_INPUTS(dfdrSquared, BaseType) {
    return sde::declare_input();
}

template<typename BaseType>
TEMPLATED_PROPERTY_TYPE_RESULTS(dfdrSquared, BaseType) {
    using traits       = detail_::NCenterTraits<BaseType>;
    using element_type = typename traits::element_type;
    using space_type   = typename traits::space_type;
    using tensor_type  = typename space_type::overlap_type;
    using my_type      = dfdrSquared<BaseType>;

    return sde::declare_result().add_field<tensor_type>(
      detail_::make_key<my_type>("[f_12, [T, f_12]]"));
}

template<typename ElementType>
using SparsedfdrSquared4C = dfdrSquared<SparseFourCenter<ElementType>>;

MULTICENTER_AO_INTEGRAL_TYPEDEFS(dfdrSquared);
MULTICENTER_AO_INTEGRAL_EXTERNS(dfdrSquared);

} // namespace property_types::ao_integrals::f12