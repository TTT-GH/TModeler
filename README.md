# TModeler

TModeler est une bibliothèque ORM (Object-Relational Mapping) multi-langages permettant de gérer des modèles de données de manière simple et efficace. 
Le projet est actuellement disponible en C++, Java et Python.

## Langages disponibles

- **C++** : [Voir la documentation C++](cpp/README.md)
- **Java** : [Voir la documentation Java](java/README.md)
- **Python** : [Voir la documentation Python](python/README.md)

## Fonctionnalités

- **Gestion des modèles de données** : Création, mise à jour, suppression, et récupération des modèles.
- **Observateurs multithread** : Permet de suivre les changements dans les données sur différents threads.
- **Filtres, jointures et agrégations** : Applique des filtres complexes sur les données, joint des modèles et effectue des agrégations.
- **Héritage de modèles et champs personnalisés** : Crée des modèles personnalisés avec des champs hérités ou nouveaux.
  
## Tests

```cpp
class Person : public TModel<Person> {
    TextField name;
    TextField design;
    FloatField ratio;
    BoolField empty;
    TimeField dob = init<TimeField>().format(TF::DATE);
    TimeField update_at = init<TimeField>().format(TF::DATE_TIME);
    ModelField<Person> mother = init<ModelField<Person>>().onDelete(TF::CASCADE);
    ModelField<Familly> familly = init<ModelField<Familly>>().onDelete(TF::CASCADE);
    ListField<Person> friends = init<ListField<Person>>();
};

Person person;
person.id = 100;
person.name = "Lambda";
person.design = "Admin";
person.meta = json;
person.ratio = 0.5;
person.empty = false;
person.dob = "2000-11-07";
person.save();

Tlist<Client, Cmd> join = Client::tms.with<Cmd>(cl, cm)
    .join(JoinType::LEFT).filter(cm.client == cl._id)       // jointure à gauche : tous les clients même sans commande
    .filter(cm.client == nullptr)                           // conserve uniquement les clients sans commande
    .order(-cl.dob)                                         // trie par date de naissance décroissante (plus jeune en premier)
    .group(cl.country)                                      // regroupe les clients par pays
    .filter(cl._id.count() >= 5);                           // filtre les pays avec au moins 5 clients sans commande
auto client = join.select<Client>().first();
Log(client.data());
```

Cette requête affiche donc :
- Le plus jeune client (par pays),
- parmi les pays ayant au moins 5 clients n’ayant jamais commandé.



# **TModeler** : [Voir la documentation](cpp/README.md)