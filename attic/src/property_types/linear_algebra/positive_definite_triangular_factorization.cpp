#include "simde/linear_algebra/positive_definite_triangular_factorization.hpp"

namespace simde {

template class CholeskyFactorization<double>;
template class CholeskyFactorization<float>;
template class CholeskyFactorization<std::complex<double>>;
template class CholeskyFactorization<std::complex<float>>;

} // namespace simde
