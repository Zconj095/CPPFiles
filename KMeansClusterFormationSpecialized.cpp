#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include <random>
#include <algorithm>

using namespace std;

using Point = vector<double>;
using Cluster = vector<Point>;

// Function to compute cosine similarity
double cosine_similarity(const Point& a, const Point& b) {
    double dot_product = 0.0;
    double norm_a = 0.0;
    double norm_b = 0.0;
    for (size_t i = 0; i < a.size(); ++i) {
        dot_product += a[i] * b[i];
        norm_a += a[i] * a[i];
        norm_b += b[i] * b[i];
    }
    return dot_product / (sqrt(norm_a) * sqrt(norm_b));
}

// Function to assign each point to the nearest centroid based on cosine similarity
vector<int> assign_clusters(const Cluster& data, const Cluster& centroids) {
    vector<int> assignments(data.size());
    for (size_t i = 0; i < data.size(); ++i) {
        double best_similarity = -numeric_limits<double>::infinity();
        int best_cluster = 0;
        for (size_t j = 0; j < centroids.size(); ++j) {
            double similarity = cosine_similarity(data[i], centroids[j]);
            if (similarity > best_similarity) {
                best_similarity = similarity;
                best_cluster = j;
            }
        }
        assignments[i] = best_cluster;
    }
    return assignments;
}

// Function to update centroids by averaging all points assigned to each cluster
Cluster update_centroids(const Cluster& data, const vector<int>& assignments, int k, int dim) {
    Cluster new_centroids(k, Point(dim, 0.0));
    vector<int> counts(k, 0);

    for (size_t i = 0; i < data.size(); ++i) {
        int cluster = assignments[i];
        counts[cluster]++;
        for (size_t j = 0; j < dim; ++j) {
            new_centroids[cluster][j] += data[i][j];
        }
    }

    for (int i = 0; i < k; ++i) {
        if (counts[i] == 0) continue;  // Avoid division by zero
        for (size_t j = 0; j < dim; ++j) {
            new_centroids[i][j] /= counts[i];
        }
    }

    return new_centroids;
}

// K-means clustering with cosine similarity
Cluster kmeans_cosine(const Cluster& data, int k, int max_iters = 100) {
    int n = data.size();
    int dim = data[0].size();
    Cluster centroids(k);

    // Randomly initialize centroids
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(0, n - 1);
    for (int i = 0; i < k; ++i) {
        centroids[i] = data[dist(gen)];
    }

    vector<int> assignments(n);

    for (int iter = 0; iter < max_iters; ++iter) {
        // Step 1: Assign points to the nearest centroid based on cosine similarity
        assignments = assign_clusters(data, centroids);

        // Step 2: Update centroids based on current assignments
        Cluster new_centroids = update_centroids(data, assignments, k, dim);

        // Check for convergence (if centroids do not change)
        if (new_centroids == centroids) {
            cout << "Converged in " << iter + 1 << " iterations." << endl;
            break;
        }
        centroids = new_centroids;
    }

    return centroids;
}

// Helper function to print clusters
void print_clusters(const Cluster& centroids) {
    cout << "Cluster centroids:" << endl;
    for (const auto& centroid : centroids) {
        for (double value : centroid) {
            cout << value << " ";
        }
        cout << endl;
    }
}

int main() {
    // Sample data points in a high-dimensional space (e.g., embeddings)
    Cluster data = {
        {0.2, 0.3, 0.5},
        {0.1, 0.7, 0.2},
        {0.6, 0.9, 0.3},
        {0.4, 0.2, 0.8},
        {0.9, 0.3, 0.6}
    };

    int k = 2; // Number of clusters
    int max_iters = 100;

    // Normalize data for cosine similarity
    for (auto& point : data) {
        double norm = sqrt(inner_product(point.begin(), point.end(), point.begin(), 0.0));
        for (double& val : point) {
            val /= norm;
        }
    }

    Cluster centroids = kmeans_cosine(data, k, max_iters);
    print_clusters(centroids);

    return 0;
}
