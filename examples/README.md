# Examples

## eprpairs.cpp

A simple pair of entangled qubits in a shared Bell state

Demonstrates the creation of the shared state using two methods:
* Calling the preset value of __b00__ from ```states.h```
* Creating a circuit that entangles two qubits into a shared Bell state, __b00__

### Method

We have two qubits, __|A>__ and __|B>__, both __|0>__
<img src="img/epr/qubits.jpg" height="121" width="571">

We create a circuit that will entangle __|A>__ and __|B>__. First an Hadamard transform puts __|A>__ into an equally weighted superposition of __|0>__ and __|1>__, then acts as a the control qubit for a NOT gate applied to __|B>__
<img src="img/epr/circuit.jpg" height="327" width="912"> 

Our system, __|AB>__ starts off in state
<img src="img/epr/starting.jpg" height="167" width="575">

And after the circuit is in state __|Φ⁺>__, or __b00__ in qSim
<img src="img/epr/b00.jpg" height="410" width="678">

__|Φ⁺>__ is an equally weighted superposition of __|00>__ and __|11>__, so after measurement you get __|00>__ 50% of the time and __|11>__ the other 50%
<img src="img/epr/measurement.jpg" height="195" width="422">

```sh
$ ./eprpairs.out

Circuit Matrix:
| 0.707  0       0.707   0     |
| 0      0.707   0       0.707 |
| 0      0.707   0      -0.707 |
| 0.707  0      -0.707   0     |


System starting state:

| 1 |
| 0 |
| 0 |
| 0 |


Our result is:

| 0.707 |
| 0     |
| 0     |
| 0.707 |


The true result is:

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

