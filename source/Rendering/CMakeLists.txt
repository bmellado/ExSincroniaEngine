set(RENDERING_HEADERS 
		Renderer.h
		SprinteRenderer.hpp
		)
set(RENDERING_SOURCES
		Renderer.cpp
		SpriteRenderer.cpp
		)

add_library(Rendering STATIC ${RENDERING_SOURCES} ${RENDERING_HEADERS} Rendering.h)
if (MSVC)
    target_compile_options(Rendering PUBLIC /wd5033)
endif(MSVC)
#target_include_directories(Time PRIVATE ${THIRD_PARTY_INCLUDE_DIRECTORIES} GRAFICA_INCLUDE_DIRECTORY)
#target_link_libraries( PRIVATE ${THIRD_PARTY_LIBRARIES})
set_property(TARGET Rendering PROPERTY CXX_STANDARD 20)
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${TIME_SOURCES} ${TIME_HEADERS})
