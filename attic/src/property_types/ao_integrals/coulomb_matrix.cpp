#include "property_types/ao_integrals/coulomb_matrix.hpp"

namespace property_types {

template class CoulombMatrix_<double>;
template class CoulombMatrix_<double, type::derived_space_t<double>>;
template class CoulombMatrix_<double, type::canonical_space_t<double>>;
template class CoulombMatrix_<float>;
template class CoulombMatrix_<float, type::derived_space_t<float>>;
template class CoulombMatrix_<float, type::canonical_space_t<float>>;

} // namespace property_types
