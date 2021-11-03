#include <constraint.h>

// Constraint class
constraint::constraint() {
  this->id = -1;
  this->name = "";
  this->nonZeros = 0;
}

constraint::~constraint() {
}

constraint::constraint(std::string name, double lowerBound, double upperBound) {
  this->id = -1;
  this->name = name;
  this->side = GTLT;
  this->lowerBound = lowerBound;
  this->upperBound = upperBound;
  this->nonZeros = 0;
}

constraint::constraint(std::string name, int side, double lowerBound, double upperBound) {
  this->id = -1;
  this->name = name;
  this->side = side;
  this->lowerBound = lowerBound;
  this->upperBound = upperBound;
  this->nonZeros = 0;
}

constraint::constraint(std::string name, int side, double bound) {
  this->id = -1;
  this->name = name;
  this->side = side;
  this->lowerBound = 0.0;
  this->upperBound = 0.0;
  if(this->side == LT) {
    this->upperBound = bound;
  } else {
    this->lowerBound = bound;
  }
  this->nonZeros = 0;
}

void constraint::setName(std::string name) {
  this->name = name;
}

void constraint::setLowerBound(double lowerBound) {
  this->lowerBound = lowerBound;
}

void constraint::setUpperBound(double upperBound) {
  this->upperBound = upperBound;
}

void constraint::setBounds(double lowerBound, double upperBound) {
  this->lowerBound = lowerBound;
  this->upperBound = upperBound;
}

double* constraint::getBounds() {
  double *bounds = new double[2];
  bounds[0] = this->lowerBound;
  bounds[1] = this->upperBound;
  return bounds;
}

double constraint::getLowerBound() {
  return this->lowerBound;
}

double constraint::getUpperBound() {
  return this->upperBound;
}

void constraint::addVariable(variable *var, double coef) {
  this->variables.push_back(var);
  this->coefs.push_back(coef);
  this->nonZeros++;
}
