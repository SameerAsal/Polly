import os 
import subprocess 
import sys
import glob

def compile_with_gcc(InputFile, OutputFile):
  include  ="-Ipolybench-c-3.2/utilities/"
  utilities="polybench-c-3.2/utilities/polybench.c"
  timing   ="-DPOLYBENCH_TIME"
  subprocess.call(["gcc", include, InputFile, timing,"-O3", utilities, "-o"+OutputFile])

def compile_with_clang(InputFile,OutputFile):
  include  ="-Ipolybench-c-3.2/utilities"
  utilities="polybench-c-3.2/utilities/polybench.c"
  timing   ="-DPOLYBENCH_TIME"
  cmd=["clang","-O3",include, InputFile, timing, utilities,"-o"+OutputFile]
  subprocess.call(cmd)
  cmd=["clang","-O3","-Xclang","-load","-Xclang","LLVMPolly.so","-mllvm","-polly",include, InputFile, timing, utilities,"-o"+OutputFile+"_polly"]
  subprocess.call(cmd)

def compute_mem_bandwidth(InputFile, view_scops=True,kernel_only=True): 
  include  = "-Ipolybench-c-3.2/utilities"
  utilities= "polybench-c-3.2/utilities/polybench.c"
  llfile   = "Internediate/"+InputFile.split('/')[-1][:-2] + ".s"
  llfile_optimized = llfile.split(".")[0] + "-optimized.s"
  # We want the pass to only be executed on the krenel.
  func_name = "kernel_" + InputFile.split('/')[-1][:-2]

#       clang -Xclang -load -Xclang LLVMPolly.so -O0 -mllvm -polly 2d-mem-bw-test.c -S -emit-llvm -o llfile.s
#       opt -load LLVMPolly.so -S -basicaa -polly  llfile.s -view-scops -analyze 

  #compile  
  cmd_compile = ["clang", "-Xclang", "-load", "-Xclang", "LLVMPolly.so", "-O0", "-mllvm", "-polly", InputFile ,"-S", "-emit-llvm", "-o" +llfile]
  subprocess.call(cmd_compile)
  #optimize

  # opt -load LLVMPolly.so -S -basicaa -polly -polly-opt-isl -polly-codegen-isl -polly-ast llfile.s  -analyze
  cmd_opt = ["opt","-load","LLVMPolly.so","-basicaa","-polly","-polly-opt-isl", "-polly-codegen-isl","-S","-polly-ast", llfile, "-o="+llfile_optimized]
  
  if view_scops == True:
    cmd_opt.append("-dot-scops")

  subprocess.call(cmd_opt)

def MoveDotfiles():
  files = glob.glob("*dot")
  files += glob.glob("*.ll")
  files += glob.glob("*.s")
  for dot_file in files:
    os.rename(dot_file, "Internediate/" + dot_file)
    

def main():
  compute_mem_bandwidth(sys.argv[1],view_scops=False, kernel_only=False)  
  exe = ""
  if len(sys.argv) == 3:
     exe = "Internediate/"+sys.argv[2]
  else: 
     exe =  "Internediate/executable"

 # compile_with_gcc(  str(sys.argv[1]).strip(), exe + "_gcc")
 # compile_with_clang(str(sys.argv[1]).strip(), exe +"_clang" )
  MoveDotfiles()

if __name__ == "__main__":
    main()



