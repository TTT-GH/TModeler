# TModeler

TModeler is a multi-language ORM (Object-Relational Mapping) library that allows managing data models in a simple and efficient way. 
The project is currently available in C++, Java and Python.

## Available Languages

- **C++** : [See C++ documentation](cpp/README.md)
- **Java** : [See Java documentation](java/README.md)
- **Python** : [See Python documentation](python/README.md)

## Features

- **Data model management** : Create, update, delete, and retrieve models.
- **Multithreaded observers** : Allows tracking changes in data across different threads.
- **Filters, joins and aggregations** : Apply complex filters on data, join models and perform aggregations.
- **Model inheritance and custom fields** : Create custom models with inherited or new fields.
  
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
    .join(JoinType::LEFT).filter(cm.client == cl._id)       // left join: all clients even without orders
    .filter(cm.client == nullptr)                           // keep only clients without orders
    .order(-cl.dob)                                         // sort by date of birth descending (youngest first)
    .group(cl.country)                                      // group clients by country
    .filter(cl._id.count() >= 5);                           // filter countries with at least 5 clients without orders
auto client = join.select<Client>().first();
Log(client.data());
```

This query therefore displays:
- The youngest client (per country),
- among the countries with at least 5 clients who have never placed an order.



# **TModeler** : [See documentation](cpp/README.md)
