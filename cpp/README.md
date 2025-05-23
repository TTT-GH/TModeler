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

## 📦 Tms<T> – TTT Model System

Un système générique de gestion de modèles orienté données, permettant :

- CRUD complet
- Observations inter-thread et inter-modulaires
- Filtres puissants
- Jointures inter-modèles
- Groupes et agrégations
- Utilitaires de manipulation directe

---

## 🧬 Définition d’un modèle

Tout modèle `T` doit être lié à son gestionnaire statique `Tms<T>` via :

```cpp
Tms<Client> tms;
```

Chaque type (`Client`, `Product`, `Cmd`, etc.) doit exposer un accès statique à son gestionnaire :

```cpp
static inline Tms<Client> tms{};
```

---

## ✨ Observations (CRUD & changements)

Exemples d’observateurs :

```cpp
Tms<Client> tms;

tms.onSave([](auto keys) {
    Log::d("onSave...\n" + Client::tms.get(keys).data());
});
tms.onCreate([](auto keys) {
    Log::d("onCreate...\n" + Client::tms.get(keys).data());
});
tms.onUpdate([](auto keys) {
    Log::d("onUpdate...\n" + Client::tms.get(keys).data());
});
tms.onDelete([](auto keys) {
    Log::d("onDelete...\n" + vectorToString(keys));
});
tms.onModelChange([](auto keys) {
    Log::d("onModelChange...\n" + vectorToString(keys));
});
```

---

## 🔍 Filtres

### Paramètres de filtre

À déclarer globalement (ex. dans un `.h`) :

```cpp
namespace Expr {
    inline Person p{};
    inline Client cl{};
    inline Product pr{};
    inline Cmd cm{};
}
using Expr::p;
using Expr::cl;
using Expr::pr;
using Expr::cm;
```

### Filtres simples

```cpp
auto ft = Person::tms.with(p).filter(
    (p.dob >= "2000-11-04") &&
    (p.name != "Michel TAMBO") &&
    (p.name != "Gaby TAMBO") &&
    (p._id >>= {186, 187})
);
Log::d(ft.data());
```

Autres exemples :

```cpp
auto all = Person::tms.all();

auto filter = Person::tms.with(p).filter(
    (p.dob >= "2000-11-04") &&
    (p.name != "Michel TAMBO") &&
    (p.meta != "") &&
    (p._id != 2) &&
    (p.ratio != 24.0) &&
    (p.empty == true)
);

auto filter2 = Person::tms.with(p).filter(
    (p._id >= 20) &&
    (p.name % "%TAMBO%") &&
    (p.id == nullptr)
);

auto filter3 = Person::tms.with(p).filter(
    (p._id >>= {7, 8, 9, 10, 11}) &&
    !(p.name >>= {"Pat TAMBO", "Michel TAMBO"})
);
```

---

## 🔗 Jointures, Groupes & Sélections

### Jointure + groupement

```cpp
auto filter1 = Client::tms.with(cl).filter(cl._id > 0)
    .order(+cl.name)
    .group(cl.name)
    .filter(cl._id.count() == 2);

Log::d("filter1: \n" + filter1.data());
```

### Jointure avec autre modèle

```cpp
Tlist<Client, Cmd> join = Client::tms.with<Cmd>(cl, cm)
    .join(JoinType::LEFT)
    .filter(cm.client == cl)
    .filter(cm.client == nullptr)
    .order(-cl.dob)
    .group(cl._id)
    .filter(cl._id.count() <= 2);

auto joinClient = join.select<Client>();
auto joinCmdClient = join.select<Cmd, Client>();

Log::d("join: \n" + join.data());
Log::d("join clients only: \n" + joinClient.data());
Log::d("join clients + commandes: \n" + joinCmdClient.data());
```

---

## 🧰 Utilitaires

### Réinitialisation

```cpp
Client::tms.clear();
Product::tms.clear();
Cmd::tms.clear();
```

### Migration / Préparation

```cpp
Client::tms.migrate();
Product::tms.migrate();
Cmd::tms.migrate();
```

### Nom du modèle

```cpp
Log::d("Client model: " + Client::tms.name());
```

---

## 🧪 Exemples complets

```cpp
// Réinitialisation
Client::tms.clear();
Product::tms.clear();
Cmd::tms.clear();

// Migration
Client::tms.migrate();
Product::tms.migrate();
Cmd::tms.migrate();

// Logging
Log::d("Model: " + Client::tms.name());

// Affichage d’un Tlist
auto list = Client::tms.all();
Log::d("_client: \n" + list.data());
```

---

## 💡 Opérateurs disponibles pour les filtres

| Opérateur        | Signification                  |
|------------------|--------------------------------|
| `==`, `!=`       | Égal, différent                |
| `>`, `<`, `>=`   | Comparaisons numériques/dates  |
| `%`              | LIKE (pattern SQL)             |
| `>>=`            | IN (dans une liste de valeurs) |
| `== nullptr`     | Champ nul                      |
| `&&`, `||`, `!`  | Logique combinatoire           |
| `.count()`       | Nombre d’occurrences (groupes) |

---

## 📦 Tms<T> – Gestionnaire de modèle

Chaque type `T` possède un singleton de type `Tms<T>` accessible via `T::tms`.

### Méthodes principales

| Méthode            | Description                        |
|--------------------|------------------------------------|
| `clear()`          | Vide tous les éléments             |
| `migrate()`        | Réinitialise le modèle             |
| `name()`           | Retourne le nom du modèle          |
| `all()`            | Retourne tous les éléments         |
| `get(keys)`        | Récupère les éléments par ID       |
| `onCreate(f)`      | Callback création                  |
| `onUpdate(f)`      | Callback mise à jour               |
| `onDelete(f)`      | Callback suppression               |
| `onSave(f)`        | Callback save (create + update)    |
| `onModelChange(f)` | Callback global sur les changements|

---
