#include "../test_property_type.hpp"
#include "simde/wavefunctions/wavefunctions.hpp"

using namespace simde;

TEST_CASE("Wavefunction") {
    test_property_type<NoncanonicalReference>({"Hamiltonian", "Input Space"},
                                              {"Output Wavefunction"});
}
