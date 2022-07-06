#include "simde/linear_algebra/lu.hpp"

namespace simde {

template class LUFactorization<double>;
template class LUFactorization<float>;
template class LUFactorization<std::complex<double>>;
template class LUFactorization<std::complex<float>>;

} // namespace simde
