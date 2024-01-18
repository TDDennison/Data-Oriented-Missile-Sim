project(common)

add_subdirectory(math_types)

set (PROJECT_SOURCE_FILES
    include/DomSimConstants.h
    )

add_library(${PROJECT_NAME} ${PROJECT_SOURCE_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(${PROJECT_NAME} math_types)
