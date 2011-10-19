#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <curl/curl.h>
#define str_s "Original Air Date"
#define LENGTH_STRING_IN_FILE 500
#define LENGTH_OF_FILENAME 50
extern char* HOME;
char config_file[LENGTH_OF_FILENAME];

int copy_check(int k, char from[], char to[], int length, const char* str_search); //copy part of massive from from[] to to[] and then return position of first symbol of string searching str_search which has length length

void print_result(int pos, char str[]); //printing symbols between first "<" and first ">" in string str after position pos

void print_season_episode(int pos, char str[]); //print all symbols in str from pos pos while first "<"

int read_db(char name_of_object, const char* name_of_serial, char massive_to_copy[]); //this function can find link from data base using variable name_of_serial and this variable can be not full - for example we have serial named "Cool serial" we just put in this variable "Cool" or "serial" and we have our link :), name object may be l - it means link of serial, and n - it means name of serial, f - means file name of our html file of our serial

void get_string(int pos, int pos1, char string[], char result_string[]); //this function copy massive from pos -> pos1 from massive string to massove result_string

void print_usage(FILE* stream, int exid_code, const char* program_name); //prints usage information
//void print_info(void);

int get_episodes(char* DESTINATION_FILE, char* WEBPAGE_URL);
