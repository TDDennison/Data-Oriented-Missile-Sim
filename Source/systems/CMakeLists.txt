project(systems)

set (PROJECT_SOURCE_FILES 
    src/EarthSystem.cpp
    src/FirstStageBoosterSystem.cpp
    src/IntegrationSystem_Euler.cpp
    src/IntegrationSystem_RK4.cpp
    src/SecondStageBoosterSystem.cpp
    src/System.cpp
    src/TestSoftwareSystem.cpp
    )

add_library(${PROJECT_NAME} ${PROJECT_SOURCE_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(${PROJECT_NAME} core)
target_link_libraries(${PROJECT_NAME} common)
target_link_libraries(${PROJECT_NAME} managers)
