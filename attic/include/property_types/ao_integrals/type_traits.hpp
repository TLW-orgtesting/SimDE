#pragma once
#include "property_types/ao_integrals/ao_integrals_fwd.hpp"
#include "property_types/ao_integrals/detail_/type_traits.hpp"

#include <tuple>

namespace property_types::ao_integrals {

/** @brief Struct used to determine if a type is that of the Yukawa integral's
 *         property type.
 *
 *  This type trait is the type that property type @p T uses for each AO
 *  integral.
 *
 *  @param T The property type to inspect.
 */
template<typename T>
using element_t = double;
//  std::conditional_t<detail_::HasDoubleElements<T>::value, double, float>;

// template<typename T>
// using element_t = typename detail_::GetElementType<T>::type;

/** @brief User API for determining how many centers an integral involves.
 *
 *  The global variable `n_centers_v<T>` is set to the number of centers that
 *  `T` invovles.
 *
 *  @tparam T The property type we are inspecting. Assumed to be the property
 *            type of an integral.
 */
template<typename T>
static constexpr auto n_centers_v = detail_::n_centers<T>();

/** @brief User API for determining if a type is the property type for the
 *         differential overlap integral.
 *
 *  If @p T is the same type as the differential overlap integral's property
 *  type this global variable will be set to true, otherwise it will be set to
 *  false.
 *
 *  @param T The type we are inspecting.
 */
template<typename T>
static constexpr auto is_doi_v = detail_::IsDOI<T>::value;

/** @brief User API for determining if a type is the property type for the
 *         nuclear-electron attraction integral.
 *
 *  If @p T is the same type as the nuclear-electron attraction integral's
 *  property type this global variable will be set to true, otherwise it will be
 *  set to false.
 *
 *  @param T The type we are inspecting.
 */
template<typename T>
static constexpr auto is_nuclear_v = detail_::IsNuclear<T>::value;

/** @brief User API for determining if a type is the property type for a Slater-
 *         type geminal integral.
 *
 *  If @p T is the same type as the Slater-type geminal integral's property
 *  type this global variable will be set to true, otherwise it will be set to
 *  false.
 *
 *  @param T The type we are inspecting.
 */
template<typename T>
static constexpr auto is_stg_v = detail_::IsSTG<T>::value;

/** @brief User API for determining if a type is the property type for the
 *         Yukawa integral.
 *
 *  If @p T is the same type as the Yukawa integral's property type this global
 *  variable will be set to true, otherwise it will be set to false.
 *
 *  @param T The type we are inspecting.
 */
template<typename T>
static constexpr auto is_yukawa_v = detail_::IsYukawa<T>::value;

} // namespace property_types::ao_integrals