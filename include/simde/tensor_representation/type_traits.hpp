#pragma once

namespace simde {

template<std::size_t N, typename OperatorType>
class AOTensorRepresentation;

template<typename T>
struct NCenters;

template<std::size_t N, typename OperatorType>
struct NCenters<AOTensorRepresentation<N, OperatorType>>
  : std::integral_constant<std::size_t, N> {};

template<typename T>
struct OperatorType;

template<std::size_t N, typename OpType>
struct OperatorType<AOTensorRepresentation<N, OpType>> {
    using type = OpType;
};

template<typename T>
static constexpr std::size_t n_centers_v = NCenters<T>::value;

template<typename T>
using operator_t = typename OperatorType<T>::type;

} // namespace simde
