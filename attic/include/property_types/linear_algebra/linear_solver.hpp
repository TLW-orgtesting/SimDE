#pragma once
#include "simde/types.hpp"
#include <sde/property_type/property_type.hpp>

namespace simde {

namespace detail {

template<typename LHS, typename RHS, typename = void>
struct linearsolve_result {};

template<typename LHS, typename RHS>
struct linearsolve_result<LHS, RHS,
                          std::enable_if_t<std::is_same_v<LHS, RHS>>> {
    using type = LHS;
};
template<typename LHS, typename RHS>
struct linearsolve_result<
  LHS, RHS, std::enable_if_t<std::is_same_v<std::complex<LHS>, RHS>>> {
    using type = RHS;
};
template<typename LHS, typename RHS>
struct linearsolve_result<
  LHS, RHS, std::enable_if_t<std::is_same_v<LHS, std::complex<RHS>>>> {
    using type = LHS;
};

template<typename LHS, typename RHS>
using linearsolve_result_t = typename linearsolve_result<LHS, RHS>::type;

}; // namespace detail

/** @brief The property type for modules that solve a system of linear
 *  equations A*X = B.
 *
 *  Modules that satisfy this property solve the system of linear equations
 *
 *  A(i,j) * X(j,k) = B(i,k)
 *
 *  where A, X and B are rank-2 tensors.
 *
 *  @tparam LHSElementType The type of the elements of the input (LHS) tensor.
 *  @tparam RHSElementType The type of the elements of the input (RHS) tensor.
 *  @tparam ResultElementType The type of the elements of the solution tensor.
 */
template<typename LHSElementType, typename RHSElementType,
         typename ResultElementType =
           detail::linearsolve_result_t<LHSElementType, RHSElementType>>
struct LinearSolver
  : public sde::PropertyType<
      LinearSolver<LHSElementType, RHSElementType, ResultElementType>> {
    /// Type of the input (LHS) tensor that accounts for LHSElementType
    using lhs_tensor_type = type::tensor<LHSElementType>;
    /// Type of the input (RHS) tensor that accounts for RHSElementType
    using rhs_tensor_type = type::tensor<RHSElementType>;
    /// Type of the output  tensor that accounts for ResultElementType
    using result_tensor_type = type::tensor<ResultElementType>;
    /// Generates the input fields required by this property type
    auto inputs_();
    /// Generates the result fields required by this property type
    auto results_();
};

//-------------------------------------Implementations--------------------------
template<typename LHSElementType, typename RHSElementType,
         typename ResultElementType>
auto LinearSolver<LHSElementType, RHSElementType,
                  ResultElementType>::inputs_() {
    auto rv = sde::declare_input()
                .add_field<lhs_tensor_type>("LHS")
                .template add_field<rhs_tensor_type>("RHS");
    rv["LHS"].set_description("LHS of linear system");
    rv["RHS"].set_description("RHS of linear system");
    return rv;
} // LinearSolver<LHSElementType, RHSElementType, ResultElementType>::inputs_

template<typename LHSElementType, typename RHSElementType,
         typename ResultElementType>
auto LinearSolver<LHSElementType, RHSElementType,
                  ResultElementType>::results_() {
    auto rv = sde::declare_result().add_field<result_tensor_type>("Solution");
    rv["Solution"].set_description("Solution for the linear system A*X = B");
    return rv;
} // LinearSolver<LHSElementType, RHSElementType, ResultElementType>::results_

extern template class LinearSolver<double, double, double>;
extern template class LinearSolver<float, float, float>;

extern template class LinearSolver<std::complex<double>, std::complex<double>,
                                   std::complex<double>>;
extern template class LinearSolver<std::complex<double>, double,
                                   std::complex<double>>;
extern template class LinearSolver<double, std::complex<double>,
                                   std::complex<double>>;

extern template class LinearSolver<std::complex<float>, std::complex<float>,
                                   std::complex<float>>;
extern template class LinearSolver<std::complex<float>, float,
                                   std::complex<float>>;
extern template class LinearSolver<float, std::complex<float>,
                                   std::complex<float>>;

} // namespace simde
