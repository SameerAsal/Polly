int A[256][256];
int B[256][256];
int C[256][256];
int x[256];
int y[256];
int tmp[256];
#define _PB_NY 256
#define _PB_NX 256

#define _PB_NI 256
#define _PB_NJ 256
#define _PB_NK 256
#define _PB_N 256

void kernel_gemm() {
#pragma scop
  int i, j, k;
  /* C := alpha*A*B + beta*C */
  for (i = 0; i < _PB_NI; i++)
    for (j = 0; j < _PB_NJ; j++)
      {
	C[i][j] = 1.0;
	for (k = 0; k < _PB_NK; ++k)
	  C[i][j] += 9.0 * A[i][k] * B[k][j];
      }
#pragma endscop
}

int main() {
  kernel_gemm();
  return 0;
}

