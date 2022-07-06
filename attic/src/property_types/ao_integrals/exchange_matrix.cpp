#include "property_types/ao_integrals/exchange_matrix.hpp"

namespace property_types {

template class ExchangeMatrix_<double>;
template class ExchangeMatrix_<double, type::derived_space_t<double>>;
template class ExchangeMatrix_<double, type::canonical_space_t<double>>;
template class ExchangeMatrix_<float>;
template class ExchangeMatrix_<float, type::derived_space_t<float>>;
template class ExchangeMatrix_<float, type::canonical_space_t<float>>;

} // namespace property_types
