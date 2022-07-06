#include "simde/embedding_partition.hpp"
#include "test_property_type.hpp"

using namespace simde;

TEST_CASE("EmbedPartition") {
    test_property_type<EmbedPartition<type::canonical_space>>(
      {"Molecule", "Basis Set", "Active Atoms", "Initial Orbitals"},
      {"Active Orbitals", "Environment Orbitals"});
}
