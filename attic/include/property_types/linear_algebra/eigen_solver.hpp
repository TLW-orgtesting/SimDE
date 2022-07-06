#pragma once
#include "simde/types.hpp"
#include <sde/property_type/property_type.hpp>

namespace simde {
namespace detail {

template<typename T>
struct eigenvalue_real {
    using type = T;
};

template<typename T>
struct eigenvalue_real<std::complex<T>> {
    using type = T;
};

template<typename T>
using eigenvalue_real_t = typename eigenvalue_real<T>::type;

} // namespace detail

/** @brief The property type for modules that perform standard eigenvalue
 *  decompositions of self-adjoint matrices A.
 *
 *  Modules that satisfy this property obtain the factorization
 *
 *  A(i,j) = V(i,k) * E(k) * conj(V(j,k))
 *
 *  for self-adjoint rank-2 tensors A(i,j) = conj(A(j,i)). V is the rank-2
 *  tensor of eigenvectors corresponding to the rank-1 tensor of eigenvalues, E.
 *  E will be returned in ascending order.
 *
 *  @tparam MatrixElementType The type of the elements of the input tensor and
 * output tensor of eigenvectors.
 *  @tparam EigenValueType The type of the output eigenvalue tensor.
 */
template<typename MatrixElementType,
         typename EigenValueType = detail::eigenvalue_real_t<MatrixElementType>>
struct SelfAdjointEigenSolver
  : public sde::PropertyType<
      SelfAdjointEigenSolver<MatrixElementType, EigenValueType>> {
    /// Type of the input tensor / output eigenvector tensor that accounts for
    /// MatrixElementType
    using matrix_tensor_type = type::tensor<MatrixElementType>;
    /// Type of the output eigenvalue tensor that accounts for EigenValueType
    using eigenvalue_matrix_tensor_type = type::tensor<EigenValueType>;
    /// Generates the input fields required by this property type
    auto inputs_();
    /// Generates the result fields required by this property type
    auto results_();
}; // struct SelfAdjointEigenSolver

/** @brief The property type for modules that perform generalized eigenvalue
 *  decompositions of self-adjoint matrix pencils (A,B).
 *
 *  Modules that satisfy this property obtain the factorization
 *
 *  A(i,j) = B(i,l) * V(l,k) * E(k) * conj(V(m,k)) * B(m,j)
 *
 *  with V(i,k) * B(k,l) * conj(V(l,j)) = delta(i,j)
 *
 *  for self-adjoint rank-2 tensors A(i,j) = conj(A(j,i)), B(i,j) = conj(B(j,i))
 * with B HPD. B is referred to as the metric. V is the rank-2 tensor of
 * generalized eigenvectors corresponding to the rank-1 tensor of eigenvalues,
 * E.  E will be returned in ascending order.
 *
 *  @tparam MatrixElementType The type of the elements of the input matrix and
 * output tensor of eigenvectors.
 *  @tparam MetricElementType The type of the elements of the input metric.
 *  @tparam EigenValueType The type of the output eigenvalue tensor.
 */
template<typename MatrixElementType,
         typename MetricElementType = MatrixElementType,
         typename EigenValueType = detail::eigenvalue_real_t<MatrixElementType>>
struct GeneralizedSelfAdjointEigenSolver
  : public sde::PropertyType<GeneralizedSelfAdjointEigenSolver<
      MatrixElementType, MetricElementType, EigenValueType>> {
    /// Type of the input (matrix) tensor / output eigenvector tensor that
    /// accounts for MatrixElementType
    using matrix_tensor_type = type::tensor<MatrixElementType>;
    /// Type of the input (metric) tensor that accounts for MetricElementType
    using metric_tensor_type = type::tensor<MetricElementType>;
    /// Type of the output eigenvalue tensor that accounts for EigenValueType
    using eigenvalue_matrix_tensor_type = type::tensor<EigenValueType>;
    /// Generates the input fields required by this property type
    auto inputs_();
    /// Generates the result fields required by this property type
    auto results_();
}; // struct SelfAdjointEigenSolver

//-------------------------------------Implementations--------------------------
template<typename MatrixElementType, typename EigenValueType>
auto SelfAdjointEigenSolver<MatrixElementType, EigenValueType>::inputs_() {
    auto rv =
      sde::declare_input().add_field<matrix_tensor_type>("Input Matrix");
    rv["Input Matrix"].set_description("The matrix to be diagonalized");
    return rv;
}; // SelfAdjointEigenSolver<MatrixElementType,EigenValueType>::inputs_

template<typename MatrixElementType, typename MetricElementType,
         typename EigenValueType>
auto GeneralizedSelfAdjointEigenSolver<MatrixElementType, MetricElementType,
                                       EigenValueType>::inputs_() {
    auto rv = sde::declare_input()
                .add_field<matrix_tensor_type>("Input Matrix")
                .template add_field<metric_tensor_type>("Input Metric");

    rv["Input Matrix"].set_description(
      "A of the (A,B) matrix pencil to be diagonalized");
    rv["Input Metric"].set_description(
      "B of the (A,B) matrix pencil to be diagonalized");
    return rv;
}; // GeneralizedSelfAdjointEigenSolver<MatrixElementType,EigenValueType>::inputs_

template<typename MatrixElementType, typename EigenValueType>
auto SelfAdjointEigenSolver<MatrixElementType, EigenValueType>::results_() {
    auto rv =
      sde::declare_result()
        .add_field<matrix_tensor_type>("Eigenvectors")
        .template add_field<eigenvalue_matrix_tensor_type>("Eigenvalues");

    rv["Eigenvalues"].set_description(
      "The vector of eigenvalues for the input matrix");
    rv["Eigenvectors"].set_description(
      "The matrix of eigenvectors for the input matrix");
    return rv;
}; // SelfAdjointEigenSolver<MatrixElementType,EigenValueType>::results_

template<typename MatrixElementType, typename MetricElementType,
         typename EigenValueType>
auto GeneralizedSelfAdjointEigenSolver<MatrixElementType, MetricElementType,
                                       EigenValueType>::results_() {
    auto rv =
      sde::declare_result()
        .add_field<matrix_tensor_type>("Eigenvectors")
        .template add_field<eigenvalue_matrix_tensor_type>("Eigenvalues");

    rv["Eigenvalues"].set_description(
      "The vector of eigenvalues for the input matrix pencil");
    rv["Eigenvectors"].set_description(
      "The matrix of eigenvectors for the input matrix pencil");
    return rv;
}; // GeneralizedSelfAdjointEigenSolver<MatrixElementType,EigenValueType>::results_

extern template class SelfAdjointEigenSolver<double, double>;
extern template class SelfAdjointEigenSolver<float, float>;
extern template class SelfAdjointEigenSolver<std::complex<double>, double>;
extern template class SelfAdjointEigenSolver<std::complex<float>, float>;

extern template class GeneralizedSelfAdjointEigenSolver<double, double, double>;
extern template class GeneralizedSelfAdjointEigenSolver<float, float, float>;
extern template class GeneralizedSelfAdjointEigenSolver<
  std::complex<double>, std::complex<double>, double>;
extern template class GeneralizedSelfAdjointEigenSolver<
  std::complex<float>, std::complex<float>, float>;
extern template class GeneralizedSelfAdjointEigenSolver<std::complex<double>,
                                                        double, double>;
extern template class GeneralizedSelfAdjointEigenSolver<std::complex<float>,
                                                        float, float>;

} // namespace simde
