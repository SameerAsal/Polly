# Create a canonicalized llvm IR file first.

if [[ "$#" -ne 1 ]]; then 
	echo "Number of argumemts you passed:" $#
	echo "Expected one argment"
        echo "Please pass input source name"
    	exit
fi
outfile=$1.ll
clang -Xclang -load -Xclang /home/sameer/svn/polly/llvm_build/lib/LLVMPolly.so -S -emit-llvm -O0  -mllvm -polly $1 -o $outfile
opt -S -load LLVMPolly.so ./$outfile -q -basicaa -analyze -mem-bw 



