# TModeler C++

## Description

TModeler est une bibliothèque ORM (Object-Relational Mapping) pour C++ qui permet de gérer les modèles de données de manière simple et efficace. Elle offre des fonctionnalités telles que la gestion des données, les observateurs, les filtres complexes, les jointures, les agrégations, et l'héritage des modèles de données.

## Installation

### Prérequis

- CMake 3.24 ou supérieur
- C++17 ou supérieur
- Git

### Dépendances

TModeler dépend des bibliothèques suivantes, qui sont intégrées automatiquement via `FetchContent` :

- **TModelerLib** (dépôt GitHub)
- **nlohmann_json** (JSON pour C++)

### Compilation

Pour intégrer ces dépendances et compiler le projet, ajoutez le code suivant dans votre fichier `CMakeLists.txt` :

```cmake
include(FetchContent)

# TModelerLib
FetchContent_Declare(
    TModelerLib
    GIT_REPOSITORY https://github.com/TTT-GH/TModeler.git
    GIT_TAG main
    SOURCE_SUBDIR cpp
)
FetchContent_MakeAvailable(TModelerLib)

# nlohmann_json
FetchContent_Declare(
    nlohmann_json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.11.2
)
FetchContent_MakeAvailable(nlohmann_json)

# Lier les bibliothèques au projet
target_link_libraries(${PROJECT_NAME}
    # ...
    PRIVATE TModeler
    PUBLIC nlohmann_json::nlohmann_json
    # ...
)
```