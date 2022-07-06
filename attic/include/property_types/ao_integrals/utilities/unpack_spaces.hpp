#pragma once
#include "property_types/ao_integrals/type_traits.hpp"
#include "property_types/types.hpp"

namespace property_types::ao_integrals {

/** @brief Given the inputs to a module unpacks the spaces for the integral.
 *
 *  This function wraps the logic required to unpack the spaces provided to an
 *  integral module.
 *
 *  @tparam PropertyType The property type whose input spaces are being
 *          unpacked.
 *
 *  @param[in] inputs The input map provided to the module. The spaces will be
 *                    unpacked from this object.
 *
 *  @return An std::vector whose elements are spaces for the integrals. The
 *          orderis left to right across the braket, e.g., the return for the
 *          ERI integral (i|ab) would be the space for i, the space for a, and
 *          then the space for b.
 *
 *  @throw std::bad_alloc if there is insufficient memory to create the return.
 *                        Strong throw guarantee.
 *  @throw std::runtime_error if the inputs do not contain the correct keys.
 *                            Strong throw guarantee.
 */
template<typename PropertyType>
auto unpack_spaces(const sde::type::input_map& inputs) {
    constexpr auto N   = n_centers_v<PropertyType>;
    using element_type = double;

    // Check the base classes of the PropertyType for a sparse base
    using base_tuple        = typename PropertyType::bases_t;
    using sparse_ao_space_t = type::sparse_ao_space_t<element_type>;
    using dense_ao_space_t  = type::ao_space_t<element_type>;
    using sparse_ncenter_t  = NCenter<N, sparse_ao_space_t>;
    constexpr bool is_sparse =
      detail_::has_type<sparse_ncenter_t, base_tuple>::value;

    // Work out AOSpace and NCenter types based on is_sparse
    using ao_space_t =
      std::conditional_t<is_sparse, sparse_ao_space_t, dense_ao_space_t>;
    using n_center_t = NCenter<N, ao_space_t>;
    using ao_vec_t   = std::vector<ao_space_t>;

    if constexpr(is_doi_v<PropertyType>) {
        const auto& b = inputs.at("bra").value<const ao_space_t&>();
        const auto& k = inputs.at("ket").value<const ao_space_t&>();
        return ao_vec_t{b, k};
    } else if constexpr(N == 2) {
        const auto& [b, k] = n_center_t::unwrap_inputs(inputs);
        return ao_vec_t{b, k};
    } else if constexpr(N == 3) {
        const auto& [b, k1, k2] = n_center_t::unwrap_inputs(inputs);
        return ao_vec_t{b, k1, k2};
    } else if constexpr(N == 4) {
        const auto& [b1, b2, k1, k2] = n_center_t::unwrap_inputs(inputs);
        return ao_vec_t{b1, b2, k1, k2};
    } else {
        // Can't get here b/c n_center_t would fail to compile
    }
}

} // namespace property_types::ao_integrals