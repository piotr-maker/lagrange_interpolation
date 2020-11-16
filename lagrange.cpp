#include "lagrange.h"


Lagrange::Lagrange() {;}

Lagrange::~Lagrange() {
    if(this->polymonial != nullptr)
        delete [] this->polymonial;
}

void Lagrange::addNode(double x, double y) {
    nodes.push_back(Node(x, y));
    if(x > this->max_x || isnan(this->max_x)) this->max_x = x;
    if(x < this->min_x || isnan(this->min_x)) this->min_x = x;
}

void Lagrange::calculate() {
    this->polymonial = new double[this->size()];
    double denominator;
    double *numerator;

    for(int i = 0; i < this->size(); i++)
        this->polymonial[i] = 0;

    for(int i = 0; i < this->size(); i++) {
        denominator = this->denominator(i);
        numerator = this->numerator(i);
        for(int j = 0; j < this->size(); j++) {
            this->polymonial[j] += this->nodes[i].y * (numerator[j] / denominator);
        }

        delete [] numerator;
    }
    

    if(this->argument_set) {
        if(this->min_x <= this->argument && this->max_x >= this->argument) {
            for(int i = 0; i < this->size(); i++)
                this->value += pow(this->argument, i) * this->polymonial[i];
        } else
            this->argument_set = false;
    }
}

double Lagrange::getMinArg()
{
    return this->min_x;
}

double Lagrange::getMaxArg()
{
    return this->max_x;
}


string Lagrange::getPolymonial() {
    stringstream ss;

    for(int i = this->size() - 1; i >= 0; i--) {
        if(this->polymonial[i] == 0) continue;
        else if(this->polymonial[i] < 0) ss << " - ";
        if(i != this->size() - 1)
            if(this->polymonial[i] >= 0) ss << " + ";
        ss << abs(this->polymonial[i]);
        if(i != 0) ss << " \u2981 " <<'x' << this->exponent[i];
    }

    return ss.str();
}


double Lagrange::getValue() {
    return this->value;
}

vector<Lagrange::Node> Lagrange::getNodes()
{
    return this->nodes;
}

void Lagrange::reset() {
    argument_set = false;
    value = 0;
    if(this->polymonial != nullptr)
        delete [] this->polymonial;
    this->polymonial = nullptr;
    nodes.clear();
}

void Lagrange::setArgument(double x) {
    this->argument = x;
    this->argument_set = true;
}


int Lagrange::size() {
    return this->nodes.size();
}

double Lagrange::denominator(int k) {
    double result = 1;

    for(int i = 0; i < this->size(); i++) {
        if(i == k) continue;
        result *= nodes[k].x - nodes[i].x;
    }

    return result;
}


double *Lagrange::numerator(int k) {
    int count = this->size();
    double* result = new double[count];
    double* temp = new double[count];
    int n = 2, init;

    for(int i = 0; i < this->size(); i++)
        result[i] = 0;

    // init first values
    if(k) init = 0;
    else init = 1;
  
    result[0] = -nodes[init].x;
    result[1] = 1;

    for(int node_index = 1; node_index < count; node_index++) {
        if(node_index == k or node_index == init) continue;
        for(int res_index = 0; res_index < n; res_index++) {
            temp[res_index + 1] += result[res_index];
            temp[res_index] += nodes[node_index].x * result[res_index] * (-1);
        }

        n++;
        // copy from temp to result and clear temp
        for(int j = 0; j < n; j++) {
            result[j] = temp[j];
            temp[j] = 0;
        }
    }

    delete [] temp;
    return result;
}
