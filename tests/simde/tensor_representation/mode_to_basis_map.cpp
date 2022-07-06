#include <catch2/catch.hpp>
#include <simde/tensor_representation/mode_to_basis_map.hpp>
#include <simde/types.hpp>

using namespace simde;

// Types of orbital spaces we need to test
using spaces_type =
  std::tuple<type::ao_space, type::derived_space, type::tot_derived_space,
             type::canonical_space, type::canonical_tot_space,
             type::independent_space>;

TEMPLATE_LIST_TEST_CASE("ModeToBasisMap", "", spaces_type) {
    // Use type parameter to work out the ModeToBasisMap specialization to test
    using space_type = TestType;
    using map_type   = ModeToBasisMap<space_type>;

    // Make a value to put into the map
    space_type value;

    // Make a default, aliasing, and owning maps; latter look like {{0, value}}
    map_type defaulted;
    map_type alias_value;
    alias_value.emplace(0, std::cref(value));
    map_type own_value(alias_value);

    // The correct addresses for aliasing vs. owning
    auto palias_value = &value;
    auto pown_value   = &own_value.at(0).get();

    SECTION("CTors") {
        SECTION("Default") { REQUIRE(defaulted.size() == 0); }

        SECTION("Copy") {
            // N.B. own_value is map_type(alias_value)
            map_type defaulted_copy(defaulted);
            map_type own_copy(own_value);

            // Check the values
            REQUIRE(defaulted_copy == defaulted);
            REQUIRE(own_value == alias_value);
            REQUIRE(own_copy == alias_value);

            // Ensure it deep copies
            REQUIRE(&own_value.at(0).get() != palias_value);
            REQUIRE(&own_copy.at(0).get() != pown_value);
        }

        SECTION("Move") {
            map_type defaulted_moved(std::move(defaulted));
            map_type alias_moved(std::move(alias_value));
            map_type own_moved(std::move(own_value));

            // Make the correct answer for moving alias_value and own_value
            map_type value_corr;
            value_corr.emplace(0, std::cref(value));

            // Check the values
            REQUIRE(defaulted_moved == map_type{});
            REQUIRE(alias_moved == value_corr);
            REQUIRE(own_moved == value_corr);

            // Should still alias the same value
            REQUIRE(&alias_moved.at(0).get() == palias_value);
            REQUIRE(&own_moved.at(0).get() == pown_value);
        }

        SECTION("Copy Assignment") {
            map_type defaulted_copy;
            auto pdefaulted_copy = &(defaulted_copy = defaulted);

            map_type alias_copy;
            auto palias_copy = &(alias_copy = alias_value);

            map_type own_copy;
            auto pown_copy = &(own_copy = own_value);

            // Check the values
            REQUIRE(defaulted_copy == defaulted);
            REQUIRE(alias_copy == alias_value);
            REQUIRE(own_copy == own_value);

            // Make sure they return references for chaining
            REQUIRE(pdefaulted_copy == &defaulted_copy);
            REQUIRE(palias_copy == &alias_copy);
            REQUIRE(pown_copy == &own_copy);

            // Ensure it deep copies
            REQUIRE(&alias_copy.at(0).get() != palias_value);
            REQUIRE(&own_copy.at(0).get() != pown_value);
        }

        SECTION("Move Assignment") {
            map_type defaulted_moved;
            auto pdefaulted_moved = &(defaulted_moved = std::move(defaulted));

            map_type alias_moved;
            auto palias_moved = &(alias_moved = std::move(alias_value));

            map_type own_moved;
            auto pown_moved = &(own_moved = std::move(own_value));

            // Make the correct answer for value_moved
            map_type value_corr;
            value_corr.emplace(0, std::cref(value));

            // Returns a reference for chaining
            REQUIRE(pdefaulted_moved == &defaulted_moved);
            REQUIRE(palias_moved == &alias_moved);
            REQUIRE(pown_moved == &own_moved);

            // Value is correct after being moved to
            REQUIRE(defaulted_moved == map_type{});
            REQUIRE(alias_moved == value_corr);
            REQUIRE(own_moved == value_corr);

            // Still aliases after the move
            REQUIRE(&alias_moved.at(0).get() == palias_value);
            REQUIRE(&own_moved.at(0).get() == pown_value);
        }
    }

    SECTION("size") {
        // Check their current states
        REQUIRE(defaulted.size() == 0);
        REQUIRE(alias_value.size() == 1);
        REQUIRE(own_value.size() == 1);

        // Make sure the count goes up by one after adding a value
        defaulted.emplace(0, std::cref(value));
        REQUIRE(defaulted.size() == 1);
    }

    SECTION("emplace") {
        // Can add a value
        defaulted.emplace(0, std::cref(value));
        REQUIRE(&defaulted.at(0).get() == palias_value);

        // Repeated calls do not overwrite the value
        space_type value2;
        defaulted.emplace(0, std::cref(value2));
        REQUIRE(&defaulted.at(0).get() == palias_value);
        REQUIRE(&defaulted.at(0).get() != &value2);
    }

    SECTION("at") {
        // Get existing values
        REQUIRE(&alias_value.at(0).get() == palias_value);
        REQUIRE(&own_value.at(0).get() == pown_value);

        // Out of bounds
        REQUIRE_THROWS_AS(defaulted.at(0), std::out_of_range);
        REQUIRE_THROWS_AS(alias_value.at(1), std::out_of_range);
        REQUIRE_THROWS_AS(own_value.at(1), std::out_of_range);
    }

    SECTION("begin/end") {
        // Check initial condition
        REQUIRE(defaulted.begin() == defaulted.end());
        REQUIRE(alias_value.begin() != alias_value.end());
        REQUIRE(own_value.begin() != own_value.end());

        // Check point to element
        auto alias_itr = alias_value.begin();
        REQUIRE(alias_itr->first == 0);
        REQUIRE(&(alias_itr->second.get()) == palias_value);

        auto own_itr = own_value.begin();
        REQUIRE(own_itr->first == 0);
        REQUIRE(&(own_itr->second.get()) == pown_value);

        // Check iteration termination
        ++alias_itr;
        REQUIRE(alias_itr == alias_value.end());
        ++own_itr;
        REQUIRE(own_itr == own_value.end());
    }

    SECTION("operator==/operator!=") {
        // Comparisons with a default instance
        REQUIRE(defaulted == map_type{});
        REQUIRE_FALSE(defaulted != map_type{});
        REQUIRE_FALSE(defaulted == alias_value);
        REQUIRE(defaulted != alias_value);
        REQUIRE_FALSE(defaulted == own_value);
        REQUIRE(defaulted != own_value);

        // values are: identical to alias_value, different mode,
        map_type alias_value2, alias_diff_mode;
        alias_value2.emplace(0, std::cref(value));
        alias_diff_mode.emplace(1, std::cref(value));

        REQUIRE(alias_value == alias_value2);
        REQUIRE_FALSE(alias_value != alias_value2);
        REQUIRE_FALSE(alias_value == alias_diff_mode);
        REQUIRE(alias_value != alias_diff_mode);
        REQUIRE(alias_value == own_value);
        REQUIRE_FALSE(alias_value != own_value);

        // owning versions of alias_value2 and alias_diff_mode
        map_type own_value2(alias_value2);
        map_type own_diff_mode(alias_diff_mode);

        REQUIRE(own_value == own_value2);
        REQUIRE_FALSE(own_value != own_value2);
        REQUIRE_FALSE(own_value == own_diff_mode);
        REQUIRE(own_value != own_diff_mode);

        // N.B. These tests miss when the value being aliased differs, but
        //      there's not a good way to test that since the types we're
        //      testing need different inputs to give them different values.
    }
}
