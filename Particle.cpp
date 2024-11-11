#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <cmath>
#include <algorithm>
#include <locale>

// Particle class representing a word in the NLP system
class Particle {
public:
    std::string word;
    int frequency;
    double sentimentScore;

    // Default constructor
    Particle() : word(""), frequency(0), sentimentScore(0.0) {}

    // Constructor with parameters
    Particle(std::string w, int freq, double sentiment) : word(w), frequency(freq), sentimentScore(sentiment) {}

    // Function to update frequency
    void updateFrequency() {
        frequency++;
    }

    // Print particle information
    void print() const {
        std::cout << "Word: " << word << ", Frequency: " << frequency << ", Sentiment: " << sentimentScore << "\n";
    }

    bool operator<(const Particle& other) const {
        return frequency > other.frequency;
    }
};

// Simple tokenizer function to split a sentence into words
std::vector<std::string> tokenize(const std::string& text) {
    std::vector<std::string> tokens;
    std::string word = "";
    for (char ch : text) {
        if (std::isalnum(ch)) {
            word += ch;
        } else if (!word.empty()) {
            tokens.push_back(word);
            word = "";
        }
    }
    if (!word.empty()) {
        tokens.push_back(word);
    }
    return tokens;
}

// Function to analyze sentiment (very basic, just a placeholder)
double analyzeSentiment(const std::string& word) {
    // Very simple: words like 'good', 'happy' return positive, and 'bad', 'sad' negative
    std::unordered_map<std::string, double> sentimentLexicon = {
        {"good", 0.8}, {"happy", 0.9}, {"great", 0.95},
        {"bad", -0.7}, {"sad", -0.8}, {"terrible", -0.9}
    };

    auto it = sentimentLexicon.find(word);
    return (it != sentimentLexicon.end()) ? it->second : 0.0; // Neutral if not found
}

// Function to process text, generating particle-based system
std::vector<Particle> processText(const std::string& text) {
    std::vector<std::string> tokens = tokenize(text);
    std::unordered_map<std::string, Particle> particles;

    // Generate particles from tokens
    for (const std::string& word : tokens) {
        double sentiment = analyzeSentiment(word);
        if (particles.find(word) == particles.end()) {
            particles[word] = Particle(word, 1, sentiment); // New particle
        } else {
            particles[word].updateFrequency(); // Existing particle, update frequency
        }
    }

    // Convert map to vector
    std::vector<Particle> particleList;
    for (const auto& entry : particles) {
        particleList.push_back(entry.second);
    }

    // Sort particles by frequency
    std::sort(particleList.begin(), particleList.end());

    return particleList;
}

// Main function demonstrating the particle-based NLP system
int main() {
    std::string inputText = "happy happy sad bad good good great terrible bad sad";

    // Process the text and generate particles
    std::vector<Particle> particles = processText(inputText);

    // Print the particles and their properties
    std::cout << "Particle-based NLP system output:\n";
    for (const Particle& p : particles) {
        p.print();
    }

    return 0;
}
