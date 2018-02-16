#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	if (argc == 2) {
		int n = atoi(argv[1]);
		if (n == 0 || n == 1) {
			printf("%d\n", n);
			return 0;
		}
		else { // n > 1
			char * args[5];
			args[0] = argv[0];
			char one [382];
			sprintf(one, "%d", n-1);
			args[1] = one;
			args[2] = "1";
			args[3] = "1";
			args[4] = NULL;
			execv(argv[0], args);
		}
	}
	else { // more than 1 cmd line arg
		int n = atoi(argv[1]);
		if (n <= 1) {
			int res = atoi(argv[2]);
			printf("%d\n", res);
			return 1;
		}
		else {
			char * args[5];
			args[0] = argv[0];
			char one [382];
			sprintf(one, "%d", n-1);
			args[1] = one;
			int two = atoi(argv[2]);
			int three = atoi(argv[3]);
			char haaa [382];
			sprintf(haaa, "%d", two + three);
			args[2] = haaa;
			args[3] = argv[2];
			args[4] = NULL;
			execv(argv[0], args);
		}
	}
	return 0; //why u even here
}