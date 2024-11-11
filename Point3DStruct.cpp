#include <iostream>
#include <vector>
#include <cstdlib>  // for rand() and srand()
#include <ctime>    // for time()
#include <cmath>    // for sqrt
#include <iomanip>  // for std::setw

// Define a simple 3D Point structure for particle positions
struct Point3D {
    double x, y, z;

    // Constructor to initialize 3D points
    Point3D(double x_=0, double y_=0, double z_=0) : x(x_), y(y_), z(z_) {}

    // Print the point for debugging purposes
    void print() const {
        std::cout << std::setw(10) << x << ", "
                  << std::setw(10) << y << ", "
                  << std::setw(10) << z << std::endl;
    }
};

// Function to generate random 3D points (particles)
std::vector<Point3D> generate_3d_data(int n_samples) {
    std::vector<Point3D> points;
    srand(time(0));  // Seed random generator
    for (int i = 0; i < n_samples; i++) {
        points.push_back(Point3D(rand() % 100, rand() % 100, rand() % 100));
    }
    return points;
}

// Function to simulate fluid flow with swap gate interference based on pressure and stress levels
std::vector<Point3D> simulate_fluid_flow(const std::vector<Point3D>& X, double pressure_level, std::string stress_type) {
    std::vector<Point3D> fluid_flow(X.size());
    double max_shift = (stress_type == "low") ? 0.5 : 1.0;
    double swap_probability = (stress_type == "high") ? pressure_level : pressure_level / 2.0;

    // Simulate fluid movement based on pressure and stress levels
    for (size_t i = 0; i < X.size(); i++) {
        if ((rand() % 100) / 100.0 < swap_probability) {
            // Swap gate interference: Swap coordinates randomly
            fluid_flow[i] = Point3D(X[i].y, X[i].z, X[i].x);  // Just a simple swap
        } else {
            // Normal flow: Small random shift in coordinates
            fluid_flow[i] = Point3D(X[i].x + (rand() % 10 - 5) * max_shift,
                                    X[i].y + (rand() % 10 - 5) * max_shift,
                                    X[i].z + (rand() % 10 - 5) * max_shift);
        }
    }
    return fluid_flow;
}

// Function to automate multiple simulations for various pressure and stress conditions
void run_simulation(std::string stress_type, std::vector<double> pressure_levels, int n_samples) {
    // Generate initial 3D data (particles)
    std::vector<Point3D> X = generate_3d_data(n_samples);

    // Iterate through pressure levels and simulate the fluid flow
    for (size_t i = 0; i < pressure_levels.size(); i++) {
        double pressure = pressure_levels[i];

        std::cout << "\nSimulation for " << stress_type << " stress at pressure level " << pressure << ":\n";
        std::cout << "--------------------------------------------\n";

        // Simulate the fluid flow under the current pressure level
        std::vector<Point3D> fluid_flow = simulate_fluid_flow(X, pressure, stress_type);

        // Print the results (for visualization, print original and new positions)
        for (size_t j = 0; j < fluid_flow.size(); j++) {
            std::cout << "Original Point: ";
            X[j].print();
            std::cout << "Fluid Flow to: ";
            fluid_flow[j].print();
            std::cout << "--------------------------------------------\n";
        }
    }
}

int main() {
    int n_samples = 10;  // Number of fluid particles to simulate
    std::vector<double> pressure_levels = {0.05, 0.1, 0.2, 0.5, 0.9};  // Different pressure levels for the simulation

    // Run low-stress simulations
    std::cout << "Starting Low-Stress Simulation...\n";
    run_simulation("low", pressure_levels, n_samples);

    // Run high-stress simulations
    std::cout << "\n\nStarting High-Stress Simulation...\n";
    run_simulation("high", pressure_levels, n_samples);

    return 0;
}
