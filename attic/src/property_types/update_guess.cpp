#include "property_types/update_guess.hpp"

namespace property_types {

template class UpdateGuess<double>;
template class UpdateGuess<double, type::derived_space_t<double>>;
template class UpdateGuess<double, type::canonical_space_t<double>>;
template class UpdateGuess<float>;
template class UpdateGuess<float, type::derived_space_t<float>>;
template class UpdateGuess<float, type::canonical_space_t<float>>;

} // namespace property_types
