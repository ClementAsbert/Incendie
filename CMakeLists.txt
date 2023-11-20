cmake_minimum_required(VERSION 3.26)
project(ProjetC C)

set(CMAKE_C_STANDARD 11)

find_package(raylib REQUIRED)
include_directories(${RAYLIB_INCLUDE_DIRS})
link_directories(${RAYLIB_LIBRARIES})


add_executable(ProjetC main.c
        Interface/cellule.h
        Interface/Foret.h
        Interface/interface_utilisateur.h
        Interface/simulation.h
        Interface/ihm.h
        implementation/Foret.c
        implementation/interface-utilisateur.c
        implementation/simulation.c
        implementation/ihm.c
)
target_link_libraries(ProjetC PRIVATE raylib)
