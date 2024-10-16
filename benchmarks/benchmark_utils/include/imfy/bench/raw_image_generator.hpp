/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <span>
#include <type_traits>
#include <vector>

namespace imfy::bench
{

template <std::uint8_t Channels, std::uint8_t ByteDepth>
class raw_image
{
	static_assert(Channels > 0U && Channels <= 4U);
	static_assert(ByteDepth == 1U || ByteDepth == 2U);

public:
	raw_image(std::uint32_t width, std::uint32_t height, bool initialize = true)
		: width_{width}
		, height_{height}
		, buffer_(static_cast<std::size_t>(width) * height * Channels * ByteDepth, 0U)
	{
		if (!initialize) [[unlikely]]
		{
			return;
		}
		constexpr std::array<std::uint8_t, 4U> channel_modulo{255U, 254U, 253U, 252U};
		if constexpr (ByteDepth == 1U)
		{
			for (std::size_t index = 0U; index < buffer_.size(); index += channels)
			{
				buffer_[index] = static_cast<std::uint8_t>(index % channel_modulo[0U]);
				if constexpr (Channels > 1U)
				{
					buffer_[index + 1U] = static_cast<std::uint8_t>(index % channel_modulo[1U]);
				}
				if constexpr (Channels > 2U)
				{
					buffer_[index + 2U] = static_cast<std::uint8_t>(index % channel_modulo[2U]);
				}
				if constexpr (Channels > 3U)
				{
					buffer_[index + 3U] = static_cast<std::uint8_t>(index % channel_modulo[3U]);
				}
			}
		}
		else
		{
			for (std::size_t index = 0U; index < buffer_.size(); index += channels * static_cast<std::size_t>(ByteDepth))
			{
				buffer_[index] = static_cast<std::uint8_t>(index % channel_modulo[0U]);
				buffer_[index + 1U] = static_cast<std::uint8_t>(index % channel_modulo[0U]);
				if constexpr (Channels > 1U)
				{
					buffer_[index + 2U] = static_cast<std::uint8_t>(index % channel_modulo[1U]);
					buffer_[index + 3U] = static_cast<std::uint8_t>(index % channel_modulo[1U]);
				}
				if constexpr (Channels > 2U)
				{
					buffer_[index + 4U] = static_cast<std::uint8_t>(index % channel_modulo[2U]);
					buffer_[index + 5U] = static_cast<std::uint8_t>(index % channel_modulo[2U]);
				}
				if constexpr (Channels > 3U)
				{
					buffer_[index + 6U] = static_cast<std::uint8_t>(index % channel_modulo[3U]);
					buffer_[index + 7U] = static_cast<std::uint8_t>(index % channel_modulo[3U]);
				}
			}
		}
	}

	static constexpr std::uint8_t channels{Channels};
	static constexpr std::uint8_t bit_depth{static_cast<std::uint8_t>(ByteDepth * 8U)};

	[[nodiscard]] std::uint32_t width() const { return width_; }
	[[nodiscard]] std::uint32_t height() const { return height_; }
	[[nodiscard]] std::span<std::uint8_t> buffer() { return buffer_; }
	[[nodiscard]] std::span<const std::uint8_t> buffer() const { return buffer_; }

private:
	std::uint32_t width_;
	std::uint32_t height_;
	std::vector<std::uint8_t> buffer_;
};

} // namespace imfy::bench