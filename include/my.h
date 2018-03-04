/* Header for libmy (Part 2) assignment. */ 

// Updated on 2/23/2018 to add support for pipes assignment

#ifndef _MY_H_ 
#define _MY_H_

#ifndef NULL 
#define NULL ((void*)0) 
#endif

#include <unistd.h> 
#include <stdlib.h>

// part 1 methods
void my_char(char); 
void my_str(char*); 
void my_int(int); 
void my_num_base(int, char* base); 
void my_alpha(); 
void my_digits();
int my_strlen(char*); 
int my_revstr(char*); 
int my_strindex(char*, char); 
int my_strrindex(char*, char);

// part 2 methods
char* my_strfind(char* s, char c);
char* my_strrfind(char *s, char c);
int my_strcmp(char *a, char *b);
int my_strncmp(char *a, char *b, int n);
char* my_strcpy(char *dst, char *src);
char* my_strncpy(char *dst, char *src, int n);
char* my_strcat(char* dst, char* src);
char* my_strdup(char* str);
char* my_strconcat(char* a, char* b);
char* my_strnconcat(char* a, char* b, int n);
int my_atoi(char* n);

// method declaration for pipes
char *my_vect2str(char **x);

// for minishell
char **my_str2vect(char* str);

#endif