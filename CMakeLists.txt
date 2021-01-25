cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)

PROJECT(Game)

include_directories(/usr/local/include ${PROJECT_SOURCE_DIR}/include)

add_subdirectory(src)

add_executable(Game game.cpp)

# Link SDL2::Main, SDL2::Image and SDL2::GFX to our project
target_link_directories(Game
        PRIVATE /usr/local/lib
        )
target_link_libraries(${PROJECT_NAME} CaGE SDL2 SDL2_image SDL2_ttf jsoncpp)
