cmake_minimum_required(VERSION 3.24)
project(TMtests LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)

# Dossier pour les dépendances externes
set(FETCHCONTENT_BASE_DIR ${CMAKE_SOURCE_DIR}/external)

# -------- TModeler (dep principale) --------
message(STATUS "Fetching TModeler...")
FetchContent_Declare(
    TModeler
    GIT_REPOSITORY https://github.com/TTT-GH/TModeler.git
    GIT_TAG main
    SOURCE_SUBDIR cpp
)
FetchContent_MakeAvailable(TModeler)

# -------- nlohmann::json --------
message(STATUS "Fetching nlohmann_json...")
FetchContent_Declare(
    nlohmann_json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.11.2
)
FetchContent_MakeAvailable(nlohmann_json)

# -------- GoogleTest --------
message(STATUS "Fetching GoogleTest...")
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.14.0
)
FetchContent_MakeAvailable(googletest)

# -------- Executable de test --------
add_executable(TMtests
    main.cpp
    Models.h
)

target_link_libraries(TMtests
    PRIVATE
        TModeler
        gtest
        gtest_main
    PUBLIC
        nlohmann_json::nlohmann_json
)

# -------- Découverte automatique des tests --------
enable_testing()
include(GoogleTest)
gtest_discover_tests(TMtests)