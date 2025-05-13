cmake_minimum_required(VERSION 3.24)

project(TModeler LANGUAGES CXX)

# Déclare une cible IMPORTED avec le nom que le projet principal attend
add_library(TModeler STATIC IMPORTED GLOBAL)

# Spécifie où se trouve la bibliothèque compilée
set_target_properties(TModeler PROPERTIES
    IMPORTED_LOCATION "${CMAKE_CURRENT_SOURCE_DIR}/lib/libTModeler.a"
    INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/include"
)