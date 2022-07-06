#include "simde/scf_iteration.hpp"

namespace simde {

template class SCFIteration<double>;
template class SCFIteration<double, type::derived_space_t<double>>;
template class SCFIteration<double, type::canonical_space_t<double>>;
template class SCFIteration<float>;
template class SCFIteration<float, type::derived_space_t<float>>;
template class SCFIteration<float, type::canonical_space_t<float>>;

} // namespace simde
