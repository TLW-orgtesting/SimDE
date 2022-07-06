#include "ao_integrals_test.hpp"
#include "property_types/ao_integrals/ao_integrals.hpp"
#include "property_types/ao_integrals/type_traits.hpp"
#include <catch2/catch.hpp>

using namespace property_types::ao_integrals;
using namespace property_types::ao_integrals::test;

template<typename T>
using all_ao_ints = decltype(
  std::tuple_cat(two_center<T>{}, three_center<T>{}, four_center<T>{}));

TEMPLATE_LIST_TEST_CASE("element_t", "", all_ao_ints<double>) {
    STATIC_REQUIRE(std::is_same_v<element_t<TestType>, double>);
}

TEMPLATE_LIST_TEST_CASE("n_centers_v", "", all_2c) {
    STATIC_REQUIRE(n_centers_v<TestType> == 2);
}

TEMPLATE_LIST_TEST_CASE("n_centers_v", "", all_3c) {
    STATIC_REQUIRE(n_centers_v<TestType> == 3);
}

TEMPLATE_LIST_TEST_CASE("n_centers_v", "", all_4c) {
    STATIC_REQUIRE(n_centers_v<TestType> == 4);
}

TEMPLATE_TEST_CASE("is_doi_v", "", float, double) {
    STATIC_REQUIRE(is_doi_v<DOI<TestType>>);
    STATIC_REQUIRE_FALSE(is_doi_v<ERI3C<TestType>>);
}

TEMPLATE_TEST_CASE("is_nuclear_v", "", float, double) {
    STATIC_REQUIRE(is_nuclear_v<Nuclear<TestType>>);
    STATIC_REQUIRE_FALSE(is_nuclear_v<ERI3C<TestType>>);
}

TEMPLATE_TEST_CASE("is_stg_v", "", float, double) {
    STATIC_REQUIRE(is_stg_v<STG<TestType>>);
    STATIC_REQUIRE_FALSE(is_stg_v<ERI3C<TestType>>);
}

TEMPLATE_TEST_CASE("is_yukawa_v", "", float, double) {
    STATIC_REQUIRE(is_yukawa_v<Yukawa<TestType>>);
    STATIC_REQUIRE_FALSE(is_yukawa_v<ERI3C<TestType>>);
}