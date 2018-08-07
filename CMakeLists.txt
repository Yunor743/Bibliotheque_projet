cmake_minimum_required (VERSION 2.8)
project (irondelle)
file (GLOB SRC
    "content/*.hpp"
    "content/*.cpp"
)
add_executable (irondelle ${SRC})
file (INSTALL build/irondelle.exe DESTINATION ./)