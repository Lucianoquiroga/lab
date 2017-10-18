#include "http.h"

char *Solicitud (char *buff, char *archivo, char *mime, char *ruta, long *longitud){

	int fd, leido;
	char *buff2 = malloc(1024*sizeof(char)), *buff3 = malloc(256*sizeof(char)), *buff4 = malloc(256*sizeof(char));
	char buffleido[256];
	memset(buffleido, 0, sizeof(buffleido));
	char *version = malloc(256*sizeof(char));
	char *archivo2;
	char extensionaux[256];
	memset(extensionaux, 0, sizeof(extensionaux));
	char *extension = malloc (256*sizeof(char));
	
	strncpy(buff2, buff, strlen(buff));

	printf("%s\n", buff);

	strtok_r(buff2, " ", &version);
	strtok_r(NULL, " ", &version);

	buff3 = strtok(buff, "/");
	buff3 = strtok(NULL, " ");
	
	archivo2 = buff3;

	strncpy(extensionaux, archivo2, strlen(archivo2));

	buff4 = strtok(extensionaux, ".");
	buff4 = strtok(NULL, " ");
	
	if (buff4 == NULL){
                extension = "error";
        }else {
                extension = buff4;
        }

        if (strcmp(extension,"html") == 0){
                strncpy(mime,"text/html",256);
        }

        if (strcmp(extension,"jpg") == 0){
                strncpy(mime,"image/jpeg",256);
        }

        if (strcmp(extension,"pdf") == 0){
                strncpy(mime,"application/pdf",256);
        }

        if (strcmp(extension,"txt") == 0){
                strncpy(mime,"text/plain",256);
        }

        if (strcmp(extension,"png") == 0){
                strncpy(mime,"image/png",256);
        }

        if (strcmp(extension,"error") == 0){
                strncpy(mime,"error",256);
        }

	strncpy(archivo, ruta, 256);
	strncat(archivo, archivo2, 256);

	if ((fd = open(archivo,O_RDONLY)) != -1){

                while ((leido = read(fd,buffleido,sizeof(buffleido))) > 0)

                        *longitud = *longitud + leido;

                        close (fd);
        }

        return version;


}
