# TModeler

TModeler est une bibliothèque ORM (Object-Relational Mapping) multi-langages permettant de gérer des modèles de données de manière simple et efficace. Le projet est actuellement disponible en C++, et dans un futur proche, des versions Java et Python seront ajoutées.

## Langages disponibles

- **C++** : [Voir la documentation C++](cpp/README.md)
- **Java** : À venir
- **Python** : À venir

## Fonctionnalités

- **Gestion des modèles de données** : Création, mise à jour, suppression, et récupération des modèles.
- **Observateurs multithread** : Permet de suivre les changements dans les données sur différents threads.
- **Filtres, jointures et agrégations** : Applique des filtres complexes sur les données, joint des modèles et effectue des agrégations.
- **Héritage de modèles et champs personnalisés** : Crée des modèles personnalisés avec des champs hérités ou nouveaux.
  
## Installation (C++)

Pour inclure TModeler dans votre projet C++, vous pouvez utiliser `FetchContent` avec CMake.

### Utilisation de `FetchContent` :

```cmake
include(FetchContent)

FetchContent_Declare(
    TModeler
    GIT_REPOSITORY https://github.com/TTT-GH/TModeler.git
    GIT_TAG main
    SOURCE_SUBDIR cpp
)

FetchContent_MakeAvailable(TModeler)