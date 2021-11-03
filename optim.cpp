#include <optim.h>

using namespace std;

// Optim class
optim::optim(int dir, int nVars, int nConstraints) {
  this->vID = 0;
  this->cID = 0;
  this->dir = dir;
  this->nVars = nVars;
  this->nConstraints = nConstraints;

  glp_init_env();
  this->prob = glp_create_prob();
  glp_set_obj_dir(this->prob, MIN);
  glp_add_cols(this->prob, nVars);
  glp_add_rows(this->prob, nConstraints);

  this->variables = new variable*[this->nVars];
  this->constraints = new constraint*[this->nConstraints];
}

optim::~optim() {
  delete [] this->variables;
  delete [] this->constraints;
  this->variables = NULL;
  this->constraints = NULL;
}

void optim::setDir(int dir) {
  this->dir = dir;
  glp_set_obj_dir(this->prob, dir);
}

void optim::addVariable(variable *var) {
  var->id = this->vID+1;
  this->variables[this->vID] = var;
  this->vID++;

  glp_set_col_bnds(this->prob, var->id, GLP_DB, var->lowerBound, var->upperBound);
  glp_set_col_kind(this->prob, var->id, var->varType);
  glp_set_obj_coef(this->prob, var->id, var->objCoef);
}

void optim::addConstraint(constraint *con) {
  con->id = this->cID+1;
  this->constraints[this->cID] = con;
  this->cID++;

  glp_set_row_name(this->prob, con->id, con->name.c_str());
  if(con->side == GT) {
    glp_set_row_bnds(this->prob, con->id, GLP_LO, con->lowerBound, 0);
  } else if(con->side == LT) {
    glp_set_row_bnds(this->prob, con->id, GLP_UP, 0, con->upperBound);
  } else {
    glp_set_row_bnds(this->prob, con->id, GLP_DB, con->lowerBound, con->upperBound);
  }
}

variable* optim::getVariable(int id) {
  return this->variables[id];
}

constraint* optim::getConstraint(int id) {
  return this->constraints[id];
}

void optim::load() {
  this->nonZeros = 0;
  for(int n=0;n<this->nConstraints;n++) {
    this->nonZeros += this->constraints[n]->nonZeros;
  }
  this->ia = new int[this->nonZeros+1];
  this->ja = new int[this->nonZeros+1];
  this->ar = new double[this->nonZeros+1];
  int cnt = 1;
  for(int c=0;c<this->nConstraints;c++) {
    for(int v=0;v<this->constraints[c]->variables.size();v++) {
      this->ia[cnt] = c+1;
      this->ja[cnt] = this->constraints[c]->variables[v]->id;
      this->ar[cnt] = this->constraints[c]->coefs[v];
      cnt++;
    }
  }
  glp_load_matrix(this->prob, this->nonZeros, this->ia, this->ja, this->ar);
}

int optim::solve(bool lOutput) {
  if(lOutput == true) {
    glp_term_out(GLP_ON);
  } else {
    glp_term_out(GLP_OFF);
  }
  glp_iocp parm;
  glp_init_iocp(&parm);
  glp_cpxcp cpparm;
  glp_init_cpxcp(&cpparm);
  glp_write_lp(this->prob, &cpparm, "out.lp");
  parm.presolve = GLP_ON;
  int err = glp_intopt(this->prob, &parm);
  this->solverStatus = glp_mip_status(this->prob);

  return err;
}

void optim::getSolution() {
  for(int v=0;v<this->nVars;v++) {
    this->variables[v]->val = glp_mip_col_val(this->prob, v+1);
  }
}

void optim::cleanUp() {
  delete [] ia;
  delete [] ja;
  delete [] ar;
  ia = ja = NULL;
  ar = NULL;

  glp_delete_prob(this->prob);
  glp_free_env();

  for(int c=0;c<this->nConstraints;c++) {
    this->constraints[c]->variables.clear();
    this->constraints[c]->variables.shrink_to_fit();
    delete this->constraints[c];
    this->constraints[c] = NULL;
  }

  for(int v=0;v<this->nVars;v++) {
    delete this->variables[v];
    this->variables[v] = NULL;
  }

  //delete [] this->variables;
  //delete [] this->constraints;
}
