add_compile_options("-O0")
add_compile_options("-g")

set(EXECUTABLE_NAME DOMSim)

set(DOMSIM_SOURCES 
    main.cpp

    Simulation.h
    Simulation.cpp
    Utilities.h

    Managers/EntityManager.h
    Managers/EntityManager.cpp
    Managers/MassManager.h
    Managers/MassManager.cpp
    Managers/MovementManager.h
    Managers/MovementManager.cpp
    Managers/TransformManager.h
    Managers/TransformManager.cpp

    Parsers/CommandLineParser/CommandLineParser.h
    Parsers/CommandLineParser/CommandLineParser.cpp
    Parsers/BinaryFileParser/BinaryFileParser.h

    Systems/BoosterSystems/FirstStageBoosterSystem.h
    Systems/BoosterSystems/FirstStageBoosterSystem.cpp
    Systems/BoosterSystems/SecondStageBoosterSystem.h
    Systems/BoosterSystems/SecondStageBoosterSystem.cpp
    
    )

add_executable(${EXECUTABLE_NAME} ${DOMSIM_SOURCES})
target_compile_features(${EXECUTABLE_NAME} PRIVATE cxx_std_17)