# Note that headers are optional, and do not affect add_library, but they will not
# show up in IDEs unless they are listed in add_library.

file(GLOB_RECURSE TARGET_INCLUDES ${PROJECT_SOURCE_DIR}/include/*.h)
file(GLOB_RECURSE TARGET_SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp)
# Optionally glob, but only for CMake 3.12 or later:
# file(GLOB HEADER_LIST CONFIGURE_DEPENDS "${ModernCMakeExample_SOURCE_DIR}/include/modern/*.hpp")
set(HEADER_LIST
    ${PROJECT_SOURCE_DIR}/src/)


include_directories(${PROJECT_SOURCE_DIR}/include)

add_library(CaGE
        STATIC
        ${TARGET_SOURCES}
        )

# We need this directory, and users of our library will need it too
target_include_directories(CaGE PUBLIC ${TARGET_INCLUDES})

set_target_properties(CaGE PROPERTIES PUBLIC_HEADER "${CRWNMeshV2_SOURCE_DIR}/include/mesh_v2/comm.h;${CRWNMeshV2_SOURCE_DIR}/include/mesh_v2/proto.h;${CRWNMeshV2_SOURCE_DIR}/include/mesh_v2/io.h;${CRWNMeshV2_SOURCE_DIR}/include/mesh_v2/crc.h;${CRWNMeshV2_SOURCE_DIR}/include/mesh_v2/queue.h;${CRWNMeshV2_SOURCE_DIR}/include/mesh_v2/table.h")

# IDEs should put the headers in a nice place
source_group(
        TREE "${PROJECT_SOURCE_DIR}/include"
        PREFIX "Header Files"
        FILES ${HEADER_LIST})

INSTALL(TARGETS CaGE
        LIBRARY DESTINATION lib
        PUBLIC_HEADER DESTINATION include/CaGE
        )
