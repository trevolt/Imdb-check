#include "imdb.h"

int copy_check(int k, char from[], char to[], int length, const char* str_search)
{
	int i, h;
	i = h = 0;
	while (i != length) {
		to[i] = from[k + i];
		++i;
	}
	to[i] = '\0';
	i = 0;
        while (i < length) {

                if (to[i] == str_search[i])
                        ++h;

                        ++i;
        }
        if (h == length)
        return k;
        else return 0;
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
	while(str[i] != ':') {
		printf("%c", str[i]);
		i++;
	}
}

void get_string(int pos, int length, char string[], char result_string[])
{
	int i=0;
	char* massive[3];
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
	massive[0]=result_string;
	printf("result_string is %s\n0 is %s\n", result_string, massive[0]);
}

void print_usage(FILE* stream, int exit_code, const char* program_name)
{
	fprintf(stream, "\nUsage: %s options [name of serial...]\n", program_name);
	fprintf(stream,
			"  -h  --help					Display this usage information.\n"
			"  -s  --serial [name of serial]   		Print information about [name of serial].\n"
			"  -d  --no-download				Do not download information from site (if you have downloaded needed files)\n"
			"  -S  --season [season...]			If you know what season info you need you can use this option\n");
	exit (exit_code);
}
