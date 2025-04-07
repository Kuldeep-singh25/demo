#include <iostream>
#include <vector>
#include <climits>

using namespace std;

const int INF = INT_MAX;  // Represents infinity (unreachable nodes)

void print_distance_table(const vector<vector<int>>& distance_table, int num_nodes) {
    cout << "Distance Vector Table:\n";
    for (int i = 0; i < num_nodes; ++i) {
        for (int j = 0; j < num_nodes; ++j) {
            if (distance_table[i][j] == INF)
                cout << "INF ";
            else
                cout << distance_table[i][j] << " ";
        }
        cout << endl;
    }
}

void distance_vector_routing(vector<vector<int>>& distance_table, int num_nodes) {
    bool updated;
    do {
        updated = false;
        for (int i = 0; i < num_nodes; ++i) {
            for (int j = 0; j < num_nodes; ++j) {
                for (int k = 0; k < num_nodes; ++k) {
                    if (distance_table[i][j] > distance_table[i][k] + distance_table[k][j]) {
                        distance_table[i][j] = distance_table[i][k] + distance_table[k][j];
                        updated = true;
                    }
                }
            }
        }
    } while (updated);
}

int main() {
    int num_nodes;

    // Input the number of nodes (routers) in the network
    cout << "Enter the number of routers (nodes): ";
    cin >> num_nodes;

    // Create the topology (graph) as an adjacency matrix
    vector<vector<int>> topology(num_nodes, vector<int>(num_nodes, INF));

    cout << "Enter the graph in the form of an adjacency matrix (use -1 for no connection):\n";
    for (int i = 0; i < num_nodes; ++i) {
        for (int j = 0; j < num_nodes; ++j) {
            if (i == j) {
                topology[i][j] = 0;  // Distance to self is 0
            } else {
                cout << "Enter the cost to go from router " << i << " to router " << j << " (-1 for no connection): ";
                int cost;
                cin >> cost;
                if (cost != -1) {
                    topology[i][j] = cost;
                }
            }
        }
    }

    // Initialize the distance table based on the input graph
    vector<vector<int>> distance_table(num_nodes, vector<int>(num_nodes, INF));

    // Set the initial distances based on the graph (topology)
    for (int i = 0; i < num_nodes; ++i) {
        for (int j = 0; j < num_nodes; ++j) {
            if (i == j) {
                distance_table[i][j] = 0;
            } else {
                distance_table[i][j] = topology[i][j];
            }
        }
    }

    // Print the initial network topology
    cout << "Initial Network Topology:\n";
    print_distance_table(distance_table, num_nodes);

    // Run the Distance Vector Routing algorithm
    cout << "Running Distance Vector Routing...\n";
    distance_vector_routing(distance_table, num_nodes);

    // Print the final distance table after routing
    cout << "Final Distance Vector Table after routing:\n";
    print_distance_table(distance_table, num_nodes);

    return 0;
}
