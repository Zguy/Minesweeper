set(SRC
	"main.cpp"
	"SFMLMinefield.cpp"
	"SFMLMinefield.h"
)

add_executable("SFMLSweeper" ${SRC})

find_package(SFML 2 COMPONENTS system window graphics REQUIRED)

target_include_directories("SFMLSweeper" PUBLIC ${SFML_INCLUDE_DIR})

target_link_libraries("SFMLSweeper" PUBLIC "core" ${SFML_LIBRARIES})

if(CMAKE_COMPILER_IS_GNUCXX)
	set_source_files_properties(${SRC} PROPERTIES COMPILE_FLAGS "-std=c++11 -Wall")
endif()
