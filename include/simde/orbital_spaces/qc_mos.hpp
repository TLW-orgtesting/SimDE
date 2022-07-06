#pragma once
#include "simde/types.hpp"
#include <pluginplay/pluginplay.hpp>

namespace simde {

template<typename InputOrbitals, typename OutputOrbitals>
DECLARE_TEMPLATED_PROPERTY_TYPE(QCMOs, InputOrbitals, OutputOrbitals);

template<typename InputOrbitals, typename OutputOrbitals>
TEMPLATED_PROPERTY_TYPE_INPUTS(QCMOs, InputOrbitals, OutputOrbitals) {
    auto rv = pluginplay::declare_input()
                .add_field<const type::fock&>("Fock Operator")
                .template add_field<const InputOrbitals&>("Orbitals");
    return rv;
}

template<typename InputOrbitals, typename OutputOrbitals>
TEMPLATED_PROPERTY_TYPE_RESULTS(QCMOs, InputOrbitals, OutputOrbitals) {
    auto rv = pluginplay::declare_result().add_field<OutputOrbitals>("PAOs");
    return rv;
}

/// Type of the property type for QC-NR-PAOs
using qcpaos = QCMOs<type::derived_space, type::canonical_space>;
/// Type of the property type for QC-LMOs
using qclmos = QCMOs<type::derived_space, type::canonical_space>;

} // namespace simde
