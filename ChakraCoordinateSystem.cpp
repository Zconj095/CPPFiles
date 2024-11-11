#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

struct Chakra {
    std::string name;
    std::string color;
    int y_position;
};

// Function to display the Cartesian plane with chakras
void displayChakraCoordinateSystem(const std::vector<Chakra>& chakras) {
    const int X_MIN = -20, X_MAX = 20;
    const int Y_MIN = -10, Y_MAX = 10;

    for (int y = Y_MAX; y >= Y_MIN; --y) {
        // Print Y-axis labels
        if (y == 0) {
            std::cout << std::setw(2) << y << " |";
        } else {
            std::cout << std::setw(2) << y << " |";
        }

        // Print the coordinate system with chakras
        for (int x = X_MIN; x <= X_MAX; ++x) {
            if (x == 0 && y != 0) {
                // Print the Y-axis line
                std::cout << "|";
            } else if (y == 0) {
                // Print the X-axis line
                if (x == 0) {
                    std::cout << "+";  // Origin
                } else {
                    std::cout << "-";  // X-axis
                }
            } else {
                // Check if there's a chakra at this position
                bool chakraPresent = false;
                for (const auto& chakra : chakras) {
                    if (y == chakra.y_position && x == 0) {
                        std::cout << chakra.name[0];  // Print the first letter of the chakra
                        chakraPresent = true;
                        break;
                    }
                }
                if (!chakraPresent) {
                    std::cout << " ";  // Empty space
                }
            }
        }
        std::cout << "\n";
    }

    // Print X-axis labels
    std::cout << "    ";
    for (int x = X_MIN; x <= X_MAX; ++x) {
        if (x % 5 == 0) {
            std::cout << std::setw(2) << x;
        } else {
            std::cout << "  ";
        }
    }
    std::cout << "\n";
}

int main() {
    std::vector<Chakra> chakras = {
        {"Muladhara", "Red", -7},
        {"Swadhisthana", "Orange", -5},
        {"Manipura", "Yellow", -3},
        {"Anahata", "Green", 0},
        {"Vishuddha", "Blue", 3},
        {"Ajna", "Indigo", 5},
        {"Sahasrara", "Violet", 7}
    };

    // Display the chakra-inspired Cartesian coordinate system
    displayChakraCoordinateSystem(chakras);

    return 0;
}
