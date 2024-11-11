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

    // Radon Change of Form: A custom transformation
    HilbertVector radonChangeOfForm() const {
        // Custom transformation, example: a rotation combined with scaling
        double scale = 2.0; // Example scaling factor
        vector<vector<complex<double>>> radonMatrix = {
            {scale * cos(M_PI / 4), -scale * sin(M_PI / 4)},
            {scale * sin(M_PI / 4), scale * cos(M_PI / 4)}
        };
        return applyGate(radonMatrix);  // Apply the transformation
    }

    // Hadamard Change of Nature (using Hadamard gate)
    HilbertVector hadamardChangeOfNature() const {
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

    // Apply the Radon Change of Form
    cout << "After applying Radon Change of Form: ";
    HilbertVector radon_qubit = qubit.radonChangeOfForm();
    radon_qubit.print();

    // Apply the Hadamard Change of Nature
    cout << "After applying Hadamard Change of Nature: ";
    HilbertVector hadamard_qubit = radon_qubit.hadamardChangeOfNature();
    hadamard_qubit.print();

    return 0;
}
