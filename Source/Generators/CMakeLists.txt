set(GEN_SRCS
    BranchGenerator.cpp
    PropertyDistance.cpp
    PropertyRepository.cpp
    TalentTreeGenerator.cpp
)

add_library(Generators ${GEN_SRCS})

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

