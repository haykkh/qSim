# hadamard.cpp

Applies an Hadamard transform to 3 qubits

See [here](https://en.wikipedia.org/wiki/Hadamard_transform) for more info

## Method

We have three qubits, **|k0>**, **|k1>**, and **|k2>**; in states **|0>**, **|0>**, and **|1>** respectively

<p><img src="../img/hadamard/qubits.jpg" height="195" width="624"></p>

```cpp
// c++

Ket k0 = states::z0;
Ket k1 = states::z0;
Ket k2 = states::z1;

Ket_ptr q0 = make_shared<Ket>(k0);
Ket_ptr q1 = make_shared<Ket>(k1);
Ket_ptr q2 = make_shared<Ket>(k2);
```

Our system, **|k0k1k2>**, starts off in state **|001>**

<p><img src="../img/hadamard/starting.jpg" height="389" width="552"></p>

```cpp
// c++

Ket state = k0 * k1 * k2;

cout << "\nSystem starting state:\n";
state.print();
```

```sh
# sh

System starting state:

| 0 |
| 1 |
| 0 |
| 0 |
| 0 |
| 0 |
| 0 |
| 0 |
```

We create a circuit that applies an Hadamard transform on all three qubits. This circuit is equivalent to the matrix printed below

<p><img src="../img/hadamard/circuit.jpg" height="366" width="566"> </p>

```cpp
// c++

vector<Ket_ptr> qubits = {q0, q1, q2};
Matrix H = gates::H;

circuit::Circuit hadamard;

hadamard.setQubits(qubits);

circuit::schematic scheme;

circuit::momentScheme moment;

for (auto i : qubits) {
    moment.push_back({H, {i}});
};

scheme = {moment};

hadamard.setCircuit(scheme);

Matrix fc = hadamard.getFinalCircuit();


cout << "\nCircuit matrix:\n";
fc.print();
```

```sh
# sh 

Circuit matrix:
| 0.354   0.354   0.354   0.354   0.354   0.354   0.354   0.354 |
| 0.354  -0.354   0.354  -0.354   0.354  -0.354   0.354  -0.354 |
| 0.354   0.354  -0.354  -0.354   0.354   0.354  -0.354  -0.354 |
| 0.354  -0.354  -0.354   0.354   0.354  -0.354  -0.354   0.354 |
| 0.354   0.354   0.354   0.354  -0.354  -0.354  -0.354  -0.354 |
| 0.354  -0.354   0.354  -0.354  -0.354   0.354  -0.354   0.354 |
| 0.354   0.354  -0.354  -0.354  -0.354  -0.354   0.354   0.354 |
| 0.354  -0.354  -0.354   0.354  -0.354   0.354   0.354  -0.354 |
```

This circuit puts the system puts into equally weighted superposition of **|000>**, **|001>**, **|010>**, **|011>**, **|100>**, **|101>**, **|110>**, and **|111>**

<p><img src="../img/hadamard/after.jpg" height="314" width="769"></p>

```cpp
// c++

state *= fc;

cout << "\nSystem state after circuit:\n";
state.print();
```

```sh
# sh

System state after circuit:

|  0.354 |
| -0.354 |
|  0.354 |
| -0.354 |
|  0.354 |
| -0.354 |
|  0.354 |
| -0.354 |
```

As our system is in an equally weighted superposition, a measurement returns **|000>**, **|001>**, **|010>**, **|011>**, **|100>**, **|101>**, **|110>**, or **|111>** with a probability of 0.125 each

```cpp
// c++

state.measure();

cout << "\nSystem state after measurement:\n";
state.print();
```

```sh
# sh

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

## Sample run

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
