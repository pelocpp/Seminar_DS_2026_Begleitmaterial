# Aufgabe: Konstante Farben

---

[Zurück](../Readme.md)

---

### Voraussetzungen: `constexpr`

## Einführung

Im Windows SDK (*System Development Kit* von Windows) gibt es die folgende Definition eines `RGB`-Makros (Datei *wingdi.h*):

```cpp
#define RGB(r,g,b)  ((COLORREF)(((BYTE)(r)|((WORD)((BYTE)(g))<<8))|(((DWORD)(BYTE)(b))<<16)))
```

Mit diesem Makro kann man mit drei primären Farben &ndash; Rot, Grün und Blau &ndash; beliebige Farben erzeugen.
Da die maximale Intensität jeder der drei Grundfarben 255 ist, genügt ein Doppelwort zum Abspeichern einer Farbe.
Hier wäre sogar noch Platz für einen vierten Kanal, den Alpha-Kanal, den wir der Einfachheit halber
in unsere Betrachtungen nicht mit einbeziehen.

Für den Datentyp einer Farbe gibt es in Windows die folgende Datentyp Definition:

```cpp
typedef DWORD COLORREF;
```

Jetzt fehlen noch die Definitionen für die verwendeten Datentypen wie z. B. `BYTE` oder `DWORD `,
die wir in der Datei *windef.h* finden.
Ein (kleiner) Ausschnitt aus dieser Datei sieht so aus:


```cpp
typedef unsigned char       BYTE;
typedef unsigned short      WORD;
typedef unsigned long       DWORD;
...
```

Damit lassen sich nun in nativen Windows Anwendungen Farben auf folgende Weise definieren:

```cpp
COLORREF red       = RGB(255, 0, 0);
COLORREF lightBlue = RGB(173, 216, 230);
COLORREF aqua      = RGB(0, 255, 255);
COLORREF darkGreen = RGB(1, 50, 32);
```

## 1. Teilaufgabe

Auch wenn es Microsoft (vor vielen Jahren) in seinen Implementierungen so gemacht hat,
muss das nicht heißen, dass dies eine gute Idee war.
Testen Sie folgende, leicht alternativ, formulierten Farbdefinitionen in einem kleinen Programm:

```cpp
COLORREF red       = RGB(255.0, 0.0, 0.0);
COLORREF lightBlue = RGB('173', '216', '230');
COLORREF aqua      = RGB("0", "255", "255");
COLORREF darkGreen = RGB(1000, 5000, 32000);
```

Bei genauem Hinsehen erkennen Sie mal kleinere, mal größere Abweichungen im Vergleich zum Originalbeispiel.

  * Welche Fehlermeldungen erzeugt ein C/C++-Compiler bei den gezeigten Variablen?
  * Welche Werte erhalten Sie bei der Ausgabe der Farben in einer Konsole?

## 2. Teilaufgabe

In einer Modern C++ Anwendung sind #define-Makros nicht mehr das Mittel der Wahl.
Schreiben Sie eine `constexpr`-Funktion `Rgb` mit derselben Funktionalität, die das `RGB`-Makro besitzt.

Verwenden Sie dazu die `#include`-Datei `<cstdint>`, um Datentypen wie `std::uint8_t` oder `std::uint32_t` zur Verfügung zu haben.
Testen Sie nun erneut die Beispiele aus dem letzten Abschnitt.

Wir beginnen zunächst mit den &bdquo;korrekten&rdquo; Anweisungen:

```cpp
constexpr std::uint32_t red       = Rgb(255, 0, 0);
constexpr std::uint32_t lightBlue = Rgb(173, 216, 230);
constexpr std::uint32_t aqua      = Rgb(0, 255, 255);
constexpr std::uint32_t darkGreen = Rgb(1, 50, 32);
```

Nun wiederholen wir das Beispiel mit fehlerhaften Parametern:

```cpp
constexpr std::uint32_t red       = Rgb(255.0, 0.0, 0.0);
constexpr std::uint32_t lightBlue = Rgb('173', '216', '230');
constexpr std::uint32_t aqua      = Rgb("0", "255", "255");
constexpr std::uint32_t darkGreen = Rgb(1000, 5000, 32000);
```

Welche Beobachtungen machen Sie beim Übersetzen des Beispiels?

Vergleichen Sie die  `constexpr`-Realisierung mit der Realisierung auf Basis des `RGB` C-Makros.

## 3. Teilaufgabe

Sollten Sie mit `constexpr` auf den Geschmack gekommen sein, dann gehen wir nun den nächsten Schritt
und erweitern die Funktionalität der `Rgb`-Funktion.
Zu diesem Zweck entwickeln wir eine Klasse `Color` mit folgender öffentlicher Schnittstelle:

| Methode | Schnittstelle und Beschreibung |
|:-|:-|:-|
| Konstruktor | `constexpr Color(std::uint8_t r, std::uint8_t g, std::uint8_t b);`<br/>Benutzerdefinierter Konstruktor, die drei Kanäle R, G und B werden in das Objekt aufgenommen. |
| Konstruktor | `constexpr Color(const std::string_view s);`<br/>Benutzerdefinierter Konstruktor, die Farbe wird durch eine Zeichenkette in hexadezimaler Form beschrieben, z. B. `"#00FFFF"`  |
| Hilfsmethode | `static constexpr Color parse(std::string_view str);`<br/>Rechnet einen Farbwert in Zeichenkettendarstellung in einen numerischen Wert um. |
| Hilfsmethode | `static constexpr std::optional<std::uint8_t> nibble(char n);`<br/>Dekodiert den Wert eines Nibbles (Zeichen `0` bis `9`, `a` bis `f` oder `A` bis `F`). |
| Hilfsmethode | `static constexpr std::optional<std::uint8_t> byte(std::string_view sv);`<br/>Dekodiert den Wert eines Bytes (z. B. `"FF"` oder `00`) |
| *getter*-Methode | `constexpr std::uint8_t GetRValue() const;`<br/>Liefert den R-Farbkanal zurück. |
| *getter*-Methode | `constexpr std::uint8_t GetGValue() const;`<br/>Liefert den G-Farbkanal zurück. |
| *getter*-Methode | `constexpr std::uint8_t GetBValue() const;`<br/>Liefert den B-Farbkanal zurück. |
| *getter*-Methode | `constexpr std::uint32_t value() const;`<br/>Liefert den Farbwert in einer Variablen des Typs `std::uint32_t` zurück. |

*Tabelle* 1: Öffentliche und private Methoden der Klasse `Color`.

Verifizieren Sie Ihre Realisierung an folgenden Beispielen:

```cpp
constexpr Color cyan{ "#00FFFF" };

constexpr auto r{ cyan.GetRValue()};
constexpr auto g{ cyan.GetGValue() };
constexpr auto b{ cyan.GetBValue() };
std::cout << std::format("{:#04X}:{:#04X}:{:#04X}", r, g, b) << std::endl;

constexpr auto value{ cyan.value() };
std::cout << std::format("{:#010X}", value) << std::endl;
```

oder auch:

```cpp
constexpr Color red{ 255, 0, 0 };
constexpr Color lightBlue{ 173, 216, 230 };
constexpr Color aqua{ 0, 255, 255 };
constexpr Color darkGreen{ 1, 50, 32 };

std::cout << std::format("{:#010X}", red.value()) << std::endl;
std::cout << std::format("{:#010X}", lightBlue.value()) << std::endl;
std::cout << std::format("{:#010X}", aqua.value()) << std::endl;
std::cout << std::format("{:#010X}", darkGreen.value()) << std::endl;
```

---

[Lösung](Exercise_06_constexpr_rgb.cpp)

---

[Zurück](../Readme.md)

---
