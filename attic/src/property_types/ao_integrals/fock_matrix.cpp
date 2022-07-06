#include "property_types/ao_integrals/fock_matrix.hpp"

namespace property_types {

template class FockMatrix_<double, type::derived_space_t<double>,
                           ao_integrals::TwoCenter<double>>;
template class FockMatrix_<float, type::derived_space_t<float>,
                           ao_integrals::TwoCenter<float>>;

} // namespace property_types
