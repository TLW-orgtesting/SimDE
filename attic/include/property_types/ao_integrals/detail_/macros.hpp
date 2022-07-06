#pragma once
#include "property_types/ao_integrals/n_center.hpp"

/** @file property_types/ao_integrals/detail_/macros.hpp
 *
 *  This file contains macros that reduce the boilerplate associated with
 *  declaring and defining property types for AO integrals.
 */

/** @brief Declares typedefs for property types that are templated on the number
 *         of centers.
 *
 *  This macro will define three templated typedefs: ``PT_NAME2C``,
 *  ``PT_NAME3C``, and ``PT_NAME4C`` where ``PT_NAME`` is the argument to the
 *  macro. The typdefs' template parameter is the element type of the integral
 *  (float or double). The typedefs respectively are for a two-centered, a
 *  three-centered, and a four-centered version of the integral. For example:
 *
 *  ```.cpp
 *  MULTICENTER_AO_INTEGRAL_TYPEDEFS(ERI);
 *  ```
 *
 *  will define the typedefs ``ERI2C``, ``ERI3C``, and ``ERI4C``.
 *
 *  @param[in] PT_NAME The name of the property type (without the angle brackets
 *                     or template parameters) that the typedefs are being
 *                     declared for.
 */
#define MULTICENTER_AO_INTEGRAL_TYPEDEFS(PT_NAME)          \
    template<typename ElementType>                         \
    using PT_NAME##2C = PT_NAME<TwoCenter<ElementType>>;   \
                                                           \
    template<typename ElementType>                         \
    using PT_NAME##3C = PT_NAME<ThreeCenter<ElementType>>; \
                                                           \
    template<typename ElementType>                         \
    using PT_NAME##4C = PT_NAME<FourCenter<ElementType>>

/** @brief Forward declares template instantiations for 2, 3, and 4 center
 *         versions of a property type.
 *
 *  This macro is designed to be put in a header file. It will declare a series
 *  of instantiations for the property type spanning all combinations of 2, 3,
 *  and 4 centers with element types of `double` and `float`. For example:
 *
 *  ```.cpp
 *  MULTICENTER_AO_INTEGRAL_EXTERNS(ERI);
 *  ```
 *  is equivalent to:
 *  ```.cpp
 *  extern template class ERI<TwoCenter<double>>;
 *  extern template class ERI<TwoCenter<float>>;
 *  extern template class ERI<ThreeCenter<double>>;
 *  extern template class ERI<ThreeCenter<float>>;
 *  extern template class ERI<FourCenter<double>>;
 *  extern template class ERI<FourCenter<float>>;
 *  ```
 *
 *  @note The user is responsible for actually instantiating these templates in
 *        a source file. This can easily be done with the
 *        `MULTICENTER_AO_INTEGRAL_DEFINES` macro.
 *
 *  @param[in] PT_NAME The name of the property type (without the angle brackets
 *                     or template parameters) that will being instantiated.
 */
#define MULTICENTER_AO_INTEGRAL_EXTERNS(PT_NAME)        \
    extern template class PT_NAME<TwoCenter<double>>;   \
    extern template class PT_NAME<TwoCenter<float>>;    \
    extern template class PT_NAME<ThreeCenter<double>>; \
    extern template class PT_NAME<ThreeCenter<float>>;  \
    extern template class PT_NAME<FourCenter<double>>;  \
    extern template class PT_NAME<FourCenter<float>>

/** @brief Actually instantiates the template classes that the
 *         MULTICENTER_AO_INTEGRAL_EXTERNS macro declares.
 *
 *  This macro should be put in a source file to force instantiation of the
 *  templated property types declared by the MULTICENTER_AO_INTEGRAL_EXTERNS
 *  macro.
 *
 *  @param[in] PT_NAME The name of the property type (without the angle brackets
 *                     or template parameters) that is being instantiated.
 */
#define MULTICENTER_AO_INTEGRAL_DEFINES(PT_NAME) \
    template class PT_NAME<TwoCenter<double>>;   \
    template class PT_NAME<TwoCenter<float>>;    \
    template class PT_NAME<ThreeCenter<double>>; \
    template class PT_NAME<ThreeCenter<float>>;  \
    template class PT_NAME<FourCenter<double>>;  \
    template class PT_NAME<FourCenter<float>>
