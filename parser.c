#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "list.h"
#include "variables.h"

char line_words[5][MAX_STRING];
int students[10];

void help() {
	printf("Usage: parser <filename>\n");
}
void savevar() {
    var *variable = (var *) malloc(sizeof(var));
    strcpy(variable->name, line_words[1]);
    list_add(variable);
}

void variable_op(var *variable, int type) {

    if(strncmp(line_words[0], "~", 1) == 0 && strncmp(line_words[2], "IS", 1) == 0) {
        variable->type = type;
        if(type == 0) {
            variable->integer = atoi(line_words[3]);
        } else if(type == 2) {
            strcpy(variable->string, line_words[3]);
        }
    }
    else {
        printf("invalid syntax \n");
    }
}

void print(char *word) {
    var *vari = list_search(word);
    if(vari) {
        // variable with that name exists, just print the value
        if(vari->type == 0) {
            printf("%d\n", vari->integer);
        } else if(vari->type == 2) {
            printf("%s\n", vari->string);
        }
    } else {
        printf("%s\n", word);
    }
}

void command(char *line) {
    // remove the \n at the end from fgets
    line[strcspn(line, "\n")] = 0;
    char *line2;
    int i = 0, type = 0;
    
    // separate line into line_words array
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


    // adverbs
    int countOfAdverbs = 0;
    for(int x=0; x< sizeof(line_words)/sizeof(line_words[0]); ++x){
        int c = 0;
        char sub[2];
        char* s = line_words[x];
        while(c < strlen(s)-2) {
            sub[c] = s[c+strlen(s)-2];
            c++;
        }

        if(strcpy(s, "ly") == 0){
            countOfAdverbs++;
        }
    }

    
    // print statement
    if(strcmp(line_words[0], "print") == 0) {
        print(line_words[1]);
    }
    // student (variable) declaration
    else if(strncmp(line_words[0], "[", 1) == 0){
    	// new student
    	// add student to array
    	if(strstr(line, "MAC") != NULL){
    		// student->value = ____
    	}
    	else if(strstr(line, "PC") != NULL){
    		// student->value = ____
    	}
    }

    // positive +1
    // if line contains "raises hand"
    else if(strstr(line, "Raises hand") != NULL){
        // multiply by countOfAdverbs if != 0
    } 

    // negative -1
    // if line contains "cough"
    else if(strstr(line, "Coughs") != NULL){
        // multiply by countOfAdverbs if != 0
    }

   	else if(list_search(line_words[0])){
        // no command found, maybe it's a variable operation
        // check that it's a variable that has been saved (list_search)
        var *vari = list_search(line_words[0]);
        if(vari) {
            variable_op(vari, type);
        }
    }
}



int open(char line[]){
	
	const char* firstLine = line;
	const char* opener = "Welcome to CPSC-402!";
    
    if(strncmp(line, opener, 20) == 0){
			return 1;
	}
	return 0;
}

void badOpening(){
    printf("%s\n", "\nERROR: \n  >> You're missing the class opener!\n");
}

int main(int argc, char **argv) {
    
    if(argc < 2) {
        help();
        return 1;
    }

    FILE *f = fopen(argv[1], "r");
    FILE *f2 = fopen(argv[1], "r");
    if(f) {
        // file exists, start parsing
        char line[100];
        int count = 0;
        int valid = 0;
        int hasNews = 0;

        while(fgets(line, sizeof(line), f) != NULL) {

            if(strcmp(line, "\n") != 0 && open(line) == 1 && count == 0) {
            	valid = 1;
            	printf("valid opener\n");
            	break;
            }
            count++;
        }

        if(valid == 1){
            while(fgets(line, sizeof(line), f2) != NULL) {
                if(strcmp(line, "\n") != 0){
                    command(line);
                }
            }
        }
        else{
            badOpening();
        }

        

    } else {
        // file doesn't exist
        help();
        return 1;
    }
    
    return 0;
}