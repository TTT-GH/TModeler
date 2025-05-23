# TModeler Python

## Description

TModeler est une bibliothèque ORM (Object-Relational Mapping) pour Java qui permet de gérer les modèles de données de manière simple et efficace. Elle offre des fonctionnalités telles que la gestion des données, les observateurs, les filtres complexes, les jointures, les agrégations, et l'héritage des modèles de données.

## Installation

### Prérequis

### Dépendances

### Compilation

## 📦 Tms<T> - TTT Model System

Un système générique de gestion de modèles orienté données, permettant :

- CRUD complet
- Observations inter-thread et inter-modulaires
- Filtres puissants
- Jointures inter-modèles
- Groupes et agrégations
- Utilitaires de manipulation directe

---

## 🧪 Init

To run the unit tests for TModeler C++, make sure you initialize the ORM properly at the beginning of your test application. This step is essential for configuring the underlying databases and loading the appropriate data models :

```Java
// App.java
// Initialize the TModeler ORM with one or more databases.
TModeler.initialize(this, new TModelerCallback() {
    @Override
    public List<Tdb> onLoadBases(List<Tdb> bases) {
        bases.add(Tdb.connect("FirstTdb"));
        return bases;
    }
    @Override
    public String onLoadServerHost() {
        return "http://192.168.236.174:8000";
    }
    @Override
    public String onLoadBaseUrl() { return "api";}
    @Override
    public String onLoadVersion() { return "v1";}
    @Override
    public String onLoadMediaHost() { return "media";}
    @Override
    public String onLoadMediaTmpDir() { return "tmp";}

    @Override
    public String onLoadMediaDir(String dir) {
        return super.onLoadMediaDir(dir);
    }

    @Override
    public void onServerAccessChange(boolean connected) {}
    @Override
    public void onPrepareSync() {
        Chanel.tms.commit();
        ChanelContext.tms.commit();
        ChanelEditor.tms.commit();
        ChanelType.tms.commit();
        //
        Messager.tms.commit();
        MessagerRole.tms.commit();
        //
        Message.tms.commit();
        //
        Messaging.tms.commit();
        MessagingMember.tms.commit();
        MessagingType.tms.commit();
    }
});
```

🧪 This initialization is required before using any TModeler models, even in tests.

---

## 🧬 Model Structure and Relations

All models inherit from TModel<T> and are declared using the TM_SCHEMA macro. Each field supports fluent configuration, such as primaryKey(), notNull(), autoIncrement(), etc.

Example: Complete Model with All Field Types
```Java
public class Message extends TModel<Message> {
    public MField<Messaging> messaging = new MField<Messaging>(Messaging.class);
    public MField<Messager> creator = new MField<Messager>(Messager.class);
    public TextField content = new TextField();
    public GeoField loc = new GeoField();


    public static final TMSerial<Message> serial = new TMSerial<Message>(Message.class);
    public static final TMS<Message> tms = initialize(Message.class, serial);
}
```

Example: Relations Between Models :
```Java
public class TMedia extends TModel<TMedia> {
    public CharField description = new CharField(255);
    public ImageField image = new ImageField();
    public ImageField file = new ImageField();


    public static final TMSerial<TMedia> serial = new TMSerial<TMedia>(TMedia.class);//With custom Serial
    public static final TMS<TMedia> tms = initialize(TMedia.class, serial);//With custom Serial
}

public class Messaging extends TModel<Messaging> {
    public CharField name = new CharField(100);
    public MField<MessagingType> typ = new MField<MessagingType>(MessagingType.class);
    public LField<TMedia> photos = new LField<TMedia>(TMedia.class);
    public MField<Message> message = new MField<Message>(Message.class);


    public static final TMSerial<Messaging> serial = new TMSerial<Messaging>(Messaging.class);
    public static final TMS<Messaging> tms = initialize(Messaging.class, serial);
}
```

Example: Advanced Model with Inheritance and Nested Models :
```Java
public class Chanel extends TModel<Chanel> {
    public CharField name = new CharField(100);
    public MField<ChanelContext> context = new MField<ChanelContext>(ChanelContext.class);
    public MField<ChanelType> typ = new MField<ChanelType>(ChanelType.class);
    public LField<Messaging> pv_messagings = new LField<Messaging>(Messaging.class);
    public LField<Messaging> pb_messagings = new LField<Messaging>(Messaging.class);
    public LField<Chanel> sub_chanels = new LField<Chanel>(Chanel.class);


    public static final TMSerial<Chanel> serial = new TMSerial<Chanel>(Chanel.class);
    public static final TMS<Chanel> tms = initialize(Chanel.class, serial);
}
```

💡 All object-oriented principles apply to models and their fields: encapsulation, inheritance, composition, etc.

---

## 💡 CRUD Operations & Usage

The framework provides a powerful and expressive ORM for handling database entities through model instances. Each model type (Client, Product, Cmd, etc.) provides a static tms manager for batch operations and persistence.

Model Lifecycle: Create, Read, Update, Delete :

```kotlin
val messager1 = Messager().init().apply {
    name.set("Olivier Tambo $i")
    photo.set(TMedia().init().apply { description.set("pp") })
}

val messager2 = Messager().init().apply { name.set("Lambda $i") }
val messager3 = Messager().init().apply { name.set("Lambda 2 $i") }.also { it.save() }
val messager4 = Messager().init().apply { name.set("Lambda 3 $i") }.also { it.save() }

val chanel1 = Chanel().init().apply {
    name.set("MAIN Chanel $i")
    context.set(ChanelContext.get(""))
    typ.set(ChanelType.mainType())
    save()
}

val chanel2 = Chanel().init().apply {
    name.set("LAMBDA Chanel $i")
    context.set(ChanelContext.get(""))
    typ.set(ChanelType.lambdaType())
    save()
}


listOf(
    Triple(MessagerRole.creator(), messager3, messaging2),
    Triple(MessagerRole.admin(), messager4, messaging2),
    Triple(MessagerRole.messager(), messager1, messaging2),
    Triple(MessagerRole.messager(), messager2, messaging2)
).map { (role, user, messaging) ->
    MessagingMember().init().apply {
        this.role.set(role)
        this.messager.set(user)
        this.messaging.set(messaging)
        save()
    }
}

listOf("Hello!!!", "How!!!", "fine!!!", "cool!!!").forEachIndexed { index, text ->
    Message().init().apply {
        content.set("$text $i")
        loc.set(LatLng(3.3265, 9.32658))
        creator.set(listOf(messager1, messager2, messager3, messager4)[index])
        messaging.set(messaging2)
        save()
    }
}
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

🔸 Simple Filters

```kotlin
messager = Messager.tms.all()
    .filter { it.name.get().uppercase().contains("Lambda") }
    .first()
```

🔸 More Examples

```kotlin
// Complex filters
myChanel = ChanelEditor.tms.all()
.filter {
    it.messager == messager &&
    it.chanel.get().context == ChanelContext.get("") &&
    it.role == MessagerRole.creator()
}
.first().chanel.get()
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

## Communication UI – Test ViewModel (Jetpack Compose)

This example demonstrates how to connect a `TViewModel` (ClientViewModel) with a Jetpack Compose UI to manage a list of clients. The goal is to test reading and writing operations through the model and reflect changes in the user interface.

### Java Model Definition
```java

```

### Jetpack Compose UI (Read & Write Test)
```kotlin

```

---