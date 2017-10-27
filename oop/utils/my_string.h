#pragma once

unsigned int my_strlen(const char *x);    //returns length of x
void my_strcpy(char *d, const char *s);   //copies from s(ource) to d(estination)
void my_strncpy(char *d, const char *s, unsigned int n); //copies from s(ource) to d(estination) maximum n (excluding \0) characters. *it adds the null character at the end*
void my_strcat(char *d, const char *s);   //copies by appending s(ource) to d(estination)
int my_strcmp(const char *s1, const char *s2);  //compares s1 to s2 and returns 0 if equal, <0 if s1<s2 and >0 if s1>s2
void my_inttostr(char *d, const int x);   //converts x to char*

char* my_strstr(const char *needle, const char *haystack);  //finds needle in haystacks and returns needle position in haystack or NULL if not found
int my_strpos(const char *needle, const char *haystack);  //returns absolute position of needle in haystack, or -1 if not found
