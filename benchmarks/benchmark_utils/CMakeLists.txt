find_package(tabulate CONFIG REQUIRED)

add_library(benchmark_utils INTERFACE
	include/imfy/bench/raw_image_generator.hpp
)

target_include_directories(benchmark_utils INTERFACE
	$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>/include
)
