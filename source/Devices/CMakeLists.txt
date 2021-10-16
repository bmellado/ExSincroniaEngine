set(WINDOW_HEADERS 
		Devices.hpp
		Joystick.hpp
		)
set(WINDOW_SOURCES
		Devices.cpp
		)

add_library(Devices STATIC ${WINDOW_SOURCES} ${WINDOW_HEADERS} )
if (MSVC)
    target_compile_options(Devices PUBLIC /wd5033)
endif(MSVC)
target_include_directories(Devices PRIVATE ${THIRD_PARTY_INCLUDE_DIRECTORIES} GRAFICA_INCLUDE_DIRECTORY Time Rendering)
target_link_libraries( Devices PRIVATE ${THIRD_PARTY_LIBRARIES})
set_property(TARGET Devices PROPERTY CXX_STANDARD 20)
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${WINDOW_SOURCES} ${WINDOW_HEADERS})
