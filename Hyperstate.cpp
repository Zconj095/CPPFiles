#include <iostream>
#include <vector>
#include <cmath>
#include <random>

class Hyperstate {
private:
    std::vector<double> position;    // 3D position (x, y, z)
    std::vector<double> orientation; // 3D orientation vector (nx, ny, nz)

    double diffusionRate; // Rate at which the orientation diffuses

public:
    // Constructor
    Hyperstate(const std::vector<double>& pos, const std::vector<double>& orient, double diffRate)
        : position(pos), orientation(orient), diffusionRate(diffRate) {}

    // Normalize a 3D vector
    std::vector<double> normalize(const std::vector<double>& vec) {
        double magnitude = std::sqrt(vec[0] * vec[0] + vec[1] * vec[1] + vec[2] * vec[2]);
        return {vec[0] / magnitude, vec[1] / magnitude, vec[2] / magnitude};
    }

    // Diffuse the orientation vector by applying random noise
    void diffuseOrientation() {
        // Adding small random noise to orientation vector for diffusion
        std::random_device rd;
        std::mt19937 gen(rd());
        std::normal_distribution<> noise(0.0, diffusionRate);

        for (int i = 0; i < 3; ++i) {
            orientation[i] += noise(gen);
        }

        // Normalize orientation to keep it a unit vector after applying noise
        orientation = normalize(orientation);
    }

    // Display the current state of the hyperstate
    void displayState() const {
        std::cout << "Position: (" << position[0] << ", " << position[1] << ", " << position[2] << ")\n";
        std::cout << "Orientation: (" << orientation[0] << ", " << orientation[1] << ", " << orientation[2] << ")\n";
    }

    // Get the current orientation (after diffusion)
    std::vector<double> getOrientation() const {
        return orientation;
    }

    // Update position with a velocity vector (simple example)
    void updatePosition(const std::vector<double>& velocity) {
        for (int i = 0; i < 3; ++i) {
            position[i] += velocity[i];
        }
    }
};

int main() {
    // Initial position and orientation vectors
    std::vector<double> initialPosition = {0.0, 0.0, 0.0};
    std::vector<double> initialOrientation = {1.0, 0.0, 0.0}; // Initial orientation in x-direction
    double diffusionRate = 0.1; // Diffusion rate (controls the noise level)

    // Create the Hyperstate object
    Hyperstate hyperstate(initialPosition, initialOrientation, diffusionRate);

    // Display initial state
    hyperstate.displayState();

    // Simulate multiple diffusion steps
    for (int i = 0; i < 5; ++i) {
        std::cout << "\nAfter diffusion step " << i + 1 << ":\n";
        hyperstate.diffuseOrientation();
        hyperstate.displayState();
    }

    return 0;
}
