# system-listy-obecnosci-cpp

Konsolowy system listy obecności napisany w C++ na zajęcia z programowania obiektowego (Politechnika Wrocławska). Projekt jest w trakcie rozwoju: powstał jako prosty program na strukturach i krok po kroku został przepisany na klasy, dziedziczenie i interfejsy.

## Co robi

- prowadzi katalog osób (imię, nazwisko, numer indeksu)
- pozwala tworzyć kilka list obecności i przełączać się między nimi
- dodaje osoby z katalogu na wybraną listę, oznacza obecność, edytuje dane i usuwa osoby z listy
- zapisuje do pliku całą listę albo dane wybranej osoby

## Menu

| Opcja | Działanie |
|---|---|
| 1 | dodaj osobę do katalogu |
| 2 | utwórz nową listę |
| 3 | wybierz listę |
| 4 | dodaj osobę z katalogu na listę |
| 5 | oznacz obecność |
| 6 | wyświetl listę obecności |
| 7 | edytuj dane osoby |
| 8 | usuń osobę z listy |
| 9 | zapisz do pliku (1 - cała lista, 2 - wybrana osoba) |
| 0 | wyjście |

## Zagadnienia programowania obiektowego w projekcie

- **hermetyzacja**: pola klasy `osoba` są chronione, dostęp przez gettery i settery
- **dziedziczenie**: `osoba` → `student` → `studentZaoczny` oraz `osoba` → `pracownik`
- **polimorfizm**: metody wirtualne `serialize()` i `drukuj()` nadpisywane w klasach pochodnych, wywoływane przez wskaźnik do klasy bazowej
- **interfejs**: `ISerializable` z czysto wirtualnymi metodami `serialize()` i `saveToFile()`, implementowany przez `osoba` i `ListaObecnosci`
- **podział odpowiedzialności**: klasa `InterfejsUzytkownika` obsługuje menu, `ListaObecnosci` przechowuje i modyfikuje dane

## Kompilacja i uruchomienie

```
g++ -std=c++17 -Wall -Wextra src/lista-obecnosci.cpp -o lista-obecnosci
./lista-obecnosci
```

## Struktura repozytorium

- `src/`: aktualny kod programu
- `archiwum/`: wcześniejsze wersje projektu z kolejnych zajęć

## Znane ograniczenia

- tablice o stałych rozmiarach: katalog do 10 osób, do 5 list, do 10 osób na liście, bez sprawdzania limitu przy dodawaniu do katalogu
- brak walidacji danych wpisywanych w menu
- cały kod w jednym pliku
