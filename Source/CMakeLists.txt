add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Utils)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Models)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Dictionaries)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Generators)

add_executable(TalentTree ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)

target_link_libraries(TalentTree
    PRIVATE
        Utils
        Models
        Dictionaries
        Generators
)

target_include_directories(TalentTree
    PRIVATE
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/Source>
)

