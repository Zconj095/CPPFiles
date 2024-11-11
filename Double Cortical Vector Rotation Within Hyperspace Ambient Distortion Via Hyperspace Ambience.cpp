#include <iostream>
#include <vector>
#include <cmath>
#include <random>

using namespace std;

// Function to generate random distortion (ambient effect)
double randomDistortion(double max_distortion) {
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(-max_distortion, max_distortion);
    return dis(gen);
}

// Class to represent a vector in hyperspace (4D)
class HyperspaceVector {
public:
    vector<double> components;

    // Constructor for a 4D vector
    HyperspaceVector(double x, double y, double z, double w) {
        components = {x, y, z, w};
    }

    // Apply ambient distortion to the vector (affects each component randomly)
    void applyAmbientDistortion(double max_distortion) {
        for (size_t i = 0; i < components.size(); ++i) {
            components[i] += randomDistortion(max_distortion);
        }
    }

    // Rotate vector in the x-y plane (cortical axis 1)
    void rotateXY(double angle) {
        double x_new = components[0] * cos(angle) - components[1] * sin(angle);
        double y_new = components[0] * sin(angle) + components[1] * cos(angle);
        components[0] = x_new;
        components[1] = y_new;
    }

    // Rotate vector in the z-w plane (cortical axis 2)
    void rotateZW(double angle) {
        double z_new = components[2] * cos(angle) - components[3] * sin(angle);
        double w_new = components[2] * sin(angle) + components[3] * cos(angle);
        components[2] = z_new;
        components[3] = w_new;
    }

    // Print the current state of the vector
    void print() const {
        cout << "Vector position: (";
        for (size_t i = 0; i < components.size(); ++i) {
            cout << components[i];
            if (i != components.size() - 1) cout << ", ";
        }
        cout << ")" << endl;
    }
};

// Simulate the double cortical vector rotation with ambient distortion
void simulateDoubleCorticalRotation(HyperspaceVector& vector, double angle_step, double max_distortion, int num_steps) {
    for (int i = 0; i < num_steps; ++i) {
        // Apply double rotation in the x-y and z-w planes
        vector.rotateXY(angle_step);
        vector.rotateZW(angle_step);

        // Apply ambient distortion (simulating hyperspace effects)
        vector.applyAmbientDistortion(max_distortion);

        // Print the current state of the vector
        vector.print();
    }
}

int main() {
    // Initialize a vector in 4D space
    HyperspaceVector vector(1.0, 0.0, 0.0, 1.0);

    // Parameters for the simulation
    double angle_step = M_PI / 12;   // Rotation step (15 degrees per step)
    double max_distortion = 0.05;    // Maximum ambient distortion
    int num_steps = 20;              // Number of simulation steps

    // Run the simulation
    simulateDoubleCorticalRotation(vector, angle_step, max_distortion, num_steps);

    return 0;
}
