cmake_minimum_required (VERSION 2.8)
project (irondelle)
file (GLOB SRC
    "content/*.hpp"
    "content/*.cpp"
)
add_executable (irondelle ${SRC})
install (PROGRAMS build/irondelle.exe DESTINATION ./)