/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include <imfy/build.hpp>
#include <imfy/dependencies.hpp>
#include <imfy/locale.hpp>

#include <fmt/base.h>

#include <cstdlib>

int main()
{
	imfy::locale::initialize();

	using imfy::build_information;
	fmt::println(
			"{:s}: {:s} Version: {:d}.{:d}.{:d}. License: {:s}. Build type: {:s}.", build_information.name,
			build_information.description, build_information.version.major, build_information.version.minor,
			build_information.version.patch, build_information.license_name, imfy::project_build_type()
	);

	fmt::println("");
	for (const imfy::dependency_t dependency : imfy::dependencies)
	{
		fmt::println(
				"{:s}: {:s} Version: {:d}.{:d}.{:d}. License: {:s}.", dependency.name, dependency.description,
				dependency.version.major, dependency.version.minor, dependency.version.patch, dependency.license_name
		);
	}

	return EXIT_SUCCESS;
}
