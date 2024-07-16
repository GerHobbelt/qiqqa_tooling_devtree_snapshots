# libgumbo_query

# Gumbo dependency include directory.
include_directories(${Gumbo_INCLUDE_DIRS})

file(GLOB SRC_FILES *.cpp)
add_library(gumbo_query_shared SHARED ${SRC_FILES})
set_target_properties(gumbo_query_shared PROPERTIES OUTPUT_NAME "gq")
add_library(gumbo_query_static STATIC ${SRC_FILES})
set_target_properties(gumbo_query_static PROPERTIES OUTPUT_NAME "gq")

set_target_properties(gumbo_query_shared PROPERTIES POSITION_INDEPENDENT_CODE ON)

target_link_libraries(gumbo_query_shared ${Gumbo_LIBRARIES})
target_link_libraries(gumbo_query_shared ${Gumbo_LIBRARIES})

set(gumbo_query_LIBRARIES gumbo_query_shared gumbo_query_static)
set_property(TARGET ${gumbo_query_LIBRARIES} PROPERTY CXX_STANDARD 11)
set_property(TARGET ${gumbo_query_LIBRARIES} PROPERTY CXX_STANDARD_REQUIRED ON)

install(TARGETS gumbo_query_shared gumbo_query_static
	LIBRARY DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/lib
     	ARCHIVE DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/lib)

file(GLOB HEAD_FILES *.h)
target_sources(gumbo_query_static INTERFACE ${HEAD_FILES})
message(${HEAD_FILES})
install(FILES ${HEAD_FILES} DESTINATION include/gq)
