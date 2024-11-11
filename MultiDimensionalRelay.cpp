#include <iostream>
#include <vector>
#include <cstdlib>  // for rand() and srand()
#include <ctime>    // for time()
#include <thread>   // for sleep_for
#include <chrono>   // for chrono::seconds
#include <algorithm> // for std::rotate
using namespace std;

class MultiDimensionalRelay {
public:
    vector<int> dimensions;
    vector<vector<vector<int>>> state;

    MultiDimensionalRelay(vector<int> dims) {
        dimensions = dims;
        state = create_empty_state(dimensions);
    }

    vector<vector<vector<int>>> create_empty_state(vector<int> dims) {
        vector<vector<vector<int>>> temp(dims[0], vector<vector<int>>(dims[1], vector<int>(dims[2], 0)));
        return temp;
    }

    void update_state(vector<int> position, int value) {
        state[position[0]][position[1]][position[2]] = value;
    }

    int relay_signal(vector<int> position) {
        return state[position[0]][position[1]][position[2]];
    }

    void display_state() {
        for (int i = 0; i < state.size(); ++i) {
            for (int j = 0; j < state[i].size(); ++j) {
                for (int k = 0; k < state[i][j].size(); ++k) {
                    cout << state[i][j][k] << " ";
                }
                cout << endl;
            }
            cout << endl;
        }
    }

    void shift_state(int dimension, int offset) {
        if (dimension >= dimensions.size()) {
            throw invalid_argument("Dimension index out of range");
        }
        if (dimension == 0) {
            shift_array(state, offset);
        } else if (dimension == 1) {
            for (auto& layer : state) {
                shift_array(layer, offset);
            }
        } else if (dimension == 2) {
            for (auto& layer : state) {
                for (auto& row : layer) {
                    shift_array(row, offset);
                }
            }
        }
    }

private:
    template <typename T>
    void shift_array(vector<T>& array, int offset) {
        offset = offset % array.size();  // Handle circular shifts
        std::rotate(array.begin(), array.begin() + (array.size() - offset), array.end()); // Rotate the array
    }
};

class CorticalShift {
public:
    MultiDimensionalRelay& relay;

    CorticalShift(MultiDimensionalRelay& relay_unit) : relay(relay_unit) {}

    void apply_cortical_shift(vector<int> shift_vector) {
        for (int dimension = 0; dimension < shift_vector.size(); ++dimension) {
            relay.shift_state(dimension, shift_vector[dimension]);
        }
        cout << "Cortical shift applied with shift vector: ";
        for (int shift : shift_vector) {
            cout << shift << " ";
        }
        cout << endl;
    }
};

class AutomatedCorticalShift {
public:
    MultiDimensionalRelay& relay;
    CorticalShift cortical_shift;
    int iterations;
    int pause_duration;

    AutomatedCorticalShift(MultiDimensionalRelay& relay_unit, int iters, int pause_sec)
        : relay(relay_unit), cortical_shift(relay_unit), iterations(iters), pause_duration(pause_sec) {}

    vector<int> generate_random_shift_vector() {
        vector<int> shift_vector;
        for (int i = 0; i < relay.dimensions.size(); ++i) {
            shift_vector.push_back(rand() % 3 - 1);  // Random shift -1, 0, or 1
        }
        return shift_vector;
    }

    void apply_automated_shifts() {
        for (int i = 0; i < iterations; ++i) {
            vector<int> shift_vector = generate_random_shift_vector();
            cout << "\nIteration " << i + 1 << ": Applying cortical shift\n";
            cortical_shift.apply_cortical_shift(shift_vector);
            cout << "State after cortical shift:\n";
            relay.display_state();

            this_thread::sleep_for(chrono::seconds(pause_duration));  // Pause between shifts
        }
    }
};

int main() {
    srand(time(0));  // Seed the random number generator

    // Create a 3x3x3 relay unit (3 dimensions of size 3)
    vector<int> dimensions = {3, 3, 3};
    MultiDimensionalRelay relay(dimensions);

    // Update some positions to set initial values
    relay.update_state({0, 0, 0}, 1);
    relay.update_state({1, 1, 1}, 2);
    relay.update_state({2, 2, 2}, 3);

    cout << "Original state:\n";
    relay.display_state();

    // Number of iterations and pause duration between shifts
    int iterations = 5;     // Number of shifts
    int pause_duration = 2; // Seconds between shifts

    // Create and run the automated cortical shift process
    AutomatedCorticalShift automated_shift(relay, iterations, pause_duration);
    automated_shift.apply_automated_shifts();

    return 0;
}
