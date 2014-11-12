set(SRC
	"Minefield.h"
	"MinefieldGenerator.cpp"
	"MinefieldGenerator.h"
	"Minesweeper.cpp"
	"Minesweeper.h"
)

add_library("core" STATIC ${SRC})

target_include_directories("core" PUBLIC ".")

if(CMAKE_COMPILER_IS_GNUCXX)
	set_source_files_properties(${SRC} PROPERTIES COMPILE_FLAGS "-std=c++11 -Wall")
endif()
