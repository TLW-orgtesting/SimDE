#pragma once
#include "simde/tensor_representation/detail_/tensor_rep_traits.hpp"

namespace simde::detail_ {

template<typename... Args>
struct TransformTraits {
private:
    template<typename T>
    using traits = TensorRepTraits<T>;

public:
    static constexpr bool has_derived = (traits<Args>::is_derived || ...);

    static constexpr bool has_tots = (traits<Args>::is_tot_derived || ...);
};

} // namespace simde::detail_
