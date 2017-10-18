#include "http.h"

struct sockaddr_in server = {};

int main() {

	int sdl, sdc, val, *sdch;
	sdl = socket(AF_INET, SOCK_STREAM, 0);
	server.sin_family = AF_INET;
	server.sin_port = htons(5000);
	server.sin_addr.s_addr = htonl(INADDR_ANY);

	setsockopt(sdl, SOL_SOCKET, SO_REUSEADDR, &val, sizeof (val));

	if (bind(sdl, (struct sockaddr *)&server, sizeof (server)) !=0) {

		perror("Error en bind");
		return -1;

	}

	if(listen(sdl, 5) != 0) {

		perror("Error de listen");
		return -2;
	}

	pthread_t tid1;
	while((sdc = accept(sdl, NULL, 0)) > 0) {
	
		if((sdch = malloc(sizeof (int))) == NULL){

			perror("malloc");
			exit(EXIT_FAILURE);
		}
		*sdch = sdc;

		if((pthread_create(&tid1, NULL, &http, (void *)sdch)) != 0){
			
			perror("pthread");
			exit(EXIT_FAILURE);
		}

	}
	
	pthread_exit(NULL);

	return 0;
} 
