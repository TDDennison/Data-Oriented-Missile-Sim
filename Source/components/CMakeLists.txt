project(components)

set (PROJECT_SOURCE_FILES 
    src/AccumulatorComponent.cpp
    src/ClockComponent.cpp
    src/Component.cpp
    src/ComponentUtilities.cpp
    src/MassComponent.cpp
    src/MovementComponent.cpp
    src/SoftwareComponent.cpp
    src/SolidRocketMotorComponent.cpp
    src/TransformComponent.cpp
    )

add_library(${PROJECT_NAME} ${PROJECT_SOURCE_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(${PROJECT_NAME} math_types)
