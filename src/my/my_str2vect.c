#include "my.h"
#include <stdio.h>

char** my_str2vect(char* str) {
	if (str) {
		char* temp = str;
		int count = 0;
		while (*temp != '\0') {
			while (*temp == ' ' || *temp == '\t' || *temp == '\n') { // you hit a space
				temp++;
			}
			if (*temp != ' ' && *temp != '\t' && *temp != '\n' && *temp != '\0') { // you hit a letter
				count++;
				temp++;
			}
			while (*temp != ' ' && *temp != '\t' && *temp != '\n' && *temp != '\0') { //go to end of letter block
				temp++;
			}
		}
		printf("%s\n", "done counting number of words");
		printf("%d\n", count);
		char ** vect = (char**) malloc((count+1)*sizeof(str));
		int lcount = 0;
		for (int i = 0; i<count; i++) {
			while (*str == ' ' || *str == '\t' || *str == '\n') {
				str++;
			} // str is at a letter at this point
			temp = str;
			lcount = 0;
			while (*temp != ' ' && *temp != '\t' && *temp != '\n' && *temp != '\0') {
				lcount++;
				temp++;
			}
			printf("%s\n", "we get before my_strncpy");
			printf("%s\n", str);
			vect[i]=my_strdup(str);
			printf("%s\n", vect[i]);
			str = temp;
		}
		vect[count+1] = NULL;
		return vect;
	}
	return NULL;
}