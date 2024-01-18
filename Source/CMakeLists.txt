add_compile_options("-O0")
add_compile_options("-g")

set(EXECUTABLE_NAME DOMSim)

set(DOMSIM_SOURCES 
    main.cpp
    )

add_executable(${EXECUTABLE_NAME} ${DOMSIM_SOURCES})
target_compile_features(${EXECUTABLE_NAME} PRIVATE cxx_std_17)

add_subdirectory(core)
add_subdirectory(logging)
add_subdirectory(components)
add_subdirectory(managers)
add_subdirectory(common)
add_subdirectory(utilities)
add_subdirectory(systems)
add_subdirectory(application)

target_link_libraries(${EXECUTABLE_NAME} application)