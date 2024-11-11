#include <iostream>
#include <vector>
#include <cmath>
#include <random>

// Function to generate a random hyperdimensional point
std::vector<double> generate_random_point(int dimensions) {
    std::vector<double> point(dimensions);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(-10, 10); // Random values between -10 and 10

    for (int i = 0; i < dimensions; ++i) {
        point[i] = dis(gen);
    }

    return point;
}

// Function to calculate Euclidean distance between two points in hyperdimensional space
double euclidean_distance(const std::vector<double>& point1, const std::vector<double>& point2) {
    if (point1.size() != point2.size()) {
        throw std::invalid_argument("Points must have the same dimension.");
    }

    double sum = 0.0;
    for (size_t i = 0; i < point1.size(); ++i) {
        sum += std::pow(point1[i] - point2[i], 2);
    }
    return std::sqrt(sum);
}

// Class representing a local space in hyperdimensional space
class HyperdimensionalLocalSpace {
private:
    int dimensions;
    std::vector<std::vector<double>> points;

public:
    HyperdimensionalLocalSpace(int dim) : dimensions(dim) {}

    // Add a point to the local space
    void add_point(const std::vector<double>& point) {
        if (point.size() != dimensions) {
            throw std::invalid_argument("Point must have the correct number of dimensions.");
        }
        points.push_back(point);
    }

    // Generate and add a random point to the space
    void add_random_point() {
        points.push_back(generate_random_point(dimensions));
    }

    // Get the number of points in the space
    int number_of_points() const {
        return points.size();
    }

    // Calculate and print distances between points in the local space
    void calculate_distances() const {
        if (points.size() < 2) {
            std::cout << "Not enough points to calculate distances." << std::endl;
            return;
        }

        for (size_t i = 0; i < points.size(); ++i) {
            for (size_t j = i + 1; j < points.size(); ++j) {
                double dist = euclidean_distance(points[i], points[j]);
                std::cout << "Distance between point " << i << " and point " << j << ": " << dist << std::endl;
            }
        }
    }
};

int main() {
    int dimensions = 5;  // For example, a 5-dimensional space
    HyperdimensionalLocalSpace localSpace(dimensions);

    // Add 5 random points to the local space
    for (int i = 0; i < 5; ++i) {
        localSpace.add_random_point();
    }

    // Print distances between all pairs of points
    localSpace.calculate_distances();

    return 0;
}
