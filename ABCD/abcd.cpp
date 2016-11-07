#ifdef _WIN32                    //Only on windows
#define _CRT_SECURE_NO_DEPRECATE //fread() is safe...
#define NO_STDIO_REDIRECT        //we can use printf() on windows...
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, const char* argv[]) {

	//Variables for data
	unsigned short p = 0;
	char* buf = (char *)calloc(30000, sizeof(char));

	//Sets all values of buf to 0 (default: 255)
	for (unsigned short i = 0; i < 30000; i++) {
		buf[i] = 0;
	}

	char* cmd = 0;
	FILE* f;

	if ((f = fopen(argv[1], "r")) != NULL) {
	
		//Gets length of string in file, creates an array and sets the array value to that of the string in the file, and finally closes the file.
		fseek(f, 0, SEEK_END);
		long s = ftell(f);
		fseek(f, 0, SEEK_SET);
		char* cmd = (char*)calloc(s + 1, sizeof(char));
		fread(cmd, s, 1, f);
		fclose(f);
		//Parse commands into numbers
		for (int i = 0; i < strlen(cmd); i++) {
			if (cmd[i] == 'A') {
				p++;
			}
			else if (cmd[i] == 'B') {
				p--;
			}
			else if (cmd[i] == 'C') {
        			buf[p] = getchar();
			}
			else if (cmd[i] == 'D') {
       	 			printf("%c", buf[p]);
			}
		}
	}
	else {
		printf("No file found...");
	}
}
