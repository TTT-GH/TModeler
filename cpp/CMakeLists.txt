cmake_minimum_required(VERSION 3.24)

project(TModeler LANGUAGES CXX)

# Déclare une cible IMPORTED avec le nom que le projet principal attend
add_library(TModeler STATIC IMPORTED GLOBAL)

# Gestion par plateforme

# 🧠 Détection du type de build (Debug, Release, etc.)
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")  # Valeur par défaut
endif()

string(TOLOWER "${CMAKE_BUILD_TYPE}" BUILD_TYPE_LOWER)

# 🧠 Détection de la plateforme et du compilateur
if(WIN32)
    if(MSVC)
        message(STATUS "✅ MSVC on Windows - ${CMAKE_BUILD_TYPE}")
        set(TMODELER_LIB_PATH "${CMAKE_CURRENT_SOURCE_DIR}/lib/windows/msvc/${BUILD_TYPE_LOWER}")
        set(TMODELER_LIB_NAME "TModeler.lib")
    elseif(MINGW)
        message(STATUS "✅ MinGW on Windows - ${CMAKE_BUILD_TYPE}")
        set(TMODELER_LIB_PATH "${CMAKE_CURRENT_SOURCE_DIR}/lib/windows/mingw/${BUILD_TYPE_LOWER}")
        set(TMODELER_LIB_NAME "libTModeler.a")
    else()
        message(FATAL_ERROR "❌ Unsupported Windows compiler")
    endif()
elseif(UNIX)
    message(STATUS "✅ GCC on Linux - ${CMAKE_BUILD_TYPE}")
    set(TMODELER_LIB_PATH "${CMAKE_CURRENT_SOURCE_DIR}/lib/linux/${BUILD_TYPE_LOWER}")
    set(TMODELER_LIB_NAME "libTModeler.a")
else()
    message(FATAL_ERROR "❌ Unsupported platform")
endif()

set_target_properties(TModeler PROPERTIES
    IMPORTED_LOCATION "${TMODELER_LIB_PATH}/${TMODELER_LIB_NAME}"
    INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/include"
)