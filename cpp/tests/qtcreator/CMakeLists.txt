cmake_minimum_required(VERSION 3.16)

project(TestMingw VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core Quick QuickControls2 QuickDialogs2)

qt_standard_project_setup()

qt_standard_project_setup(REQUIRES 6.8)

qt_add_executable(appTestMingw
    main.cpp
)

qt_add_qml_module(appTestMingw
    URI TestMingw
    VERSION 1.0
    QML_FILES
        Main.qml
        SOURCES models.h models.cpp
        SOURCES clientgenerator.h clientgenerator.cpp
        SOURCES viewmodels.hpp
)

message(STATUS "Qt6 Core Version: ${Qt6Core_VERSION}")

# 📥 Dépendances externes via FetchContent
include(FetchContent)

FetchContent_Declare(
    TModeler
    GIT_REPOSITORY https://github.com/TTT-GH/TModeler.git
    GIT_TAG main
    SOURCE_SUBDIR cpp
)
FetchContent_MakeAvailable(TModeler)

# 📦 Ajouter nlohmann/json via FetchContent
FetchContent_Declare(
    nlohmann_json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.11.2
)
FetchContent_MakeAvailable(nlohmann_json)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appTestMingw PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appTestMingw
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appTestMingw
    PRIVATE Qt6::Quick
    PRIVATE Qt6::QuickControls2
    PRIVATE Qt6::QuickDialogs2
    PRIVATE TModeler
    PRIVATE TModelerQtAdapter
    PUBLIC nlohmann_json::nlohmann_json
)

include(GNUInstallDirs)
install(TARGETS appTestMingw
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
