# integral - całka

## Problem
Przybliżanie wartości całki metogą trapezów.

![integral-method](http://upload.wikimedia.org/wikipedia/commons/a/a8/Calkowanie_numeryczne-metoda_trapezow.png)

[Pełny opis via Wikipedia](http://upload.wikimedia.org/wikipedia/commons/a/a8/Calkowanie_numeryczne-metoda_trapezow.png)

## Rozwiązanie


### Algorytm sekwencyjny

##### 1. Wyliczamy `h` oraz ustalamy `x`:

```
h = (b – a) / n;
x = a;
```

##### 2. Dla `i = {0..n}` wyliczamy przybliżenie całki:

```
integral += [ f(x) + f(x+h) ] / 2 * h;
`x += h;
```

##### 3. Wypisujemy wynik.

---

###Algorytm równoległy (MPI)

##### 1. Wyliczamy `h`:

```
h = (b – a) / n;
```

##### 2. Każdy proces ustala swoje początkowe `x`:

```
x = a + (rank*n/np) * h;
```

##### 3. Każdy proces dla `i = { rank*n/np..(rank+1)*n/np - 1 }` wylicza swoją częśćoszacowania całki:

```
integral += [ f(x) + f(x+h) ] / 2 * h;
x += h;
```

##### 4. Dokonujemy zliczenia oszacowań (`MPI_Reduce`),
##### 5. proces o `rank` równym `0` wypisuje wynik.
