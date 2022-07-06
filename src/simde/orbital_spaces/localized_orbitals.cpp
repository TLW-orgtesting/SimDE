#include "simde/orbital_spaces/localized_orbitals.hpp"

namespace simde {

template class LocalizedOrbitals<type::derived_space>;
template class LocalizedOrbitals<type::canonical_space>;

} // namespace simde
