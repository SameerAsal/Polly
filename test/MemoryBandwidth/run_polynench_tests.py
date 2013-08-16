import os 
import subprocess 
import sys

def CompileFile(compiler="", options="", inputFile="", output=""):
  subprocess.call(["ls", "-l"])

def compile_with_gcc(InputFile, OutputFile):
  compiler ="gcc"
  opt_level="-O3"
  include  ="-Iutilities/"
  utilities="polybench-c-3.2/utilities/polybench.c"
  timing   ="-DPOLYBENCH_TIME"
  subprocess.call([compiler, include, InputFile, timing, opt_level, utilities, "-o"+OutputFile])
  subprocess.call(["./"+OutputFile])

def compile_with_clang(InputFile,OutputFile):
  compiler ="clang"
  opt_level="-O3"
  include  ="-Iutilities/"
  utilities="polybench-c-3.2/utilities/polybench.c"
  timing   ="-DPOLYBENCH_TIME"
  subprocess.call([compiler,"-Xclang","-load", "-Xclang" ,"LLVMPolly.so" ,"-mllvm","-polly","-mllvm",include, InputFile, timing, opt_level, utilities, "-o"+OutputFile])
  subprocess.call("./"+OutputFile)

def compute_mem_bandwidth(InputFile): 
  compiler ="clang"
  include  ="-Ipolybench-c-3.2/utilities/"
  utilities="polybench-c-3.2/utilities/polybench.c"
  timing   ="-DPOLYBENCH_TIME"
  subprocess.call(["clang","-S","-emit-llvm","-O3","-Xclang","-load","-Xclang","LLVMPolly.so","-mllvm","-polly","-mllvm","-view-scops",include, InputFile, timing, utilities])

#  subprocess.call(["opt","-S","-load","LLVMPolly.so","./llfile.ll","-q","-basicaa","-analyze","-mem-bw"])


def main():
  print 'Argument List:', str(sys.argv)	

  compute_mem_bandwidth(sys.argv[1])
#  compile_with_gcc(  str(sys.argv[1]).strip(), str(sys.argv[2]) + "_gcc")
#  compile_with_clang(str(sys.argv[1]).strip(), str(sys.argv[2]) + "_clang")

if __name__ == "__main__":
    main()



