#pragma once
#include "simde/types.hpp"
#include <pluginplay/property_type/property_type.hpp>

namespace simde {

DECLARE_PROPERTY_TYPE(ShellNorms);

//------------------------Implementations---------------------------------------

PROPERTY_TYPE_INPUTS(ShellNorms) {
    using basis_type = const simde::type::ao_space&;
    auto rv          = pluginplay::declare_input()
                .add_field<basis_type>("Basis1")
                .template add_field<basis_type>("Basis2");
    rv["Basis1"].set_description("The first basis set");
    rv["Basis2"].set_description("The second basis set");
    return rv;
}

PROPERTY_TYPE_RESULTS(ShellNorms) {
    using return_type = std::vector<std::vector<double>>;
    auto rv =
      pluginplay::declare_result().add_field<return_type>("Screening Matrix");
    rv["Screening Matrix"].set_description(
      "The Cauchy Schwarz screening matrix");
    return rv;
}

} // namespace simde
