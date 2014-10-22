set(SRC
	"main.cpp"
)

add_executable("ConsoleSweeper" ${SRC})

target_link_libraries("ConsoleSweeper" PUBLIC "core")

if(CMAKE_COMPILER_IS_GNUCXX)
	set_source_files_properties(${SRC} PROPERTIES COMPILE_FLAGS "-std=c++11 -Wall")
endif()
