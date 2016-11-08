//Still needs to be cleaned up a bit... Not final version
//Plan on adding resizable stack for programs bigger that can store more than 300000 characters
#define _CRT_SECURE_NO_DEPRECATE //fread() is safe...
#define NO_STDIO_REDIRECT        //we can use printf() on windows...

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, const char* argv[]) {

	//Variables for data
	unsigned char p = 0;
	int stackSize = 0;
	char* buf = (char *)calloc(30000, sizeof(char));

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
		//We do not need ,[] because they are not really used in gopher
		for (int i = 0; i < strlen(cmd); i++) {
			if (cmd[i] == '+') {
				p++;
			}
			else if (cmd[i] == '-') {
				p--;
			}
			else if (cmd[i] == 'X') {
				p += 4;
			}
			else if (cmd[i] == '÷') {
				p -= 4;
			}
			else if (cmd[i] == '^') {
				p += 8;
			}
			else if (cmd[i] == '@') {
				p -= 8;
			}
			else if (cmd[i] == '?') {
				p += 16;
			}
			else if (cmd[i] == '!') {
				p -= 16;
			}
			else if (cmd[i] == '&') {
				p += 32;
			}
			else if (cmd[i] == '%') {
				p -= 32;
			}
			else if (cmd[i] == '$') {
				p += 64;
			}
			else if (cmd[i] == '#') {
				p -= 64;
			}
			else if (cmd[i] == ':') {
				p += 128;
			}
			else if (cmd[i] == ';') {
				p -= 128;
			}
			else if (cmd[i] == '\'') {
				p *= 2;
			}
			else if (cmd[i] == '.') {
				p /= 2;
			}
			else if (cmd[i] == '<') {
				for (short i = stackSize; i > 0; i--) {
					buf[i] = buf[i - 1];
				}
				buf[0] = (char)p;
				stackSize++;
			}
			else if (cmd[i] == '=') {
				for (short i = 0; i < stackSize; i++) {
					printf("%c", buf[i]);
				}
			}
		}
	}
	else {
		printf("No file found...");
	}
}
