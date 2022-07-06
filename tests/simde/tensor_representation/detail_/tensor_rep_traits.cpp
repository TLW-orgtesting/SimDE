#include "simde/tensor_representation/detail_/tensor_rep_traits.hpp"
#include <catch2/catch.hpp>

using namespace simde;

/// Tuple containing all of the spaces we need to handle
using spaces_type =
  std::tuple<type::ao_space, type::derived_space, type::tot_derived_space,
             type::canonical_space, type::canonical_tot_space,
             type::independent_space>;

TEMPLATE_LIST_TEST_CASE("TensorRepTraits", "", spaces_type) {
    using space_type      = TestType;
    using traits_type     = detail_::TensorRepTraits<space_type>;
    using mode_type       = typename traits_type::mode_type;
    using const_reference = typename traits_type::const_reference;
    using map_type        = typename traits_type::map_type;

    SECTION("mode_type") {
        using corr = unsigned int;
        STATIC_REQUIRE(std::is_same_v<corr, mode_type>);
    }

    SECTION("const_reference") {
        using corr = std::reference_wrapper<const space_type>;
        STATIC_REQUIRE(std::is_same_v<const_reference, corr>);
    }

    SECTION("map_type") {
        using corr = ModeToBasisMap<space_type>;
        STATIC_REQUIRE(std::is_same_v<map_type, corr>);
    }

    SECTION("is_ao_space") {
        constexpr auto is_ao_space = traits_type::is_ao_space;
        constexpr bool corr        = std::is_same_v<space_type, type::ao_space>;
        STATIC_REQUIRE(is_ao_space == corr);
    }

    SECTION("is_derived") {
        constexpr auto is_derived = traits_type::is_derived;
        constexpr bool corr =
          std::is_same_v<space_type, type::derived_space> ||
          std::is_same_v<space_type, type::canonical_space> ||
          std::is_same_v<space_type, type::independent_space>;
        STATIC_REQUIRE(is_derived == corr);
    }

    SECTION("is_tot_derived") {
        constexpr auto is_tot_derived = traits_type::is_tot_derived;
        constexpr bool corr =
          std::is_same_v<space_type, type::tot_derived_space> ||
          std::is_same_v<space_type, type::canonical_tot_space>;
        STATIC_REQUIRE(is_tot_derived == corr);
    }

    SECTION("is_independent") {
        constexpr auto is_independent = traits_type::is_independent;
        constexpr bool corr =
          std::is_same_v<space_type, type::independent_space>;
        STATIC_REQUIRE(is_independent == corr);
    }
}
