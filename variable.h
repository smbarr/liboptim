#ifndef __VARIABLE_H__
#define __VARIABLE_H__

#include <glpk.h>
#include <string>

class variable {
  public:
    variable();
    variable(std::string, int, double, double, double);
    ~variable();

    int id; // Set when added to the optimization problem
    std::string name;
    int varType;
    double lowerBound, upperBound;
    double objCoef;
    double val;

    void setName(std::string);
    void setVarType(int);
    void setObjCoef(double);
    void setLowerBound(double);
    void setUpperBound(double);
    void setBounds(double, double);
    double getObjCoef();
    double* getBounds();
    double getLowerBound();
    double getUpperBound();
    int getVarType();
};

#endif
