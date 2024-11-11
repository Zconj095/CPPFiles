#include <iostream>
#include <vector>
#include <cmath>

// Define a Hyperstate class to represent a point in Hyperspace
class Hyperstate {
public:
    std::vector<double> coordinates;

    // Constructor to initialize a hyperstate in N-dimensional space
    Hyperstate(std::vector<double> coords) : coordinates(coords) {}

    // Print the coordinates of the hyperstate
    void printState() const {
        std::cout << "Hyperstate: ( ";
        for (double coord : coordinates) {
            std::cout << coord << " ";
        }
        std::cout << ")" << std::endl;
    }
};

// Hyperspace class that contains a collection of Hyperstates
class Hyperspace {
public:
    std::vector<Hyperstate> hyperstates;

    // Add a new hyperstate to the hyperspace
    void addHyperstate(const Hyperstate& state) {
        hyperstates.push_back(state);
    }

    // Print all hyperstates in the hyperspace
    void printHyperspace() const {
        for (const auto& state : hyperstates) {
            state.printState();
        }
    }
};

// Function to rotate a hyperstate by a specified angle (2D example)
Hyperstate rotateHyperstate(const Hyperstate& state, double angle) {
    if (state.coordinates.size() != 2) {
        std::cerr << "Rotation only implemented for 2D hyperstates." << std::endl;
        return state;
    }

    double x = state.coordinates[0];
    double y = state.coordinates[1];

    // Apply 2D rotation matrix
    double new_x = x * cos(angle) - y * sin(angle);
    double new_y = x * sin(angle) + y * cos(angle);

    return Hyperstate({new_x, new_y});
}

// Function to translate a hyperstate by a vector
Hyperstate translateHyperstate(const Hyperstate& state, const std::vector<double>& translation) {
    if (state.coordinates.size() != translation.size()) {
        std::cerr << "Dimension mismatch between state and translation vector." << std::endl;
        return state;
    }

    std::vector<double> new_coords;
    for (size_t i = 0; i < state.coordinates.size(); ++i) {
        new_coords.push_back(state.coordinates[i] + translation[i]);
    }

    return Hyperstate(new_coords);
}

int main() {
    // Create a hyperspace
    Hyperspace hyperspace;

    // Create and add hyperstates to the hyperspace
    Hyperstate state1({1.0, 2.0});
    Hyperstate state2({3.0, 4.0});
    Hyperstate state3({-1.0, 2.5});

    hyperspace.addHyperstate(state1);
    hyperspace.addHyperstate(state2);
    hyperspace.addHyperstate(state3);

    // Print the original hyperspace
    std::cout << "Original Hyperspace:" << std::endl;
    hyperspace.printHyperspace();

    // Apply a 90-degree rotation to a hyperstate in 2D
    double angle = M_PI / 2; // 90 degrees in radians
    Hyperstate rotatedState = rotateHyperstate(state1, angle);

    std::cout << "\nAfter 90-degree rotation of state1:" << std::endl;
    rotatedState.printState();

    // Apply a translation to the hyperstate
    std::vector<double> translation = {1.0, -0.5};
    Hyperstate translatedState = translateHyperstate(state1, translation);

    std::cout << "\nAfter translation of state1 by vector {1.0, -0.5}:" << std::endl;
    translatedState.printState();

    return 0;
}
