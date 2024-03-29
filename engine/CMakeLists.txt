add_library(BetoneiraEngine SHARED
    "${CMAKE_CURRENT_SOURCE_DIR}/engine.cpp"
    
    "${CMAKE_CURRENT_SOURCE_DIR}/../external/glad/glad.c"

    "${CMAKE_CURRENT_SOURCE_DIR}/../external/SOIL/soil.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../external/SOIL/image_dxt.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../external/SOIL/image_helper.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../external/SOIL/stb_image_aug.c"

    "${CMAKE_CURRENT_SOURCE_DIR}/window/window.cpp"
    
    "${CMAKE_CURRENT_SOURCE_DIR}/shared/shared.cpp"
    
    "${CMAKE_CURRENT_SOURCE_DIR}/file/file.cpp"
    
    "${CMAKE_CURRENT_SOURCE_DIR}/color/color.cpp"
    
    "${CMAKE_CURRENT_SOURCE_DIR}/input/input.cpp"
    
    "${CMAKE_CURRENT_SOURCE_DIR}/random/random.cpp"
    
    "${CMAKE_CURRENT_SOURCE_DIR}/os/os.cpp"
    
    "${CMAKE_CURRENT_SOURCE_DIR}/math/vector/vector.cpp"
    
    "${CMAKE_CURRENT_SOURCE_DIR}/time/time.cpp"
    
    "${CMAKE_CURRENT_SOURCE_DIR}/graphics/texture/texture.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/graphics/shader/shader.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/graphics/mesh2d/mesh2d.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/graphics/mesh2dTextured/mesh2dTextured.cpp"
)

target_link_libraries(BetoneiraEngine glfw3)
target_link_libraries(BetoneiraEngine OpenGL::GL)
target_link_libraries(BetoneiraEngine Boost::filesystem)
target_link_libraries(BetoneiraEngine "${JPEG_LIBRARIES}")
target_link_libraries(BetoneiraEngine "${PNG_LIBRARIES}")

target_include_directories(BetoneiraEngine PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}/../external" "${JPEG_INCLUDE_DIR}" "${PNG_INCLUDE_DIR}")