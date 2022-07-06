#include "simde/tensor_representation/tensor_representation_fxn.hpp"
#include <catch2/catch.hpp>

using namespace simde;

/* Testing Strategy:
 *
 * At this point we know that split_basis_op, TensorRepParser, and ao_dispatch
 * all work correctly. What we need to test is that data flows through
 * tensor_representation correctly. To that end it suffices to make sure a
 * dispatch of each type (AOs, general AOs, transformed, and general
 * transformed) works correctly.
 *
 * N.B. If a dispatch picks the wrong branch we'll get a runtime error about the
 *      module not satisfying that property type.
 *
 * TODO: In lambda modules chack addresses of inputs to ensure no copy occurs.
 *       Requires tackling PluginPlay#192 first.
 */

TEST_CASE("tensor_representation") {
    type::ao_space aos;
    type::derived_space mos;
    type::el_el_coulomb r12;

    type::tensor t;
    type::tensor_of_tensors tot;
    SECTION("AO dispatch") {
        using pt = AOTensorRepresentation<2, type::el_el_coulomb>;
        auto mod =
          pluginplay::make_lambda<pt>([&](auto&& b, auto&& op, auto&& k) {
              REQUIRE(b == aos);
              REQUIRE(op == r12);
              REQUIRE(k == aos);
              return t;
          });
        auto [rv] = tensor_representation(mod, aos, r12, aos);
        REQUIRE(rv == t);
    }

    SECTION("Derived dispatch") {
        using pt = TransformedTensorRepresentation<4, type::el_el_coulomb>;
        auto mod = pluginplay::make_lambda<pt>(
          [&](auto&& aos_in, auto&& mos_in, auto&& op) {
              REQUIRE(aos_in.size() == 2);
              REQUIRE(aos_in.count(1) == 1);
              REQUIRE(aos_in.at(1).get() == aos);
              REQUIRE(aos_in.count(3) == 1);
              REQUIRE(aos_in.at(3).get() == aos);
              REQUIRE(mos_in.size() == 2);
              REQUIRE(mos_in.count(0) == 1);
              REQUIRE(mos_in.at(0).get() == mos);
              REQUIRE(mos_in.count(2) == 1);
              REQUIRE(mos_in.at(2).get() == mos);
              REQUIRE(op == r12);
              return t;
          });
        auto [rv] = tensor_representation(mod, mos, aos, r12, mos, aos);
        REQUIRE(rv == t);
    }

    // SECTION("General derived dispatch") {
    //     using pt =
    //       GeneralTransformedTensorRepresentation<4, type::el_el_coulomb>;
    //     auto mod = pluginplay::make_lambda<pt>(
    //       [&](auto&& aos_in, auto&& sparse_aos, auto&& ind_mos, auto&&
    //       dep_mos,
    //           auto&& op) {
    //           REQUIRE(aos_in.size() == 1);
    //           REQUIRE(aos_in.count(2) == 1);
    //           REQUIRE(aos_in.at(2).get() == aos);
    //           REQUIRE(sparse_aos.size() == 1);
    //           REQUIRE(sparse_aos.count(3) == 1);
    //           REQUIRE(sparse_aos.at(3).get() == aos_i);
    //           REQUIRE(ind_mos.size() == 1);
    //           REQUIRE(ind_mos.count(0) == 1);
    //           REQUIRE(ind_mos.at(0).get() == mos_i);
    //           REQUIRE(dep_mos.size() == 1);
    //           REQUIRE(dep_mos.count(1) == 1);
    //           REQUIRE(dep_mos.at(1).get() == paos_i);
    //           REQUIRE(op == r12);
    //           return tot;
    //       });
    //     auto [rv] = tensor_representation(mod, mos_i, paos_i, r12, aos,
    //     aos_i); REQUIRE(rv == tot);
    // }

    // SECTION("Not a valid dispatch") {
    //     using pt = AOTensorRepresentation<2, type::el_el_coulomb>;
    //     auto mod =
    //       pluginplay::make_lambda<pt>([&](auto, auto, auto) { return t; });
    //     REQUIRE_THROWS_AS(tensor_representation(mod, mos, r12, mos),
    //                       std::runtime_error);
    // }
}
