#include <iostream>
#include <vector>
#include <complex>
#include <cmath>

using namespace std;

// Define complex number type for quantum states
using Complex = complex<double>;
using QuantumState = vector<Complex>;

// Function to normalize a quantum state (making sure the total probability is 1)
QuantumState normalize(const QuantumState& state) {
    double normValue = 0.0;
    for (const auto& amp : state) {
        normValue += norm(amp);  // Use std::norm to calculate the squared magnitude
    }
    normValue = sqrt(normValue);

    QuantumState normalizedState(state.size());
    for (size_t i = 0; i < state.size(); ++i) {
        normalizedState[i] = state[i] / normValue;
    }
    return normalizedState;
}

// Calculate the inner product of two quantum states
Complex innerProduct(const QuantumState& state1, const QuantumState& state2) {
    Complex result(0.0, 0.0);
    for (size_t i = 0; i < state1.size(); ++i) {
        result += conj(state1[i]) * state2[i];
    }
    return result;
}

// Calculate the expectation value of an observable (given as a matrix) in a quantum state
double expectationValue(const vector<vector<Complex>>& observable, const QuantumState& state) {
    QuantumState resultState(state.size(), 0.0);

    // Matrix multiplication (Observable * state)
    for (size_t i = 0; i < observable.size(); ++i) {
        for (size_t j = 0; j < observable[i].size(); ++j) {
            resultState[i] += observable[i][j] * state[j];
        }
    }

    // Inner product <state|O|state>
    Complex expValue = innerProduct(state, resultState);
    return expValue.real();
}

// Calculate the variance of an observable
double variance(const vector<vector<Complex>>& observable, const QuantumState& state) {
    double expVal = expectationValue(observable, state);

    // Calculate (O^2) and then compute <state|O^2|state>
    vector<vector<Complex>> observableSquared(observable.size(), vector<Complex>(observable.size(), 0.0));

    for (size_t i = 0; i < observable.size(); ++i) {
        for (size_t j = 0; j < observable[i].size(); ++j) {
            for (size_t k = 0; k < observable.size(); ++k) {
                observableSquared[i][j] += observable[i][k] * observable[k][j];
            }
        }
    }

    double expValSquared = expectationValue(observableSquared, state);
    return expValSquared - expVal * expVal;
}

// Generate a hyperstate (superposition of two states)
QuantumState createHyperstate(const QuantumState& state1, const QuantumState& state2, double alpha) {
    QuantumState hyperstate(state1.size());
    for (size_t i = 0; i < state1.size(); ++i) {
        hyperstate[i] = alpha * state1[i] + (1 - alpha) * state2[i];
    }
    return normalize(hyperstate);
}

int main() {
    // Define two quantum states (for example, basis vectors in a 2D Hilbert space)
    QuantumState state1 = { Complex(1, 0), Complex(0, 0) };  // |0>
    QuantumState state2 = { Complex(0, 0), Complex(1, 0) };  // |1>

    // Define an observable (a 2x2 Hermitian matrix)
    vector<vector<Complex>> observable = {
        { Complex(1, 0), Complex(0, 0) },
        { Complex(0, 0), Complex(2, 0) }
    };

    // Create a hyperstate (superposition) from state1 and state2
    double alpha = 0.6;  // Some coefficient for superposition
    QuantumState hyperstate = createHyperstate(state1, state2, alpha);

    // Calculate expectation value and variance of the observable in this hyperstate
    double expValue = expectationValue(observable, hyperstate);
    double var = variance(observable, hyperstate);

    cout << "Expectation Value: " << expValue << endl;
    cout << "Variance: " << var << endl;

    return 0;
}
