#include "property_types/ao_integrals/xc_quantities.hpp"

namespace property_types {

template class PureXCQuantities<double>;
template class PureXCQuantities<double, type::derived_space_t<double>>;
template class PureXCQuantities<double, type::canonical_space_t<double>>;
template class PureXCQuantities<float>;
template class PureXCQuantities<float, type::derived_space_t<float>>;
template class PureXCQuantities<float, type::canonical_space_t<float>>;

template class HybridXCQuantities<double>;
template class HybridXCQuantities<double, type::derived_space_t<double>>;
template class HybridXCQuantities<double, type::canonical_space_t<double>>;
template class HybridXCQuantities<float>;
template class HybridXCQuantities<float, type::derived_space_t<float>>;
template class HybridXCQuantities<float, type::canonical_space_t<float>>;

template class DoubleHybridXCQuantities<double>;
template class DoubleHybridXCQuantities<double, type::derived_space_t<double>>;
template class DoubleHybridXCQuantities<double,
                                        type::canonical_space_t<double>>;
template class DoubleHybridXCQuantities<float>;
template class DoubleHybridXCQuantities<float, type::derived_space_t<float>>;
template class DoubleHybridXCQuantities<float, type::canonical_space_t<float>>;

} // namespace property_types
