#include "simde/tensor_representation/detail_/split_basis_op.hpp"
#include "simde/types.hpp"
#include <catch2/catch.hpp>

using namespace simde;

TEST_CASE("split_basis_op(bra,op,ket)") {
    type::ao_space bra, ket;
    type::el_el_coulomb r12;

    auto&& [op, bases] = detail_::split_basis_op(bra, r12, ket);

    auto&& bra_out = std::get<0>(bases);
    auto&& ket_out = std::get<1>(bases);

    SECTION("Values") { REQUIRE(bases == std::make_tuple(bra, ket)); }

    SECTION("Were not copied") {
        REQUIRE(&op == &r12);
        REQUIRE(&bra == &bra_out);
        REQUIRE(&ket == &ket_out);
    }

    // The following should fail to compile because op isn't in the middle
    // (uncomment to check)
    // -------------------------------------------------------------------------
    // auto&& [op2, bases2] = detail_::split_basis_op(r12, bra, ket);
    // auto&& [op2, bases2] = detail_::split_basis_op(bra, ket, r12);
}

TEST_CASE("split_basis_op(bra,op,ket1, ket2)") {
    type::ao_space bra, ket1, ket2;
    type::el_el_coulomb r12;

    auto&& [op, bases] = detail_::split_basis_op(bra, r12, ket1, ket2);

    auto&& bra_out  = std::get<0>(bases);
    auto&& ket1_out = std::get<1>(bases);
    auto&& ket2_out = std::get<2>(bases);

    SECTION("Values") { REQUIRE(bases == std::make_tuple(bra, ket1, ket2)); }

    SECTION("Were not copied") {
        REQUIRE(&op == &r12);
        REQUIRE(&bra == &bra_out);
        REQUIRE(&ket1 == &ket1_out);
        REQUIRE(&ket2 == &ket2_out);
    }

    // The following should fail to compile because op isn't the 1st argument
    // (uncomment to check)
    // -------------------------------------------------------------------------
    // auto&& [op2, bases2] = detail_::split_basis_op(r12, bra, ket1, ket2);
    // auto&& [op2, bases2] = detail_::split_basis_op(bra, ket1, r12, ket2);
    // auto&& [op2, bases2] = detail_::split_basis_op(bra, ket1, ket2, r12);
}

TEST_CASE("split_basis_op(bra1,bra2,op,ket1, ket2)") {
    type::ao_space bra1, bra2, ket1, ket2;
    type::el_el_coulomb r12;

    auto&& [op, bases] = detail_::split_basis_op(bra1, bra2, r12, ket1, ket2);

    auto&& bra1_out = std::get<0>(bases);
    auto&& bra2_out = std::get<1>(bases);
    auto&& ket1_out = std::get<2>(bases);
    auto&& ket2_out = std::get<3>(bases);

    SECTION("Values") {
        REQUIRE(bases == std::make_tuple(bra1, bra2, ket1, ket2));
    }

    SECTION("Were not copied") {
        REQUIRE(&op == &r12);
        REQUIRE(&bra1 == &bra1_out);
        REQUIRE(&bra2 == &bra2_out);
        REQUIRE(&ket1 == &ket1_out);
        REQUIRE(&ket2 == &ket2_out);
    }

    // The following should fail to compile because op isn't the 1st argument
    // (uncomment to check)
    // -------------------------------------------------------------------------
    // auto&& [op2, bases2] = detail_::split_basis_op(r12, bra1, bra2, ket1,
    // ket2);
    // auto&& [op2, bases2] = detail_::split_basis_op(bra1, r12, bra2, ket1,
    // ket2);
    // auto&& [op2, bases2] = detail_::split_basis_op(bra1, bra2, ket1, r12,
    // ket2);
    // auto&& [op2, bases2] = detail_::split_basis_op(bra1, bra2, ket1, ket2,
    // r12);
}
