/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "include/imfy/bench/encode_lodepng.hpp"

#include <lodepng.h>

#include <cstdint>
#include <cstdlib>
#include <span>
#include <vector>

namespace
{

} // namespace

namespace imfy::bench
{

std::size_t encode_lodepng(
		const std::uint32_t width, const std::uint32_t height, const std::span<const std::uint8_t> input_image,
		const std::uint8_t color_type, const std::uint8_t bit_depth
)
{
	std::vector<std::uint8_t> buffer{};
	auto error =
			lodepng::encode(buffer, input_image.data(), width, height, static_cast<LodePNGColorType>(color_type), bit_depth);
	if (error != 0U) [[unlikely]]
	{
		std::abort();
	}

	return buffer.size();
}

} // namespace imfy::bench