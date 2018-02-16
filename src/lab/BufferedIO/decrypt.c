#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

char convert (char c, int key) {
	while (key > 0) {
		if (c == 'A') {
			c = 'Z';
			key--;
		}
		else if (c == 'a') {
			c = 'z';
			key--;
		}
		else if (c == ' ' || c == '!') {
			return c;
		}
		else {
			c--;
			key--;
		}
	}
	return c;
}

int main() {
	char red[3];
	int eopen = open("encrypted.txt", O_RDONLY);
	char res[45];
	int key = 5;
	int counter =0;
	while (read(eopen, red, 3) > 0	) {
		for (int i = 0; i <= 2; i++) {
			char cur = red[i];
			char dec = convert(cur, key);
			res[counter] = dec;
			counter++;
		}
		key += 2;
	}
	int dwrite = open("solution.txt", O_WRONLY);
	write(dwrite, res, 44);
	close(dwrite);
	close(eopen);
	return 0;
}