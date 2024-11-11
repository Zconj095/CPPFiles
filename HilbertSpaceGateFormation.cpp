#include <iostream>
#include <vector>
#include <complex>
#include <cmath>

using namespace std;

class HilbertVector {
private:
    vector<complex<double>> components; // Components of the vector

public:
    HilbertVector(initializer_list<complex<double>> list) : components(list) {}

    // Apply a gate (2x2 matrix) to this vector
    HilbertVector applyGate(const vector<vector<complex<double>>>& gate) const {
        vector<complex<double>> new_components(2);
        new_components[0] = gate[0][0] * components[0] + gate[0][1] * components[1];
        new_components[1] = gate[1][0] * components[0] + gate[1][1] * components[1];
        return HilbertVector({new_components[0], new_components[1]});
    }

    // Print the vector components
    void print() const {
        cout << "(";
        for (size_t i = 0; i < components.size(); ++i) {
            cout << components[i];
            if (i != components.size() - 1) cout << ", ";
        }
        cout << ")" << endl;
    }
};

// Pauli-X gate (Quantum NOT gate)
vector<vector<complex<double>>> PauliXGate() {
    return {{0, 1}, {1, 0}};
}

// Pauli-Y gate
vector<vector<complex<double>>> PauliYGate() {
    return {{0, complex<double>(0, -1)}, {complex<double>(0, 1), 0}};
}

// Pauli-Z gate
vector<vector<complex<double>>> PauliZGate() {
    return {{1, 0}, {0, -1}};
}

// Hadamard gate
vector<vector<complex<double>>> HadamardGate() {
    return {{1 / sqrt(2), 1 / sqrt(2)}, {1 / sqrt(2), -1 / sqrt(2)}};
}

int main() {
    // Define a quantum state (a qubit, which is a 2-dimensional Hilbert vector)
    HilbertVector qubit = {1.0, 0.0}; // |0> state
    cout << "Initial state: ";
    qubit.print();

    // Apply the Pauli-X gate (quantum NOT gate)
    cout << "After applying Pauli-X gate: ";
    HilbertVector new_qubit = qubit.applyGate(PauliXGate());
    new_qubit.print();

    // Apply the Hadamard gate
    cout << "After applying Hadamard gate: ";
    new_qubit = qubit.applyGate(HadamardGate());
    new_qubit.print();

    return 0;
}
