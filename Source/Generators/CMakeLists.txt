set(GEN_SRCS
    BranchGenerator.cpp
    PropertyDistance.cpp
    PropertyRepository.cpp
    TalentTreeGenerator.cpp
)

add_library(Generators ${GEN_SRCS})

target_compile_options(Generators
    PRIVATE
        $<$<CXX_COMPILER_ID:MSVC>:${WARNING_FLAGS_MSVC}>
        $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:${WARNING_FLAGS_NON_MSVC}>
)

target_link_libraries(Generators
    PUBLIC
        Utils
        Models
        Dictionaries
)

target_include_directories(Generators
    PRIVATE
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/Source>
)

