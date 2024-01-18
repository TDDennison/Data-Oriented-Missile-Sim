project(math_types)

set (PROJECT_SOURCE_FILES 
    src/Matrix3.cpp
    src/Matrix4.cpp
    src/Quaternion.cpp
    src/Vector3.cpp
    )

add_library(${PROJECT_NAME} ${PROJECT_SOURCE_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(${PROJECT_NAME} core)