#include "http.h"

int main() {

	int sdl, sdc,val;
	char *ruta = "archivos/";
	sdl = socket(AF_INET, SOCK_STREAM, 0);

	struct sockaddr_in server = {};

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

	signal(SIGCHLD, SIG_IGN);

	while((sdc = accept(sdl, NULL, 0)) > 0) {
	
		if(fork() == 0){
		
			close(sdl);
	
			http(sdc, (struct sockaddr *)&server, ruta);

			close(sdc);

			return 0;

		}

		close(sdc);	

	}

	return 0;
}

