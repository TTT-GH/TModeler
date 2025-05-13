cmake_minimum_required(VERSION 3.24)

# Déclaration du projet
project(TModeler LANGUAGES CXX)

# Version du standard C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Inclusion des headers
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Déclaration de la bibliothèque statique existante
add_library(TModelerLib STATIC IMPORTED)

# Emplacement du fichier binaire de la lib statique
set_target_properties(TModelerLib PROPERTIES
    IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/lib/libTModeler.a
)