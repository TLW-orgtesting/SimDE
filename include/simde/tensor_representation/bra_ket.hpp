#pragma once
#include "simde/types.hpp"
#include <pluginplay/pluginplay.hpp>

namespace simde {

template<typename BraType, typename OpType, typename KetType>
DECLARE_TEMPLATED_PROPERTY_TYPE(BraKet, BraType, OpType, KetType);

template<typename BraType, typename OpType, typename KetType>
TEMPLATED_PROPERTY_TYPE_INPUTS(BraKet, BraType, OpType, KetType) {
    using op_t = const OpType&;

    auto rv = pluginplay::declare_input()
                .add_field<const BraType&>("Bra")
                .template add_field<op_t>("Operator")
                .template add_field<const KetType&>("Ket");
    return rv;
}

template<typename BraType, typename OpType, typename KetType>
TEMPLATED_PROPERTY_TYPE_RESULTS(BraKet, BraType, OpType, KetType) {
    auto rv = pluginplay::declare_result().add_field<double>("value");
    return rv;
}

template<typename BraType, typename KetType>
using CorrelationEnergy = BraKet<BraType, type::els_hamiltonian, KetType>;

template<typename BraType>
using ElectronicEnergy = BraKet<BraType, type::els_hamiltonian, BraType>;

template<typename BraType>
using TotalEnergy = BraKet<BraType, type::hamiltonian, BraType>;

} // namespace simde
