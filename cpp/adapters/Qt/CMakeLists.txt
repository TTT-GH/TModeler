cmake_minimum_required(VERSION 3.24)

project(TModelerQtAdapter LANGUAGES CXX)

# Une cible spécifique pour le ViewModel QML
add_library(TModelerQtAdapter INTERFACE)

# Inclure les headers (ex: TViewModel.hpp)
target_include_directories(TModelerQtAdapter INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# Cette cible dépend de TModeler (interface uniquement)
target_link_libraries(TModelerQtAdapter INTERFACE TModeler)