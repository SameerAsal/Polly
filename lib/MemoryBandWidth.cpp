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
//
//===----------------------------------------------------------------------===//

#include "polly/Dependences.h"
#include "isl/aff_type.h"
#include "isl/union_map.h"
#include "polly/LinkAllPasses.h"
#include "polly/ScopInfo.h"

using namespace llvm;
using namespace polly;

namespace {

class MemoryBandwidth : public ScopPass {

public:
  static char ID;
  explicit MemoryBandwidth() : ScopPass(ID) {}

  virtual bool runOnScop(Scop &S);
  void printScop(llvm::raw_ostream &OS) const;
  void getAnalysisUsage(AnalysisUsage &AU) const;
};
}

char MemoryBandwidth::ID = 0;

bool MemoryBandwidth::runOnScop(Scop &S) {
  Dependences *D = &getAnalysis<Dependences>();

  int Kinds =
      Dependences::TYPE_RAW | Dependences::TYPE_WAR | Dependences::TYPE_WAW;

  isl_union_map *Deps = D->getDependences(Kinds);

  isl_union_map_free(Deps);
  return false;
}

void MemoryBandwidth::printScop(raw_ostream &OS) const {}

void MemoryBandwidth::getAnalysisUsage(AnalysisUsage &AU) const {
  ScopPass::getAnalysisUsage(AU);
  AU.addRequired<Dependences>();
}

Pass *polly::createMemoryBandwidth() { return new MemoryBandwidth(); }

INITIALIZE_PASS_BEGIN(MemoryBandwidth, "polly-bwm",  "Compute memory Bandwidth", false, false)
INITIALIZE_PASS_DEPENDENCY(Dependences)
INITIALIZE_PASS_DEPENDENCY(ScopInfo)
INITIALIZE_PASS_END(MemoryBandwidth, "polly-bwm", "Compute memory Bandwidth",  false, false)

