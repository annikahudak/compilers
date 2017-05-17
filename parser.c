#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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

void help() {
    printf("Usage: parser <filename>\n");
}

void findStudent(char *sName){
    // create temp student
    Student *s = (Student *) malloc(sizeof(Student));
    strcpy(s->name, sName);

    // find out which student obj you're dealing with
    // it will be a non-null student whose name is the same as the current student
    // set the values of current student from this student's information
    if(zero != NULL && (strcmp(sName, zero->name) == 0)) {
        s->value = zero->value;
        s->num = zero->num;
    }
    else if(one != NULL && (strcmp(sName, one->name) == 0)) {
        s->value = one->value;
        s->num = one->num;
    }
    else if(two != NULL && (strcmp(sName, two->name) == 0)) {
        s->value = two->value;
        s->num = two->num;
    }
    else if(three != NULL && (strcmp(sName, three->name) == 0)) {
        s->value = three->value;
        s->num = three->num;
    }
    else if(four != NULL && (strcmp(sName, four->name) == 0)) {
        s->value = four->value;
        s->num = four->num;
    }
    else if(five != NULL && (strcmp(sName, five->name) == 0)) {
        s->value = five->value;
        s->num = five->num;
    }
    else if(six != NULL && (strcmp(sName, six->name) == 0)) {
        s->value = six->value;
        s->num = six->num;
    }
    else if(seven != NULL && (strcmp(sName, seven->name) == 0)) {
        s->value = seven->value;
        s->num = seven->num;
    }
    else if(eight != NULL && (strcmp(sName, eight->name) == 0)) {
        s->value = eight->value;
        s->num = eight->num;
    }
    else if(nine != NULL && (strcmp(sName, nine->name) == 0)) {
        s->value = nine->value;
        s->num = nine->num;
    }

    // set var current to temporary student variable
    current = s;
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

    i--;
    //THE VARIABLE i NOW REFERS TO THE LAST INDEX IN THE LIST OF WORDS IN THE LINE
    //HENCE, line_words[i] will return the last word, line_words[0] will return the first


    // if found "David Tyler" check to see if he says Goodmorning
    if(dt == 1 && counter == 0){
        if(strstr(line, "Good") != NULL){
            dtValid = 1;
        }else{
            printf("%s\n", "\nERROR: \n  >> Class must start with Goodmorning.\n");
        }
        counter++;
    }
    // David Tyler Goodmorning
    if(strcmp(line_words[0], "David") == 0){
        dt++;
        if(dt > 1){
            printf("\n");
        }
    }
    // determine which student is talking/doing an action --> set curr_student
    else if(strstr(line_words[0], ":") != NULL) {
        //this is a new variable context. change current_student to whoevers talking
        //fixes index to remove the :
        char *sName = line_words[0];
        sName[strlen(sName)-1] = 0;

        // update value of var current
        findStudent(sName);
    }
    // student (variable) declaration
    else if(strncmp(line_words[0], "[", 1) == 0){
        // new student
        // add student to array

        char *p = line_words[0];
        p++; // skip first character which is "["
        Student *s = (Student *) malloc(sizeof(Student));
        strcpy(s->name, p);

        // fourth word should be name of computer
        // computer name initializes students values
        char *comp = line_words[3];
        comp[strlen(comp)-1] = 0;

        if(strstr(comp, "MAC") != NULL){
            s->value = 25;
        }
        else if(strstr(comp, "PC") != NULL){
            s->value = 10;
        }
        else {
            printf("%s\n", "\nERROR: \n  >> Student did not come prepared with a computer. \n");
            return;
        }

        switch(studentCounter){
            case 0: zero = s; zero->num = studentCounter; break;
            case 1: one = s; one->num = studentCounter; break;
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

    // if the line denotes an action it will be surrounded by ()
    // this if statement checks if the first character is an (
    else if(strncmp(line_words[0], "(", 1) == 0) {

        //take "(" off of first word and ")" off of last word
        char* first = line_words[0];
        first++;
        char* last = line_words[i];
        last[strlen(last)-1] = 0;

        // determine action, then execute:
        // if "participates" student->value += 1
        // if "sneezes" student->value -=1
        // if "notebook" student->value *= -1

        // value of every line individually added to student's existing value
        int thisLine = 0;
        
    // iterate through all words in a line
        for(int j = 0; j < i+1; j++) {

            // iterate over all words in line and count adverbs
            if(strstr(line_words[j], "ly") != NULL) {
                int length = strlen(line_words[j]);
            
                // if a short adverb, *= 2
                if(length <= 10) {
                    thisLine *= 2;
                }
                // if a long adverb, *=5
                else {
                    thisLine *= 5;
                }
            }
            else if(strstr(line_words[j], "participates") != NULL) {
                thisLine += 1;
            }
            else if(strstr(line_words[j], "sneezes") != NULL) {
                thisLine -= 1;
            }
            else if(strstr(line_words[j], "notebook") != NULL) {
                thisLine *= -1;
            }
            else if(strstr(line_words[j], "questions") != NULL) {
                thisLine -= 5;
            }
            else if(strstr(line_words[j], "studies") != NULL) {
                thisLine += 5;
            }
            current->value += thisLine;
        
        // prints ASCII equivalent of student's value
            if(strstr(line_words[j], "yells") != NULL) {
                
                // get student's name by removing "("
                char *p = line_words[0];
                p++;
                findStudent(p);

                printf("%c", current->value);
            }
        // prints integer value of student
            else if(strstr(line_words[j], "mutters") != NULL) {
                
                // get student's name by removing "("
                char *p = line_words[0];
                p++;
                findStudent(p);

                printf("%d", current->value);
            }
        }

        // save current student object to the correct student
        int student_id = current->num;
        switch(student_id){
            case 0: zero = current; break;
            case 1: one = current; break;
            case 2: two = current; break;
            case 3: three = current; break;
            case 4: four = current; break;
            case 5: five = current; break;
            case 6: six = current; break;
            case 7: seven = current; break;
            case 8: eight = current; break;
            case 9: nine = current; break;
        }

    }

}
void printStudents(){

    if(zero != NULL) {
        printf("STUDENT 0: %s -- %d\n", zero->name, zero->value);
    }
    if(one != NULL) {
        printf("STUDENT 1: %s -- %d\n", one->name, one->value);
    }
    if(two != NULL) {
        printf("STUDENT 2: %s -- %d\n", two->name, two->value);
    }
    if(three != NULL) {
        printf("STUDENT 3: %s -- %d\n", three->name, three->value);
    }
    if(four != NULL) {
        printf("STUDENT 4: %s -- %d\n", four->name, four->value);
    }
    if(five != NULL) {
        printf("STUDENT 5: %s -- %d\n", five->name, five->value);
    }
    if(six != NULL) {
        printf("STUDENT 6: %s -- %d\n", six->name, six->value);
    }
    if(seven != NULL) {
        printf("STUDENT 7: %s -- %d\n", seven->name, seven->value);
    }
    if(eight != NULL) {
        printf("STUDENT 8: %s -- %d\n", eight->name, eight->value);
    }
    if(nine != NULL) {
        printf("STUDENT 9: %s -- %d\n", nine->name, nine->value);
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
        int valid = 0;

        while(fgets(line, sizeof(line), f) != NULL) {

            if(strcmp(line, "\n") != 0 && open(line) == 1){ // && count == 0) {
                valid = 1;
                break;
            }
        }
    
    // valid indicates whether file starts with "Welcome to..."
        if(valid == 1){
            while(fgets(line, sizeof(line), f2) != NULL) {
                if(strcmp(line, "\n") != 0){
                    command(line);
                }
            }
            printf("Students in the classroom: \n");
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
