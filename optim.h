#ifndef __OPTIM_H__
#define __OPTIM_H__

#include <glpk.h>
#include <optim_defs.h>
#include <variable.h>
#include <constraint.h>

class optim {
  public:
    optim(int, int, int);
    ~optim();

    int dir;
    int nVars;
    int nConstraints;
    int vID, cID;
    variable **variables;
    constraint **constraints;
    glp_prob *prob;
    int *ia, *ja;
    double *ar;
    int nonZeros;
    int solverStatus;

    //bool isValid();
    void setDir(int dir);
    void addVariable(variable*);
    void addConstraint(constraint*);
    variable* getVariable(int);
    constraint* getConstraint(int);
    void load();
    int solve(bool);
    void getSolution();
    void cleanUp();
};

#endif
