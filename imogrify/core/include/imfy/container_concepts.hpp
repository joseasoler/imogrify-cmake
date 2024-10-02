/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <type_traits>

namespace imfy
{

/**
 * Imogrify containers enforce that its elements can be constructed, moved, swapped and destroyed without exceptions.
 * @tparam Type Type being checked.
 */
template <typename Type>
struct is_containable : std::conjunction<
														std::is_nothrow_swappable<Type&>, std::is_nothrow_default_constructible<Type>,
														std::is_nothrow_move_constructible<Type>, std::is_nothrow_move_assignable<Type>,
														std::is_nothrow_destructible<Type>>
{
};

/**
 * Imogrify containers enforce that its elements can be constructed, moved, swapped and destroyed without exceptions.
 * @tparam Type Type being checked.
 */
template <typename Type>
inline constexpr bool is_containable_v = is_containable<Type>::value;

/**
 * Imogrify containers enforce that its elements can be constructed, moved, swapped and destroyed without exceptions.
 * @tparam Type Type being checked.
 */
template <typename Type>
concept containable = is_containable_v<Type>;

} // namespace imfy
