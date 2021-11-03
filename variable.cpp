#include <optim_defs.h>
#include <variable.h>

// Variable class
variable::variable() {
  this->id = -1;
  this->name = "";
  this->varType = CONTINUOUS;
  this->objCoef = 0.0;
  this->lowerBound = 0.0;
  this->upperBound = 0.0;
}

variable::~variable() {
}

variable::variable(std::string name, int varType, double objCoef, double lowerBound, double upperBound) {
  this->id = -1;
  this->name = name;
  this->varType = varType;
  this->objCoef = objCoef;
  this->lowerBound = lowerBound;
  this->upperBound = upperBound;
}

void variable::setName(std::string name) {
  this->name = name;
}

void variable::setVarType(int varType) {
  this->varType = varType;
}

void variable::setObjCoef(double objCoef) {
  this->objCoef = objCoef;
}

void variable::setLowerBound(double lowerBound) {
  this->lowerBound = lowerBound;
}

void variable::setUpperBound(double upperBound) {
  this->upperBound = upperBound;
}

void variable::setBounds(double lowerBound, double upperBound) {
  this->lowerBound = lowerBound;
  this->upperBound = upperBound;
}

double* variable::getBounds() {
  double *bounds = new double[2];
  bounds[0] = this->lowerBound;
  bounds[1] = this->upperBound;
  return bounds;
}

double variable::getLowerBound() {
  return this->lowerBound;
}

double variable::getUpperBound() {
  return this->upperBound;
}

double variable::getObjCoef() {
  return this->objCoef;
}

int variable::getVarType() {
  return this->varType;
}
