 #include <stdio.h>
 #include <omp.h>
 #define NUM_THREADS 5

FILE *fptr;

int main(int argc, char const *argv[]){
  omp_set_num_threads(NUM_THREADS);
  fptr = fopen("Jam","w"); 
  float mat[100][100];
  float C[100][100];
  float num = 1.0;
  int j;
  int i;
  int n = 100;
  double t1,t2,tiempo;

  t1 = omp_get_wtime();
  for (int i = 0; i < 100; i++) {
    for (int j = 0; j < 100; j++) {
      mat[i][j] = j;
      C[i][j] = 0;
    }
  }

  for(int i=0; i<100; i++){
    for(int j=0; j<100; j++){
      for(int k=0; k<100; k++){
       C[i][j] = 0;
        C[i][j] += mat[i][k] * mat[i][k];
      }
    }

  }

  #pragma omp parallel
  {
  	#pragma omp for 

  	for( i = 0; i < 100; i++){
  	 for ( j = 0; j < 100; j++){
      fprintf(fptr,"%f , ", C[i][j]);
      if (j*1 == 99) {
         fprintf(fptr,"\n");
         }
     } 
    }
   }

  t2 = omp_get_wtime();
  tiempo = t2-t1;
  fprintf(fptr, "Tiempo: %f", tiempo);
  fclose(fptr);
} 