#matrix-vector - mnożenie macierzy przez wektora

## Problem

Wyliczanie iloczynu macierzy kwadratowej oraz wektora.

![matrix-vector-method](../images/matrix-vector-method.png)

## Rozwiązanie

Algorytm sekwencyjny

##### 1. Wypełniamy macierz `M[ size ][ size ]` oraz wektor `N[ size ]` losowymi liczbami,

##### 2. Wyliczamy iloczyn macierz/wektor `W[ size ]` stosując wzór:

```
W[ i ] = M[ i ] * N[ i ]; 
```
Gdzie `M[ i ]` oznacza i-ty rząd mcierzy `M`,

##### 3. Drukujemy wynik `W[ size ]`.