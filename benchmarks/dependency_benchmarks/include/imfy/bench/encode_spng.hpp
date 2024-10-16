/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <cstddef>
#include <cstdint>
#include <span>

namespace imfy::bench
{

std::size_t encode_spng(
		std::uint32_t width, std::uint32_t height, std::span<const std::uint8_t> input_image, std::uint8_t color_type,
		std::uint8_t bit_depth, std::uint8_t compression_level
);

} // namespace imfy::bench