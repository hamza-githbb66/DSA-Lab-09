#include <iostream>
#include <vector>
#include <string>
#include <cmath>
using namespace std;

// STAR SYSTEM CLASS
class StarSystem {
public:
    int system_id;
    string name;
    int num_planets;

    // Coordinates
    float x, y, z;

    bool is_habitable;

    // Child star systems
    vector<StarSystem*> children;

    // Travel costs to corresponding children
    vector<float> travel_costs;

    // Constructor
    StarSystem(int id, string n, int planets,
               float x1, float y1, float z1, bool habitable) {

        system_id = id;
        name = n;
        num_planets = planets;

        x = x1;
        y = y1;
        z = z1;

        is_habitable = habitable;
    }
};

// TRAVEL ROUTE CLASS
class TravelRoute {
public:
    float travel_cost;

    TravelRoute(float cost) {
        travel_cost = cost;
    }
};

// GALAXY CLASS
class Galaxy {
private:
    int M;
    StarSystem* root;

public:

    // Constructor with M only
    Galaxy(int m) {
        M = m;
        root = NULL;
    }

    // Overloaded constructor with M and root
    Galaxy(int m, StarSystem* r) {
        M = m;
        root = r;
    }
    // Add a child to a star system
    void addChild(StarSystem* parent,
                  StarSystem* child,
                  float cost) {

        if (parent == NULL || child == NULL) {
            return;
        }

        if (parent->children.size() < M) {

            parent->children.push_back(child);

            parent->travel_costs.push_back(cost);
        }
        else {
            cout << "Maximum children limit reached!" << endl;
        }
    }
    // Checking whether M-ary tree is balanced
    bool is_balanced(StarSystem* x) const {

        if (x == NULL) {
            return true;
        }

        int minSize = 100000;
        int maxSize = -1;

        // Checking every child subtree
        for (int i = 0; i < x->children.size(); i++) {

            StarSystem* child = x->children[i];

            // If any child subtree is unbalanced
            if (!is_balanced(child)) {
                return false;
            }

            // Calculate size of current child subtree
            int size = count_nodes(child);

            if (size < minSize) {
                minSize = size;
            }

            if (size > maxSize) {
                maxSize = size;
            }
        }

        // Leaf node is balanced
        if (x->children.size() == 0) {
            return true;
        }

        // Difference between child subtree sizes
        return (maxSize - minSize) <= 1;
    }
    // Count total nodes in a subtree
    int count_nodes(StarSystem* x) const {

        if (x == NULL) {
            return 0;
        }

        int count = 1;

        for (int i = 0; i < x->children.size(); i++) {

            count += count_nodes(x->children[i]);
        }

        return count;
    }
    // Count leaf nodes
    int count_leaves(StarSystem* x) const {

        if (x == NULL) {
            return 0;
        }

        // If node has no children, it is a leaf
        if (x->children.size() == 0) {
            return 1;
        }

        int count = 0;

        // Count leaves in all child subtrees
        for (int i = 0; i < x->children.size(); i++) {

            count += count_leaves(x->children[i]);
        }
        return count;
    }
    // Display galaxy tree
    void display(StarSystem* x) const {

        if (x == NULL) {
            return;
        }

        cout << "System ID: " << x->system_id
             << " | Name: " << x->name
             << " | Planets: " << x->num_planets
             << " | Habitable: " << (x->is_habitable ? "Yes" : "No")
             << endl;

        for (int i = 0; i < x->children.size(); i++) {

            cout << "  Travel Cost: "
                 << x->travel_costs[i] << endl;

            display(x->children[i]);
        }
    }
    // Get root node
    StarSystem* getRoot() const {
        return root;
    }
};

// MAIN FUNCTION
int main() {

    // Creating a star systems
    StarSystem* s1 = new StarSystem(1, "Milky Way", 8,
                                    0, 0, 0, true);
    StarSystem* s2 = new StarSystem(2, "Alpha", 4,
                                    10, 20, 30, true);
    StarSystem* s3 = new StarSystem(3, "Beta", 3,
                                    15, 25, 35, false);
    StarSystem* s4 = new StarSystem(4, "Gamma", 5,
                                    20, 30, 40, true);
    StarSystem* s5 = new StarSystem(5, "Delta", 2,
                                    25, 35, 45, false);
    StarSystem* s6 = new StarSystem(6, "Epsilon", 6,
                                    30, 40, 50, true);
    StarSystem* s7 = new StarSystem(7, "Zeta", 1,
                                    35, 45, 55, true);
    // Create Galaxy with maximum 3 children per node
    Galaxy galaxy(3, s1);

    // Connect star systems and travel routes
    galaxy.addChild(s1, s2, 10.5);
    galaxy.addChild(s1, s3, 15.5);
    galaxy.addChild(s1, s4, 20.5);

    galaxy.addChild(s2, s5, 5.5);
    galaxy.addChild(s2, s6, 8.5);

    galaxy.addChild(s3, s7, 12.5);

    // Display Galaxy
    cout << "GALAXY REPRESENTATION" << endl;
    galaxy.display(galaxy.getRoot());

    // Check whether tree is balanced
    cout << "\nIs Galaxy Balanced? ";

    if (galaxy.is_balanced(galaxy.getRoot())) {
        cout << "Yes" << endl;
    }
    else {
        cout << "No" << endl;
    }

    // Count leaf nodes
    cout << "\nTotal Leaf Nodes: "
         << galaxy.count_leaves(galaxy.getRoot())
         << endl;

    return 0;
}