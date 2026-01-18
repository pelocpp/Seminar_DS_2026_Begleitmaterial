# Aufgabe: Die STL und eine Klasse `Phonebook`

---

[Zurück](../Readme.md)

---

### Voraussetzungen: Grundlagen der STL

## Einführung

Schreiben Sie eine Klasse `Phonebook`, die die grundlegende Funktionalität eines Telefonbuchs realisiert.
Eine Person hat einen Vor- und Nachnamen (`std::string`) und besitzt eine Telefonnummer (`std::size_t`).
Das Telefonbuch unterstützt das Hinzufügen, das Nachschauen, das Entfernen und das Ausgeben aller Einträge.

## 1. Teilaufgabe: Erste Realisierung einer Klasse `Phonebook`

Folgende Aspekte werden betrachtet:
  * Entwicklung einer Anwendung mit der STL (Standard Template Library).
  * Anwendung eines sequentiellen oder assoziativen STL-Containers (`std::vector` oder `std::unordered_map`).
  * Anwendung elementarer STL Algorithmen wie z. B. `std::find_if` und `std::for_each`.
  * Einsatz von Lambdas.
  * Gebrauch von Iteratoren.

Im Großen und Ganzen kann man sagen, dass die Funktionsweise der Methoden der Klasse `Phonebook` selbsterklärend ist.
Weitere Details zur Definition dieser Methoden entnehmen Sie bitte *Tabelle* 1:

| Methode        | Schnittstelle und Beschreibung |
|:-------------- |:-----------------------------------------|
| `size` | `size_t size();`<br/>Liefert die Anzahl der Einträge im Telefonbuch zurück. |
| `insert` | `bool insert(const std::string& first, const std::string& last, size_t number);`<br/>Fügt einen Eintrag, bestehend aus den Werten *Vorname*, *Nachname* und Telefonnummer, in das Telefonbuch ein. Ist der Name (*Vorname* und *Nachname*) im Telefonbuch schon enthalten, liefert die Funktion `false` zurück, andernfalls `true`. |
| `update` | `bool update(const std::string& first, const std::string& last, size_t number);`<br/>Ändert einen Eintrag im Telefonbuch. Zu vorgegebenem Namen (*Vorname* und *Nachname*) wird eine neue Nummer im Telefonbuch eingetragen. Sind die Angaben des Namens falsch, liefert die Funktion `false` zurück, andernfalls `true`. |
| `search` | `std::optional<std::size_t> search(const std::string& first, const std::string& last);`<br/>Sucht einen Eintrag im Telefonbuch. Zu vorgegebenem Namen (*Vorname* und *Nachname*) wird die Telefonnummer (im dritten Parameter `number`) zurückgegeben. Sind die Namensangaben korrekt, liefert die Funktion die Telefonnummer in einem `std::optional<std::size_t>`-Objekt zurück, andernfalls wird `std::nullopt` zurückgegeben. |
| `remove` | `bool remove(const std::string& first, const std::string& last);`<br/>Entfernt einen Eintrag (*Vorname* und *Nachname*) im Telefonbuch. |
| `contains` | `bool contains(const std::string& first, const std::string& last);`<br/>Liefert die Information zurück, ob ein bestimmter Eintrag (*Vorname* und *Nachname*) im Telefonbuch vorhanden ist oder nicht. |
| `print` | `void print();`<br/>Gibt den Inhalt des Telefonbuchs in der Konsole aus. |

*Tabelle* 1: Beschreibung der öffentlichen Schnittstelle einer Telefonbuch-Realisierung.

Es folgen einige Hinweise zur Realisierung:

Die Klasse `std::vector` ist der STL-Allzweck Container für eine Ansammlung von Daten,
deren Umfang sich zur Laufzeit eines Programms ändern kann.

Wie müssen Sie ein konkretes `std::vector`-Objekt definieren,
wenn wir pro Eintrag die drei Informationen *Vorname* (`std::string`), *Nachname* (`std::string`) und *Telefonnummer* (`std::size_t`)
im Telefonbuch ablegen wollen? Es bieten sich mehrere Möglichkeiten zur Realisierung an!

<img src="cpp_vector_phonebook.svg" width="400">

*Abbildung* 1. Struktureller Aufbau eines `std::vector`-Objekts mit mehreren Telefonbucheinträgen.

Bilden Sie die in *Tabelle* 1 geforderten Methoden der öffentlichen Schnittstelle einer `PhoneBook`-Klasse
geeignet auf STL-Algorithmen ab.
Denkbar wäre zum Beispiel:

  * Methode `search` &Rightarrow; `std::find_if`
  * Methode `print` &Rightarrow; `std::for_each`


## 2. Teilaufgabe: Eine verbesserte Realisierung auf Basis des STL-Containers `std::unordered_map`

In einer eher einfachen Realisierung wurden die Einträge des Telefonbuchs wie ein Teilaufgabe 1 angedacht
in einem `std::vector`-Objekt abgelegt.
Überlegen Sie, ob diese Container-Klasse ideal für den vorliegenden Anwendungsfall ist.
Nehmen Sie eine zweite Realisierung vor, die auf einem `std::unordered_map`-Container fußt.

<img src="cpp_hash_table_phonebook.svg" width="600">

*Abbildung* 2. Struktureller Aufbau einer Hashtabelle (hier: Hash-Kollision durch separate Verkettung gelöst).


---

[Lösung](Exercise_03_STL_Phonebook.cpp)

---

[Zurück](../Readme.md)

---
