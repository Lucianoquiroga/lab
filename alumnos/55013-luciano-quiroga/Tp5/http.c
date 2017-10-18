#include "http.h"

void *http(void *sd_conn){
	
	int fd, leido, leido2, sdc;
	long longitud = 0;
	char buff[1024], buff2[1024], archivo[256], mime[256];
	char *version = NULL, *estado = NULL, cabecera[512], *version2 = "HTTP/1.1";
	char *ruta = "archivos/";
	sdc = *((int *)sd_conn);

	if (sd_conn != NULL){
		free(sd_conn);
	}

	memset(buff, 0, sizeof(buff));
	memset(buff2, 0, sizeof(buff2));
	memset(archivo, 0, sizeof(archivo));
	memset(mime, 0, sizeof(mime));
	memset(cabecera, 0, sizeof(cabecera));

	if((leido = read(sdc, buff, sizeof(buff))) > 0){

		version = Solicitud(buff, archivo, mime, ruta, &longitud);

                if (!(strncmp(buff,"GET",3) == 0)){
                        estado = "500 INTERNAL SERVER ERROR\n";
                        write(sdc,estado,strlen(estado));
                        exit(0);
                } else if (!(strncmp(version,"HTTP/1.1",8) == 0)){
                        estado = "ERROR VERSION --> HTTP/1.1\n";
                        write(sdc,estado,strlen(estado));
                        exit(0);
                } else if ((fd = open(archivo, O_RDONLY)) < 0){
                        estado = "404 Not Found: Recurso no encontrado!\n";
                        write(sdc,estado,strlen(estado));
                } else {
		
			estado = "200 OK";

			leido2 = snprintf(cabecera, sizeof cabecera, "%s %s\r\nContent-Length: %ld\r\nContent-Type: %s\r\n\r\n", version2, estado, longitud, mime);
	
			write(sdc, cabecera, leido2);

			while((leido2 = read(fd, buff2, sizeof buff2)) > 0){

				write(sdc, buff2, leido2);
	
				memset(buff2, 0, sizeof(buff2));

			}

			close(fd);
			close(sdc);
		}

	}

	close(fd);
	close(sdc);
	pthread_exit(NULL);
}

