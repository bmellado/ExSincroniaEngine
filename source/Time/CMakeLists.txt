set(TIME_HEADERS 
		Timer.hpp
		)
set(TIME_SOURCES
		Timer.cpp
		)

add_library(Time STATIC ${TIME_SOURCES} ${TIME_HEADERS} time.h)
if (MSVC)
    target_compile_options(Time PUBLIC /wd5033)
endif(MSVC)
#target_include_directories(Time PRIVATE ${THIRD_PARTY_INCLUDE_DIRECTORIES} GRAFICA_INCLUDE_DIRECTORY)
#target_link_libraries( PRIVATE ${THIRD_PARTY_LIBRARIES})
set_property(TARGET Time PROPERTY CXX_STANDARD 20)
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${TIME_SOURCES} ${TIME_HEADERS})
