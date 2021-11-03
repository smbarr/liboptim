## libOptim - An abstracted library for specifying optimization problems

### About

libOptim is currently built for GLPK. Its goal is to make the specification of an optimization problem using sparse matrices simpler and more readable.

### Tutorial

1. Initialize optimization problem

`optim *opt = new optim(MIN, 3, 2)`

2. Create a decision variable

`variable *v1 = new variable(string("x1"), CONTINUOUS, 1.0, 0.0, 10.0);`

3. Create a constraint

`constraint *c1 = new constraint(string("c1"), LT, 5.0);`

4. Add variables to a constraint

`c1->addVariable(v2,  1.0);`\
`c1->addVariable(v1,  1.0);`

5. Add variables and constraints to optimization

`opt->addVariable(v1);`\
`opt->addConstraint(c1);`

6. Build and solve problem

`opt->load();`\
`opt->solve(true); // Boolean controls output to terminal `\
`opt->getSolution();`\
`opt->cleanUp();`
