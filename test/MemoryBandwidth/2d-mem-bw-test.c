int A[200][200];
int B[200][200];

void poly_test() {
  int i,j;
  for (i = 0; i < 200; i++) {
    for (j = 0; j < 200; j++) {
       A[i][j] = B[j][i]*A[j][i]*90;
    }
  }
}

int main() {
  poly_test();
  return 0;
}

