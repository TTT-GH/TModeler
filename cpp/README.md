# TModeler C++

## Description

TModeler is an ORM (Object-Relational Mapping) library for C++ that allows managing data models simply and efficiently. It offers features such as data management, observers, complex filters, joins, aggregations, and data model inheritance.

## Installation

### Prerequisites

- CMake 3.24 or higher
- C++17 or higher
- Git

### Dependencies

TModeler depends on the following libraries, which are automatically integrated via `FetchContent`:

- **TModelerLib** (GitHub repository)
- **nlohmann_json** (JSON for C++)
- **Bins near your executable** (If you use geo-spatial features: Copy all TModeler/bin/ files according to your compiler, near your executable)

### Compilation

To integrate these dependencies and compile the project, add the following code to your `CMakeLists.txt` file:

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

# Link the libraries to the project
target_link_libraries(${PROJECT_NAME}
    # ...
    PRIVATE TModeler
    PUBLIC nlohmann_json::nlohmann_json
    # ...
)
```

## 📦 Tms<T> - TTT Model System

A generic data-oriented model management system, enabling:

- Full CRUD
- Inter-thread and inter-module observations
- Powerful filters
- Inter-model joins
- Grouping and aggregations
- Direct manipulation utilities

---

## 🧪 Init

To run the unit tests for TModeler C++, make sure you initialize the ORM properly at the beginning of your test application. This step is essential for configuring the underlying databases and loading the appropriate data models :

```cpp
// Initialize the TModeler ORM with one or more databases.
TModeler::start()
    .dbReady([]()
    {
        // Data management starts here
    })
    .init(Tdb::Builder()
        .type(Tdb::Type::SQLITE)
        .dbDir("/tmp/sql")              // Path to SQLite database directory
        .dbName("test.db")              // Database filename
        .accept("models.shops")         // Accept specific model packages
        .accept("models.users")
        .get())
    .init(Tdb::Builder()
        .type(Tdb::Type::SQLITE)
        .host("localhost")              // Optional: for compatibility
        .dbName("test2.db")
        .get());
```

🧪 This initialization is required before using any TModeler models, even in tests.

---

## 🧬 Model Structure and Relations

All models inherit from TModel<T> and are declared using the TM_SCHEMA macro. Each field supports fluent configuration, such as primaryKey(), notNull(), autoIncrement(), etc.

Example: Complete Model with All Field Types
```cpp
class Client : public TModel<Client> {
    TM_SCHEMA(Client, "models.shops", TF(name), TF(age), TF(height), TF(dob), TF(friends))

    TextField name;
    IntField age;
    FloatField height;
    TimeField dob = init<TimeField>().format(TF::DATE);
    ListField<Client> friends;  // Self-referencing list
};

// into a .cpp for static tms access
TM_MANAGER(Client)
```

Example: Relations Between Models :
```cpp
class Product : public TModel<Product> {
    TM_SCHEMA(Product, "models.shops", TF(name))

    TextField name;
};
TM_MANAGER(Product)

class Cmd : public TModel<Cmd> {
    TM_SCHEMA(Cmd, "models.shops", TF(client), TF(product))

    ModelField<Client> client;      // Many-to-one
    ModelField<Product> product;    // Many-to-one
};
TM_MANAGER(Cmd)
```

Example: Advanced Model with Inheritance and Nested Models :
```cpp
class Familly : public TModel<Familly> {
    TM_SCHEMA(Familly, "models.group", TF(name))

    TextField name;
};

class Person : public TModel<Person> {
    TM_SCHEMA(Person, "models.users",
        TF(name), TF(design), TF(ratio), TF(empty),
        TF(dob), TF(update_at),
        TF(myFamilly), TF(bigFamilly), TF(friends))

    TextField name;
    TextField design;
    FloatField ratio;
    BoolField empty;
    TimeField dob = init<TimeField>().format(TF::DATE);
    TimeField update_at = init<TimeField>().format(TF::DATE_TIME);
    ModelField<Person> myFamilly = init<ModelField<Person>>().onDelete(TF::CASCADE);
    ModelField<Familly> bigFamilly = init<ModelField<Familly>>().onDelete(TF::CASCADE);
    ListField<Person> friends = init<ListField<Person>>();
    GeoField location = GeoField().spatialIndex(true);
};

// Geo spatial object model
class Geo : public TModel<Geo> {
    TM_SCHEMA(Geo, "models.space", TF(title), TF(description), TF(loc), TF(geometry))

    TextField title;
    TextField description;
    GeoField loc = GeoField().spatialIndex();
    GeoField geometry = GeoField().spatialIndex();
};
```

💡 All object-oriented principles apply to models and their fields: encapsulation, inheritance, composition, etc.

---

## 💡 CRUD Operations & Usage

The framework provides a powerful and expressive ORM for handling database entities through model instances. Each model type (Client, Product, Cmd, etc.) provides a static tms manager for batch operations and persistence.

Model Lifecycle: Create, Read, Update, Delete :

```cpp
Client cl1, cl2, cl3, cl4, cl5;
Product pr1, pr2, pr3;
Cmd cm1, cm2, cm3, cm4, cm5, cm6;

// Clear all records (use with caution)
Client::tms.clear();
Product::tms.clear();
Cmd::tms.clear();

// Start database communication (mandatory)
comm();

// Create clients
if (Client::tms.all().empty()) {
    cl1.name = "Lambda";
    cl1.age = 15;
    cl1.height = 1.70;
    cl1.dob = "2010-01-01";
    // ...
    cl5.name = "Lambda 2";
    cl5.age = 19;
    cl5.height = 1.50;
    cl5.dob = "2015-05-10";

    // Create or save records
    if (!cl1.create()) {
        Log::d("create: \ncan't");
    }
    cl2.save(); cl3.save(); cl4.save(); cl5.save();

    cl4.name = "Lambda 3";  // Update
    cl4.save();

    cl5.del();  // Delete

    // Manage relations (vector-based)
    cl1.friends = { &cl2, &cl3 };
    cl1.friends += cl4;

    cl1.save();
}

// Create products
if (Product::tms.all().empty()) {
    pr1.name = "Poulet"; pr2.name = "Poisson"; pr3.name = "Porc";
    pr1.save(); pr2.save(); pr3.save();
}

// Create commands (orders)
if (Cmd::tms.all().empty()) {
    cm1.client = cl1; cm1.product = pr1; cm1.save();
    cm2.client = cl1; cm2.product = pr2; cm2.save();
    cm3.client = cl2; cm3.product = pr3; cm3.save();
    cm4.client = cl2; cm4.product = pr1; cm4.save();
    cm5.client = cl1; cm5.product = pr2; cm5.save();
    cm6.client = cl3; cm6.product = pr3; cm6.save();
}

// Log all persisted data
Log::d("Client: \n" + Client::tms.all().data());
Log::d("Product: \n" + Product::tms.all().data());
Log::d("Cmd: \n" + Cmd::tms.all().data());

// Accessing relational data
Client ct = Cmd::tms.all().first().client;
Log::d("_client: \n" + ct.data());
```

JSON Fields & Embedded Objects :

```cpp
JsonField jf;

if (!jf) {
    jf += 2025;
    jf += 2024;
    jf += 2023;
    jf += { 2022, 2021, 2020 };

    jf += {
        { "array", jf.json() },
        { "cont", jf.contains(2020) }
    };

    jf += { { "object", jf.json() } };

    jf += {
        { "name", "Lambda" },
        { "age", 24 },
        { "poids", 80.3 }
    };

    jf += {
        { "marie", jf.get("poids") > 50 },
        { "enfants", jf.accept("names") }
    };
}

Person person;
person.id = 100;
person.name = "Lambda 4";
person.design = "Admin";
person.meta = jf.json();  // Save complex JSON data
person.ratio = 0.5;
person.empty = false;
person.dob = "2000-11-07";
person.create();

// Print model metadata and full content
Log::d("");
Log::d(Person::tms.name());
Log::d(Person::tms.all().data());
```

---

## ✨ Observing Changes: Inter-Thread & Inter-Module CRUD Events

The framework supports event-based observation of model changes (Create, Read, Update, Delete). These hooks can be registered to automatically react to specific actions (e.g., onSave, onDelete, etc.) and are particularly useful for :
- UI updates
- Data synchronization between threads or modules
- Live logs or analytics
- Reactive programming needs

Example: Observing Client changes :

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
### Description of Events

#### Callback Triggers

| **Callback**       | **Triggered When...**                                                  |
|--------------------|-------------------------------------------------------------------------|
| `onSave`           | A model is created or updated and successfully persisted.              |
| `onCreate`         | A model is newly created.                                               |
| `onUpdate`         | A model is modified and updated.                                        |
| `onDelete`         | A model is deleted from storage.                                        |
| `onModelChange`    | A change occurs to the model (create, update, delete, etc.).            |

#### Notes

- `keys` is a `std::vector<KeyType>` representing the primary keys of affected models.
- You can fetch the updated data using `Model::tms.get(keys)` or `Model::tms.get(key)`.

#### Use Case: Live Logging

With these hooks, you can create **live dashboards**, **loggers**, or **UI refresh mechanisms** that automatically react when the data changes-even across threads or modules.

---

## 🔍 Filtering, Joins, and Query Composition

The framework offers expressive, type-safe filtering and joining on in-memory models using a custom DSL based on C++ lambdas and operator overloading.

🔹 Setup for Filtering Expressions
To filter using model fields in expressions, declare reusable lambda objects:

```cpp
// In a common .h file
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

🔸 Simple Filters

```cpp
auto ft = Person::tms.with(p).filter(
    (p.dob >= "2000-11-04") &&
    (p.name != "Lambda") &&
    (p.name != "Lambda 2") &&
    (p._id >>= {186, 187})
);
Log::d(ft.data());
```

🔸 More Examples

```cpp
// Filter with null, like and boolean checks

auto all = Person::tms.all();

auto filter = Person::tms.with(p).filter(
    (p.dob >= "2000-11-04") &&
    (p.name != "Lambda 3") &&
    (p.meta != "") &&
    (p._id != 2) &&
    (p.ratio != 24.0) &&
    (p.empty == true)
);

// Filter with null, like and boolean checks
auto filter2 = Person::tms.with(p).filter(
    (p._id >= 20) &&
    (p.name % "%Lambda%") &&      // SQL LIKE
    (p.id == nullptr)            // NULL comparison
);

// Complex negated filters
auto filter3 = Person::tms.with(p).filter(
    (p._id >>= {7, 8, 9, 10, 11}) &&
    !(p.name >>= {"Lambda", "Lambda 2"})
);
```
#### ✅ Available Operators

#### Operator Comparison Table

| **C++ Syntax**           | **Equivalent SQL** | **Meaning**              |
|--------------------------|--------------------|---------------------------|
| `==`, `!=`, `>=`, `<=`, `<`, `>` | Standard comparisons | Field comparison          |
| `expr1 && expr2`         | `AND`              | Logical AND               |
| ``expr1     expr2``      | `OR`               | Logical OR                |
| `!expr`                  | `NOT`              | Negation                  |
| `expr % "pattern"`       | `LIKE`             | Pattern match (SQL-like)  |
| `expr >>= {x, y}`        | `IN (x, y)`         | Membership                |
| `expr == nullptr`        | `IS NULL`          | Null check                |

---

## 🔗 Filters with Join, Order, Group, and Aggregates

### Join + Group

```cpp
auto filter1 = Client::tms.with(cl)
    .filter(cl._id > 0)
    .order(+cl.name)                 // Ascending sort
    .group(cl.name)                 // Group by name
    .filter(cl._id.count() == 2);   // HAVING clause
Log::d("filter1: \n" + filter1.data());
```

### 🔀 Joins & Multi-Model Filters

```cpp
Tlist<Client, Cmd> join = Client::tms.with<Cmd>(cl, cm)
    .join(JoinType::LEFT) // without this : INNERT JOIN by default
    .filter(cm.client == cl)
    .filter(cm.client == nullptr)
    .order(-cl.dob)                     // Descending sort
    .group(cl._id)
    .filter(cl._id.count() <= 2);       // Aggregate filter

auto joinClient = join.select<Client>();
auto joinCmdClient = join.select<Cmd, Client>();

Log::d("join: \n" + join.data());
Log::d("join only Client: \n" + joinClient.data());
Log::d("join Cmd + Client: \n" + joinCmdClient.data());
```
📌 Notes
- Filters and joins do not modify data, they work like std::views.
- You can combine filter, order, group, and select() to build complex data queries.
- Join supports INNER, LEFT, and possibly RIGHT/FULL depending on implementation.

### Geo Spatial

```cpp
auto filter = Geo::tms.with(g0)
        .lazy()
        .filter(g0.loc.index(p1) && g0.loc.intersects(p1))
        .group(g0.title)
        .filter(g0._id.count() >= 2)
        .build();
    Log::d(filter.data());
    filter = Geo::tms.with(g0)
        .lazy()
        .filter(g0.loc.index(s1) && (g0.loc.distance(s1) <= 10) && (g0.loc.azimuth(s1) < 30))
        .group(g0.title)
        .filter(g0._id.count() >= 2)
        .build();
    Log::d(filter.data());
```

---

## 🧰 Model Utilities & Direct Manipulation

Each model type provides several utility functions via its Tms<Model> interface, accessible using the Model::tms static member.

### 🧹 clear() – Wipe all data

Remove all existing entries in memory:

```cpp
Client::tms.clear();
Product::tms.clear();
Cmd::tms.clear();
```
This is useful for:

- Resetting state during testing
- Clearing in-memory cache
- Simulating a "cold start" without persistent data

### ⚙️ migrate() – (Re)Initialize the model

```cpp
Client::tms.migrate();
Product::tms.migrate();
Cmd::tms.migrate();
```
This method typically ensures:
- Data structures are ready
- Schemas are validated or adapted (if needed)
- Can be called at startup or after a clear()

### 🏷️ name() – Get model name as string

```cpp
std::string modelName = Client::tms.name();
Log::d("Client model is: " + modelName);
```
Useful for logging or for generic model introspection.

---

## 📋 Example: Resetting and Verifying All

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

## Communication UI – Test ViewModel

This example demonstrates how to connect a `TViewModel` (ClientViewModel) with a QtQuick UI to manage a list of clients. The goal is to test reading and writing operations through the model and reflect changes in the user interface.

### C++ Model Definition
```cpp
// Model definition using the framework's macros
class Client : public TModel<Client> {
    TM_SCHEMA(Client, "models.shops", TF(name), TF(email), TF(friends))

    TextField name;
    TextField email;
    ListField<Client> friends;
};

// Item wrapper to expose to QML
class ClientItem : public TItem<Client> {
    Q_OBJECT
    TM_QML_ITEM
};

// ViewModel exposed to QML
class ClientViewModel : public TViewModel<Client> {
    Q_OBJECT
    TM_QML_VM(Client, ClientItem)
};
```

### QML UI (Read & Write Test)
```qml
property var item: clientModel.get(index)

Row {
    spacing: 10
    anchors.verticalCenter: parent.verticalCenter

    Text {
        text: item.data.name + " (" + item.data.email + ")"
        font.bold: index === listView.currentIndex
    }
}

//...

Button {
    text: "Update"
    enabled: selectedIndex >= 0
    onClicked: {
        let item = clientModel.get(selectedIndex)
        let current = item.data
        current.name = nameInput.text
        current.email = emailInput.text
        item.data = current
        nameInput.text = ""
        emailInput.text = ""
        selectedIndex = -1
    }
}
```

---