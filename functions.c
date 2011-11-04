#include "imdb.h"

int copy_check(int k, char from[], char to[], int length, const char* str_search) //we can change this function for strstr(string_in_search, string_search)
{
	int i, h;
	i = h = 0;
	while (i != length) {
		to[i] = from[k + i];
		i++;
	}
	to[i] = '\0';
	i = 0;
        while (i < length) {

                if (to[i] == str_search[i])
                        h++;

                        i++;
        }
        if (h == length)
        return k;
        else return -1; //it's for check first symbol
}

void print_result(int pos, char str[])
{
	int g, i, position_1=0, position_2=0;
	g = 0;
        for (i = pos; i < strlen(str); ++i) {
        	if (str[i] == '>' && g == 0) {
        		position_1 = i;
        		++g;
        	}
        	if (str[i] == '<' && g == 1) {
        		position_2 = i;
        		++g;
        	}
      	}

       	while (position_1 < position_2) {
       		++position_1;
	
		if (position_1 == position_2);
        	else printf("%c", str[position_1]);
       	}
}

void print_season_episode(int pos, char str[])
{
	int i;
	i=pos;
	while(str[i] != '<') { //before was : - it's because exactly print what we need
		printf("%c", str[i]);
		i++;
	}
}

void get_string(int pos, int length, char string[], char result_string[])
{
	int i=0;
	if(!pos) {
		for(i=0; i < (length - pos); i++)
			result_string[i] = string[pos + i];

		result_string[i] = '\0';
	} else {
		for(i=0; i <= (length - pos - 2); i++)
			result_string[i] = string[pos + i + 1];

			if(result_string[i - 2] == '\\')
				result_string[i - 2] = '\0';
		result_string[i] = '\0';
	}
}

void print_usage(FILE* stream, int exit_code, const char* program_name)
{
	fprintf(stream, "\nUsage: %s [option 1] [value of option 1] [option 2] [value of option 2]...\n", program_name);
	fprintf(stream,
			"  -h  --help					Display this usage information.\n"
			"  -s  --serial [name of serial]   		Print information about [name of serial].\n"
			"  -d  --no-download				Do not download information from site (if you have\n"
			"						downloaded needed files).\n"
			"  -S  --season [number of season]		If you know what season info you need you can use\n"
			"						this option.\n"
			"  -u  --update					Only download all files from config file to update them.\n"
			"  -e  --episode [number of episode]		Use this option if you need info only about\n"
			"						episode [episode], using only with [season] option.\n"
			"  -D  --date					Print only date of episode, using only with [season] [episode] option\n");
	exit (exit_code);
}

void download_all_files(void)
{
	//for start i need to read data base for file names....
	char string[LENGTH_STRING_IN_FILE], file_name[LENGTH_OF_FILENAME], link[LENGTH_STRING_IN_FILE], destination_file[LENGTH_STRING_IN_FILE];
	int i=0;
	FILE* l_db;

	if ((l_db = fopen(config_file, "r")) == NULL) {
			printf("Error while open %s\n", config_file);
			perror("");
			}

	while(!feof(l_db)) {
                 if (fgets(string, LENGTH_STRING_IN_FILE - 1, l_db)) {
			 while (string[i] != '\\') {
				 serial_name[i] = string[i];
				 i++;
			 }
			 serial_name[i]  = '\0';
			 

		 if(read_db('f', file_name)) {
			 read_db('l', link);
			 strcpy(destination_file, working_file);
			 strcat(destination_file, file_name);
		 }

		 if (get_episodes(destination_file, link))
			 printf("No connection ?\n");

		 for (i=0; i<= strlen(destination_file); i++) //nulling our massive, it's because more than one file_name, for non add other file_name to string
		 destination_file[i] = '\0';


		 i=0;
		 	}
		 }
	fclose (l_db);
}
