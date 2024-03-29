include_directories("${CMAKE_CURRENT_SOURCE_DIR}/src" "${CMAKE_SOURCE_DIR}/engine" "${Boost_INCLUDE_DIRS}")
add_definitions(-DBOOST_TEST_DYN_LINK)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(game "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp")

# get dll(s)
add_custom_command(TARGET game POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_BINARY_DIR}/engine/libBetoneiraEngine.dll"
        "$<TARGET_FILE_DIR:game>"
)


# get assets folder
add_custom_command(TARGET game POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/assets"
        "$<TARGET_FILE_DIR:game>/assets"
)

target_link_libraries(game BetoneiraEngine ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})