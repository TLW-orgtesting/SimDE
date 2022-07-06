#include "../ao_integrals_test.hpp"
#include "property_types/ao_integrals/ao_integrals.hpp"
#include "property_types/ao_integrals/detail_/type_traits.hpp"
#include <catch2/catch.hpp>

using namespace property_types::ao_integrals;
using namespace property_types::ao_integrals::test;

TEMPLATE_TEST_CASE("detail_::IsNCenter (false)", "", float, std::vector<int>) {
    STATIC_REQUIRE_FALSE(detail_::IsNCenter<TestType>::value);
    STATIC_REQUIRE(detail_::IsNCenter<TestType>::n_centers == 0);
}

TEMPLATE_LIST_TEST_CASE("detail_::IsNCenter", "", all_ncenter) {
    STATIC_REQUIRE(detail_::IsNCenter<TestType>::value);
}

TEMPLATE_LIST_TEST_CASE("detail_::NCenterTraits<2>", "", two_ncenter_list) {
    using type = detail_::NCenterTraits<TestType>;
    STATIC_REQUIRE(type::n_centers == 2);
}

TEMPLATE_LIST_TEST_CASE("detail_::NCenterTraits<3>", "", three_ncenter_list) {
    using type = detail_::NCenterTraits<TestType>;
    STATIC_REQUIRE(type::n_centers == 3);
}

TEMPLATE_LIST_TEST_CASE("detail_::NCenterTraits<4>", "", four_ncenter_list) {
    using type = detail_::NCenterTraits<TestType>;
    STATIC_REQUIRE(type::n_centers == 4);
}

TEST_CASE("detail_::HasNCenters<N, std::tuple<>>") {
    STATIC_REQUIRE_FALSE(detail_::HasNCenters<2, std::tuple<>>::value);
    STATIC_REQUIRE_FALSE(detail_::HasNCenters<3, std::tuple<>>::value);
    STATIC_REQUIRE_FALSE(detail_::HasNCenters<4, std::tuple<>>::value);
}

TEMPLATE_TEST_CASE("detail_::HasNCenters<N>", "", float, double) {
    SECTION("Just the center") {
        using the_tuple = std::tuple<TwoCenter<TestType>>;
        STATIC_REQUIRE(detail_::HasNCenters<2, the_tuple>::value);
        STATIC_REQUIRE_FALSE(detail_::HasNCenters<3, the_tuple>::value);
    }

    SECTION("Center and something") {
        SECTION("Center 1st") {
            using the_tuple = std::tuple<TwoCenter<TestType>, TestType>;
            STATIC_REQUIRE(detail_::HasNCenters<2, the_tuple>::value);
            STATIC_REQUIRE_FALSE(detail_::HasNCenters<3, the_tuple>::value);
        }

        SECTION("Center 2nd") {
            using the_tuple = std::tuple<TestType, TwoCenter<TestType>>;
            STATIC_REQUIRE(detail_::HasNCenters<2, the_tuple>::value);
            STATIC_REQUIRE_FALSE(detail_::HasNCenters<3, the_tuple>::value);
        }
    }

    SECTION("Center and two somethings") {
        SECTION("Center 1st") {
            using the_tuple = std::tuple<TwoCenter<TestType>, TestType, int>;
            STATIC_REQUIRE(detail_::HasNCenters<2, the_tuple>::value);
            STATIC_REQUIRE_FALSE(detail_::HasNCenters<3, the_tuple>::value);
        }
        SECTION("Center 2nd") {
            using the_tuple = std::tuple<TestType, TwoCenter<TestType>, int>;
            STATIC_REQUIRE(detail_::HasNCenters<2, the_tuple>::value);
            STATIC_REQUIRE_FALSE(detail_::HasNCenters<3, the_tuple>::value);
        }
        SECTION("Center 3rd") {
            using the_tuple = std::tuple<TestType, int, TwoCenter<TestType>>;
            STATIC_REQUIRE(detail_::HasNCenters<2, the_tuple>::value);
            STATIC_REQUIRE_FALSE(detail_::HasNCenters<3, the_tuple>::value);
        }
    }
}

TEMPLATE_LIST_TEST_CASE("detail_::IsTwoCentered", "", all_2c) {
    STATIC_REQUIRE(detail_::IsTwoCentered<TestType>::value);
}

TEMPLATE_LIST_TEST_CASE("detail_::IsTwoCentered", "", all_3c) {
    STATIC_REQUIRE_FALSE(detail_::IsTwoCentered<TestType>::value);
}

TEMPLATE_LIST_TEST_CASE("detail_::IsTwoCentered", "", all_4c) {
    STATIC_REQUIRE_FALSE(detail_::IsTwoCentered<TestType>::value);
}

TEMPLATE_LIST_TEST_CASE("detail_::IsThreeCentered", "", all_3c) {
    STATIC_REQUIRE(detail_::IsThreeCentered<TestType>::value);
}

TEMPLATE_LIST_TEST_CASE("detail_::IsThreeCentered", "", all_2c) {
    STATIC_REQUIRE_FALSE(detail_::IsThreeCentered<TestType>::value);
}

TEMPLATE_LIST_TEST_CASE("detail_::IsThreeCentered", "", all_4c) {
    STATIC_REQUIRE_FALSE(detail_::IsThreeCentered<TestType>::value);
}

TEMPLATE_LIST_TEST_CASE("detail_::IsFourCentered", "", all_4c) {
    STATIC_REQUIRE(detail_::IsFourCentered<TestType>::value);
}

TEMPLATE_LIST_TEST_CASE("detail_::IsFourCentered", "", all_2c) {
    STATIC_REQUIRE_FALSE(detail_::IsFourCentered<TestType>::value);
}

TEMPLATE_LIST_TEST_CASE("detail_::IsFourCentered", "", all_3c) {
    STATIC_REQUIRE_FALSE(detail_::IsFourCentered<TestType>::value);
}

TEMPLATE_LIST_TEST_CASE("detail_::n_centers()", "", all_2c) {
    STATIC_REQUIRE(detail_::n_centers<TestType>() == 2);
}

TEMPLATE_LIST_TEST_CASE("detail_::n_centers()", "", all_3c) {
    STATIC_REQUIRE(detail_::n_centers<TestType>() == 3);
}

TEMPLATE_LIST_TEST_CASE("detail_::n_centers()", "", all_4c) {
    STATIC_REQUIRE(detail_::n_centers<TestType>() == 4);
}

// TEMPLATE_LIST_TEST_CASE("HasFloatElements", "", two_center<float>) {
//     STATIC_REQUIRE(detail_::HasFloatElements<TestType>::value);
// }

// TEMPLATE_LIST_TEST_CASE("HasFloatElements", "", two_center<double>) {
//     STATIC_REQUIRE_FALSE(detail_::HasFloatElements<TestType>::value);
// }

// TEMPLATE_LIST_TEST_CASE("HasFloatElements", "", three_center<float>) {
//     STATIC_REQUIRE(detail_::HasFloatElements<TestType>::value);
// }

// TEMPLATE_LIST_TEST_CASE("HasFloatElements", "", three_center<double>) {
//     STATIC_REQUIRE_FALSE(detail_::HasFloatElements<TestType>::value);
// }

// TEMPLATE_LIST_TEST_CASE("HasFloatElements", "", four_center<float>) {
//     STATIC_REQUIRE(detail_::HasFloatElements<TestType>::value);
// }

// TEMPLATE_LIST_TEST_CASE("HasFloatElements", "", four_center<double>) {
//     STATIC_REQUIRE_FALSE(detail_::HasFloatElements<TestType>::value);
// }

// TEMPLATE_LIST_TEST_CASE("HasDoubleElements", "", two_center<float>) {
//     STATIC_REQUIRE_FALSE(detail_::HasDoubleElements<TestType>::value);
// }

// TEMPLATE_LIST_TEST_CASE("HasDoubleElements", "", two_center<double>) {
//     STATIC_REQUIRE(detail_::HasDoubleElements<TestType>::value);
// }

// TEMPLATE_LIST_TEST_CASE("HasDoubleElements", "", three_center<float>) {
//     STATIC_REQUIRE_FALSE(detail_::HasDoubleElements<TestType>::value);
// }

// TEMPLATE_LIST_TEST_CASE("HasDoubleElements", "", three_center<double>) {
//     STATIC_REQUIRE(detail_::HasDoubleElements<TestType>::value);
// }

// TEMPLATE_LIST_TEST_CASE("HasDoubleElements", "", four_center<float>) {
//     STATIC_REQUIRE_FALSE(detail_::HasDoubleElements<TestType>::value);
// }

// TEMPLATE_LIST_TEST_CASE("HasDoubleElements", "", four_center<double>) {
//     STATIC_REQUIRE(detail_::HasDoubleElements<TestType>::value);
// }

TEMPLATE_TEST_CASE("detail_::IsDOI", "", float, double) {
    STATIC_REQUIRE(detail_::IsDOI<DOI<TestType>>::value);
    STATIC_REQUIRE_FALSE(detail_::IsDOI<ERI3C<TestType>>::value);
}

TEMPLATE_TEST_CASE("detail_::IsNuclear", "", float, double) {
    STATIC_REQUIRE(detail_::IsNuclear<Nuclear<TestType>>::value);
    STATIC_REQUIRE_FALSE(detail_::IsNuclear<ERI3C<TestType>>::value);
}

TEMPLATE_TEST_CASE("detail_::IsSTG", "", float, double) {
    STATIC_REQUIRE(detail_::IsSTG<STG<TestType>>::value);
    STATIC_REQUIRE_FALSE(detail_::IsSTG<ERI3C<TestType>>::value);
}

TEMPLATE_TEST_CASE("detail_::IsYukawa", "", float, double) {
    STATIC_REQUIRE(detail_::IsYukawa<Yukawa<TestType>>::value);
    STATIC_REQUIRE_FALSE(detail_::IsYukawa<ERI3C<TestType>>::value);
}