#include "simde/update_mos.hpp"

namespace simde {

template class UpdateMOs<double>;
template class UpdateMOs<double, type::derived_space_t<double>>;
template class UpdateMOs<double, type::canonical_space_t<double>>;
template class UpdateMOs<float>;
template class UpdateMOs<float, type::derived_space_t<float>>;
template class UpdateMOs<float, type::canonical_space_t<float>>;

} // namespace simde
