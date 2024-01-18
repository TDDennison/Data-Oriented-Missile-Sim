project(managers)

set (PROJECT_SOURCE_FILES 
    src/AccumulatorManager.cpp
    src/ClockManager.cpp
    src/EntityManager.cpp
    src/MassManager.cpp
    src/MovementManager.cpp
    src/SolidRocketMotorManager.cpp
    src/TestSoftwareManager.cpp
    src/TransformManager.cpp
    )

add_library(${PROJECT_NAME} ${PROJECT_SOURCE_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(${PROJECT_NAME} components)
target_link_libraries(${PROJECT_NAME} core)
target_link_libraries(${PROJECT_NAME} logging)