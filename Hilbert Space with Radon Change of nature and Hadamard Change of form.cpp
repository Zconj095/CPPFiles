#include <iostream>
#include <vector>
#include <complex>
#include <cmath>

using namespace std;

class HilbertVector {
private:
    vector<complex<double>> components;  // Components of the vector (complex amplitudes)

public:
    HilbertVector(initializer_list<complex<double>> list) : components(list) {}

    // Apply a gate (2x2 matrix) to this vector
    HilbertVector applyGate(const vector<vector<complex<double>>>& gate) const {
        vector<complex<double>> new_components(2);
        new_components[0] = gate[0][0] * components[0] + gate[0][1] * components[1];
        new_components[1] = gate[1][0] * components[0] + gate[1][1] * components[1];
        return HilbertVector({new_components[0], new_components[1]});
    }

    // Radon Change of Nature: A custom transformation
    HilbertVector radonChangeOfNature() const {
        // Custom transformation representing a change of "nature" of the quantum state
        // This could be represented by a rotation followed by scaling
        double scaling_factor = 1.5;  // A sample scaling factor
        vector<vector<complex<double>>> radonMatrix = {
            {cos(M_PI / 6), -sin(M_PI / 6)},
            {sin(M_PI / 6), cos(M_PI / 6)}
        };

        HilbertVector rotated_vector = applyGate(radonMatrix);
        for (auto& component : rotated_vector.components) {
            component *= scaling_factor;  // Scale the state vector components
        }

        return rotated_vector;  // Return the modified vector
    }

    // Hadamard Change of Form (using Hadamard gate)
    HilbertVector hadamardChangeOfForm() const {
        vector<vector<complex<double>>> hadamardMatrix = {
            {1 / sqrt(2), 1 / sqrt(2)},
            {1 / sqrt(2), -1 / sqrt(2)}
        };
        return applyGate(hadamardMatrix);  // Apply Hadamard transformation
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

int main() {
    // Define a quantum state (a qubit, which is a 2-dimensional Hilbert vector)
    HilbertVector qubit = {1.0, 0.0};  // |0> state
    cout << "Initial state: ";
    qubit.print();

    // Apply the Radon Change of Nature
    cout << "After applying Radon Change of Nature: ";
    HilbertVector radon_qubit = qubit.radonChangeOfNature();
    radon_qubit.print();

    // Apply the Hadamard Change of Form
    cout << "After applying Hadamard Change of Form: ";
    HilbertVector hadamard_qubit = radon_qubit.hadamardChangeOfForm();
    hadamard_qubit.print();

    return 0;
}
