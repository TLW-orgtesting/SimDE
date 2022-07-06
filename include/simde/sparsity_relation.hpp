#pragma once
#include "simde/types.hpp"
#include <pluginplay/property_type/property_type.hpp>

namespace simde {

/** @brief The property type for modules that compute a sparse relation.
 *
 *  @tparam IndependType The type of the independent basis.
 *  @tparam DependType The type of the dependent basis.
 */
template<typename IndependType, typename DependType>
DECLARE_TEMPLATED_PROPERTY_TYPE(SparsityRelation, IndependType, DependType);

template<typename IndependType, typename DependType>
TEMPLATED_PROPERTY_TYPE_INPUTS(SparsityRelation, IndependType, DependType) {
    auto rv = pluginplay::declare_input()
                .add_field<const IndependType&>("Independent Basis")
                .template add_field<const DependType&>("Dependent Basis");
    rv["Independent Basis"].set_description("The dense basis");
    rv["Dependent Basis"].set_description("The sparse basis");
    return rv;
}

template<typename IndependType, typename DependType>
TEMPLATED_PROPERTY_TYPE_RESULTS(SparsityRelation, IndependType, DependType) {
    using chemist::type::sparse_map;
    auto rv = pluginplay::declare_result().add_field<sparse_map>("Sparse Map");
    rv["Sparse Map"].set_description(
      "Map from a given member of the independent basis to its"
      " domain in the dependent basis set");
    return rv;
}

using AO2AO = SparsityRelation<type::ao_space, type::ao_space>;
using MO2AO = SparsityRelation<type::derived_space, type::ao_space>;
using MO2MO = SparsityRelation<type::derived_space, type::derived_space>;

} // namespace simde
