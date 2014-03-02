# integral - całka

## Problem
Przybliżanie wartości całki metogą trapezów.

![integral-method](http://upload.wikimedia.org/wikipedia/commons/a/a8/Calkowanie_numeryczne-metoda_trapezow.png)

[Pełny opis via Wikipedia](http://upload.wikimedia.org/wikipedia/commons/a/a8/Calkowanie_numeryczne-metoda_trapezow.png)

## Rozwiązanie


### Algorytm sekwencyjny

##### 1. Wyliczamy `h` oraz ustalamy `x`:

```
h = (b – a) / n,
x = a;
```

##### 2. Dla `i = {0..n}` wyliczamy przybliżenie całki:

```
integral += [ f(x) + f(x+h) ] / 2 * h,
`x += h,
```

##### 3. Wypisujemy wynik.


