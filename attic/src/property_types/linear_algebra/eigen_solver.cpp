#include "simde/linear_algebra/eigen_solver.hpp"

namespace simde {

template class SelfAdjointEigenSolver<double, double>;
template class SelfAdjointEigenSolver<float, float>;
template class SelfAdjointEigenSolver<std::complex<double>, double>;
template class SelfAdjointEigenSolver<std::complex<float>, float>;

template class GeneralizedSelfAdjointEigenSolver<double, double, double>;
template class GeneralizedSelfAdjointEigenSolver<float, float, float>;
template class GeneralizedSelfAdjointEigenSolver<std::complex<double>,
                                                 std::complex<double>, double>;
template class GeneralizedSelfAdjointEigenSolver<std::complex<float>,
                                                 std::complex<float>, float>;
template class GeneralizedSelfAdjointEigenSolver<std::complex<double>, double,
                                                 double>;
template class GeneralizedSelfAdjointEigenSolver<std::complex<float>, float,
                                                 float>;

} // namespace simde
