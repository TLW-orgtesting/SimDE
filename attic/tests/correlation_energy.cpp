#include "test_property_type.hpp"
#include <property_types/correlation_energy.hpp>

TEST_CASE("CorrelationEnergy"){
    test_property_type<property_types::CorrelationEnergy<>>(
        {"Molecule", "Basis Set", "Reference Molecular Orbitals", "Derivative"},
        {"Correlation Energy"}
    );
}
