#include "simde/linear_algebra/matrix_inverse.hpp"

namespace simde {

template class MatrixInverse<double>;
template class MatrixInverse<float>;
template class MatrixInverse<std::complex<double>>;
template class MatrixInverse<std::complex<float>>;

} // namespace simde
