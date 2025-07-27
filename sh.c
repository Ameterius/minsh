#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>

#define command_in 1024
int sh_state = 1;

// fun fucts?
int session_sys_return_error = 0;
int session_commands_failed = 0; // very, very buggy
int session_commands_total = 0; 

void x(){
	int custom_stab = 0; // for custom command (like nekoshell-info)
	while(sh_state == 1){
		printf("%%> "); // we should fetch this via config
		fflush(stdout);
		char bfr[command_in];
		if(fgets(bfr, sizeof(bfr), stdin) == NULL){
			printf("\n");
			break;
		}
		bfr[strcspn(bfr, "\n")] = '\0';
		session_commands_total++;
		if (strcmp(bfr, "minsh-info") == 0){
			printf("MinShell v0.0.1\n\nRepo: https://github.com/Ameterius/minshell\n");
			custom_stab = 1;
		}
		if (strcmp(bfr, "minsh-session") == 0){
			printf("Some shitty facts about this session\n\nsystem() returned -1: %i\ncommands returned >0: %i\ntotal executed commands: %i\n", session_sys_return_error, session_commands_failed, session_commands_total);
			custom_stab = 1;
		}
		if (strcmp(bfr, "exit") == 0){sh_state = 0;} // Exit
		else{
			  if (custom_stab == 0){
				int cdm = system(bfr);
				switch(cdm){
					case -1:
						printf("(system() returned -1)\n");
						break;
					default:
						if(cdm>0){
							//perror("command failed");
						}
						break;
				}
			  }
			   else
			   {
				   custom_stab = 0;
				   continue;
			   }
			}
		}
	}


int main(int argc, char *argv[]) {
    if (argc == 2 && strcmp(argv[1], "--version") == 0) {
        printf("0.0.1\n");
        return 0;
    }
	x();
}
