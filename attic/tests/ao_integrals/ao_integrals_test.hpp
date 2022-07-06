#include "property_types/ao_integrals/ao_integrals.hpp"
#include <tuple>

namespace property_types::ao_integrals::test {

//------------------------------------------------------------------------------
// These typedefs are used for testing some of the AO integrals template
// meta-programming.
//------------------------------------------------------------------------------

// All the possible NCenter<2, T>
using two_ncenter_list =
  std::tuple<TwoCenter<float>, TwoCenter<double>, SparseTwoCenter<float>,
             SparseTwoCenter<double>>;

// All the possible NCenter<3, T>
using three_ncenter_list =
  std::tuple<ThreeCenter<float>, ThreeCenter<double>, SparseThreeCenter<float>,
             SparseThreeCenter<double>>;

// All the possible NCenter<4, T>
using four_ncenter_list =
  std::tuple<FourCenter<float>, FourCenter<double>, SparseFourCenter<float>,
             SparseFourCenter<double>>;

// All of the two centered AO integrals, templated on element type
template<typename T>
using two_center =
  std::tuple<f12::CorrelationFactor2C<T>, ERI2C<T>, EDipole<T>, EQuadrupole<T>,
             EOctopole<T>, Kinetic<T>, Nuclear<T>, Overlap<T>,
             SparseTwoCenter<T>, STG2C<T>, TwoCenter<T>, Yukawa2C<T>>;

// All of the three-centered AO integrals, templated on element type
template<typename T>
using three_center =
  std::tuple<f12::CorrelationFactor3C<T>, ERI3C<T>, SparseThreeCenter<T>,
             STG3C<T>, ThreeCenter<T>, Yukawa3C<T>>;

// All of the four-centered AO integrals, templated on element type
template<typename T>
using four_center =
  std::tuple<f12::CorrelationFactor4C<T>, DOI<T>, ERI4C<T>, FourCenter<T>,
             SparseFourCenter<T>, STG4C<T>, Yukawa4C<T>>;

// All of the ncenter list smashed together
using all_ncenter = decltype(std::tuple_cat(
  two_ncenter_list{}, three_ncenter_list{}, four_ncenter_list{}));

// All of the two-centered integrals (includes all element types)
using all_2c =
  decltype(std::tuple_cat(two_center<float>{}, two_center<double>{}));

// All of the three-centered integrals (includes all element types)
using all_3c =
  decltype(std::tuple_cat(three_center<float>{}, three_center<double>{}));

// All of the four-centered integrals (includes all element types)
using all_4c =
  decltype(std::tuple_cat(four_center<float>{}, four_center<double>{}));

} // namespace property_types::ao_integrals::test