#include <iostream>
#include <vector>
#include <cmath>

// A class to represent a vector in a Hilbert space
class HilbertVector {
private:
    std::vector<double> components; // Components of the vector

public:
    HilbertVector(std::initializer_list<double> list) : components(list) {}

    // Inner product (dot product in Euclidean space)
    double innerProduct(const HilbertVector& other) const {
        double result = 0.0;
        for (size_t i = 0; i < components.size(); ++i) {
            result += components[i] * other.components[i];
        }
        return result;
    }

    // Norm of the vector
    double norm() const {
        return std::sqrt(innerProduct(*this));
    }

    // Apply a linear transformation (change of form)
    HilbertVector transform(const std::vector<std::vector<double>>& matrix) const {
        size_t dim = components.size();
        HilbertVector result({0.0, 0.0, 0.0}); // Initialize to zero vector of the same size
        for (size_t i = 0; i < dim; ++i) {
            double new_value = 0.0;
            for (size_t j = 0; j < dim; ++j) {
                new_value += matrix[i][j] * components[j];
            }
            result.components[i] = new_value;
        }
        return result;
    }

    // Print the vector components
    void print() const {
        std::cout << "(";
        for (size_t i = 0; i < components.size(); ++i) {
            std::cout << components[i];
            if (i != components.size() - 1) std::cout << ", ";
        }
        std::cout << ")" << std::endl;
    }
};

int main() {
    // Define a vector in the Hilbert space
    HilbertVector v1 = {1.0, 2.0, 3.0};
    std::cout << "Original vector: ";
    v1.print();

    // Define a transformation matrix (3x3 for 3-dimensional space)
    std::vector<std::vector<double>> transformationMatrix = {
        {2.0, 0.0, 0.0},
        {0.0, 3.0, 0.0},
        {0.0, 0.0, 1.0}
    };

    // Apply the transformation (change of form)
    HilbertVector v2 = v1.transform(transformationMatrix);
    std::cout << "Transformed vector: ";
    v2.print();

    return 0;
}
