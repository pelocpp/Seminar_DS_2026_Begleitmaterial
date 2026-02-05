# Aufgabe: Rückgabe eines `std::unique_ptr<>`-Objekts aus einer Funktion

---

[Zurück](../Readme.md)

---

### Voraussetzungen: `std::unique_ptr<>`, bei Bedarf `std::tuple<>` und `std::optional`

## Einführung

In dieser Aufgabe wollen wir ein `std::unique_ptr<>`-Objekt in einem Unterprogramm (Funktion, Methode) anlegen.
Es sollen verschiedene Wege aufgezeigt und bewertet werden, wie diese `std::unique_ptr<>`-Variable aus dem Unterprogramm
zurückgegeben werden kann.

Da man meistens auch andere Werte zurückgeben möchte, gibt es mehrere gängige Vorgehensweisen.
Im Folgenden finden Sie die wichtigsten Methoden mit Hinweisen, wann welche anzuwenden ist.

Schreiben Sie eine Funktion `splitToDigits`, die eine ganze Zahl in ihre einzelnen Ziffern zerlegt.
Die Ziffern der Zahl sind der Reihe nach in einem dynamisch allokierten Speicherblock abzulegen.
Offensichtlich muss die Funktion neben der Zerlegung der Zahl auch die Anzahl der einzelnen Ziffern berechnen,
um so die Länge des dynamisch zu allokierenden Speichbereichs zu kennen.

Natürlich wird der Speicherblock für die einzelnen Ziffern mit dem `new`-Operator angelegt,
die Adresse ist aber &ndash; ganz konform zu Modern C++ &ndash; durch ein `std::unique_ptr<>`-Objekt zu verwalten.

  * Welche Möglichkeiten gibt es, das `std::unique_ptr<>`-Objekt aus der Funktion zurückzugeben?

  * Welche Vorteile hat es, mit einem `std::unique_ptr<std::size_t[]>`-Objekt anstatt mit einem `std::size_t*`-Zeiger zu arbeiten?
 
## Weitere Hinweise

Beachten Sie generell in Ihrer Realisierung, dass neben dem Zeiger auch die Anzahl der Ziffern in einer zweiten Variablen zurückgegeben werden soll.
Und zu guter Letzt soll auch noch eine boolsche Variable zurückgeliefert werden, die angibt,
ob die Funktion `splitToDigits` in ihrer Funktionsweise korrekt gearbeitet hat oder nicht.
Die Berechnung des Ergebnisses stellt hier weniger das Problem dar,
aber die interne Speicherplatzanforderung mit `new` muss nicht immer funktionieren.
Ein Wert von `true` bedeutet, dass der Speicherbereich und die Längenangabe eine korrekte Zerlegung der Zahl darstellen,
in allen anderen Fällen wird `false` zurückgeben.

## Mehrere Möglichkeiten der Umsetzung

Um Ihnen eine kleine Hilfestellung zu geben, folgen hier einige Hinweise für die Spezifikation der `splitToDigits`-Funktion:

  * Liefere direkt ein `std::unique_ptr<>`-Objekt zurück (Verschiebe-Semantik oder *Copy-Move-Elision* hinter den Kulissen).
  * Oder: Liefere eine Strukturvariable zurück (klassische Herangehensweise, im Prinzip der zu favorisierende Ansatz).
  * Oder: Liefere ein `std::tuple`-Objekt zurück (moderne, leichtgewichtige Herangehensweise, Lesbarkeit nicht ganz so gut).
  * Oder: Verwende Rückgabewert und eine Menge an *Out*-Parametern (*Call-by-Reference* &ndash; ähnlich wie die Variante mit Strukturvariablen zu bewerten).
  * Oder: Liefere ein `std::pair` zurück (wenn es kompakt sein soll und man mit zwei Werten auskommt).
  * Oder: Rückgabe mit Hilfe von `std::optional` und `std::pair` (interessant, wenn nicht immer ein Ergebnis vorliegen muss).

*Beispiel*:

Wählt man für die Umsetzung den Weg mit der Rückgabe einer Strukturvariable,
dann könnte das Hauptprogramm so aussehen:

```cpp
01: struct DigitsSplitting
02: {
03:     // TBD
04: };
05: 
06: void test()
07: {
08:     DigitsSplitting splitting{ splitToDigits(12345) };
09: 
10:     if (splitting.m_success) {
11: 
12:         // extract elements of struct DigitsSplitting
13:     }
14: }
```

*Ausgabe*:

```
Splitting of 12345:
0: 1
1: 2
2: 3
3: 4
4: 5
```

Wählt man hingegen für die Umsetzung den Weg mit der Rückgabe eines `bool`-Werts
und übergibt für alle weiteren Rückgabeparameter Referenzen an die `splitToDigits`-Funktion,
so könnte der Testrahmen wie folgt aussehen:


```cpp
01: void test()
02: {
03:     // pass all parameters by reference
04:     std::size_t number{ 12345 };
05:     std::size_t count{};
06:     std::unique_ptr<std::size_t[]> buffer{};
07: 
08:     bool success{ splitToDigitsByRef(number, buffer, count) };
09: 
10:     if (success) {
11:         // print results to the console
12:     }
13: }
```

## Integration in den Unit Test Framework

Bei Erstellung der Lösung im Kontext des Unit Test Frameworks könnte eine Struktur 
der Aufgabe so aussehen:

```cpp
TEST_CLASS(SchulungModernCpp_Test)
{
    // ===================================================================
    // Übung Rückgabe eines `std::unique_ptr<>`-Objekts aus einer Funktion
    //====================================================================

    /** Rückgabewert **/ splitToDigitsByRef(/** Parameter **/)
    {
        // Implementation
    }
    
    TEST_METHOD(Übung5)
    {
        // Passe den Test an den von dir gewählten Methodenkopf an.
        size_t number{ 54321 };
        bool success{ splitToDigitsByRef(/** Argumente **/) };
        if (success) {
            std::span<size_t> digits{ /** Input für Span**/ };
            std::cout << std::format("Splitting of {}:\n", number);
            for (size_t i{}; auto digit : digits) {
                std::cout << std::format("{}: {}\n", i, digit);
                ++i;
            }
        }
    }
}
```

---

[Lösung](Exercise_05_Returning_UniquePtr.cpp)

---

[Zurück](../Readme.md)

---
