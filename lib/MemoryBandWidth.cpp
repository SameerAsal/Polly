//===- MemoryBandwidthination.cpp - Eliminate dead iteration  ----------------===//
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
#include "isl/map.h"

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
    // Count the number of statements.
    // Loop over all the statements in the scope.
//    int computation_count = 0;
	for (Scop::iterator SI = S.begin(); SI != S.end(); SI++) {
		ScopStmt *Stmt  = *SI;
		BasicBlock* bb =  Stmt->getBasicBlock();
		printf("Basic Block: %s\n",bb->getName());
		// loops over every instruction in the basic block.
		for (BasicBlock::iterator instruction = bb->begin(); instruction != bb->end(); instruction++) {
          if (instruction->mayReadOrWriteMemory()) {
            printf("\tMemory related instruction:\t%s\n", instruction->getOpcodeName());
             } else {
           		switch (instruction->getOpcode()) {
                  case Instruction::Add:
           		  case Instruction::Sub:
                  case Instruction::Mul:
				    printf("\tInstruction found, it is\t:\t%s\n", instruction->getOpcodeName());
                    break;
                 default:
                	 printf("\twInstruction is:\t\t%s\n", instruction->getOpcodeName());
  	           		}
           		}
		}
	}
	// Count the number of memory oprations:
	return false;
}

void MemoryBandwidth::printScop(raw_ostream &OS) const {}

void MemoryBandwidth::getAnalysisUsage(AnalysisUsage &AU) const {
	  ScopPass::getAnalysisUsage(AU);
}

Pass *polly::createMemoryBandwidthPass() { return new MemoryBandwidth(); }


INITIALIZE_PASS_BEGIN(MemoryBandwidth, "mem-bw",   "Polly - Compute memory Bandwidth", false, false)
INITIALIZE_PASS_DEPENDENCY(Dependences)
INITIALIZE_PASS_DEPENDENCY(ScopInfo)
INITIALIZE_PASS_END(MemoryBandwidth, "mem-bw", "Polly - Computes Memory Bandwidth",
                    false, false)
