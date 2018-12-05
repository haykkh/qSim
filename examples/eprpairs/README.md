# eprpairs.cpp

A simple pair of entangled qubits in a shared Bell state

Demonstrates the creation of the shared state using two methods:
* Calling the preset value of __b00__ from ```states.h```
* Creating a circuit that entangles two qubits into a shared Bell state, __b00__

See [here](https://en.wikipedia.org/wiki/Bell_state) for more info

## Method

We have two qubits, __|A>__ and __|B>__, both in state __|0>__
<p><img src="../img/epr/qubits.jpg" height="84" width="434"></p>

```cpp
Ket a = states::z0;
Ket b = states::z0;

Ket_ptr A = make_shared<Ket>(a);
Ket_ptr B = make_shared<Ket>(b);
```

Our system, __|AB>__, starts off in state __|00>__
<p><img src="../img/epr/starting.jpg" height="211" width="672"></p>

```cpp
Ket ab = a * b;

cout << "\nSystem starting state:\n";
ab.print();
```
```sh
System starting state:

| 1 |
| 0 |
| 0 |
| 0 |
```

We create a circuit that will entangle __|A>__ and __|B>__. First an Hadamard transform puts __|A>__ into an equally weighted superposition of __|0>__ and __|1>__, then __|A>__ acts asthe control qubit for a NOT gate applied to __|B>__. This circuit is equivalent to the matrix printed below
<p><img src="../img/epr/circuit.jpg" height="236" width="729"> </p>

```cpp
circuit::Circuit bell;

bell.setQubits({A, B});

bell.setCircuit({
    {
        {H, {A}}
    },
    {
        {CX, {A, B}}
    }
});

Matrix fc = bell.getFinalCircuit();

cout << "\nCircuit Matrix:\n";
fc.print();
```

```sh
Circuit Matrix:
| 0.707  0      0.707  0     |
| 0      0.707  0      0.707 |
| 0      0.707  0     -0.707 |
| 0.707  0     -0.707  0     |
```

After the circuit, our system is in state __|Φ⁺>__, or __b00__ in qSim
<p><img src="../img/epr/b00.jpg" height="402" width="571"></p>

```cpp
ab *= fc;

cout << "\nResult from circuit:\n";
ab.print(); 

Ket b00 = states::b00;

cout << "\nRecalled variable result:\n";    
b00.print();
```
```sh
Result from circuit:

| 0.707 |
| 0     |
| 0     |
| 0.707 |


Recalled variable result:

| 0.707 |
| 0     |
| 0     |
| 0.707 |
```


__|Φ⁺>__ is an equally weighted superposition of __|00>__ and __|11>__, so after measurement you get __|00>__ or __|11>__ with a probability of 0.5
<p><img src="../img/epr/measurement.jpg" height="172" width="702"></p>

```cpp
ab.measure();

cout << "\nState after measurement:\n";
ab.print();
```
```sh
State after measurement:

| 0 |
| 0 |
| 0 |
| 1 |
```

```sh
$ ./eprpairs

Circuit Matrix:
| 0.707  0      0.707  0     |
| 0      0.707  0      0.707 |
| 0      0.707  0     -0.707 |
| 0.707  0     -0.707  0     |


System starting state:

| 1 |
| 0 |
| 0 |
| 0 |


Result from circuit:

| 0.707 |
| 0     |
| 0     |
| 0.707 |


Recalled variable result:

| 0.707 |
| 0     |
| 0     |
| 0.707 |


State after measurement:

| 0 |
| 0 |
| 0 |
| 1 |
```