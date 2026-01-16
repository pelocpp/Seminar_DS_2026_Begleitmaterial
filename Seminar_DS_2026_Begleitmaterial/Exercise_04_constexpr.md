# Aufgabe: Maximum dreier Zahlen

---

[Zurück](../Readme.md)

---

### Voraussetzungen: `constexpr`, Lambdas und teilweise Templates

Schreiben Sie eine Funktion `maximum`, die zu drei vorgegebenen Zahlen die größte Zahl ermittelt und als Rückgabewert zurückliefert.
Natürlich kommen hier `if`-Anweisungen ins Spiel, es gibt aber durchaus mehrere Möglichkeiten, das Ziel zu erreichen.

Die `maximum`-Funktion soll für alle elementaren Datentypen, die man vergleichen kann, aufrufbar sein.
Inwieweit beim Aufruf der `maximum`-Funktion alle drei Parameter denselben Datentyp haben müssen
oder &bdquo;geringfügige&rdquo; Unterschiede erlaubt sind,
ist Ihrer Entscheidung überlassen.

Die Funktion soll den Qualifizierer `constexpr` besitzen.
Überprüfen Sie Ihre Realisierung darauf hin, dass `maximum` bei konstanten Argumenten oder bei mit `constexpr` deklarierten Variablen
das Ergebnis bereits zur Übersetzungszeit berechnet.

*Beispiel*:

```cpp
constexpr auto result = maximum(1, 2, 3);
```

Aus dem Maschinencode des Programms können wir ablesen,
dass der Übersetzer den Wert 3 bereits berechnet hat:

```
constexpr auto result = maximum(1, 2, 3);
00007FF6CEF273CC  mov dword ptr [result1], 3   // <= value 3 resides in machine code  
```

### Zusatzfrage:

Welche unterschiedlichen Möglichkeiten gibt es in der Deklaration der Schnittstelle der `maximum`-Funktion?
Diskutieren bzw. erläutern Sie die Unterschiede der jeweiligen Deklaration.

---
