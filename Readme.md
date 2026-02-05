# Seminar Diamant Software

---

## Aufgaben

### [Verwendung von Smart Pointern für Membervariablen einer Klasse](./Seminar_DS_2026_Begleitmaterial/Exercise_01_Smart_Pointer.md)

### [Löschen aller ungeraden Elemente in einem sequenziellen STL-Container](./Seminar_DS_2026_Begleitmaterial/Exercise_02_STL_Erase_Remove.md)

### [Die STL und eine Klasse `Phonebook`](./Seminar_DS_2026_Begleitmaterial/Exercise_03_STL_Phonebook.md)

### [Maximum dreier Zahlen](./Seminar_DS_2026_Begleitmaterial/Exercise_04_constexpr_maximum.md)

### [Rückgabe eines `std::unique_ptr<>`-Objekts aus einer Funktion](./Seminar_DS_2026_Begleitmaterial/Exercise_05_Returning_UniquePtr.md)

### [RGB Farben](./Seminar_DS_2026_Begleitmaterial/Exercise_06_constexpr_rgb.md)

---

## Hinweise zur Lösung der Aufgaben

Es ist vorgesehen, dass Sie die Aufgaben &ndash; soweit machbar &ndash; im Kontext
des *Unit Test Frameworks* realisiert werden. Auf diese Weise lassen sich auch
Diamant Software spezifische Klassen
wie z. B. `SA_Integer` verwenden, die sonst nicht zur Verfügung stehen würden.

In jeder Aufgabe befindet sich ein kleines Beispiel, wie eine Integration
der Aufgabenstellung in den Unit Test Framework aussehen könnte.

---

## Laufzeitmessungen

Für Laufzeitmessungen findet man in diesem Repository eine Klasse `ScopedTimer` vor.
Es handelt sich um eine *Header-Only*-Klasse,
ihr vollständiger Quellcode (Deklarationen und Implementierungen) wird in der Header-Dateien
bereitgestellt.

Ein Beispiel für die Verwendung dieser Klasse könnte so aussehen:

```cpp
// ==================================================================================
// Beispiel zur Verwendung des ScopedTimers.
// Er misst die Zeit vom Aufruf seines Konstruktors bis zum Aufruf seines Destruktors.
// Die gemessene Zeit wird im Testergebniss ausgegeben.

// ggf. noch anzupassen
#include "CppUnitTest.h"
#include "ScopedTimer.h"   // geeignet umzukopieren

#include <SA_Basis/LC1_UnitTestHelpers.h>

#include <chrono>
#include <vector>
#include <algorithm>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

TEST_METHOD(ProfileVectorNoReserve) {
    ScopedTimer timer{ ScopedTimer::Resolution::Micro };

    std::vector<int> vec;
    for (int i = 0; i < LARGE_NUMBER; ++i) {
        vec.push_back(i);
    }
}

TEST_METHOD(ProfileVectorReserve) {
    ScopedTimer timer{ ScopedTimer::Resolution::Micro };

    std::vector<int> vec;
    vec.reserve(LARGE_NUMBER);
    for (int i = 0; i < LARGE_NUMBER; ++i) {
        vec.push_back(i);
    }
}
```

---