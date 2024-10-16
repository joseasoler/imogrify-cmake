find_package(lodepng CONFIG REQUIRED)
find_package(SPNG CONFIG REQUIRED)

add_executable(dependency_benchmark_png_encode dependency_benchmark_png_encode.cpp)

target_compile_options(dependency_benchmark_png_encode PRIVATE ${IMOGRIFY_CPP_WARNING_FLAGS})

target_link_libraries(dependency_benchmark_png_encode PRIVATE
	lodepng
	nanobench::nanobench
	PNG::PNG
	$<IF:$<TARGET_EXISTS:spng::spng>,spng::spng,spng::spng_static>
)