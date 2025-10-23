# Repozytorium z rozwiązaniami zadań z olimpiad AMPPZ

Repozytorium zawiera rozwiązania zadań z olimpiad AMPPZ pogrupowane tematycznie.

## Testowanie programów

Poprawność napisanych programów sprawdzana jest za pomocą testów jednostkowych. Testy zdefiniowane są jako zestawy danych wejściowych (*in*) i spodziewanych danych wyjściowych (*out*). 

*1.in* - *1.out* <br>
*2.in* - *2.out* <br>
itd.

Dla programu, który ma pobierać n par liczb, by następnie obliczyć ich sumy, pliki mogą mieć następującą zawartość:

1.in:
```
2
1 3
5 4
```

1.out:
```
4
9
```
Testy algorytmów można wykonać lokalnie z pomocą skryptu *test.py*. Program przyjmuje ścieżkę do programu napisanego w C++ oraz ścieżkę do katalogu z testami. Skrypt kompiluje program a następnie przeprowadza testy i zwraca informację o rezultacie i czasie wykonania testu. Według zasad, para plików testu powinna mieć wspólną nazwę i rozszerzenia odpowiednio *in* i *out*.

```
python test.py .\sample_program\sample_program.cpp .\sample_program\tests
```
