#pragma once
#include "simde/tensor_representation/general_transformed_tensor_representation.hpp"
#include "simde/types.hpp"
namespace simde {

using TransformedERI3 = TransformedTensorRepresentation<3, type::el_el_coulomb>;
using TransformedERI4 = TransformedTensorRepresentation<4, type::el_el_coulomb>;
using TransformedExchange = TransformedTensorRepresentation<2, type::el_scf_k>;
using TransformedF12Commutator =
  TransformedTensorRepresentation<4, type::el_el_f12_commutator>;
using TransformedFock = TransformedTensorRepresentation<2, type::fock>;
using TransformedOverlap =
  TransformedTensorRepresentation<2, type::el_identity>;
using TransformedSTG4 = TransformedTensorRepresentation<4, type::el_el_stg>;
using TransformedYukawa4 =
  TransformedTensorRepresentation<4, type::el_el_yukawa>;

using TransformedLocalERI4 =
  GeneralTransformedTensorRepresentation<4, type::el_el_coulomb>;

using TransformedLocalOverlap =
  GeneralTransformedTensorRepresentation<2, type::el_identity>;

} // namespace simde
