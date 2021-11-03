/*//////////////////////////////
//   Problem Statement:
//
//   max x1+2*x2+x3
//   s.t.
//     x1+x2 <= 5
//     x3-x1 >= 2
*///////////////////////////////

#include <iostream>
#include <string>
#include <optim.h>

using namespace std;

int main(int argc, char** argv) {
  optim *opt = new optim(MIN, 3, 2);

  variable *v1 = new variable(string("x1"), CONTINUOUS, 1.0, 0.0, 10.0);
  variable *v2 = new variable(string("x2"), CONTINUOUS, 2.0, 0.0, 10.0);
  variable *v3 = new variable(string("x3"), INTEGER, 1.0, 0.0, 10.0);

  // x1+x2 <= 5
  constraint *c1 = new constraint(string("c1"), LT, 5.0);
  // x3-x1 >= 2
  constraint *c2 = new constraint(string("c2"), GT, 2.5);

  c1->addVariable(v2,  1.0);
  c1->addVariable(v1,  1.0);
  c2->addVariable(v1, -1.0);
  c2->addVariable(v3,  1.0);

  opt->addVariable(v1);
  opt->addVariable(v2);
  opt->addVariable(v3);

  opt->addConstraint(c1);
  opt->addConstraint(c2);

  opt->load();
  opt->solve(true);
  opt->getSolution();

  printf("Optimal solution:\n");
  printf("%s = %f\n",v1->name.c_str(),v1->val);
  printf("%s = %f\n",v2->name.c_str(),v2->val);
  printf("%s = %f\n",v3->name.c_str(),v3->val);

  opt->cleanUp();

  return 0;
}
