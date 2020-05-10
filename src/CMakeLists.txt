set (ofs_cpp_srcs
	engine/object.cpp
	main/main.cpp
	universe/body.cpp
	universe/star.cpp
)

set (ofs_h_srcs
	engine/object.h
	main/core.h
	universe/object.h
	util/color.h
)

add_executable(ofs ${ofs_cpp_srcs} ${ofs_h_srcs})