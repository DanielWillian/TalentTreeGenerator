set(DICT_SRCS
    BranchDictionary.cpp
    PropertyDictionary.cpp
    TalentDictionary.cpp
    TalentDictionaryLevel1.cpp
    TalentDictionaryLevel2.cpp
    TalentDictionaryLevel3.cpp
    TalentDictionaryLevel4.cpp
    TalentDictionaryLevel5.cpp
    TalentDictionaryLevel6.cpp
    TalentDictionaryLevel7.cpp
    TalentDictionaryLevel8.cpp
    TalentDictionaryLevel9.cpp
)

add_library(Dictionaries ${DICT_SRCS})

target_compile_options(Dictionaries
    PRIVATE
        $<$<CXX_COMPILER_ID:MSVC>:${WARNING_FLAGS_MSVC}>
        $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:${WARNING_FLAGS_NON_MSVC}>
)

target_link_libraries(Dictionaries
    PUBLIC
        Utils
)

target_include_directories(Dictionaries
    PRIVATE
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/Source>
)

