# hadamard.cpp

Applies an Hadamard transform to 3 qubits

See [here](https://en.wikipedia.org/wiki/Hadamard_transform) for more info

## Method

We have three qubits, __|k0>__, __|k1>__, and __|k2>__; in states __|0>__, __|0>__, and __|1>__ respectively
<p><img src="../img/hadamard/qubits.jpg" height="195" width="624"></p>

Our system, __|k0k1k2>__, starts off in state __|001>__
<p><img src="../img/hadamard/starting.jpg" height="389" width="552"></p>

We create a circuit that applies an Hadamard transform on all three qubits. This circuit is equivalent to the matrix printed below
<p><img src="../img/hadamard/circuit.jpg" height="366" width="566"> </p>


This circuit puts the system puts into equally weighted superposition of __|000>__, __|001>__, __|010>__, __|011>__, __|100>__, __|101>__, __|110>__, and __|111>__
<p><img src="../img/hadamard/after.jpg" height="314" width="769"></p>

As our system is in an equally weighted superposition, a measurement returns __|000>__, __|001>__, __|010>__, __|011>__, __|100>__, __|101>__, __|110>__, or __|111>__ with a probability of 0.125 each

```sh
$ /hadamard

Circuit matrix:
| 0.354   0.354   0.354   0.354   0.354   0.354   0.354   0.354 |
| 0.354  -0.354   0.354  -0.354   0.354  -0.354   0.354  -0.354 |
| 0.354   0.354  -0.354  -0.354   0.354   0.354  -0.354  -0.354 |
| 0.354  -0.354  -0.354   0.354   0.354  -0.354  -0.354   0.354 |
| 0.354   0.354   0.354   0.354  -0.354  -0.354  -0.354  -0.354 |
| 0.354  -0.354   0.354  -0.354  -0.354   0.354  -0.354   0.354 |
| 0.354   0.354  -0.354  -0.354  -0.354  -0.354   0.354   0.354 |
| 0.354  -0.354  -0.354   0.354  -0.354   0.354   0.354  -0.354 |


System starting state:

| 0 |
| 1 |
| 0 |
| 0 |
| 0 |
| 0 |
| 0 |
| 0 |


System state after circuit:

|  0.354 |
| -0.354 |
|  0.354 |
| -0.354 |
|  0.354 |
| -0.354 |
|  0.354 |
| -0.354 |


System state after measurement:

| 0 |
| 0 |
| 0 |
| 1 |
| 0 |
| 0 |
| 0 |
| 0 |
```

