project(logging)

set (PROJECT_SOURCE_FILES 
    src/BinaryLogger.cpp
    )

add_library(${PROJECT_NAME} ${PROJECT_SOURCE_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(${PROJECT_NAME} core)