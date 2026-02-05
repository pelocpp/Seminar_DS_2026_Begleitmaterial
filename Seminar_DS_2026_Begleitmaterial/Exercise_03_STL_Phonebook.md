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
  * Entwicklung einer Anwendung mit der STL (*Standard Template Library*).
  * Anwendung eines sequentiellen oder assoziativen STL-Containers (`std::vector` oder `std::unordered_map`).
  * Anwendung elementarer STL Algorithmen wie z. B. `std::find_if` und `std::for_each`.
  * Einsatz von Lambdas.
  * Gebrauch von Iteratoren.

Im Großen und Ganzen kann man sagen, dass die Funktionsweise der Methoden der Klasse `Phonebook` selbsterklärend ist.
Weitere Details zur Definition ihrer Methoden entnehmen Sie bitte *Tabelle* 1:

| Methode        | Schnittstelle und Beschreibung |
|:-------------- |:-----------------------------------------|
| `size` | `size_t size() const;`<br/>Liefert die Anzahl der Einträge im Telefonbuch zurück. |
| `insert` | `bool insert(const std::string& first, const std::string& last, size_t number);`<br/>Fügt einen Eintrag, bestehend aus den Werten Vorname (`const std::string& first`), Nachname (`const std::string& last`) und Telefonnummer (`std::size_t number`), in das Telefonbuch ein. Ist der Name (Vor- und Nachname) im Telefonbuch schon enthalten, liefert die Funktion `false` zurück, andernfalls `true`. |
| `update` | `bool update(const std::string& first, const std::string& last, size_t number);`<br/>Ändert einen Eintrag im Telefonbuch. Zu vorgegebenem Namen (`const std::string& first` und `const std::string& last`) wird eine neue Nummer im Telefonbuch eingetragen. Sind die Angaben des Namens falsch, liefert die Funktion `false` zurück, andernfalls `true`. |
| `search` | `std::optional<std::size_t> search(const std::string& first, const std::string& last) const;`<br/>Sucht einen Eintrag im Telefonbuch. Sind die Namensangaben korrekt, liefert die Funktion die Telefonnummer in einem `std::optional<std::size_t>`-Objekt zurück, andernfalls wird `std::nullopt` zurückgegeben. |
| `remove` | `bool remove(const std::string& first, const std::string& last);`<br/>Entfernt einen Eintrag im Telefonbuch. Sind die Namensangaben korrekt, liefert die Funktion `true` zurück, andernfalls `false`. |
| `contains` | `bool contains(const std::string& first, const std::string& last) const;`<br/>Liefert die Information zurück, ob ein bestimmter Eintrag (Vor- und Nachname) im Telefonbuch vorhanden ist oder nicht. |
| `print` | `void print() const;`<br/>Gibt den Inhalt des Telefonbuchs in der Konsole aus. |

*Tabelle* 1: Beschreibung der öffentlichen Schnittstelle einer Telefonbuch-Realisierung.


*Hinweis*:<br />
Bei Erstellung der Klasse `Phonebook` im Kontext des Unit Test Frameworks sehen die Signaturen
der Methoden so aus (Beachten Sie den Gebrauch der Klassen `SA_String` und `SA_Integer`):

```cpp
class Phonebook
{
    size_t size();
    bool insert(const SA_String& first, const SA_String& last, SA_Integer number);
    bool search_legacy(const SA_String& first, const SA_String& last, SA_Integer& number);
    std::optional<SA_Integer> search_optional(const SA_String& first, const SA_String& last);
    std::optional<std::unique_ptr<SA_Integer>> search_optional_ptr (const SA_String& first, const SA_String& last);
    bool remove(const SA_String& first, const SA_String& last);
    bool contains(const SA_String& first, const SA_String& last); 
    void print();
};
```


Es folgen einige Hinweise zur Realisierung:

Die Klasse `std::vector` ist der STL-Allzweck Container für eine Ansammlung von Daten,
deren Umfang sich zur Laufzeit eines Programms ändern kann.

Wie müssen Sie ein konkretes `std::vector`-Objekt bzw. eine Klasse `Entry` definieren,
wenn wir pro Eintrag die drei Informationen Vorname (`const std::string& first`), Nachname (`const std::string& last`) und Telefonnummer (`std::size_t number`)
im Telefonbuch ablegen wollen? Es bieten sich für Klasse `Entry` mehrere Möglichkeiten zur Realisierung an!

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

<img src="cpp_hash_table_phonebook.svg" width="650">

*Abbildung* 2. Struktureller Aufbau einer Hashtabelle (hier: Hash-Kollision durch separate Verkettung gelöst).


## Integration in den Unit Test Framework

Bei Erstellung der Lösung im Kontext des Unit Test Frameworks könnte eine Struktur 
der Aufgabe so aussehen:

```cpp
TEST_CLASS(SchulungModernCpp_Test)
{
    // ===================================================================
    // Übung Klasse Phonebook
    //====================================================================

    class Phonebook
    {
        size_t size();
        bool insert(const SA_String& first, const SA_String& last, SA_Integer number);
        bool search_legacy(const SA_String& first, const SA_String& last, SA_Integer& number);
        std::optional<SA_Integer> search_optional(const SA_String& first, const SA_String& last);
        std::optional<std::unique_ptr<SA_Integer>> search_optional_ptr (const SA_String& first, const SA_String& last);
        bool remove(const SA_String& first, const SA_String& last);
        bool contains(const SA_String& first, const SA_String& last); 
        void print();
    };
    
    TEST_METHOD(Übung3) {
        // TBD
    }
}
```

---

[Lösung](Exercise_03_STL_Phonebook.cpp)

---

[Zurück](../Readme.md)

---
