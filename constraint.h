#ifndef __CONSTRAINT_H__
#define __CONSTRAINT_H__

#include <optim_defs.h>
#include <glpk.h>
#include <string>
#include <vector>
#include <variable.h>

class constraint {
  public:
    constraint();
    constraint(std::string, int, double);
    constraint(std::string, double, double);
    constraint(std::string, int, double, double);
    ~constraint();

    int id; // Set when added to the optimization problem
    int nonZeros;
    int side;
    std::string name;
    double lowerBound, upperBound;
    std::vector<variable*> variables;
    std::vector<double> coefs;

    void setName(std::string);
    void setLowerBound(double);
    void setUpperBound(double);
    void setBounds(double, double);
    double* getBounds();
    double getLowerBound();
    double getUpperBound();

    void addVariable(variable*, double);
};

#endif
