int A[200][200];
int B[200];

int main() {
  
  int i,j;
/* for (i = 0; i < 200; i++) {
     A[i] = 2;    //S 
  }

  for (i = 0; i < 200; i++) {
     B[i] = A[i]; //S3
  }*/

  for (i = 0; i < 200; i++) {
    for (j = 0; j < 200; j++) {
       A[i][j] = B[i]*90;
    }
  }

  return 0;
}
