find_package(lodepng CONFIG REQUIRED)
find_package(SPNG CONFIG REQUIRED)

add_executable(dependency_benchmark_png_encode
	include/imfy/bench/encode_libpng.hpp
	include/imfy/bench/encode_lodepng.hpp
	include/imfy/bench/encode_spng.hpp
	encode_libpng.cpp
	encode_lodepng.cpp
	encode_spng.cpp
	dependency_benchmark_png_encode.cpp
)

target_include_directories(dependency_benchmark_png_encode PRIVATE
	$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>/include
)

target_compile_options(dependency_benchmark_png_encode PRIVATE ${IMOGRIFY_CPP_WARNING_FLAGS})

target_link_libraries(dependency_benchmark_png_encode PRIVATE
	fmt::fmt
	lodepng
	magic_enum::magic_enum
	nanobench::nanobench
	PNG::PNG
	$<IF:$<TARGET_EXISTS:spng::spng_static>,spng::spng_static,spng::spng>
	imogrify_arguments
	benchmark_utils
)