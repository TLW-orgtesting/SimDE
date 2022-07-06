#include "simde/linear_algebra/qr.hpp"
#include "tests/test_property_type.hpp"

TEST_CASE("QR") {
    test_property_type<property_types::QRFactorization<double>>(
      {"Input Matrix"}, {"Q", "R"});
}
TEST_CASE("RankRevealingQR") {
    test_property_type<property_types::RankRevealingQRFactorization<double>>(
      {"Input Matrix"}, {"Rank", "Q", "R"});
}
