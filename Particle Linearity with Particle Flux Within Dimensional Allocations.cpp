#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

// Define a particle class to hold the particle's position and velocity
class Particle {
public:
    vector<double> position;
    vector<double> velocity;
    double mass;

    // Constructor to initialize particle in n-dimensional space
    Particle(vector<double> initial_position, vector<double> initial_velocity, double particle_mass)
        : position(initial_position), velocity(initial_velocity), mass(particle_mass) {}

    // Update the particle's position based on current velocity and time step
    void updatePosition(double time_step) {
        for (size_t i = 0; i < position.size(); ++i) {
            position[i] += velocity[i] * time_step;
        }
    }

    // Apply a force to the particle and update its velocity (Newton's 2nd law: F = ma)
    void applyForce(const vector<double>& force, double time_step) {
        for (size_t i = 0; i < velocity.size(); ++i) {
            velocity[i] += (force[i] / mass) * time_step;
        }
    }

    // Print the current position of the particle
    void printPosition() const {
        cout << "Particle position: (";
        for (size_t i = 0; i < position.size(); ++i) {
            cout << position[i];
            if (i != position.size() - 1) cout << ", ";
        }
        cout << ")" << endl;
    }
};

// Apply a flux field to the particle (this could represent a flow of energy or particles)
void applyFluxField(Particle& particle, const vector<double>& flux, double time_step) {
    // A simple model where flux adds a small velocity to the particle
    vector<double> flux_force(particle.position.size());
    for (size_t i = 0; i < flux.size(); ++i) {
        flux_force[i] = flux[i];  // The flux acts like a constant force in each dimension
    }
    particle.applyForce(flux_force, time_step);
}

// Simulate particle motion with linearity and particle flux
void simulateParticleMotion(Particle& particle, const vector<double>& flux_field, double time_step, int num_steps) {
    for (int i = 0; i < num_steps; ++i) {
        // Apply flux field to the particle
        applyFluxField(particle, flux_field, time_step);
        // Update particle position based on velocity
        particle.updatePosition(time_step);
        // Print current position
        particle.printPosition();
    }
}

int main() {
    // Initialize a particle in 3D space
    vector<double> initial_position = {0.0, 0.0, 0.0}; // Starting at the origin
    vector<double> initial_velocity = {1.0, 1.0, 0.0}; // Moving diagonally in the x-y plane
    double particle_mass = 1.0; // Mass of the particle

    Particle particle(initial_position, initial_velocity, particle_mass);

    // Define a flux field acting on the particle (e.g., a constant force in the x and z directions)
    vector<double> flux_field = {0.1, 0.0, 0.2};  // Simulates particle flux in 3D space

    // Time step and number of simulation steps
    double time_step = 0.1;
    int num_steps = 20;

    // Simulate particle motion in 3D
    simulateParticleMotion(particle, flux_field, time_step, num_steps);

    // Now extend the system to 4D (hyperspace)
    vector<double> initial_position_4D = {0.0, 0.0, 0.0, 0.0}; // Start at the origin in 4D space
    vector<double> initial_velocity_4D = {1.0, 1.0, 0.0, 0.5}; // Moving diagonally in x-y-w space

    Particle particle_4D(initial_position_4D, initial_velocity_4D, particle_mass);

    // Define a flux field in 4D space
    vector<double> flux_field_4D = {0.1, 0.0, 0.2, 0.1}; // Flux in 4D space

    // Simulate particle motion in 4D
    cout << "\nSimulating in 4D space:" << endl;
    simulateParticleMotion(particle_4D, flux_field_4D, time_step, num_steps);

    return 0;
}
