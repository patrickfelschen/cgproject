cmake_minimum_required(VERSION 3.16)
project(CG)
set(CMAKE_CXX_STANDARD 23)

file(GLOB_RECURSE SOURCE_FILES_REC CONFIGURE_DEPENDS "src/*.hpp" "src/*.cpp")

add_executable(CG ${SOURCE_FILES_REC})

IF (WIN32)
    # OpenGL Extension Wrangler Library
    set(GLEW_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libraries/win32/glew/include/)
    set(GLEW_LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libraries/win32/glew/lib/)
    find_library(GLEW_LIBRARY NAMES glew32 PATHS ${GLEW_LIB_DIR})

    # Graphics Library Framework
    set(GLFW_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libraries/win32/glfw/include/)
    set(GLFW_LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libraries/win32/glfw/lib/)
    find_library(GLFW_LIBRARY NAMES glfw3 PATHS ${GLFW_LIB_DIR})

    # FreeImage
    set(FREEIMAGE_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libraries/win32/freeimage/include/)
    set(FREEIMAGE_LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libraries/win32/freeimage/lib/)
    find_library(FREEIMAGE_LIBRARY NAMES FreeImage PATHS ${FREEIMAGE_LIB_DIR})

    # Open Asset Import Library
    set(ASSIMP_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libraries/win32/assimp/include)
    set(ASSIMP_LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libraries/win32/assimp/lib/)
    find_library(ASSIMP_LIBRARY NAMES assimp-vc140-mt PATHS ${ASSIMP_LIB_DIR})

    include_directories(${GLEW_INCLUDE_DIR} ${GLFW_INCLUDE_DIR} ${FREEIMAGE_INCLUDE_DIR} ${ASSIMP_INCLUDE_DIR})
    set(CG_LIBRARIES ${GLEW_LIBRARY} ${GLFW_LIBRARY} ${FREEIMAGE_LIBRARY} ${ASSIMP_LIBRARY} opengl32)

    # Copy *.dll files to build folder
    add_custom_command(TARGET CG POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different ${GLEW_LIB_DIR}glew32.dll $<TARGET_FILE_DIR:CG>)
    add_custom_command(TARGET CG POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different ${GLFW_LIB_DIR}glfw3.dll $<TARGET_FILE_DIR:CG>)
    add_custom_command(TARGET CG POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different ${FREEIMAGE_LIB_DIR}FreeImage.dll $<TARGET_FILE_DIR:CG>)
    add_custom_command(TARGET CG POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different ${ASSIMP_LIB_DIR}assimp-vc140-mt.dll $<TARGET_FILE_DIR:CG>)
ELSE()
    # APPLE / UNIX
ENDIF()

target_link_libraries(CG ${CG_LIBRARIES})