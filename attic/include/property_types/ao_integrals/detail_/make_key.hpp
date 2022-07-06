#pragma once
#include "property_types/ao_integrals/type_traits.hpp"
#include <string>

namespace property_types::ao_integrals::detail_ {

/** @brief Makes the result key for a given operator.
 *
 *  This function wraps the making of a key for a property type that is an AO
 *  integral.
 *
 *  @tparam The property type we are making the result key for.
 *
 *  @param[in] op The string representation of the operator involved in the
 *                integral.
 *
 *  @return The string to use as the result key for the property type.
 */

template<typename BaseType>
auto make_key(const std::string& op) {
    auto middle = (op == "" ? "" : op + "|");
    if constexpr(n_centers_v<BaseType> == 2) {
        return "(m|" + middle + "n)";
    } else if constexpr(n_centers_v<BaseType> == 3) {
        return "(m|" + middle + "nl)";
    } else if constexpr(n_centers_v<BaseType> == 4) {
        return "(mn|" + middle + "ls)";
    } else {
        // Can't get here because n_centers_v won't compile
    }
}

} // namespace property_types::ao_integrals::detail_
