#include "imdb.h"

int read_db(char object, const char* name_serial, char file_name[])
{
	char string[LENGTH_STRING_IN_FILE], string_cp[LENGTH_STRING_IN_FILE];
	int i=0, k=0, pos=0, pos1=0, count_tab=0, count_match=0; //pos = position of first tab, pos1 = position of 2 tab
	FILE *l_db;

	if((l_db=fopen(config_file, "r")) == NULL) {
                 printf("Error while open file %s\n", config_file);
                 perror("");
                 exit(1);
         }

	while(!feof(l_db)) {
		if (fgets(string, LENGTH_STRING_IN_FILE - 1, l_db)) { //last symbol is \0
			for(k=0; k <= strlen(string); k++) {
				if (string[k] == '\\' && count_tab == 0) { //we can make this in function below for optimized code but it will make later for example while - \ then count_tab++ and then print info
                  			pos=k;
					count_tab++;
				} else if (string[k] == '\\' && count_tab == 1) { //count +is for count tab symbol
					pos1=k;
					count_tab++;
				}
                	}
			i=0;
			while(string[i] != '\\') {
				if(pos && string[i] != '\0' && pos1) {

					if(copy_check(i, string, string_cp, strlen(name_serial), name_serial) != -1) {

						if(object == 'l') // if we have to print link let's do it
							get_string(pos, pos1, string, file_name);
						else if(object == 'n') //in other case we print name of serial
							get_string(0, pos, string, file_name);
						else if(object == 'f') //printing file name
							get_string(pos1, strlen(string), string, file_name);

						count_match++; //this will count matching string this is for no print unknown result
					}
				}
				i++;
			}
			pos=0;
			pos1=0;
			count_tab=0;
			int i;
			for(i=0; i<=strlen(string); i++)
				string[i] = '\0';
		}
	}
	fclose(l_db);
	return count_match;
}
