all:
	clang -Xclang -load -Xclang LLVMPolly.so -O0 -mllvm -polly 2d-mem-bw-test.c -S -emit-llvm -o llfile.s
	opt -load LLVMPolly.so -S -basicaa -polly -polly-opt-isl -polly-codegen-isl -polly-ast llfile.s  -analyze
#	opt -load LLVMPolly.so  -basicaa -polly -polly-opt-isl -polly-codegen-isl  -polly-ast llfile.s  -o=llfile_optimised.bc

#	clang llfile_optimised.bc -o exe_opt
#	clang 2d-mem-bw-test.c    -o exe
#	clang 2d-mem-bw-test.c -O3 -o exe_O3

