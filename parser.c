#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "list.h"
#include "variables.h"

char line_words[5][MAX_STRING];

void help() {
	printf("Usage: parser <filename>\n");
}
void savevar() {
    var *variable = (var *) malloc(sizeof(var));
    strcpy(variable->name, line_words[1]);
    list_add(variable);
}

void variable_op(var *variable, int type) {
    // check if it's an assignment
    if(strncmp(line_words[1], "=", 1) == 0) {
        variable->type = type;
        if(type == 0) {
            variable->integer = atoi(line_words[2]);
        } else if(type == 2) {
            strcpy(variable->string, line_words[2]);
        }
    }
}

void print(char *word) {
    var *vari = list_search(word);
    if(vari) {
        // variable with that name exists, just print the value
        if(vari->type == 0) {
        	printf("%s\n", "WE AN INT YO" );
            printf("%d\n", vari->integer);
        } else if(vari->type == 2) {
        	printf("%s\n", "WE A STRING YO" );

            printf("%s\n", vari->string);
        }
    } else {
    	printf("%s\n", "UM");
        printf("%s\n", word);
    }
}

void command(char *line) {
    // remove the \n at the end from fgets
    line[strcspn(line, "\n")] = 0;
    char *line2;
    int i = 0, type = 0;
    
    line2 = strtok(line, " ");
    while(line2 != NULL) {
        if(line2[0] == '"') {
            line2++;
            type = 2;
            strcpy(line_words[i], "");
            while(line2 != NULL) {
                strcat(line_words[i], line2);
                strcat(line_words[i], " ");
                line2 = strtok(NULL, "\"");
            }
        } else {
            strcpy(line_words[i], line2);
            line2 = strtok(NULL, " ");
        }
        i++;
    }
    
    if(strcmp(line_words[0], "print") == 0) {
        print(line_words[1]);
    } else if(strcmp(line_words[0], "var") == 0) {
        savevar();
    } else {
        // no command found, maybe it's a variable operation
        var *vari = list_search(line_words[0]);
        if(vari) {
            variable_op(vari, type);
        }
    }
}
void badMorning(){
	printf("%s\n", "\nERROR: \n  >> You're missing the Good in your Morning!!!\n");
}
int open(char line[]){
	
	const char* firstLine = line;
	const char* opener = "Good Morning!";

    if(strncmp(line, opener, 13) == 0){
			return 1;
	}
	badMorning();
	return 0;
}
int validateNews(char nextLine[]){
	const char* line = nextLine;
	const char* news = "Tech News:";

	if(strncmp(line, news, 10) == 0){
		return 1;
	}
	return 0;
}



int main(int argc, char **argv) {
    
    if(argc < 2) {
        help();
        return 1;
    }
    
    FILE *f = fopen(argv[1], "r");
    if(f) {
        // file exists, start parsing
        char line[100];
        int count = 0;
        int valid = 0;

        while(fgets(line, sizeof(line), f) != NULL) {
            if(strcmp(line, "\n") != 0) {
            	if(count == 0){
            		valid = open(line);
            		printf("%d\n", valid );

            		if(valid == 0){
            			break;
            		}
            	}
         		
                command(line);
            }
            else{
            	badMorning();
            	break;
            }
            count++;
        }
    } else {
        // file doesn't exist
        help();
        return 1;
    }
    
    return 0;
}