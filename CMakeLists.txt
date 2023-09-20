cmake_minimum_required(VERSION 3.26)
project(ProjetC C)

set(CMAKE_C_STANDARD 11)

add_executable(ProjetC main.c
        Interface/cellule.h
        Interface/Foret.h
        Interface/interface_utilisateur.h
        Interface/simulation.h
        implementation/Foret.c
        implementation/interface-utilisateur.c
)
