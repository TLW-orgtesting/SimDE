#pragma once
#include "simde/types.hpp"
#include <pluginplay/property_type/property_type.hpp>

namespace simde {

template<typename ResultBasis, typename InputBasis>
DECLARE_TEMPLATED_PROPERTY_TYPE(ComplimentaryAuxiliaryBasisSet, ResultBasis,
                                InputBasis);

template<typename ResultBasis, typename InputBasis>
TEMPLATED_PROPERTY_TYPE_INPUTS(ComplimentaryAuxiliaryBasisSet, ResultBasis,
                               InputBasis) {
    auto rv =
      pluginplay::declare_input().add_field<const InputBasis&>("orbital basis");
    return rv;
}

template<typename ResultBasis, typename InputBasis>
TEMPLATED_PROPERTY_TYPE_RESULTS(ComplimentaryAuxiliaryBasisSet, ResultBasis,
                                InputBasis) {
    auto rv = pluginplay::declare_result().add_field<ResultBasis>("CABS");
    return rv;
}

using CABS =
  ComplimentaryAuxiliaryBasisSet<type::derived_space, type::ao_space>;

} // namespace simde
