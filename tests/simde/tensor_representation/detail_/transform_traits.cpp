#include "simde/tensor_representation/detail_/transform_traits.hpp"
#include <catch2/catch.hpp>

using namespace simde::detail_;

TEST_CASE("Transform Traits") {
    using ao  = simde::type::ao_space;
    using d   = simde::type::derived_space;
    using dt  = simde::type::tot_derived_space;
    using c   = simde::type::canonical_space;
    using ct  = simde::type::canonical_tot_space;
    using ind = simde::type::independent_space;

    SECTION("has_derived") {
        STATIC_REQUIRE_FALSE(TransformTraits<ao, ao, ao, ao>::has_derived);
        STATIC_REQUIRE(TransformTraits<ao, d>::has_derived);
        STATIC_REQUIRE(TransformTraits<c, ao, c>::has_derived);
        STATIC_REQUIRE(TransformTraits<ind, ao, c, c>::has_derived);
        STATIC_REQUIRE(TransformTraits<ind, ct, ind, ct>::has_derived);
    }

    SECTION("has_tots") {
        STATIC_REQUIRE_FALSE(TransformTraits<ao, ao, ao, ao>::has_tots);
        STATIC_REQUIRE_FALSE(TransformTraits<ao, d>::has_tots);
        STATIC_REQUIRE_FALSE(TransformTraits<c, ao, c>::has_tots);
        STATIC_REQUIRE_FALSE(TransformTraits<ind, ao, c, c>::has_tots);
        STATIC_REQUIRE(TransformTraits<ind, ct, ind, ct>::has_tots);
    }
}
