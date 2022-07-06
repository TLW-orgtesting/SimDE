#include "property_types/correlation_energy.hpp"

namespace property_types {

template class CorrelationEnergy<double>;
template class CorrelationEnergy<double, type::derived_space_t<double>>;
template class CorrelationEnergy<double, type::canonical_space_t<double>>;
template class CorrelationEnergy<float>;
template class CorrelationEnergy<float, type::derived_space_t<float>>;
template class CorrelationEnergy<float, type::canonical_space_t<float>>;

} // namespace property_types
