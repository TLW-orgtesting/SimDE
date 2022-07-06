// #pragma once
// #include "property_types/types.hpp"
// #include <sde/property_type/property_type.hpp>

// namespace property_types {

// /** @brief The property type for modules that compute canonical orbitals.
//  *
//  *  Canonical orbitals diagonalize the Fock matrix. Modules that satisfy this
//  *  property type take an input set of orbitals and a Fock matrix and return
//  *  the orbitals that digonalize the Fock matrix.
//  *
//  *  @tparam InputOrbitalType The type of the input orbitals.
//  *  @tparam OutputOrbitalType The type of the output orbitals.
//  */
// template<typename InputOrbitalType, typename OutputOrbitalType>
// DECLARE_TEMPLATED_PROPERTY_TYPE(CanonicalOrbitals, InputOrbitalType,
//                                 OutputOrbitalType);

// template<typename InputOrbitalType, typename OutputOrbitalType>
// TEMPLATED_PROPERTY_TYPE_INPUTS(CanonicalOrbitals, InputOrbitalType,
//                                OutputOrbitalType) {
//     auto rv =
//       sde::declare_input()
//         .add_field<const InputOrbitalType&>("Orbitals")
//         .template add_field<const chemist::type::tensor<double>&>("F");
//     return rv;
// }

// template<typename InputOrbitalType, typename OutputOrbitalType>
// TEMPLATED_PROPERTY_TYPE_RESULTS(CanonicalOrbitals, InputOrbitalType,
//                                 OutputOrbitalType) {
//     auto rv = sde::declare_result().add_field<OutputOrbitalType>("K");
//     return rv;
// }

// } // namespace property_types