#pragma once
#include "simde/types.hpp"
#include <sde/property_type/property_type.hpp>

namespace simde {

/** @brief The property type for modules that perform LU factorizations
 *  of general matrices A = L * U
 *
 *  Modules that satisfy this property compute the factorization
 *
 *  A(i,j) = L(i,k) * U(k,j)
 *
 *  for general square rank-2 tensors A. L (U) is a lower (upper) triangular
 * rank-2 tensor.
 *
 *  @tparam MatrixElementType The type of the elements of the input/output
 * tensors.
 */
template<typename MatrixElementType>
struct LUFactorization
  : public sde::PropertyType<LUFactorization<MatrixElementType>> {
    /// Type of the input / output  tensors that accounts for MatrixElementType
    using matrix_tensor_type = type::tensor<MatrixElementType>;
    /// Generates the input fields required by this property type
    auto inputs_();
    /// Generates the result fields required by this property type
    auto results_();
};

//-------------------------------------Implementations--------------------------

template<typename MatrixElementType>
auto LUFactorization<MatrixElementType>::inputs_() {
    auto rv =
      sde::declare_input().add_field<matrix_tensor_type>("Input Matrix");
    rv["Input Matrix"].set_description("The matrix to be factorized");
    return rv;
} // LUFactorization<MatrixElementType>::inputs_

template<typename MatrixElementType>
auto LUFactorization<MatrixElementType>::results_() {
    auto rv = sde::declare_result()
                .add_field<matrix_tensor_type>("L")
                .template add_field<matrix_tensor_type>("U");
    rv["L"].set_description("L of A = L * U");
    rv["U"].set_description("U of A = L * U");
    return rv;
} // LUFactorization<MatrixElementType>::results_

extern template class LUFactorization<double>;
extern template class LUFactorization<float>;
extern template class LUFactorization<std::complex<double>>;
extern template class LUFactorization<std::complex<float>>;

} // namespace simde
