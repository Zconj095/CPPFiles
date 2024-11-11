#include <iostream>
#include <vector>
#include <cmath>
#include <random>

// Define the Hyperstate class, which contains a collection of attributes
class Hyperstate {
private:
    std::vector<double> attributes;  // The set of values representing the state

public:
    Hyperstate(int dimensions) : attributes(dimensions, 0.0) {}

    // Generate a random hyperstate
    void randomize_state() {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(-10, 10); // Random values between -10 and 10

        for (auto& value : attributes) {
            value = dis(gen);
        }
    }

    // Getter for attributes
    const std::vector<double>& get_attributes() const {
        return attributes;
    }

    // Update the hyperstate's attribute at a given index
    void update_attribute(int index, double value) {
        if (index >= 0 && index < attributes.size()) {
            attributes[index] = value;
        }
    }

    // Calculate Euclidean distance between two hyperstates
    static double calculate_distance(const Hyperstate& h1, const Hyperstate& h2) {
        if (h1.attributes.size() != h2.attributes.size()) {
            throw std::invalid_argument("Hyperstates must have the same number of dimensions.");
        }

        double sum = 0.0;
        for (size_t i = 0; i < h1.attributes.size(); ++i) {
            sum += std::pow(h1.attributes[i] - h2.attributes[i], 2);
        }
        return std::sqrt(sum);
    }

    // Print hyperstate values
    void print_state() const {
        std::cout << "Hyperstate: ";
        for (const auto& value : attributes) {
            std::cout << value << " ";
        }
        std::cout << std::endl;
    }
};

// Define the HyperstateLocalSpace class, which holds a collection of hyperstates
class HyperstateLocalSpace {
private:
    int dimensions;
    std::vector<Hyperstate> hyperstates;

public:
    HyperstateLocalSpace(int dim) : dimensions(dim) {}

    // Add a hyperstate to the local space
    void add_hyperstate(const Hyperstate& hyperstate) {
        if (hyperstate.get_attributes().size() != dimensions) {
            throw std::invalid_argument("Hyperstate must have the correct number of dimensions.");
        }
        hyperstates.push_back(hyperstate);
    }

    // Generate and add a random hyperstate
    void add_random_hyperstate() {
        Hyperstate h(dimensions);
        h.randomize_state();
        hyperstates.push_back(h);
    }

    // Calculate and print distances between hyperstates
    void calculate_distances() const {
        if (hyperstates.size() < 2) {
            std::cout << "Not enough hyperstates to calculate distances." << std::endl;
            return;
        }

        for (size_t i = 0; i < hyperstates.size(); ++i) {
            for (size_t j = i + 1; j < hyperstates.size(); ++j) {
                double dist = Hyperstate::calculate_distance(hyperstates[i], hyperstates[j]);
                std::cout << "Distance between hyperstate " << i << " and hyperstate " << j << ": " << dist << std::endl;
            }
        }
    }

    // Print all hyperstates
    void print_hyperstates() const {
        for (size_t i = 0; i < hyperstates.size(); ++i) {
            std::cout << "Hyperstate " << i << ": ";
            hyperstates[i].print_state();
        }
    }
};

int main() {
    int dimensions = 4;  // Example: 4-dimensional hyperstate space
    HyperstateLocalSpace localSpace(dimensions);

    // Add 3 random hyperstates
    for (int i = 0; i < 3; ++i) {
        localSpace.add_random_hyperstate();
    }

    // Print hyperstates
    localSpace.print_hyperstates();

    // Calculate and print distances between hyperstates
    localSpace.calculate_distances();

    return 0;
}
