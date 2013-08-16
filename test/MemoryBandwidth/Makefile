all:
        clang -Xclang -load -Xclang LLVMPolly.so -O0 -mllvm -polly 2d-mem-bw-test.c -S -emit-llvm -o ll.s
        opt -load LLVMPolly.so -S -basicaa -polly -polly-opt-isl -polly-codegen-isl -polly-ast -polly-mem-bw ll.s  -analyze
        opt -load LLVMPolly.so -S -basicaa -polly -polly-opt-isl -polly-codegen-isl llfile.s  -o=ll_optimised.s
      #	clang llfile_optimised.bc -o exe_opt
#	clang 2d-mem-bw-test.c    -o exe
#	clang 2d-mem-bw-test.c -O3 -o exe_O3