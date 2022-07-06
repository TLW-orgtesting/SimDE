#pragma once
#include <catch2/catch.hpp>
// Type of an initializer list filled with strings
using string_list = std::initializer_list<std::string>;

/**@brief Factors out the boilerplate required to test a property type
 *
 * @tparam T The type of the property type
 * @param input_fields An initializer list of the property type's input fields
 * @param result_fields An initializer list of the property type's returns
 */
template<typename T>
inline static void test_property_type(string_list input_fields,
                                      string_list result_fields) {
    SECTION("inputs") {
        auto inputs = T::inputs();
        REQUIRE(inputs.size() == input_fields.size());
        for(const auto& field : input_fields) SECTION(field) {
                REQUIRE(inputs.count(field) == 1);
            }
    }
    SECTION("results") {
        auto results = T::results();
        REQUIRE(results.size() == result_fields.size());
        for(const auto& field : result_fields) SECTION(field) {
                REQUIRE(results.count(field) == 1);
            }
    }
}
