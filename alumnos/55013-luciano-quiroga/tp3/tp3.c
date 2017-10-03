#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <ctype.h>
#include <getopt.h>

int main(int argc, char **argv)
{
	int leido;
	int a[2], b[2], c[2], d[2], e[2], f[2];
	char buff[2000], buffcopia[2000];
	char s2[] = " \n";
	char cantletras4[10], cantletras5[10], cantletras6[10];
	pid_t pid;
	int x, fdlec2;
	int fdlec1 = 0;
	int flags = 0,opt;
	int tfnd = 0;
	char *archivo1 = NULL;
	char *archivo2 = NULL;
	char archivole[20];
	char archivoes[20];
	char archivolec1[20], archivolec2[20];

	memset(buff, '\0',  2000);
	memset(buffcopia, '\0',  2000);
	memset(cantletras4, '\0', 10);			
	memset(cantletras5, '\0', 10);			
	memset(cantletras6, '\0', 10);	
	
	while (( opt = getopt(argc, argv, "i:o:")) != -1){
		
		switch(opt){

			case 'i':
				archivo1 = optarg;
				sprintf(archivole, "%s", archivo1);
				fdlec1 = open(archivole,O_RDONLY); 			
				flags = 1;
				break;
			case 'o':
				archivo2 = optarg;
				sprintf(archivoes, "%s", archivo2);
				tfnd = 1;
				break;
			default:
				exit(EXIT_FAILURE);
		}
	}
	pipe(a);
	pipe(b);
	pipe(c);
	pipe(d);
	pipe(e);
	pipe(f);

	printf("PADRE: Soy el proceso con id = %d. \n", getpid());

	printf("\n");
	
	for(x=1;x<=3;x++){
	
		pid = fork();
		if(pid){
			
			if(x == 1){
		
				close(a[0]);
				close(b[1]);	
			
				sprintf(archivolec1,"./%s", archivole);			

		
				while((leido = read(fdlec1, buff, sizeof buff)) > 0){
					write(a[1], buff, sizeof buff);
					memset(buff, '\0', sizeof buff);	
				}
				//write(a[1], buff, sizeof buff);
				
				close(a[1]);
			}else if(x == 2){
				
				close(c[0]);
				close(d[1]);	

				sprintf(archivolec2,"./%s", archivole);			
				
				//fdlec2 = open(archivolec1, O_RDONLY);			
				lseek(fdlec1 ,0 ,SEEK_SET);	
				while((leido = read(fdlec1, buffcopia, sizeof buffcopia)) > 0){
					write(c[1], buffcopia, sizeof buffcopia);
					memset(buffcopia, '\0', sizeof buffcopia);	
				}
				//write(c[1], buff, sizeof buff);
			
				close(c[1]);
			}else{
							
				close(e[0]);
				close(f[1]);	

				sprintf(archivolec2,"./%s", archivole);			
				
				//fdlec2 = open(archivolec1, O_RDONLY);			
				lseek(fdlec1 ,0 ,SEEK_SET);	
				while((leido = read(fdlec1, buffcopia, sizeof buffcopia)) > 0){
					write(e[1], buffcopia, sizeof buffcopia);
					memset(buffcopia, '\0', sizeof buffcopia);	
				}
				//write(c[1], buff, sizeof buff);
			
				close(e[1]);
			}

		}else{
				
			if(x == 1){
				
			int leido2, cantidad2 = 0;
			char buff2[1000];
			char *palabras;					
			char cantletras2[10];
			int nchars;		
		
			printf("HIJO %d: Soy el hijo con id =  %d, mi padre tiene id =  %d.\n", x,getpid(),getppid());
			
			memset(buff2, '\0',  1000);
			memset(cantletras2, '\0', 10);			
			
			close(a[1]);
			close(b[0]);
				
			while((leido2 = read(a[0], buff2, sizeof buff2)) > 0){
			
				palabras = strtok(buff2, s2);			
			
				while((palabras = strtok(NULL, s2)) != NULL){
			
					cantidad2++;			

				}	
			}
		
			close(a[0]);
			printf("HIJO 1: Cantidad de palabras %d.\n", cantidad2);	
		
			nchars = sprintf(cantletras2,"%d", cantidad2);

			write(b[1], cantletras2, nchars);		
		
			close(b[1]);
			printf("HIJO 1: Ahora por fin termino.\n");
			
			return 0;

			}else if(x == 2){
				
			int leido2, cantidad2 = 0;
			char buff2[2000];
			char *palabras;					
			char cantletras2[10];
			int nchars;		
		
			printf("HIJO %d: Soy el hijo con id =  %d, mi padre tiene id =  %d.\n", x,getpid(),getppid());
			
			memset(buff2, '\0',  2000);
			memset(cantletras2, '\0', 10);			
			
			close(c[1]);
			close(d[0]);
				
			while((leido2 = read(c[0], buff2, sizeof buff2)) > 0){
			
				palabras = strtok(buff2, s2);			
			
				while((palabras = strtok(NULL, s2)) != NULL){
			
					cantidad2++;			

				}	
			}
		
			close(c[0]);
			printf("HIJO 2: Cantidad de palabras %d.\n", cantidad2);	
		
			nchars = sprintf(cantletras2,"%d", cantidad2);

			write(d[1], cantletras2, nchars);		
		
			close(d[1]);
			printf("HIJO 2: Ahora por fin termino.\n");
	
			return 0;
					
			}else{
					
			int leido3, cantidad3 = 0, i, j, k,p;
			char buff3[2000], cantletras3[10];
			char *palabras3;
			char texto[40], texto2[40],texto3[40];
			int fd, nchars2, nchars3;
			char archivoesf[20];
			char palabra1[]= "Hypertext";
	
	
			printf("HIJO %d: Soy el hijo con id =  %d, mi padre tiene id =  %d.\n", x,getpid(),getppid());
			printf("Palabra %s\n", palabra1);	
			
			sprintf(archivoesf,"./%s", archivoes);			

			fd = open(archivoesf,O_WRONLY|O_CREAT|O_TRUNC, 0664);			
			
			memset(buff3, '\0',  2000);
			
			close(e[1]);
			close(f[0]);
								
			while((leido3 = read(e[0], buff3, sizeof buff3)) > 0){			
			
				palabras3 = strtok(buff3, s2);			
				
				memset(texto3, '\0', 40);			

				nchars3 = sprintf(texto3,"%s\n", palabras3);				

				for(i=0; texto3[i];i++){
				
					texto3[i] = toupper(texto3[i]);
				}
								
				write(fd, texto3, nchars3);

				while((palabras3 = strtok(NULL, s2)) != NULL){
					
					memset(texto2, '\0', 40);
					memset(texto, '\0', 40);
					//strcpy(texto2,palabras3);			
					//strcpy(texto,palabras3);			
					sprintf(texto2, "%s\n", palabras3);
					nchars2 = sprintf(texto, "%s\n", palabras3);

					for(i=0; texto2[i];i++){
				
						texto2[i] = tolower(texto2[i]); 

					}
					
					j = strcmp(texto, texto2);

					if(j < 0){
	
						for(k = 0; texto[k];k++){
							texto[k] = toupper(texto[k]);
						}

						//printf("%s\n", texto);
						cantidad3++;
						write(fd, texto, nchars2);
					}
				}	
			}
						

			close(e[0]);
			cantidad3++;
			printf("HIJO 3: Cantidad de palabras encontradas que empiezan con letras mayusculas %d.\n", cantidad3);	
		
			printf("HIJO 3: Las palabras encontradas se han convertido todas a mayusculas y se han copiado en el archivo salida.\n");	
			sprintf(cantletras3,"%d", cantidad3);
			
			write(f[1], cantletras3, strlen(cantletras3));		
			close(f[1]);
			printf("HIJO 3: Ahora por fin termino.\n");
	
			return 0;
			}
		}

	}
	
	read(b[0], cantletras4, sizeof cantletras4);
	read(d[0], cantletras5, sizeof cantletras5);		
	read(f[0], cantletras6, sizeof cantletras6);		
	
	printf("\nPADRE: Cantidad de palabras leidas del primer hijo %s.\n", cantletras4);	
	printf("PADRE: Cantidad de palabras leidas del segundo hijo %s.\n", cantletras5);	
	printf("PADRE: Cantidad de palabras leidas del segundo hijo %s.\n", cantletras6);	
	
	close(b[0]);
	close(d[0]);
	close(f[0]);

	printf("PADRE: Ahora por fin termino.\n");

	return 0;
}




/*						
			int leido3, cantidad3 = 0, i, j, k;
			char buff3[2000], cantletras3[10];
			char *palabras3;
			char texto[40], texto2[40],texto3[40];
			int fd, nchars2, nchars3;
			char archivoesf[20];
		
			printf("HIJO %d: Soy el hijo con id =  %d, mi padre tiene id =  %d.\n", x,getpid(),getppid());
			
			
			sprintf(archivoesf,"./%s", archivoes);			

			fd = open(archivoesf,O_WRONLY|O_CREAT|O_TRUNC, 0664);			
			
			memset(buff3, '\0',  2000);
			
			close(c[1]);
			close(d[0]);
								
			while((leido3 = read(c[0], buff3, sizeof buff3)) > 0){			
			
				palabras3 = strtok(buff3, s2);			
				
				memset(texto3, '\0', 40);			

				nchars3 = sprintf(texto3,"%s\n", palabras3);				

				for(i=0; texto3[i];i++){
				
					texto3[i] = toupper(texto3[i]);
				}
								
				write(fd, texto3, nchars3);

				while((palabras3 = strtok(NULL, s2)) != NULL){
					
					memset(texto2, '\0', 40);
					memset(texto, '\0', 40);
					//strcpy(texto2,palabras3);			
					//strcpy(texto,palabras3);			
					sprintf(texto2, "%s\n", palabras3);
					nchars2 = sprintf(texto, "%s\n", palabras3);

					for(i=0; texto2[i];i++){
				
						texto2[i] = tolower(texto2[i]); 

					}
					
					j = strcmp(texto, texto2);
	
					if(j < 0){
	
						for(k = 0; texto[k];k++){
							texto[k] = toupper(texto[k]);
						}

						//printf("%s\n", texto);
						cantidad3++;
						write(fd, texto, nchars2);
					}			

				}	
			}
						

			close(c[0]);
			cantidad3++;
			printf("HIJO 2: Cantidad de palabras encontradas que empiezan con letras mayusculas %d.\n", cantidad3);	
		
			printf("HIJO 2: Las palabras encontradas se han convertido todas a mayusculas y se han copiado en el archivo salida.\n");	
			sprintf(cantletras3,"%d", cantidad3);
			
			write(d[1], cantletras3, strlen(cantletras3));		
			close(d[1]);
			printf("HIJO 2: Ahora por fin termino.\n");
	
			return 0;*/
