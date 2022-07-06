#pragma once
#include "simde/types.hpp"
#include <pluginplay/property_type/property_type.hpp>

namespace simde {

DECLARE_PROPERTY_TYPE(AuxiliaryBasisSet);

PROPERTY_TYPE_INPUTS(AuxiliaryBasisSet) {
    using basis_type = const simde::type::ao_space&;
    auto rv =
      pluginplay::declare_input().add_field<basis_type>("AtomicBasisSet");
    rv["AtomicBasisSet"].set_description("The atomic basis set");
    return rv;
}

PROPERTY_TYPE_RESULTS(AuxiliaryBasisSet) {
    using basis_type = simde::type::ao_space;
    auto rv =
      pluginplay::declare_result().add_field<basis_type>("AuxiliaryBasisSet");
    rv["AuxiliaryBasisSet"].set_description("The density fitting basis set");
    return rv;
}

} // namespace simde