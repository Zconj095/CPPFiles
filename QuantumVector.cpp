#include <iostream>
#include <complex>
#include <cmath>

class QuantumVector {
private:
    std::complex<double> x, y, z; // Coordinates in 3D space as complex numbers

public:
    // Constructor to initialize the vector
    QuantumVector(std::complex<double> x_, std::complex<double> y_, std::complex<double> z_) : x(x_), y(y_), z(z_) {}

    // Default constructor (zero vector)
    QuantumVector() : x(0), y(0), z(0) {}

    // Print the vector
    void print() const {
        std::cout << "Vector: (" << x << ", " << y << ", " << z << ")\n";
    }

    // Addition of two vectors
    QuantumVector operator+(const QuantumVector& other) const {
        return QuantumVector(x + other.x, y + other.y, z + other.z);
    }

    // Dot product of two vectors
    std::complex<double> dot(const QuantumVector& other) const {
        return x * std::conj(other.x) + y * std::conj(other.y) + z * std::conj(other.z);
    }

    // Cross product of two vectors (for 3D vectors)
    QuantumVector cross(const QuantumVector& other) const {
        return QuantumVector(
            y * other.z - z * other.y,
            z * other.x - x * other.z,
            x * other.y - y * other.x
        );
    }

    // Magnitude (length) of the vector
    double magnitude() const {
        return std::sqrt(std::norm(x) + std::norm(y) + std::norm(z));
    }

    // Relay operation: applies a transformation matrix to the vector
    // Here, we use a simple example of a rotation in the XY plane.
    QuantumVector relayRotationXY(double angleRadians) const {
        std::complex<double> cosAngle = std::cos(angleRadians);
        std::complex<double> sinAngle = std::sin(angleRadians);

        std::complex<double> newX = cosAngle * x - sinAngle * y;
        std::complex<double> newY = sinAngle * x + cosAngle * y;

        return QuantumVector(newX, newY, z); // Z remains unchanged in XY-plane rotation
    }
};

int main() {
    // Example usage:
    std::complex<double> i(0, 1); // imaginary unit

    // Define two quantum vectors in the Cartesian coordinate system
    QuantumVector v1(std::complex<double>(1, 2), std::complex<double>(2, -1), std::complex<double>(0, 3));
    QuantumVector v2(std::complex<double>(0, 1), std::complex<double>(3, 0), std::complex<double>(1, -1));

    std::cout << "Vector 1: ";
    v1.print();

    std::cout << "Vector 2: ";
    v2.print();

    // Addition of vectors
    QuantumVector v3 = v1 + v2;
    std::cout << "Vector 1 + Vector 2: ";
    v3.print();

    // Dot product
    std::complex<double> dotProduct = v1.dot(v2);
    std::cout << "Dot product of Vector 1 and Vector 2: " << dotProduct << "\n";

    // Cross product
    QuantumVector crossProduct = v1.cross(v2);
    std::cout << "Cross product of Vector 1 and Vector 2: ";
    crossProduct.print();

    // Magnitude of v1
    std::cout << "Magnitude of Vector 1: " << v1.magnitude() << "\n";

    // Relay operation: rotation in XY plane by 45 degrees (π/4 radians)
    double angle = M_PI / 4; // 45 degrees in radians
    QuantumVector rotatedV1 = v1.relayRotationXY(angle);
    std::cout << "Vector 1 after 45 degree rotation in the XY plane: ";
    rotatedV1.print();

    return 0;
}
