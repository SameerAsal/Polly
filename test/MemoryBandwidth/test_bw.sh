# Create a canonicalized llvm IR file first.
clang -Xclang -load -Xclang /home/sameer/svn/polly/llvm_build/lib/LLVMPolly.so -S -emit-llvm -O0  -mllvm -polly mem-bw-test.c -o mem-bw-test.ll 
opt -S -load LLVMPolly.so ./mem-bw-test.ll -q -basicaa -analyze -mem-bw




