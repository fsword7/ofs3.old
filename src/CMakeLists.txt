set (ofs_cpp_srcs
	engine/object.cpp
	engine/player.cpp
	main/sdl2/main.cpp
	render/gl/context.cpp
	render/camera.cpp
	render/scene.cpp
	universe/body.cpp
	universe/star.cpp
	universe/surface.cpp
	util/fix128.cpp
	util/tree.cpp
	universe/body.cpp
	universe/frame.cpp
	universe/star.cpp
	universe/stardb.cpp
	universe/startree.cpp
	universe/surface.cpp
	universe/universe.cpp
)

set (ofs_h_srcs
	engine/object.h
	engine/player.h
	main/core.h
	render/gl/context.h
	render/camera.h
	render/scene.h
	universe/frame.h
	universe/object.h
	universe/surface.h
	util/color.h
	util/fix128.h
	util/tree.h
	universe/astro.h
	universe/object.h
	universe/stardb.h
	universe/startree.h
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