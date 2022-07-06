#include "property_types/ao_integrals/emultipole.hpp"

namespace property_types::ao_integrals {

template class EMultipole<double, 1>;
template class EMultipole<float, 1>;
template class EMultipole<double, 2>;
template class EMultipole<float, 2>;
template class EMultipole<double, 3>;
template class EMultipole<float, 3>;

} // namespace property_types::ao_integrals
