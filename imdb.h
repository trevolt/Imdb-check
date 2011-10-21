#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <curl/curl.h>
#include <sys/stat.h>
#define str_s "Original Air Date"
#define LENGTH_STRING_IN_FILE 500
#define LENGTH_OF_FILENAME 50
extern char* HOME; //variable for home directory
char config_file[LENGTH_OF_FILENAME]; //our configuration file
char config_directory[LENGTH_OF_FILENAME]; //our directory where all files will save
char working_file[LENGTH_OF_FILENAME]; //our file with which we will work
#define text_of_config "The big bang theory\\http://www.imdb.com/title/tt0898266/episodes\\ep_tbbt\\\nThe fringe\\http://www.imdb.com/title/tt1119644/episodes\\ep_fringe\\\nThe dexter\\http://www.imdb.com/title/tt0773262/episodes\\ep_dex\\\n" //this is example string in configuration file 

int copy_check(int k, char from[], char to[], int length, const char* str_search); //copy part of massive from from[] to to[] and then return position of first symbol of string searching str_search which has length length

void print_result(int pos, char str[]); //printing symbols between first "<" and first ">" in string str after position pos

void print_season_episode(int pos, char str[]); //print all symbols in str from pos pos while first "<"

int read_db(char name_of_object, const char* name_of_serial, char massive_to_copy[]); //this function can find link from data base using variable name_of_serial and this variable can be not full - for example we have serial named "Cool serial" we just put in this variable "Cool" or "serial" and we have our link :), name object may be l - it means link of serial, and n - it means name of serial, f - means file name of our html file of our serial

void get_string(int pos, int pos1, char string[], char result_string[]); //this function copy massive from pos -> pos1 from massive string to massove result_string

void print_usage(FILE* stream, int exid_code, const char* program_name); //prints usage information

int get_episodes(char* DESTINATION_FILE, char* WEBPAGE_URL);
