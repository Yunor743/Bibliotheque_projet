cmake_minimum_required (VERSION 2.8)
project (irondel)
file (GLOB SRC
    "content/*.hpp"
    "content/*.cpp"
)
add_executable (
    irondel ${SRC}
    ${CMAKE_CURRENT_SOURCE_DIR}/ressources/icon.rc
)
install (PROGRAMS build/irondel.exe DESTINATION ./)