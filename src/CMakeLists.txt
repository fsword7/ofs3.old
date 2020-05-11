set (ofs_cpp_srcs
	engine/object.cpp
	main/main.cpp
	universe/body.cpp
	universe/star.cpp
	universe/surface.cpp
	util/fix128.cpp
	util/tree.cpp
)

set (ofs_h_srcs
	engine/object.h
	main/core.h
	universe/object.h
	universe/surface.h
	util/color.h
	util/fix128.h
	util/tree.h
)

add_executable(ofs ${ofs_cpp_srcs} ${ofs_h_srcs})
target_link_libraries(ofs
	GLEW::GLEW
	Freetype::Freetype
	fmt::fmt
)