# Aufgabe: Löschen aller ungeraden Elemente in einem sequenziellen STL-Container

---

[Zurück](../Readme.md)

---

### Voraussetzungen: STL-Container `std::vector<int>`, Methode `erase`, STL-Algorithmus `std::remove_if`

## *Teilaufgabe* 1

Wir studieren in dieser Aufgabe das folgende kleine Programm
zum Testen der `erase`-Methode an einem `std::vector<int>`-Objekt.
Es sollen alle geraden Elemente eines `std::vector<int>`-Objekts entfernt werden:

```cpp
01: void test ()
02: {
03:     std::vector<int> vec{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
04: 
05:     // erase all even numbers
06:     for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it)
07:     {
08:         if (*it % 2 == 0) {
09:             vec.erase(it);
10:         }
11:     }
12: }
```

Welchen Inhalt hat der STL-Container `vec` Ihrer Meinung nach am Ende der `test`-Funktion?
Bringen Sie das Programm zum Laufen. Geben Sie den Inhalt des `std::vector<int>`-Containers am Ende der `test`-Funktion
in der Konsole aus. **Welche Beobachtungen machen Sie bei der Ausführung des Programms?**

## *Teilaufgabe* 2

Welche Änderungen sind an der `test`-Funktion notwendig, so dass die Ausführung korrekt verläuft.
Es ist durchaus möglich, die `for`-Wiederholungsschleife beizubehalten.
Was fällt Ihnen an diesem Beispiel betrachtet zum Thema &bdquo;ungültige Iteratoren&rdquo; ein?

## *Teilaufgabe* 3

Für die Aufgabenstellung eignet sich auch eine Verwendung des STL-Algorithmus `std::remove_if`.
Schreiben Sie die `test`-Funktion so um, dass der STL-Algorithmus `std::remove_if` zum Einsatz kommt.

## *Teilaufgabe* 4

Mit Teilaufgabe 2 und 3 stehen sich nun zwei Lösungen gegenüber:

  * Lösung mit einer `for`-Kontrollstruktur und wiederholtem Aufruf der `erase`-Methode.
  * Lösung mit STL-Algorithmus `std::remove_if` und einmaligem Aufruf der `erase`-Methode.

Schreiben Sie ein kleines Testprogramm, in dem Sie die beiden Realisierungen in einer Wiederholungsschleife aufrufen.
Zum Messen der Zeit verwenden Sie eine Klasse `ScopedTimer`,
deren Quellcode Sie [hier](https://github.com/pelocpp/cpp_modern/blob/master/GeneralSnippets/ScopedTimer/ScopedTimer.h) finden.
Welche Beobachtungen können Sie in Bezug auf die Ausführungszeiten des Vergleichs machen?

## *Teilaufgabe* 5

Verwenden Sie für die bisher erstellten Lösungen an Stelle des `int`-Datentyps den projekt-spezifischen
Datentyp `SA_Integer`. Vergleichen Sie noch einmal die Ausführungszeiten des Programms.

---

[Lösung](Exercise_02_STL_Erase_Remove.cpp)

---

[Zurück](../Readme.md)

---
