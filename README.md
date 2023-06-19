# Zestaw 5
Ten projekt dotyczy obsługi płótna do rysowania figur geometrycznych za pomocą znaków ASCII.

## Jak pobrać projekt
Aby pobrać projekt, wykonaj poniższe kroki:

1. Skopiuj adres URL repozytorium projektu.
2. Otwórz terminal i przejdź do katalogu, w którym chcesz umieścić projekt.
3. Wykonaj polecenie `git clone <adres_repozytorium>`.
## Jak skompilować projekt
Aby skompilować projekt, upewnij się, że masz zainstalowany kompilator C++ (np. g++) na swoim systemie. Następnie wykonaj poniższe kroki:

1. Otwórz terminal i przejdź do katalogu projektu.
2. Wykonaj polecenie `g++ Zadanie5.1.cpp -o Zadanie5`.
Po wykonaniu tych kroków, plik wykonywalny o nazwie "Zadanie5" zostanie utworzony w katalogu projektu.

## Jak używać projektu
Aby używać projektu, wykonaj poniższe kroki:

1. Przygotuj plik konfiguracyjny zawierający informacje o płótnie i figurach, np. "plik.txt", który zawiera takie informajce: 

- Canvas 20 10
- OutputFile output.txt
- EmptySymbol " "
- Figure Rectangle 14 6 3 3 # |Figure Rectangle 4 2 2 2 #

2. Uruchom projekt, podając nazwę pliku konfiguracyjnego jako argument w linii poleceń. Na przykład: `./Zadanie5.txt`.
3. Projekt odczyta plik konfiguracyjny, narysuje figury na płótnie i zapisze wynik do pliku "output.txt" (zgodnie z konfiguracją).
