/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <imfy/allocator.hpp>
#include <imfy/container_concepts.hpp>

#include <vector>

namespace imfy
{

/**
 * Convenience wrapper for vector.
 * @tparam Type Type contained in this vector.
 * @tparam Allocator Allocator to be used for the vector.
 */
template <containable Type, class Allocator = imfy::allocator<Type>>
using vector = std::vector<Type, Allocator>;

} // namespace imfy
