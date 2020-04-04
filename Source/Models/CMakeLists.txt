set(MODELS_SRCS
    Property.cpp
    Talent.cpp
    TalentEntry.cpp
    TalentTree.cpp
)

add_library(Models ${MODELS_SRCS})

target_compile_options(Models
    PRIVATE
        $<$<CXX_COMPILER_ID:MSVC>:${WARNING_FLAGS_MSVC}>
        $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:${WARNING_FLAGS_NON_MSVC}>
)

