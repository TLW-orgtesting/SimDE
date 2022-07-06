#pragma once

namespace simde {

/** @brief A collection of enums which encapsulate various
 *  matrix properties which influence the behaviour of
 *  certain property types.
 */
struct MatrixProperties {
    /// Specification of triangular matrices
    enum Triangle { Upper, Lower };
}; // struct MatrixProperties

} // namespace simde
