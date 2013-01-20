//===- DeadCodeElimination.cpp - Eliminate dead iteration  ----------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This is a skeleton that is meant to contain a dead code elimination pass
// later on.
//
// The idea of this pass is to loop over all statements and to remove statement
// iterations that do not calculate any value that is read later on. We need to
// make sure to forward RAR and WAR dependences.
//
// A case where this pass might be useful is
// http://llvm.org/bugs/show_bug.cgi?id=5117
//
//===----------------------------------------------------------------------===//

#include "polly/Dependences.h"
#include "isl/aff_type.h"
#include "isl/union_map.h"
#include "polly/LinkAllPasses.h"
#include "polly/ScopInfo.h"
#include "isl/union_map.h"
#include "isl/set.h"

using namespace llvm;
using namespace polly;

namespace {

class DeadCodeElim : public ScopPass {

public:
  static char ID;
  explicit DeadCodeElim() : ScopPass(ID) {
  }

  virtual bool runOnScop(Scop &S);
  void printScop(llvm::raw_ostream &OS) const;
  void getAnalysisUsage(AnalysisUsage &AU) const;
};
}

char DeadCodeElim::ID = 0;

bool DeadCodeElim::runOnScop(Scop &S) {
  Dependences *D = &getAnalysis<Dependences>();
  isl_union_map *Dependences_WAW = D->getDependences(Dependences::TYPE_WAW);
  isl_union_map *Dependences_RAW = D->getDependences(Dependences::TYPE_RAW);
  isl_union_set *OriginalDomain = S.getDomains();

  isl_union_map *IterationsToDeleteDomainsMap;
  isl_union_set *IterationsToDelete ;
  isl_union_set *NewDomains;
  bool converged = false;

  printf("Dependence_RAW\n");
  isl_union_map_dump(Dependences_RAW);

  printf("Dependence_WAW\n\n");
  isl_union_map_dump(Dependences_WAW);
  int count = 0;
  while(!converged){

    printf("count = %i.\n",count++);
    IterationsToDeleteDomainsMap = isl_union_map_subtract(isl_union_map_copy(Dependences_WAW), isl_union_map_copy(Dependences_RAW));
    IterationsToDelete = isl_union_map_domain(IterationsToDeleteDomainsMap);

    printf("Iterations to delete:\n");
    isl_union_set_dump(IterationsToDelete);

    converged = isl_union_set_is_empty(IterationsToDelete);
    NewDomains = isl_union_set_subtract(OriginalDomain,isl_union_set_copy(IterationsToDelete));

    printf("New Domains\n");
    isl_union_set_dump(NewDomains);

    //Update the RAW dependence map after deleting the statements.
    Dependences_RAW = isl_union_map_subtract_domain(Dependences_RAW,isl_union_set_copy(IterationsToDelete));
    Dependences_RAW = isl_union_map_subtract_range(Dependences_RAW,isl_union_set_copy(IterationsToDelete));

    printf("New Dependence_RAW\n");
    isl_union_map_dump(Dependences_RAW);

    //Update the WAW dependence map after deleting the statements.
    Dependences_WAW = isl_union_map_subtract_domain(Dependences_WAW,isl_union_set_copy(IterationsToDelete));
    Dependences_WAW = isl_union_map_subtract_range(Dependences_WAW,IterationsToDelete);

    printf("New Dependence_WAW\n");
    isl_union_map_dump(Dependences_WAW);
    OriginalDomain = NewDomains;
    printf("******Loop Finished******\n\n\n");

  }

  isl_union_map_free(Dependences_RAW);
  isl_union_map_free(Dependences_WAW);

  for (Scop::iterator SI = S.begin(), SE = S.end(); SI != SE; ++SI) {
    ScopStmt *Stmt = *SI;
    isl_set *StmtDomain = Stmt->getDomain();
    isl_union_set *StmtDomainUnion = isl_union_set_from_set(StmtDomain);
    isl_union_set *NewStmtDomainUnion =
        isl_union_set_intersect(StmtDomainUnion, isl_union_set_copy(NewDomains));
    isl_set *NewStmtDomain;
    if (isl_union_set_is_empty(NewStmtDomainUnion)) {
      NewStmtDomain = isl_set_empty(Stmt->getDomainSpace());
      isl_union_set_free(NewStmtDomainUnion);
    } else {
      NewStmtDomain = isl_set_from_union_set(NewStmtDomainUnion);
    }
    Stmt->restrictDomain(NewStmtDomain);
  }
  isl_union_set_free(NewDomains);
  return false;
}

void DeadCodeElim::printScop(raw_ostream &OS) const {
}

void DeadCodeElim::getAnalysisUsage(AnalysisUsage &AU) const {
  ScopPass::getAnalysisUsage(AU);
  AU.addRequired<Dependences>();
}

Pass *polly::createDeadCodeElimPass() { return new DeadCodeElim(); }

INITIALIZE_PASS_BEGIN(DeadCodeElim, "polly-dce",
                      "Polly - Remove dead iterations", false, false)
INITIALIZE_PASS_DEPENDENCY(Dependences)
INITIALIZE_PASS_DEPENDENCY(ScopInfo)
INITIALIZE_PASS_END(DeadCodeElim, "polly-dce",
                      "Polly - Remove dead iterations", false, false)

Pass* polly::createDeadCodeElimPass() {
  return new DeadCodeElim();
}
