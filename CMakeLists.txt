CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

PROJECT(imdb_check C)

set(CMAKE_C_FLAGS "-O3 -Wall -lcurl")

ADD_EXECUTABLE(imdb_check main.c functions.c read_db.c get_episodes.c)
