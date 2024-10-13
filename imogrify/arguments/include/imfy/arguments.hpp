/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <imfy/path.hpp>

#include <cstdint>
#include <string>
#include <variant>
#include <vector>

#include "image_format.hpp"

namespace imfy
{

/** Stores additional, format-specific information to use during encoding. */
using output_information = std::variant<std::monostate, png_information>;

struct pipeline_arguments final
{
public:
	/** Expected image format for input files. */
	image_format input_format;
	/** Image format to use for output files. */
	image_format output_format;
	/** Specific format details to use for output files. */
	output_information output_info;
	/** List of input files to be processed. */
	std::vector<std::basic_string<fs::path_char_t>> input_paths;
	/** Paths to use for the output of each input file. */
	std::vector<std::basic_string<fs::path_char_t>> output_paths;
};

/** Controls the reports printed by the application. Each level also contains previous ones. */
enum class verbosity_level : std::uint8_t
{
	/** Error reporting. */
	error,
	/** Warning reporting. */
	warning,
	/** Reports stages such as input file processing, start and end of pipelines and so on. */
	stages,
	/** Real time progress report of each pipeline. */
	progress,
	/** Each individual file being processed. */
	files,
};

struct arguments final
{
public:
	/** If set to true, the application will display the help and exit. */
	bool show_help;
	/** Show time reports. */
	bool report_time;
	/** Level of logging verbosity chosen by the user. */
	verbosity_level verbosity;
	/* Number of threads to use. */
	std::uint8_t thread_count;
	/** One or more sets of pipeline instructions to apply. */
	std::vector<pipeline_arguments> pipeline_args;
};

} // namespace imfy