#pragma once
#include "simde/types.hpp"
#include <sde/property_type/property_type.hpp>

namespace simde {

/** @brief The property type for modules that perform QR factorizations
 *  of general matrices A = Q * R
 *
 *  Modules that satisfy this property compute the factorization
 *
 *  A(i,j) = Q(i,k) * R(k,j)
 *
 *  for general rank-2 tensors A. Q is a unitary matrix (Q(i,k) * conj(Q(j,k)) =
 * delta(i,j)) and R is upper triangular
 *
 *  @tparam MatrixElementType The type of the elements of the input/output
 * tensors.
 */
template<typename MatrixElementType>
struct QRFactorization
  : public sde::PropertyType<QRFactorization<MatrixElementType>> {
    /// Type of the input / output  tensors that accounts for MatrixElementType
    using matrix_tensor_type = type::tensor<MatrixElementType>;
    /// Generates the input fields required by this property type
    auto inputs_();
    /// Generates the result fields required by this property type
    auto results_();
};

/** @brief The property type for modules that perform (pivoted) rank revealing
 * QR factorizations of general matrices A = Q * R
 *
 *  Modules that satisfy this property compute the factorization
 *
 *  A(i,j) = Q(i,k) * R(k,j)
 *
 *  for general rank-2 tensors A. Q is a unitary matrix (Q(i,k) * conj(Q(j,k)) =
 * delta(i,j)) and R is upper triangular. The diagonals of R are sorted in
 * decending order as to reveal the rank of A (Q)
 *
 *  @tparam MatrixElementType The type of the elements of the input/output
 * tensors.
 */
template<typename MatrixElementType>
struct RankRevealingQRFactorization
  : public sde::PropertyType<RankRevealingQRFactorization<MatrixElementType>> {
    /// Type of the input / output  tensors that accounts for MatrixElementType
    using matrix_tensor_type = type::tensor<MatrixElementType>;
    /// Type of the return type for the rank
    using rank_value_type = std::size_t;
    /// Generates the input fields required by this property type
    auto inputs_();
    /// Generates the result fields required by this property type
    auto results_();
};

//-------------------------------------Implementations--------------------------

template<typename MatrixElementType>
auto QRFactorization<MatrixElementType>::inputs_() {
    auto rv =
      sde::declare_input().add_field<matrix_tensor_type>("Input Matrix");
    rv["Input Matrix"].set_description("The matrix to be factorized");
    return rv;
} // QRFactorization<MatrixElementType>::inputs_

template<typename MatrixElementType>
auto QRFactorization<MatrixElementType>::results_() {
    auto rv = sde::declare_result()
                .add_field<matrix_tensor_type>("Q")
                .template add_field<matrix_tensor_type>("R");
    rv["Q"].set_description("Q of A = Q * R");
    rv["R"].set_description("R of A = Q * R");
    return rv;
} // QRFactorization<MatrixElementType>::results_

extern template class QRFactorization<double>;
extern template class QRFactorization<float>;
extern template class QRFactorization<std::complex<double>>;
extern template class QRFactorization<std::complex<float>>;

template<typename MatrixElementType>
auto RankRevealingQRFactorization<MatrixElementType>::inputs_() {
    auto rv =
      sde::declare_input().add_field<matrix_tensor_type>("Input Matrix");
    rv["Input Matrix"].set_description("The matrix to be factorized");
    return rv;
} // RankRevealingQRFactorization<MatrixElementType>::inputs_

template<typename MatrixElementType>
auto RankRevealingQRFactorization<MatrixElementType>::results_() {
    auto rv = sde::declare_result()
                .add_field<rank_value_type>("Rank")
                .template add_field<matrix_tensor_type>("Q")
                .template add_field<matrix_tensor_type>("R");
    rv["Rank"].set_description("Rank of A and Q");
    rv["Q"].set_description("Q of A = Q * R");
    rv["R"].set_description("R of A = Q * R");
    return rv;
} // RankRevealingQRFactorization<MatrixElementType>::results_

extern template class RankRevealingQRFactorization<double>;
extern template class RankRevealingQRFactorization<float>;
extern template class RankRevealingQRFactorization<std::complex<double>>;
extern template class RankRevealingQRFactorization<std::complex<float>>;

} // namespace simde
