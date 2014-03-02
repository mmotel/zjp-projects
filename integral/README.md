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

## Testy

### Sprzęt

Do testów (pomiarów czasów) używałem notebooka Samsung R590 z
procesorem Intel Core-i3 (2 rdzenie, 4 wątki) oraz pamięcią RAM o rozmiarze
4GB (2x2GB).

### Przebieg

Testy polegały na 500-krotnym uruchomieniu każdej z wersji programu
(sekwencyjenj i równoległej) dla n = {512, 1024, 2048, 4096, 8192, 16384}.
Następie następowało zliczanie czasów działania każdego uruchomienia oraz
wyliczanie śrendnich czasów dla obu wersji dla każdego n.
Średnie czasy zostały użyte do opracowania wyników.

### Wyniki

Legenda:
* `n` – ilość podziałów
* `sequence` – czas wersji sekwencyjnej (w sekundach)
* `mpi` – czas wersji równoległej (w sekundach)

```
n 		seq 			mpi
512 	0,0002544992 	0,0003078672

1024 	0,0005363293 	0,0004394188

2048 	0,0009618086 	0,0006383014

4096 	0,0019404019 	0,0010874134

8192 	0,0038068895 	0,0020514985

16384 	0,0057940177 	0,002838576
```
