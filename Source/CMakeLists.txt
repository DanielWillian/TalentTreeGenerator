add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Utils)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Models)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Time)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Dictionaries)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Generators)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Options)

add_executable(TalentTreeGenerator ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)

target_link_libraries(TalentTreeGenerator
    PRIVATE
        Utils
        Models
        Time
        Dictionaries
        Generators
        Options
)

target_compile_options(TalentTreeGenerator
    PRIVATE
        $<$<CXX_COMPILER_ID:MSVC>:${WARNING_FLAGS_MSVC}>
        $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:${WARNING_FLAGS_NON_MSVC}>
)

target_include_directories(TalentTreeGenerator
    PRIVATE
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/Source>
)

set_target_properties(TalentTreeGenerator PROPERTIES
    OUTPUT_NAME "ttg")

