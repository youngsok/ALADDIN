#include "bb_gemm.h"
#include "gem5/dma_interface.h"

void bb_gemm(int x[N], int y[N], int z[N]){
#ifdef DMA_MODE
	dmaLoad(&x[0], ROWSIZE*BLOCKSIZE*4*8);
  dmaLoad(&y[0], BLOCKSIZE*BLOCKSIZE*4*8);
  dmaLoad(&z[0], ROWSIZE*BLOCKSIZE*4*8);
#endif
  int i, k, j, temp_x;
	loopi:for ( i = 0; i < ROWSIZE; ++i){
		loopk:for (k = 0; k < BLOCKSIZE; ++k){
	      		temp_x = x[i * ROWSIZE + k];
			loopj:for (j = 0; j < BLOCKSIZE; ++j){
	      			z[i * ROWSIZE + j] += temp_x * y[k*ROWSIZE + j];
      			}

      		}
	}
#ifdef DMA_MODE
	dmaStore(&z[0], ROWSIZE*BLOCKSIZE*4*8);
#endif
}
void print(int *a, int size)
{
	int i;

	for (i = 0; i < size; i++)
		printf("%u\t", a[i]);
}

int main()
{
	int i;
  int  *x;
  int *y;
  int *z;
  x = (int*) malloc(sizeof(int) * N); //ROWSIZE * BLOCKSIZE
  y = (int*) malloc(sizeof(int) * N); //BLOCKSIZE * BLOCKSIZE
  z = (int*) malloc(sizeof(int) * N);

  int max, min;
	srand(8650341L);
  max = 128;
  min = 0;
  for(i=0; i<N; i++){
    x[i] = (TYPE)(((double) rand() / (RAND_MAX)) * (max-min) + min);
    y[i] = (TYPE)(((double) rand() / (RAND_MAX)) * (max-min) + min);
    z[i] = 0;
  }

	bb_gemm(x, y, z);
  print(z, N);
	printf("\n");

	return 0;
}

