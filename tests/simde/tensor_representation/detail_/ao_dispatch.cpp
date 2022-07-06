#include "simde/tensor_representation/detail_/ao_dispatch.hpp"
#include <catch2/catch.hpp>
#include <pluginplay/pluginplay.hpp>

using namespace simde;

TEST_CASE("ao_dispatch") {
    type::ao_space bra1, bra2, ket1, ket2;
    type::el_el_coulomb r12;

    typename detail_::TensorRepTraits<type::ao_space>::map_type aos;

    type::tensor t;
    SECTION("N == 2") {
        aos.emplace(0, std::cref(bra1));
        aos.emplace(1, std::cref(ket1));

        using pt = AOTensorRepresentation<2, type::el_el_coulomb>;

        auto l =
          pluginplay::make_lambda<pt>([&](auto&& b, auto&& op, auto&& k) {
              // TODO: Remove extra copy and use these require statements
              // REQUIRE(&b == &bra1);
              // REQUIRE(&op == &r12);
              // REQUIRE(&k == &ket1);
              REQUIRE(b == bra1);
              REQUIRE(op == r12);
              REQUIRE(k == ket1);
              return t;
          });

        auto [rv] = detail_::ao_dispatch<2>(l, aos, r12);
        REQUIRE(rv == t);
    }

    SECTION("N == 3") {
        aos.emplace(0, std::cref(bra1));
        aos.emplace(1, std::cref(ket1));
        aos.emplace(2, std::cref(ket2));

        using pt = AOTensorRepresentation<3, type::el_el_coulomb>;

        auto l = pluginplay::make_lambda<pt>(
          [&](auto&& b, auto&& op, auto&& k1, auto&& k2) {
              // TODO: Remove extra copy and use these require statements
              // REQUIRE(&b == &bra1);
              // REQUIRE(&op == &r12);
              // REQUIRE(&k1 == &ket1);
              // REQUIRE(&k2 == &ket2);
              REQUIRE(b == bra1);
              REQUIRE(op == r12);
              REQUIRE(k1 == ket1);
              REQUIRE(k2 == ket2);
              return t;
          });

        auto [rv] = detail_::ao_dispatch<3>(l, aos, r12);
        REQUIRE(rv == t);
    }

    SECTION("N == 4") {
        aos.emplace(0, std::cref(bra1));
        aos.emplace(1, std::cref(bra2));
        aos.emplace(2, std::cref(ket1));
        aos.emplace(3, std::cref(ket2));

        using pt = AOTensorRepresentation<4, type::el_el_coulomb>;

        auto l = pluginplay::make_lambda<pt>(
          [&](auto&& b1, auto&& b2, auto&& op, auto&& k1, auto&& k2) {
              // TODO: Remove extra copy and use these require statements
              // REQUIRE(&b1 == &bra1);
              // REQUIRE(&b2 == &bra2);
              // REQUIRE(&op == &r12);
              // REQUIRE(&k1 == &ket1);
              // REQUIRE(&k2 == &ket2);
              REQUIRE(b1 == bra1);
              REQUIRE(b2 == bra2);
              REQUIRE(op == r12);
              REQUIRE(k1 == ket1);
              REQUIRE(k2 == ket2);
              return t;
          });

        auto [rv] = detail_::ao_dispatch<4>(l, aos, r12);
        REQUIRE(rv == t);
    }
}
