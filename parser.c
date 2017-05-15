#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "arraylist.h"

char line_words[5][256];

int dt = 0;
int dtValid = 0;
int counter = 0;

int studentCounter = 0;

typedef struct {
	int num;
	char name[256];
	int value;
} Student;

Student* current = NULL;

Student* zero = NULL;// = (Student *) malloc(sizeof(Student));
Student* one = NULL;// = (Student *) malloc(sizeof(Student));
Student* two = NULL;// = (Student *) malloc(sizeof(Student));
Student* three = NULL;// = (Student *) malloc(sizeof(Student));
Student* four = NULL;//= (Student *) malloc(sizeof(Student));
Student* five = NULL;// = (Student *) malloc(sizeof(Student)); 
Student* six = NULL;//= (Student *) malloc(sizeof(Student));
Student* seven = NULL;// = (Student *) malloc(sizeof(Student));
Student* eight = NULL;// = (Student *) malloc(sizeof(Student));
Student* nine = NULL;//= (Student *) malloc(sizeof(Student));

//Arraylist list = arraylist_create( Boolean (*equals)(const Object object_1, const Object object_2));

//Student* students[10] = {zero, one, two, three, four, five, six, seven, eight, nine};

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
      // determine which student is talking/doing an action --> set curr_student
    else if(strstr(line_words[0], ":") != NULL) {
        //this is a new variable context. change current_student to whoevers talking
        //remove the :
        char *s_name = line_words[0];
        s_name[strlen(s_name)-1] = 0;
        strcpy(current->name, s_name);

        printf("Current student: %s\n", current->name);
    }
    // print statement
    else if(strcmp(line_words[0], "print") == 0) {
        printf("%s",line_words[1]);
    }
    // student (variable) declaration
    else if(strncmp(line_words[0], "[", 1) == 0){
    	// new student
    	// add student to array
    	

    	//var *variable = (var *) malloc(sizeof(var));
    	//strcpy(variable->name, line_words[1]);

    	
    	char *p = line_words[0];
    	p++; 
    	Student *s = (Student *) malloc(sizeof(Student));
    	strcpy(s->name, p);

    	char *comp = line_words[3];
    	comp[strlen(comp)-1] = 0;



    	if(strstr(comp, "MAC") != NULL){
    		// student->value = ____
    		s->value = 1;

    		printf("%s has a %s\n", s->name, "MAC" );
    	}
    	else if(strstr(comp, "PC") != NULL){
    		// student->value = ____
    		s->value = -1;

    		printf("%s has a %s\n", s->name, "PC" );
    	}
    	else {
    		printf("%s\n", "\nERROR: \n  >> Student did not come prepared with a computer. \n");
    		return;
    	}

    	switch(studentCounter){
    		case 0: zero = s; zero->num = studentCounter; printf("%s%s%d", "Student zero created.\n", zero->name, zero->num ); break;
    		case 1: one = s; one->num = studentCounter; printf("%s%s%d", "Student one created.\n", one->name, one->num ); break;
    		case 2: two = s; two->num = studentCounter; break;
    		case 3: three = s; three->num = studentCounter; break;
    		case 4: four = s; four->num = studentCounter; break;
    		case 5: five = s; five->num = studentCounter; break;
    		case 6: six = s; six->num = studentCounter; break;
    		case 7: seven = s; seven->num = studentCounter; break;
    		case 8: eight = s; eight->num = studentCounter; break;
    		case 9: nine = s; nine->num = studentCounter; break;
    	}
    	studentCounter++;
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
/*void fillArray(){
	for (int i = 0; i < 10; ++i)
	{
		Student *temp = (Student *) malloc(sizeof(Student)); 
		students[i] = temp;
	}
}*/
void printStudents(){
	for(int i = 0; i < 10; i++){
		//printf("%s\n", students[i]->name );
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
    //fillArray();
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
            printStudents();
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