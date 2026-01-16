# Aufgabe: Verwendung von Smart Pointern für Membervariablen einer Klasse

---

[Zurück](../Readme.md)

---

### Voraussetzungen: `std::unique_ptr<>` und `std::shared_ptr<>`

In dieser Aufgabe gehen wir auf den Gebrauch eines Smartpointers als Membervariable einer Klasse ein.

Schreiben Sie eine Klasse `MyString`,
die die ersten Schritte einer Realisierung für eine Zeichenketten-Klasse darstellen könnte.
Die Zeichen sind auf der Halde (*Heap*) abzulegen,
ihre Anzahl soll prinzipiell beliebig groß sein dürfen.

*Abbildung* 1 zeigt ein `MyString`-Objekt, das die Zeichenkette `ABCDEFGHIJ`
der Länge 10 enthält.
Die Variable `m_length` ist vom Typ `std::size_t`, 
der Typ der Variablen `m_string` ist bewusst offen gehalten.

Betrachten Sie genau, welche Anteile eines `MyString`-Objekts auf dem Stack
und welche auf dem Heap liegen:

<img src="cpp_exercise_my_string.svg" width="600" />

*Abbildung* 1: Aufteilung eines `MyString`-Objekts auf die beiden Speicherbereiche *Stack* und *Heap*.

## `std::shared_ptr`- oder `std::unique_ptr`-Objekt?

Der Gebrauch von `new` und `delete` ist in einem Modern C++ Programm nicht mehr angesagt.
Wir greifen deshalb auf eine *Smart Pointer* Klasse zurück,
um die Adresse der Zeichen auf dem Heap zu verwalten.

Es ist sorgfältig zu überlegen und zu begründen,
ob sich hierfür ein `std::shared_ptr`- oder ein `std::unique_ptr`-Objekt besser eignet.

*Hinweis*:
Technisch gesehen ist es möglich, mit beiden Klassen eine `MyString`-Realisierung
auf die Beine zu stellen. Bei näherem Hinsehen sollte jedoch deutlich werden,
dass auf Grund der Anforderungen an die `MyString`-Klasse nur eine der beiden Klassen in Betracht kommt.

## Minimaler Funktionsumfang der Klasse `MyString`

Für eine minimale Ausstattung der `MyString`-Klasse realisieren wir

  * einen benutzerdefinierten Konstruktor, der eine `const char*` Zeichenkette entgegennimmt,
  deren Zeichen im `MyString`-Objekt aufzunehmen sind,
  * eine `print`-Methode zur Ausgabe der Zeichen in der Konsole,
  * eine `length`-Methode, die die Anzahl der Zeichen zurückliefert und
  * einen Index-Operator, um auf einzelne Zeichen in der Zeichenkette lesend und schreibend zugreifen zu können.


| Name | Beschreibung |
|:-|:-|
| `MyString(const char* s)` | Benutzerdefinierter Konstruktor &ndash; die Zeichen des Parameters `s` werden in das Objekt aufgenommen. |
| `void print()` | Ausgabe der Zeichenkette auf der Konsole. |
| `std::size_t length()` | Liefert die Anzahl der Zeichen zurück. |
| `char& operator[] (int index);` | Lesender oder schreibender Zugriff auf ein einzelnes Zeichen der Zeichenkette. |

*Tabelle* 1: Minimaler Funktionsumfang der Klasse `MyString`.

Nun kommen wir auf den zweiten Schwerpunkt der Aufgabe zu sprechen:

## Regelwerk Rule-of-Zero oder Rule-of-Three?

Es ist das *Rule-of-Zero* oder *Rule-of-Three* Regelwerk zu betrachten und in seiner Umsetzung
in der Klasse `MyString` zu begründen. 

1. Frage:<br />
Kann man das *Rule-of-Zero* Regelwerk in Anspruch nehmen?
 
In diesem Fall wäre folglich keine der drei fraglichen Methoden/Operatoren Kopierkonstruktor, Zuweisungsoperator und Destruktor zu realisieren.
Verifizieren Sie, ob in Ihrer Realisierung der `MyString`-Klasse diese drei Methoden/Operatoren zur Laufzeit zur Verfügung stehen?
Welche Ergebnisse erhalten Sie bei der Ausführung?


2. Frage:<br />
Wenn die Antwort auf die erste Frage &bdquo;Nein&rdquo; lautet,
wie sieht dann eine Realisierung dieser drei Methoden/Operatoren aus?
Testen Sie die Implementierung mit entsprechenden Beispielen.

## Klasse `MyString` und die Verschiebe-Semantik: Regelwerk Rule-of-Five

Neben dem Kopieren lassen sich ab C++ 11 Objekte auch verschieben.
Welche Methoden/Operatoren muss die Klasse `MyString` bereitstellen,
so dass deren Objekte auch verschoben werden können.

Zeigen Sie das Verschieben an entsprechenden Beispielen auf.

---
