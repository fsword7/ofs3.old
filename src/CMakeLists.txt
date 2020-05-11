set (ofs_cpp_srcs
	engine/object.cpp
	main/sdl2/main.cpp
	universe/body.cpp
	universe/star.cpp
	universe/surface.cpp
	util/fix128.cpp
	util/tree.cpp
	universe/body.cpp
	universe/star.cpp
	universe/stardb.cpp
	universe/surface.cpp
	universe/universe.cpp
)

set (ofs_h_srcs
	engine/object.h
	main/core.h
	universe/object.h
	universe/surface.h
	util/color.h
	util/fix128.h
	util/tree.h
	universe/astro.h
	universe/object.h
	universe/stardb.h
	universe/surface.h
	universe/universe.h
)

include_directories(
	${SDL2_INCLUDE_DIRS}
	${OPENGL_INCLUDE_DIRS}
	${GLEW_INCLUDE_DIRS}
	${FREETYPE_INCLUDE_DIRS}
)

add_executable(ofs ${ofs_cpp_srcs} ${ofs_h_srcs})
target_link_libraries(ofs
	SDL2::Main
	SDL2::Image
	GLEW::GLEW
	Freetype::Freetype
	fmt::fmt
)