#include "imdb.h"

int main(int argc, char *argv[])
{
	int i=0, pos=0, pos_e=0, next_option, no_download=0, count_match=0, only_refresh=0, print_only_date=0;
	char str[LENGTH_STRING_IN_FILE], str_out[LENGTH_STRING_IN_FILE], file_name[LENGTH_OF_FILENAME], name[LENGTH_STRING_IN_FILE], link[LENGTH_STRING_IN_FILE];
	FILE *ep_serial=NULL, *l_db; //this should be in imdb.h ldb
	char str_se[LENGTH_STRING_IN_FILE]="Season ";
	struct stat st;
	const char* number_season=NULL;
	const char* episode=NULL;
	const struct option long_options[] = {
		{ "help",	0,	NULL,	'h'},
		{ "serial",	1,	NULL,	's'},
		{ "no-download",0,	NULL,	'd'},
		{ "season",	1,	NULL,	'S'},
		{ "update",	0,	NULL,	'u'},
		{ "episode",	1,	NULL,	'e'},
		{ "date",	0,	NULL,	'D'},
		{ NULL,		0,	NULL,	 0 }
	};
	const char* const short_options = "hs:dS:ue:D";

	do {
		next_option = getopt_long(argc, argv, short_options, long_options, NULL);
		switch (next_option)
		{
			case 'h':  /* -h --help*/
				print_usage (stdout, 0, argv[0]);

			case 's':  /* -s --serial*/
				if(strlen(optarg) < 500)
				strcpy(serial_name, optarg);
				else {
					printf("\nUnknown defintion of [serial] option\nYou entired: <%s>\n", optarg);
					exit (1);
				}
				break;

			case 'd': //-d for no download
				no_download=1;
				break;

			case 'S': //it will season
				number_season = optarg;
				break;

			case 'u': //for refresh option
				only_refresh=1;
				break;

			case 'e': //for only episode print
				episode=optarg;
				break;
			case 'D': //for print only date of needed episode
				print_only_date=1;
				break;

			case '?': /*uknowkn option*/
				print_usage (stderr, 1, argv[0]);

			case -1: /*no options*/
				print_usage (stderr, 1, argv[0]);
				break;

			default: //unknokwn result
				abort ();
		}
	}
	while (next_option != -1);

	//getting our variable
	strcpy(config_directory, getenv("HOME")); //copy variable HOME
	strcat(config_directory, "/.imdb"); //added /.imdb to this variable
	strcpy(config_file,config_directory);
        strcat(config_file, "/links_db");
	strcpy(working_file, config_directory);
        strcat(working_file, "/");

	if(stat(config_directory, &st)) //checking for existence of our configuration directory
		mkdir(config_directory, 0777);

	if(stat(config_file, &st)) { //checking for existence for configuration file
		if ((l_db = fopen(config_file, "w")) == NULL) {
			printf("Error while open file %s\n", config_file);
			perror("");
			exit (1);
		}
		if (fwrite(text_of_config, sizeof(char), strlen(text_of_config), l_db) < strlen(text_of_config)) {
			printf("Error while writing to file %s\n", config_file);
			perror("");
			exit (1);
		}
		fclose (l_db); //replace this to read_db function
	}

	if (only_refresh) { //change all if to case
		download_all_files();
		exit (0);
	}

	if(number_season != NULL && strlen(number_season) > 2) {
		printf("\nUnknown defintion of [season] option\nYou entired: <%s>\n", number_season);
		exit(1);
	}

	if(number_season != NULL)
                 strcat(str_se, number_season);

	if(episode != NULL && number_season != NULL && strlen(episode) < 4) {
		strcat(str_se, ", Episode ");
		strcat(str_se, episode);
		strcat(str_se, ":");
	} else if (number_season == NULL && episode != NULL) {
		printf("\n---You should define [episode] option with [season]---\n");
		exit (1);
	} else if (number_season != NULL && episode !=NULL && strlen(episode) > 4) {
		printf("\nUnknown definition of [episode] option\nYou entired: <%s>\n", episode);
		exit (1);
	} else if ((episode == NULL || number_season == NULL) && print_only_date) {
		printf("\n---You should define [season] and [episode] for use option [date]---\n");
		exit (1);
	}

	if(strlen(serial_name) <= 4) {
		printf("\n\n----You must specify more then %d symbols in [serial] variable----\n\n", strlen(serial_name));
		exit(1);
	}

	if(!read_db('n', name)) {
		printf("!!!No match found by serial name!!!\nYou entired: <%s>\n", serial_name);
		exit(1);
	} else {
		read_db('l', link);
		//read_db('n', name);
		read_db('f', file_name);
		strcat(working_file, file_name);
	}

	if(no_download) {
		if((ep_serial = fopen(working_file, "r"))==NULL) {
			printf("Error while open file %s", file_name);
			perror("");
			exit(1);
		}
	}
	else {
		if (get_episodes(working_file, link))
			printf("No connection ?\n");

			ep_serial = fopen(working_file, "r");
	}


	while(!feof(ep_serial)) {
		if(fgets(str, LENGTH_STRING_IN_FILE - 1, ep_serial)) {
			if(!i) {
				if (print_only_date);
				else {
					printf("\n\t  /-------------The name of serial is %s-------------\\\n\n", name);
					printf("--------Season----------------Date-------------------Title------------------\n");
				}
			}
			for(i=0; i<= strlen(str); i++) {
					if(copy_check(i, str, str_out, strlen(str_s), str_s) != -1 && pos_e) {
						pos=copy_check(i, str, str_out, strlen(str_s), str_s);
						if (print_only_date)
							print_result(pos, str);
						else {
							print_season_episode(pos_e, str);
							printf("\t|  ");
							print_result(pos, str);
							printf("   \t|  ");
							print_result(pos_e, str);
							printf("\n----------------------------------------------------------------------------\n");
							}
						count_match++;
						pos_e=0;
						pos=0;
					}
				if(copy_check(i, str, str_out, strlen(str_se), str_se) != -1) //it will find Season info which is first in string - so pos_e can't be 0 when we try find Original Air Date
					pos_e=copy_check(i, str, str_out, strlen(str_se), str_se);
				
			}
		}
	}
	if(!count_match)
		printf("\n----------------------------!!!No match found!!!----------------------------\n");
	fclose(ep_serial);
	return 0;
}
