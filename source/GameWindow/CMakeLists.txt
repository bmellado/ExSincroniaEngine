set(WINDOW_HEADERS 
		GameWindow.hpp
		)
set(WINDOW_SOURCES
		GameWindow.cpp
		)

add_library(Window STATIC ${WINDOW_SOURCES} ${WINDOW_HEADERS} )
if (MSVC)
    target_compile_options(Window PUBLIC /wd5033)
endif(MSVC)
target_include_directories(Window PRIVATE ${THIRD_PARTY_INCLUDE_DIRECTORIES} GRAFICA_INCLUDE_DIRECTORY Time Rendering)
target_link_libraries( Window PRIVATE ${THIRD_PARTY_LIBRARIES})
set_property(TARGET Window PROPERTY CXX_STANDARD 20)
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${WINDOW_SOURCES} ${WINDOW_HEADERS})
