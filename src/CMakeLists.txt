# Collect files and set groups
file(GLOB_RECURSE ALGO_INC CMAKE_CONFIGURE_DEPENDS algorithm/*.h)
file(GLOB_RECURSE ALGO_SRC CMAKE_CONFIGURE_DEPENDS algorithm/*.cpp)
source_group(Algorithm FILES ${ALGO_INC} ${ALGO_SRC})

file(GLOB_RECURSE GEOM_INC CMAKE_CONFIGURE_DEPENDS geometry/*.h)
file(GLOB_RECURSE GEOM_SRC CMAKE_CONFIGURE_DEPENDS geometry/*.cpp)
source_group(Geometry FILES ${GEOM_INC} ${GEOM_SRC})

file(GLOB_RECURSE UTIL_INC CMAKE_CONFIGURE_DEPENDS utils/*.h)
file(GLOB_RECURSE UTIL_SRC CMAKE_CONFIGURE_DEPENDS utils/*.cpp)
source_group(Utils FILES ${UTIL_INC} ${UTIL_SRC})

# Create a Nurbs library
set(LIB_NAME NURBS_LIB)
add_library(${LIB_NAME} ${ALGO_SRC} ${GEOM_SRC} ${UTIL_SRC})

# Third-party dependencies
set(3RD_PARTY_DIR ${CMAKE_SOURCE_DIR}/3rd-parties)
# Eigen
set(Eigen3_DIR "${3RD_PARTY_DIR}/Eigen3/share/eigen3/cmake")
find_package(Eigen3 REQUIRED)
# OpenGL
set(GL_DIR "${3RD_PARTY_DIR}/OpenGL")

# Include directories and link libraries
target_include_directories(${LIB_NAME} PUBLIC algorithm geometry utils)
target_include_directories(${LIB_NAME} PUBLIC Eigen3::Eigen)
target_include_directories(${LIB_NAME} PUBLIC ${GL_DIR}/Include)

target_link_libraries(${LIB_NAME} PUBLIC Eigen3::Eigen)
target_link_libraries(${LIB_NAME} PUBLIC opengl32.lib ${GL_DIR}/Libs/glfw3.lib ${GL_DIR}/Libs/glad.lib)