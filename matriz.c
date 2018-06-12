#include <stdio.h>
#include <time.h>

int cont = 0;
int num = 0;

int main(){
	int num;
	int matriz[3][3];
	srand(time(NULL));


	for (int i = 0; i<3; i++){
		for (int j = 0; j<3; j++){
			//num = rand() % 2;
			matriz[i][j]=rand() % 2;
		}
	}
	
	for (int row=0; row<3; row++){
		for(int columns=0; columns<3; columns++){
			printf("%d   ", matriz[row][columns]);
		}
		printf("\n");
	}
}
