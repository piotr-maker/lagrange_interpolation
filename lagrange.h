# ifndef LAGRANGE_H
#define LAGRANGE_H

#include <cmath>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

class Lagrange {
public:
    struct Node {
        double x;
        double y;
        Node(double x, double y) : x(x), y(y) {};
    };

    Lagrange();
    ~Lagrange();
    void addNode(double x, double y);
    void calculate();
    double getMinArg();
    double getMaxArg();
    string getPolymonial();
    double getValue();
    vector<Node> getNodes();
    void reset();
    void setArgument(double x);
    int size();

private:
    char const *exponent[10] = { "\u2070", "\u00B9", "\u00B2", "\u00B3", "\u2074", "\u2075", "\u2076", "\u2077", "\u2078", "\u2079" };

    bool argument_set = false;
    double argument;
    double value = 0;
    double min_x = NAN;
    double max_x = NAN;
    double *polymonial = nullptr;
    vector<Node> nodes;
    double denominator(int k);
    double *numerator(int k);
};

#endif // LAGRANGE_H
