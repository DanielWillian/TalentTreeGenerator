set(TIME_SRCS
    TimeRepository.cpp
)

add_library(Time ${TIME_SRCS})

target_compile_options(Time
    PRIVATE
        $<$<CXX_COMPILER_ID:MSVC>:${WARNING_FLAGS_MSVC}>
        $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:${WARNING_FLAGS_NON_MSVC}>
)

