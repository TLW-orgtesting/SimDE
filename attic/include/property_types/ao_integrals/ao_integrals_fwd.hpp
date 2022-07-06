#pragma once
#include <cstddef>

/** @file ao_integrals_fwd.hpp
 *
 *  Forward declarations of the AO integrals types, primarily for template
 *  meta-programming.
 */

namespace property_types::ao_integrals {

template<typename T>
struct CorrelationFactor;

template<typename T>
struct DOI;

template<typename T>
struct ERI;

template<typename T, unsigned Order>
struct EMultipole;

template<typename T>
struct Kinetic;

template<std::size_t N, typename T>
struct NCenter;

template<typename T>
struct Nuclear;

template<typename T>
struct Overlap;

template<typename T>
struct STG;

template<typename T>
struct Yukawa;

} // namespace property_types::ao_integrals