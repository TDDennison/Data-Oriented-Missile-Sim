project(DMSF)

#add_compile_options("-O3") # Uncomment for full optimizations
add_compile_options("-O0")
add_compile_options("-g")

IF($ENV{DOMSIM_TESTS} STREQUAL "TRUE")
    add_compile_definitions(RUN_UNIT_TESTS)
ENDIF($ENV{DOMSIM_TESTS} STREQUAL "TRUE")

IF($ENV{DOMSIM_REAL_DOUBLE} STREQUAL "TRUE")
    add_compile_definitions(REAL_DOUBLE)
ENDIF($ENV{DOMSIM_REAL_DOUBLE} STREQUAL "TRUE")



add_subdirectory(Source)