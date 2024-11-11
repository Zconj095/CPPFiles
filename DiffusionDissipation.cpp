#include <iostream>
#include <vector>
#include <cmath>  // For floor and mathematical operations

using namespace std;

class DiffusionDissipation {
public:
    // Constructor to initialize dissipation rate and diffusion factor
    DiffusionDissipation(double dissipation_rate, double diffusion_factor) {
        this->dissipation_rate = dissipation_rate;
        this->diffusion_factor = diffusion_factor;
    }

    // Apply diffusion-based dissipation to the energy
    double apply_dissipation(double energy) {
        // Energy loss is proportional to the difference between current energy and zero
        double dissipated_energy = energy * dissipation_rate;
        double diffusion_loss = energy * diffusion_factor;

        // Subtract dissipated energy and diffusion loss
        energy -= dissipated_energy + diffusion_loss;

        return max(energy, 0.0);  // Ensure energy does not go below zero
    }

private:
    double dissipation_rate;  // Dissipation rate
    double diffusion_factor;  // Diffusion coefficient
};

class HypergateFusionDissipator {
public:
    // Constructor to initialize the parameters
    HypergateFusionDissipator(double initial_energy, double fusion_rate, double max_safe_energy, DiffusionDissipation dissipation_model)
        : energy(initial_energy), fusion_rate(fusion_rate), max_safe_energy(max_safe_energy), dissipation_model(dissipation_model) {}

    // Simulate energy dissipation over a period of time
    vector<double> dissipate_energy(int time_steps) {
        vector<double> energy_levels;

        for (int t = 0; t < time_steps; t++) {
            // Fusion adds energy
            energy += fusion_rate;

            // Use the dissipation model to reduce energy
            energy = dissipation_model.apply_dissipation(energy);

            // Ensure energy doesn't go below zero
            energy = max(energy, 0.0);

            // Store energy level
            energy_levels.push_back(energy);

            // Check if energy exceeds safe levels
            if (energy > max_safe_energy) {
                cout << "Warning: Unsafe energy levels reached at step " << t << "! Energy: " << energy << endl;
                break;
            }
        }

        return energy_levels;
    }

private:
    double energy;  // Current energy level
    double fusion_rate;  // Fusion rate
    double max_safe_energy;  // Maximum safe energy level
    DiffusionDissipation dissipation_model;  // Diffusion dissipation model
};

// Main function to automate multiple runs of the simulation
int main() {
    // Parameters for the simulation
    double initial_energy = 1000.0;  // Arbitrary energy units
    double fusion_rate = 100.0;  // Fusion rate, energy added per time step
    double max_safe_energy = 2000.0;  // Maximum safe energy level

    // Create the diffusion dissipation model
    double dissipation_rate = 0.05;  // Dissipation rate
    double diffusion_factor = 0.02;  // Diffusion factor
    DiffusionDissipation diffusion_model(dissipation_rate, diffusion_factor);

    // Create the fusion dissipator with the diffusion dissipation model
    HypergateFusionDissipator dissipator(initial_energy, fusion_rate, max_safe_energy, diffusion_model);

    // Simulate the energy dissipation over 100 time steps
    int time_steps = 100;
    vector<double> energy_levels = dissipator.dissipate_energy(time_steps);

    // Output the energy levels for each time step
    cout << "Energy levels over time:" << endl;
    for (size_t i = 0; i < energy_levels.size(); ++i) {
        cout << "Step " << i << ": " << energy_levels[i] << endl;
    }

    return 0;
}
