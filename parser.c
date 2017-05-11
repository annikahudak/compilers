#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char line_words[5][256];
int students[10];
int dt = 0;
int dtValid = 0;
int counter = 0;

typedef struct {
	char* name;
	int value;
} Student;

void help() {
	printf("Usage: parser <filename>\n");
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
   /* int countOfAdverbs = 0;
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
    }*/

    // if found "David Tyler" check to see if he says Goodmorning
    if(dt == 1 && counter == 0){
    	if(strstr(line, "Good") != NULL){
    		dtValid = 1;
    		printf("%s","valid Goodmorning\n");
    	}else{
    		printf("%s\n", "\nERROR: \n  >> Class must start with Goodmorning.\n");
    	}
    	counter++;
    }
    // David Tyler Goodmorning
    if(strcmp(line_words[0], "David") == 0){
    	dt = 1;
    }
    // print statement
    else if(strcmp(line_words[0], "print") == 0) {
        printf("%s",line_words[1]);
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

            if(strcmp(line, "\n") != 0 && open(line) == 1){ // && count == 0) {
            	valid = 1;
            	printf("valid opener\n");
            	break;
            }
            //count++;
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