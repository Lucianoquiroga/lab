#include <string.h>

#include "parser.h"

int count_w(char *line)
{
    	char *tok;
    	char *delim = " ";
    	int count = 0;

    	for (tok = strtok(line, delim);
		tok != NULL;
            	tok = strtok(NULL, delim), count++);

    	return count;
}

int count_s(char *line)
{
	//Lista de palabras: Hypertext, protocol, HTTP, MIME, gateway, URL y URI.
	char *tok, *line2;
	char *delim = " ";
	int count = 0, h, h1;
	char key[] = "Hypertext";
	char key1[] = "hypertext";
	

	for (tok = strtok(line, delim); tok != NULL; tok = strtok(NULL, delim)){

		h = strcmp(key,tok);
		h1 = strcmp(key1,tok);

		if(h == 0){
                	count++;
		}	
		if(h1 == 0){
			count++;
		}
	}	

	return count;
}

int count_ss(char *line)
{
        //Lista de palabras: Hypertext, protocol, HTTP, MIME, gateway, URL y URI.
        char *tok;
        char *delim = " ";
        int count = 0, h, h1;
        char key[] = "Protocol";
    	char key1[] = "protocol";
    
        for (tok = strtok(line, delim); tok != NULL; tok = strtok(NULL, delim)){

                h = strcmp(key,tok);
		h1 = strcmp(key1,tok);

                if(h == 0){
                        count++;
                }
		if(h1 == 0){
			count++;	
		}
        }

        return count;
}

