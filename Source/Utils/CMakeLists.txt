set(UTILS_SRCS
    Constants.cpp
    Random.cpp
    Statics.cpp
)

add_library(Utils ${UTILS_SRCS})

target_compile_options(Utils
    PRIVATE
        $<$<CXX_COMPILER_ID:MSVC>:${WARNING_FLAGS_MSVC}>
        $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:${WARNING_FLAGS_NON_MSVC}>
)

