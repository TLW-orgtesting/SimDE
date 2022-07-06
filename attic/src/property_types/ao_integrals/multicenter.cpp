#include "property_types/ao_integrals/electron_repulsion.hpp"
#include "property_types/ao_integrals/f12/f12.hpp"
#include "property_types/ao_integrals/stg.hpp"
#include "property_types/ao_integrals/yukawa.hpp"

namespace property_types::ao_integrals {
namespace f12 {

MULTICENTER_AO_INTEGRAL_DEFINES(CorrelationFactor);
MULTICENTER_AO_INTEGRAL_DEFINES(CorrelationFactorSquared);
MULTICENTER_AO_INTEGRAL_DEFINES(dfdrSquared);
MULTICENTER_AO_INTEGRAL_DEFINES(GR);

} // namespace f12

MULTICENTER_AO_INTEGRAL_DEFINES(ERI);
template class ERI<SparseFourCenter<double>>;
template class ERI<SparseFourCenter<float>>;
MULTICENTER_AO_INTEGRAL_DEFINES(STG);
MULTICENTER_AO_INTEGRAL_DEFINES(Yukawa);

} // namespace property_types::ao_integrals
