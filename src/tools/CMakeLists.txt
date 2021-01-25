add_executable(CaGEPackager ${PROJECT_SOURCE_DIR}/src/tools/FileGenerator.cpp)
add_dependencies(CaGEPackager CaGE)
target_link_libraries(CaGEPackager CaGE SDL2 SDL2_image SDL2_ttf)

target_link_directories(CaGEPackager PRIVATE /usr/local/lib)

INSTALL(TARGETS CaGEPackager
        RUNTIME DESTINATION bin
        )