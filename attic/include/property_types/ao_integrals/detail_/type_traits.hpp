#pragma once
#include "property_types/ao_integrals/ao_integrals_fwd.hpp"
#include <tuple>

namespace property_types::ao_integrals::detail_ {

/** @brief Template for determining if a type is an instantiation of NCenter.
 *
 *  The primary template is activated for types @p T which are not
 *  instantiations of NCenter. It contains a static member `value` which is
 *  false and a static member `n_centers` which is set to 0.
 *
 *  @tparam T The type we are inspecting.
 */
template<typename T>
struct IsNCenter : std::false_type {
    static constexpr std::size_t n_centers = 0;
    using space_type                       = void;
};

template<std::size_t N, typename AOSpaceType>
struct IsNCenter<NCenter<N, AOSpaceType>> : std::true_type {};

template<typename T>
struct NCenterTraits;

template<std::size_t N, typename AOSpaceType>
struct NCenterTraits<NCenter<N, AOSpaceType>> {
    static constexpr std::size_t n_centers = N;
    using space_type                       = AOSpaceType;
    using element_type                     = double;
};

/** @brief Template that determines if a tuple contains a NCenter<N, T>
 * instance.
 *
 *
 */
template<std::size_t N, typename T>
struct HasNCenters;

template<std::size_t N>
struct HasNCenters<N, std::tuple<>> {
    static constexpr bool value = false;
};

template<std::size_t N, typename T, typename... Args>
struct HasNCenters<N, std::tuple<T, Args...>>
  : HasNCenters<N, std::tuple<Args...>> {
private:
    using base_t                      = HasNCenters<N, std::tuple<Args...>>;
    static constexpr bool is_n_center = IsNCenter<T>::value;
    template<typename U>
    static constexpr bool right_n = NCenterTraits<U>::n_centers == N;
    static constexpr bool value_() {
        if constexpr(is_n_center) {
            return right_n<T>;
        } else {
            return false;
        }
    }

public:
    static constexpr bool value = base_t::value || value_();
};

/// Stolen from https://stackoverflow.com/a/25958302
template<typename T, typename Tuple>
struct has_type;

template<typename T>
struct has_type<T, std::tuple<>> : std::false_type {};

template<typename T, typename U, typename... Ts>
struct has_type<T, std::tuple<U, Ts...>> : has_type<T, std::tuple<Ts...>> {};

template<typename T, typename... Ts>
struct has_type<T, std::tuple<T, Ts...>> : std::true_type {};

/// Used to determine if the type @p T appears in the tuple of type @p Tuple
template<typename T, typename Tuple>
static constexpr bool has_type_v = has_type<T, Tuple>::value;

template<typename T>
struct IsTwoCentered {
    static constexpr bool value = HasNCenters<2, typename T::bases_t>::value;
};

template<typename T>
struct IsTwoCentered<NCenter<2, T>> : std::true_type {};

template<typename T>
struct IsTwoCentered<ao_integrals::DOI<T>> : std::false_type {};

template<typename T>
struct IsThreeCentered {
    static constexpr bool value = HasNCenters<3, typename T::bases_t>::value;
};

template<typename T>
struct IsThreeCentered<NCenter<3, T>> : std::true_type {};

/** @brief Primary template for determining if a type is for a four-center
 *         integral.
 *
 *  The primary template takes care of the scenario where the type derives from
 *  `FourCenter`. The type contains a static member `value` which is true if @T
 *  is a property type that derives from `FourCenter` and false otherwise.
 *
 *  @tparam T The property type we are inspecting. Assumed to be the type of a
 *            valid property type.
 */
template<typename T>
struct IsFourCentered {
    static constexpr bool value = HasNCenters<4, typename T::bases_t>::value;
};

template<typename T>
struct IsFourCentered<NCenter<4, T>> : std::true_type {};

template<typename T>
struct IsFourCentered<ao_integrals::DOI<T>> : std::true_type {};

/** @brief Convenience function for determining how many centers an integral
 *         involves.
 *
 *  This `constexpr` determines how many centers an integral has based on the
 *  type. It relies on `IsXCentered` type traits working correctly (`X` being
 *  `Two`, `Three`, or `Four`).
 *
 *  @tparam T The type we are inspecting. Assumed to be a valid property type
 *            for which one of `IsTwoCentered`, `IsThreeCentered`, or
 *            `IsFourCentered` is true. If none are true this function will not
 *            compile.
 *
 *  @return The number of centers in the integral.
 */
template<typename T>
constexpr auto n_centers() {
    if constexpr(IsTwoCentered<T>::value) {
        return 2;
    } else if constexpr(IsThreeCentered<T>::value) {
        return 3;
    } else if constexpr(IsFourCentered<T>::value) {
        return 4;
    } else {
        // If we get here we know v will be false
        constexpr bool v = IsFourCentered<T>::value;
        static_assert(v, "Does not derive from NCenters<N,T>");
    }
}

/** @brief Struct used to determine if the elements of an AO integral
 * are of type float.
 *
 *  This struct contains a global variable named ``value``, which is
 * set to true if @p T is a property type that inherits from
 * ``NCenter<N, float>`` for arbitrary ``N``. ``value`` is false
 * otherwise.
 *
 *  @tparam T The property type to inspect.
 */
// template<typename T>
// struct HasFloatElements {
//     static constexpr auto value =
//       std::is_same_v<ao_integrals::TwoCenter<float>, T> ||
//       std::is_same_v<ao_integrals::ThreeCenter<float>, T> ||
//       std::is_same_v<ao_integrals::FourCenter<float>, T> ||
//       std::is_same_v<ao_integrals::SparseTwoCenter<float>, T> ||
//       std::is_same_v<ao_integrals::SparseThreeCenter<float>, T> ||
//       std::is_same_v<ao_integrals::SparseFourCenter<float>, T> ||
//       has_type_v<ao_integrals::TwoCenter<float>, typename T::bases_t> ||
//       has_type_v<ao_integrals::ThreeCenter<float>, typename T::bases_t> ||
//       has_type_v<ao_integrals::FourCenter<float>, typename T::bases_t>;
// };

// /** @brief Struct used to determine if the elements of an AO integral are of
//  *         type double.
//  *
//  *  This struct contains a global variable named ``value``, which is set to
//  true
//  *  if @p T is a property type that inherits from ``NCenter<N, double>`` for
//  *  arbitrary ``N``. ``value`` is false otherwise.
//  *
//  *  @tparam T The property type to inspect.
//  */
// template<typename T>
// struct HasDoubleElements {
//     static constexpr auto value =
//       std::is_same_v<ao_integrals::TwoCenter<double>, T> ||
//       std::is_same_v<ao_integrals::ThreeCenter<double>, T> ||
//       std::is_same_v<ao_integrals::FourCenter<double>, T> ||
//       has_type_v<ao_integrals::TwoCenter<double>, typename T::bases_t> ||
//       has_type_v<ao_integrals::ThreeCenter<double>, typename T::bases_t> ||
//       has_type_v<ao_integrals::FourCenter<double>, typename T::bases_t>;
// };

/** @brief Struct used to determine if a type is that of the differential
           overlap integral's property type.
 *
 *  The primary template is instantiated for all @p T which aren't a
 *  specialization of `ao_integrals::DOI`. When instantiated the class will have
 *  a static constexpr member `value` which be set to false.
 *
 *  @tparam T The type we are inspecting.
 */
template<typename T>
struct IsDOI : std::false_type {};

/** @brief Struct used to determine if a type is that of the differential
 *         overlap integral's property type.
 *
 *  This specialization is instantiated when @p T is a specialization of
 *  `ao_integrals::DOI`. When instantiated this specialization will have a
 *  static constexpr member `value` which is set to true.
 *
 *  @tparam T The scalar type of the integral values.
 */
template<typename T>
struct IsDOI<property_types::ao_integrals::DOI<T>> : std::true_type {};

/** @brief Struct used to determine if a type is that of the electron-nuclear
 *         attraction property type.
 *
 *  The primary template is instantiated for all @p T which aren't a
 *  specialization of `ao_integrals::Nuclear`. When instantiated the class will
 *  have a static constexpr member `value` which be set to false.
 *
 *  @tparam T The type we are inspecting.
 */
template<typename T>
struct IsNuclear : std::false_type {};

/** @brief Struct used to determine if a type is that of the nuclear-electron
 *         attraction integral's property type.
 *
 *  This specialization is instantiated when @p T is a specialization of
 *  `ao_integrals::Nuclear`. When instantiated this specialization will have a
 *  static constexpr member `value` which is set to true.
 *
 *  @tparam T The scalar type of the integral values.
 */
template<typename T>
struct IsNuclear<property_types::ao_integrals::Nuclear<T>> : std::true_type {};

/** @brief Struct used to determine if a type is that of a Slater-type geminal's
           property type.
 *
 *  The primary template is instantiated for all @p T which aren't a
 *  specialization of `ao_integrals::STG`. When instantiated the class will have
 *  a static constexpr member `value` which be set to false.
 *
 *  @tparam T The type we are inspecting.
 */
template<typename T>
struct IsSTG : std::false_type {};

/** @brief Struct used to determine if a type is that of the Slater-type geminal
 *         integral's property type.
 *
 *  This specialization is instantiated when @p T is a specialization of
 *  `ao_integrals::STG`. When instantiated this specialization will have a
 *  static constexpr member `value` which is set to true.
 *
 *  @tparam T The scalar type of the integral values.
 */
template<typename T>
struct IsSTG<property_types::ao_integrals::STG<T>> : std::true_type {};

/** @brief Struct used to determine if a type is that of the Yukawa integral's
 *         property type.
 *
 *  The primary template is instantiated for all @p T which aren't a
 *  specialization of `ao_integrals::Yukawa`. When instantiated the class will
 *  have a static constexpr member `value` which be set to false.
 *
 *  @tparam T The type we are inspecting.
 */
template<typename T>
struct IsYukawa : std::false_type {};

/** @brief Struct used to determine if a type is that of the Yukawa integral's
 *         property type.
 *
 *  This specialization is instantiated when @p T is a specialization of
 *  `ao_integrals::Yukawa`. When instantiated this specialization will have a
 *  static constexpr member `value` which is set to true.
 *
 *  @tparam T The scalar type of the integral values.
 */
template<typename T>
struct IsYukawa<property_types::ao_integrals::Yukawa<T>> : std::true_type {};

} // namespace property_types::ao_integrals::detail_