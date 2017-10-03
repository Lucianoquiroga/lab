#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "proc.h"

int main(int argc, char **argv)
{
	char buffer[80];
	int nread;
	//int pfd[3][2];
	int pfd[2][2];

	/*for(int i=0; i<3; i++){
		pipe(pfd[i]);
		launchProc(i, pfd[i]);	
	}*/

	int *mcomp;
	int om;

	om = shm_open("/objeto", O_CREAT|O_RDWR, 0644);

	mcomp = mmap(NULL, 100, PROT_READ|PROT_WRITE, MAP_SHARED, om, 0);


	printf("Leido: %d\n", *mcomp);






	for(int i=0; i<2; i++){
                pipe(pfd[i]);
                launchProc(i, pfd[i]);  
        }


	close(pfd[0][0]);
	close(pfd[1][0]);
	//close(pfd[2][0]);
	
	do {
		memset(buffer, 0, sizeof buffer);
		nread = read(STDIN_FILENO, buffer, sizeof buffer);
		//write(STDOUT_FILENO, buffer, nread);
		write(pfd[0][1], buffer, nread);
		write(pfd[1][1], buffer, nread);
		//write(pfd[2][1], buffer, nread);
	} while (nread > 0);

	close(pfd[0][1]);
	close(pfd[1][1]);
	//close(pfd[2][1]);
	
	return 0;
}

