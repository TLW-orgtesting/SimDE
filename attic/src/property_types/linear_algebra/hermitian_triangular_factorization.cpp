#include "simde/linear_algebra/hermitian_triangular_factorization.hpp"

namespace simde {

template class BunchKaufmanFactorization<double>;
template class BunchKaufmanFactorization<float>;
template class BunchKaufmanFactorization<std::complex<double>>;
template class BunchKaufmanFactorization<std::complex<float>>;

} // namespace simde
