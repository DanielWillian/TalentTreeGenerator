set(OPTIONS_SRCS
    ProgramOptions.cpp
    Options.cpp
)

# Creates C resources file from files in given directory
function(create_resources dir output)
    file(WRITE ${output} "")
    file(GLOB bins ${dir}/*)
    foreach(bin ${bins})
        string(REGEX MATCH "([^/]+)$" filename ${bin})
        string(REGEX REPLACE "\\.| |-" "_" filename ${filename})
        file(READ ${bin} filedata HEX)
        # Convert hex data for C compatibility
        string(REGEX REPLACE "([0-9a-f][0-9a-f])" "0x\\1," filedata ${filedata})
        file(APPEND ${output} "const char ${filename}[] = {${filedata}0x00};\nconst unsigned ${filename}_size = sizeof(${filename});\n")
    endforeach()
endfunction()

create_resources(${PROJECT_SOURCE_DIR}/Resource/Options ${PROJECT_BINARY_DIR}/Resource/Resource.h)

add_library(Options ${OPTIONS_SRCS})

target_compile_options(Options
    PRIVATE
        $<$<CXX_COMPILER_ID:MSVC>:${WARNING_FLAGS_MSVC}>
        $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:${WARNING_FLAGS_NON_MSVC}>
)

target_include_directories(Options
    PRIVATE
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/Source>
        $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/Resource>
)

