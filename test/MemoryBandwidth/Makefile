all:
	clang -Xclang -load -Xclang LLVMPolly.so -O0 -mllvm -polly 2d-mem-bw-test.c -S -emit-llvm -o ll.s
	#opt -load LLVMPolly.so -S -basicaa -polly -polly-opt-isl -polly-codegen-isl -polly-ast -polly-mem-bw ll.s  -analyze
	opt -load LLVMPolly.so -S -basicaa -polly -polly-mem-bw ll.s -analyze -o=/dev/null
	#opt -load LLVMPolly.so -S -basicaa -polly -polly-opt-isl -polly-codegen-isl ll.s  -o=ll_optimised.s
	#clang llfile_optimised.bc -o exe_opt
	#clang 2d-mem-bw-test.c    -o exe
	#clang 2d-mem-bw-test.c -O3 -o exe_O3
test:
	g++ test_case.cpp -o bandwidth_example
	g++ -O3 test_case.cpp -o bandwidth_example_O3 
	clang++ test_case.cpp -o bandwidth_example_clang
	clang++ -O3 test_case.cpp -o bandwidth_example_clang_O3
