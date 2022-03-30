#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAX_LINE_LEN 200
#define MAX_EVENTS 1000

/*
    Function: main
    Description: represents the entry point of the program.
    Inputs:
        - argc: indicates the number of arguments to be passed to the program.
        - argv: an array of strings containing the arguments passed to the program.
    Output: an integer describing the result of the execution of the program:
        - 0: Successful execution.
        - 1: Erroneous execution.
*/


typedef struct {// store all the data of each event
    int hasData;
    char description[100];
    char timezone[200];
    char location[100];
    char day[100];
    char month[100];
    char year[100];
    char dweek[200];
    char start[200];
    char end[200];
} Event;

typedef struct {//stores the data after the "start" from the command line
    char year[100];
    char month[100];
    char day[100];
} Start;

typedef struct {//stores the data after the "end" from the command line
    char year[100];
    char month[100];
    char day[100];
} End;

//if given string is a usable word it returns a value. this value will determine the destination of strings to follow
//calender = 1/12, event = 2/13, description = 3/14, timezone = 4/15
//location = 5/16, day = 6/17, month = 7/18, year = 8/19, dweek = 9/20
//start = 10/21, end = 11/22///
int makeTag(char givenString[]){ //compares given tag with all tags to determine where next string should be stored
    char CALENDER[20] = "<calendar>";
    char ENDCALENDER[20] = "</calendar>";
    char EVENT[20] = "<event>";
    char ENDEVENT[20] = "</event>";
    char DESCRIPTION[20] = "<description>";
    char ENDDESCRIPTION[20] = "</description>";
    char TIMEZONE[20] = "<timezone>";
    char ENDTIMEZONE[20] = "</timezone>";
    char LOCATION[20] = "<location>";
    char ENDLOCATION[20] = "</location>";
    char DAY[20] = "<day>";
    char ENDDAY[20] = "</day>";
    char MONTH[20] = "<month>";
    char ENDMONTH[20] = "</month>";
    char YEAR[20] = "<year>";
    char ENDYEAR[20] = "</year>";
    char DWEEK[20] = "<dweek>";
    char ENDDWEEK[20] = "</dweek>";
    char START[20] = "<start>";
    char ENDSTART[20] = "</start>";
    char END[20] = "<end>";
    char ENDEND[20] = "</end>";


    if (strcmp(givenString, CALENDER) == 0){
        return 1;
    }
    if (strcmp(givenString, ENDCALENDER) == 0){
        return 12;
    }
    if (strcmp(givenString, EVENT) == 0){
        return 2;
    }
    if (strcmp(givenString, ENDEVENT) == 0){
        return 13;
    }
    if (strcmp(givenString, DESCRIPTION) == 0){
        return 3;
    }
    if (strcmp(givenString, ENDDESCRIPTION) == 0){
        return 14;
    }
    if (strcmp(givenString, TIMEZONE) == 0){
        return 4;
    }
    if (strcmp(givenString, ENDTIMEZONE) == 0){
        return 15;
    }
    if (strcmp(givenString, LOCATION) == 0){
        return 5;
    }
    if (strcmp(givenString, ENDLOCATION) == 0){
        return 16;
    }
    if (strcmp(givenString, DAY) == 0){
        return 6;
    }
    if (strcmp(givenString, ENDDAY) == 0){
        return 17;
    }
    if (strcmp(givenString, MONTH) == 0){
        return 7;
    }
    if (strcmp(givenString, ENDMONTH) == 0){
        return 18;
    }
    if (strcmp(givenString, YEAR) == 0){
        return 8;
    }
    if (strcmp(givenString, ENDYEAR) == 0){
        return 19;
    }
    if (strcmp(givenString, DWEEK) == 0){
        return 9;
    }
    if (strcmp(givenString, ENDDWEEK) == 0){
        return 20;
    }
    if (strcmp(givenString, START) == 0){
        return 10;
    }
    if (strcmp(givenString, ENDSTART) == 0){
        return 21;
    }
    if (strcmp(givenString, END) == 0){
        return 11;
    }
    if (strcmp(givenString, ENDEND) == 0){
        return 22;
    }
    else {
        printf("invalid string given: %s", givenString);
    }
    return 0;
}

void makeDashes(char* dashStorage, int givenLength){ // creates amount of dashes equal to the int passed to it -1 because of the way i made lines
    int counter = 0;
    while (counter < givenLength-1){
        dashStorage[counter] = '-';
        counter++;
    }
    dashStorage[counter]= '\0';
}

void monthConvert(char* monthNumber, char *monthAsString){// takes the string integer and outputs the month name.
    int monthAsNumber = atoi(monthNumber);
    if (monthAsNumber == 1){
        strcpy(monthAsString, "January");
    }
    if (monthAsNumber == 2){
        strcpy(monthAsString, "February");
    }
    if (monthAsNumber == 3){
        strcpy(monthAsString, "March");
    }
    if (monthAsNumber == 4){
        strcpy(monthAsString, "April");
    }
    if (monthAsNumber == 5){
        strcpy(monthAsString, "May");
    }
    if (monthAsNumber == 6){
        strcpy(monthAsString, "June");
    }
    if (monthAsNumber == 7){
        strcpy(monthAsString, "July");
    }
    if (monthAsNumber == 8){
        strcpy(monthAsString, "August");
    }
    if (monthAsNumber == 9){
        strcpy(monthAsString, "September");
    }
    if (monthAsNumber == 10){
        strcpy(monthAsString, "October");
    }
    if (monthAsNumber == 11){
        strcpy(monthAsString, "November");
    }
    if (monthAsNumber == 12){
        strcpy(monthAsString, "December");
    }
}

void startHourConvert(Event* event){ // takes the start value in an event and formats it to the assignment
    int numberAsInt = atoi(event->start);
    int isHalfHour;
    char secondHalf[10];
    secondHalf[0] = event->start[3];
    secondHalf[1] = event->start[4];
    secondHalf[2] = '\0';
    isHalfHour = strcmp(secondHalf, ":30"); // returns -10 if :00 and -7 if :30.
    strcpy(event->start, "");

    if (numberAsInt == 1){
        if (isHalfHour==-10){
        strcpy(event->start, "01:00 AM");
        }
        if (isHalfHour == -7){
            strcpy(event->start, "01:30 AM");
        }
    }
    if (numberAsInt == 2){
        if (isHalfHour==-10){
        strcpy(event->start, "02:00 AM");
        }
        if (isHalfHour == -7){
            strcpy(event->start, "02:30 AM");
        }
    }
    if (numberAsInt == 3){
        if (isHalfHour==-10){
        strcpy(event->start, "03:00 AM");
        }
        if (isHalfHour == -7){
            strcpy(event->start, "03:30 AM");
        }
    }
    if (numberAsInt == 4){
        if (isHalfHour==-10){
        strcpy(event->start, "04:00 AM");
        }
        if (isHalfHour == -7){
            strcpy(event->start, "04:30 AM");
        }
    }
    if (numberAsInt == 5){
        if (isHalfHour==-10){
        strcpy(event->start, "05:00 AM");
        }
        if (isHalfHour == -7){
            strcpy(event->start, "05:30 AM");
        }
    }
    if (numberAsInt == 6){
        if (isHalfHour==-10){
        strcpy(event->start, "06:00 AM");
        }
        if (isHalfHour == -7){
            strcpy(event->start, "06:30 AM");
        }
    }
    if (numberAsInt == 7){
        if (isHalfHour==-10){
        strcpy(event->start, "07:00 AM");
        }
        if (isHalfHour == -7){
            strcpy(event->start, "07:30 AM");
        }
    }
    if (numberAsInt == 8){
        if (isHalfHour==-10){
        strcpy(event->start, "08:00 AM");
        }
        if (isHalfHour == -7){
            strcpy(event->start, "08:30 AM");
        }
    }
    if (numberAsInt == 9){
        if (isHalfHour==-10){
        strcpy(event->start, "09:00 AM");
        }
        if (isHalfHour == -7){
            strcpy(event->start, "09:30 AM");
        }
    }
    if (numberAsInt == 10){
        if (isHalfHour==-10){
        strcpy(event->start, "10:00 AM");
        }
        if (isHalfHour == -7){
            strcpy(event->start, "10:30 AM");
        }
    }
    if (numberAsInt == 11){
        if (isHalfHour==-10){
        strcpy(event->start, "11:00 AM");
        }
        if (isHalfHour == -7) {
            strcpy(event->start, "11:30 AM");
        };
    }
    if (numberAsInt == 12){
        if (isHalfHour==-10){
        strcpy(event->start, "12:00 PM");
        }
        if (isHalfHour == -7){
            strcpy(event->start, "12:30 PM");
        }
    }
    if (numberAsInt == 13){
        if (isHalfHour==-10){
        strcpy(event->start, "01:00 PM");
        }
        if (isHalfHour == -7){
            strcpy(event->start, "01:30 PM");
        }
    }
    if (numberAsInt == 14){
        if (isHalfHour==-10){
        strcpy(event->start, "02:00 PM");
        }
        if (isHalfHour == -7){
            strcpy(event->start, "02:30 PM");
        }
    }
    if (numberAsInt == 15){
        if (isHalfHour==-10){
        strcpy(event->start, "03:00 PM");
        }
        if (isHalfHour == -7){
            strcpy(event->start, "03:30 PM");
        }
    }
    if (numberAsInt == 16){
        if (isHalfHour==-10){
        strcpy(event->start, "04:00 PM");
        }
        if (isHalfHour == -7){
            strcpy(event->start, "04:30 PM");
        }
    }
    if (numberAsInt == 17){
        if (isHalfHour==-10){
        strcpy(event->start, "05:00 PM");
        }
        if (isHalfHour == -7){
            strcpy(event->start, "05:30 PM");
        }
    }
    if (numberAsInt == 18){
        if (isHalfHour==-10){
        strcpy(event->start, "06:00 PM");
        }
        if (isHalfHour == -7){
            strcpy(event->start, "06:30 PM");
        }
    }
    if (numberAsInt == 19){
        if (isHalfHour==-10){
        strcpy(event->start, "07:00 PM");
        }
        if (isHalfHour == -7){
            strcpy(event->start, "07:30 PM");
        }
    }
    if (numberAsInt == 20){
        if (isHalfHour==-10){
        strcpy(event->start, "08:00 PM");
        }
        if (isHalfHour == -7){
            strcpy(event->start, "08:30 PM");
        }
    }
    if (numberAsInt == 21){
        if (isHalfHour==-10){
        strcpy(event->start, "09:00 PM");
        }
        if (isHalfHour == -7){
            strcpy(event->start, "09:30 PM");
        }
    }
    if (numberAsInt == 22){
        if (isHalfHour==-10){
        strcpy(event->start, "10:00 PM");
        }
        if (isHalfHour == -7){
            strcpy(event->start, "10:30 PM");
        }
    }
    if (numberAsInt == 23){
        if (isHalfHour==-10){
        strcpy(event->start, "11:00 PM");
        }
        if (isHalfHour == -7){
            strcpy(event->start, "11:30 PM");
        }
    }
}

void endHourConvert(Event* event){ // takes the end value in an event and formats it to the assignment
    int numberAsInt = atoi(event->end);
    int isHalfHour;
    char secondHalf[20];
    secondHalf[0] = event->end[3];
    secondHalf[1] = event->end[4];
    secondHalf[2] = '\0';
    isHalfHour = strcmp(secondHalf, ":30");
    strcpy(event->end, "");

    if (numberAsInt == 1){
        if (isHalfHour==-10){
        strcpy(event->end, "01:00 AM");
        }
        if (isHalfHour == -7){
            strcpy(event->end, "01:30 AM");
        }
    }
    if (numberAsInt == 2){
        if (isHalfHour==-10){
        strcpy(event->end, "02:00 AM");
        }
        if (isHalfHour == -7){
            strcpy(event->end, "02:30 AM");
        }
    }
    if (numberAsInt == 3){
        if (isHalfHour==-10){
        strcpy(event->end, "03:00 AM");
        }
        if (isHalfHour == -7){
            strcpy(event->end, "03:30 AM");
        }
    }
    if (numberAsInt == 4){
        if (isHalfHour==-10){
        strcpy(event->end, "04:00 AM");
        }
        if (isHalfHour == -7){
            strcpy(event->end, "04:30 AM");
        }
    }
    if (numberAsInt == 5){
        if (isHalfHour==-10){
        strcpy(event->end, "05:00 AM");
        }
        if (isHalfHour == -7){
            strcpy(event->end, "05:30 AM");
        }
    }
    if (numberAsInt == 6){
        if (isHalfHour==-10){
        strcpy(event->end, "06:00 AM");
        }
        if (isHalfHour == -7){
            strcpy(event->end, "06:30 AM");
        }
    }
    if (numberAsInt == 7){
        if (isHalfHour==-10){
        strcpy(event->end, "07:00 AM");
        }
        if (isHalfHour == -7){
            strcpy(event->end, "07:30 AM");
        }
    }
    if (numberAsInt == 8){
        if (isHalfHour==-10){
        strcpy(event->end, "08:00 AM");
        }
        if (isHalfHour == -7){
            strcpy(event->end, "08:30 AM");
        }
    }
    if (numberAsInt == 9){
        if (isHalfHour==-10){
        strcpy(event->end, "09:00 AM");
        }
        if (isHalfHour == -7){
            strcpy(event->end, "09:30 AM");
        }
    }
    if (numberAsInt == 10){
        if (isHalfHour==-10){
        strcpy(event->end, "10:00 AM");
        }
        if (isHalfHour == -7){
            strcpy(event->end, "10:30 AM");
        }
    }
    if (numberAsInt == 11){
        if (isHalfHour==-10){
        strcpy(event->end, "11:00 AM");
        }
        if (isHalfHour == -7){
            strcpy(event->end, "11:30 AM");
        };
    }
    if (numberAsInt == 12){
        if (isHalfHour==-10){
        strcpy(event->end, "12:00 PM");
        }
        if (isHalfHour == -7){
            strcpy(event->end, "12:30 PM");
        }
    }
    if (numberAsInt == 13){
        if (isHalfHour==-10){
        strcpy(event->end, "01:00 PM");
        }
        if (isHalfHour == -7){
            strcpy(event->end, "01:30 PM");
        }
    }
    if (numberAsInt == 14){
        if (isHalfHour==-10){
        strcpy(event->end, "02:00 PM");
        }
        if (isHalfHour == -7){
            strcpy(event->end, "02:30 PM");
        }
    }
    if (numberAsInt == 15){
        if (isHalfHour==-10){
        strcpy(event->end, "03:00 PM");
        }
        if (isHalfHour == -7){
            strcpy(event->end, "03:30 PM");
        }
    }
    if (numberAsInt == 16){
        if (isHalfHour==-10){
        strcpy(event->end, "04:00 PM");
        }
        if (isHalfHour == -7){
            strcpy(event->end, "04:30 PM");
        }
    }
    if (numberAsInt == 17){
        if (isHalfHour==-10){
        strcpy(event->end, "05:00 PM");
        }
        if (isHalfHour == -7){
            strcpy(event->end, "05:30 PM");
        }
    }
    if (numberAsInt == 18){
        if (isHalfHour==-10){
        strcpy(event->end, "06:00 PM");
        }
        if (isHalfHour == -7){
            strcpy(event->end, "06:30 PM");
        }
    }
    if (numberAsInt == 19){
        if (isHalfHour==-10){
        strcpy(event->end, "07:00 PM");
        }
        if (isHalfHour == -7){
            strcpy(event->end, "07:30 PM");
        }
    }
    if (numberAsInt == 20){
        if (isHalfHour==-10){
        strcpy(event->end, "08:00 PM");
        }
        if (isHalfHour == -7){
            strcpy(event->end, "08:30 PM");
        }
    }
    if (numberAsInt == 21){
        if (isHalfHour==-10){
        strcpy(event->end, "09:00 PM");
        }
        if (isHalfHour == -7){
            strcpy(event->end, "09:30 PM");
        }
    }
    if (numberAsInt == 22){
        if (isHalfHour==-10){
        strcpy(event->end, "10:00 PM");
        }
        if (isHalfHour == -7){
            strcpy(event->end, "10:30 PM");
        }
    }
    if (numberAsInt == 23){
        if (isHalfHour==-10){
        strcpy(event->end, "11:00 PM");
        }
        if (isHalfHour == -7){
            strcpy(event->end, "11:30 PM");
        }
    }
}

// the big organizer. takes entire file and parses it.
// uses other functions to store the data (see makeTag, Event struct)
void readData(FILE* inputfile, Event event[]){
    int arrayIndex = 0;
    int ch = fgetc(inputfile);
    int curTag = 0;     // start with tag leading nowhere
    char curString[100];
    while (ch != EOF){
        if (ch == '<'){ // generates the tag word that will allow us to determine where the string goes
            char tagWord[50];
            tagWord[0] = ch;
            int i = 1;
            while (ch != '>'){
                ch = fgetc(inputfile);
                tagWord[i] = ch;
                i++;
            }
            tagWord[i] = '\0';
            curTag = makeTag(tagWord); //create a tag to tell us where to store next string
            strcpy(tagWord, ""); // reset tagword

            if (curTag == 13){ // tag 13 means "/event" so we increment the index
                arrayIndex++;
                event[arrayIndex].hasData = 0;
            }

            if(curTag < 12 && curTag > 2){ // < 12 means its a "start" word so the letters following are what we want to save"
             ch = fgetc(inputfile); //should be a character right after a '>'
             int j = 0;
             event[arrayIndex].hasData = 1; // used to check if the struct has any data inside later
                while (ch != '<'){
                    curString[j]=ch;
                    ch = fgetc(inputfile);
                    j++;
                }
                curString[j] = '\0';

                if (curTag == 3){ // depending on tag number, store string to corrosponding spot in the struct.
                    strcpy(event[arrayIndex].description, curString);
                }
                if (curTag == 4){
                    strcpy(event[arrayIndex].timezone, curString);
                }
                if (curTag == 5){
                    strcpy(event[arrayIndex].location, curString);
                }
                if (curTag == 6){
                    strcpy(event[arrayIndex].day, curString);
                }
                if (curTag == 7){
                    strcpy(event[arrayIndex].month, curString);
                }
                if (curTag == 8){
                    strcpy(event[arrayIndex].year, curString);
                }
                if (curTag == 9){
                    strcpy(event[arrayIndex].dweek, curString);
                }
                if (curTag == 10){
                    strcpy(event[arrayIndex].start, curString);
                }
                if (curTag == 11){
                    strcpy(event[arrayIndex].end, curString);
                }
                strcpy(curString, "");
            }
        }
        ch = fgetc(inputfile);
    }
}

void formatStartInput(char* startInputs, Start* start){ // takes the "start" part of the command and puts the date into a struct to oragnize.
    int i  = 0;
    int j = 0;

    char startInput[100];
    strcpy(startInput, startInputs);

    while (startInput[i]!='\0'){
        if (startInput[i] == '='){
            i++; // move to first char after the '='
            while (startInput[i] != '/' && startInput[i]!='\0'){
                start->year[j] = startInput[i];
                j++;
                i++;
            }
            start->year[j] = '\0';
            j=0;
            i++;
            while(startInput[i]!='/'){
                start->month[j] = startInput[i];
                j++;
                i++;
            }
            start->month[j] = '\0';
            j=0;
            i++;
            while (startInput[i]!= '\0'){
                start->day[j]=startInput[i];
                j++;
                i++;
            }
        }
        i++;
    }
}

void formatEndInput(char* endInputs, End* end){ // takes the "end" part of the command and formats it so we can use it.

    char endInput[100];
    strcpy(endInput, endInputs);
    int i  = 0;
      int j = 0;
      while (endInput[i]!= '\0'){
          if (endInput[i] == '='){
              i++; // move to first char after the '='
              while (endInput[i] != '/'){
                  end->year[j] = endInput[i];
                  j++;
                  i++;
              }
              end->year[j] = '\0';
              j=0;
              i++;
              while(endInput[i]!='/'){
                  end->month[j] = endInput[i];
                  j++;
                  i++;
              }
              end->month[j] = '\0';
              j=0;
              i++;
              while (endInput[i]!= '\0'){
                  end->day[j]=endInput[i];
                  j++;
                  i++;
              }
          }
          i++;
      }

}

void formatFileInput(char* fileInputs, char formattedFileName[]){// watch bill birds videos for this, plan is to format this and use it as an argument for fopen.
    int i = 0;
    int j  = 0;

    char fileInput[100];
    strcpy(fileInput, fileInputs);

    while(fileInput[i] != '\0'){
        if (fileInput[i] == '='){
            i++;
            while (fileInput[i]!='\0'){
                formattedFileName[j]=fileInput[i];
                i++;
                j++;
            }
            formattedFileName[j] = '\0';
        }
    i++;
    }
}

void outputData(Event events[], End endDate, Start startDate){//take all the date we have stored and output to assignment specs
    int eI = 0; // short for eventIndex because im going to use it alot and i dont want to retype it all the time.
    char monthName[20];
    int dateUsed = 0; // 0 for the current date not being output yet (used if multiple events on the same day)
    int curHour = 0; // hour tracker
    int curDay = atoi(startDate.day);
    int curMonth = atoi(startDate.month);
    int endDay = atoi(endDate.day);
    int endMonth = atoi(endDate.month);
    int startOfList = 0;

    while(curDay!=endDay+1 || curMonth!=endMonth){//plus 1 because of the way we increase days in the loop // end loop when we hit the correct day+month

        while (events[eI].hasData!=0){// checks if struct has any data

            if (atoi(events[eI].month)==curMonth && atoi(events[eI].day)==curDay && atoi(events[eI].start)==curHour){

             if (dateUsed==0){
                   dateUsed = 1;
                     if (startOfList == 1){ // check if this is the first event to be output. if it isnt separate the events.
                       printf("\n");
                       printf("\n");
                   }

                   startOfList = 1;
                   monthConvert(events[eI].month, monthName); // convert month to needed output
                   int printStatementLength = printf("%s %s, %s (%s)\n", monthName, events[eI].day, events[eI].year, events[eI].dweek);// print event details.
                   char dashes[100];
                   makeDashes(dashes, printStatementLength); // create '-' of the same length as the print statement
                   printf("%s\n", dashes);
                   startHourConvert(&events[eI]);
                   endHourConvert(&events[eI]);
                   printf("%s to %s: %s {{%s}} | %s", events[eI].start, events[eI].end, events[eI].description, events[eI].location, events[eI].timezone);
                 }

                 else if (dateUsed == 1){ // if the date has been used we just print the stuff under the dashes
                 printf("\n");
                 startHourConvert(&events[eI]);
                 endHourConvert(&events[eI]);
                 printf("%s to %s: %s {{%s}} | %s", events[eI].start, events[eI].end, events[eI].description, events[eI].location, events[eI].timezone);
                }

            }
            eI++; // check next struct
        }

        eI = 0;
        curHour++;

        if(curHour==25){ //counts the days then months
        curHour= 0;
        dateUsed = 0;
        curDay++;

            if (curDay==32){
            curDay=0;
            curMonth++;
            }
        }
        if (curDay==32 || curMonth ==12){
            exit(0);
        }
    }
}

int main(int argc, char *argv[])
{
    /* Starting calling your own code from this point. */
    // Ideally, please try to decompose your solution into multiple functions that are called from a concise main() function.

    char fileFromLine[100];
    formatFileInput(argv[3], fileFromLine);
    FILE* inputfile = fopen(fileFromLine, "r");
    if (inputfile==NULL){
        printf("unable to open the file\n");
        return 0;
    }

    Event eventList[MAX_EVENTS]; // storing max events. why not

    Start startFromTerminal;

    End endFromTerminal;

    readData(inputfile, eventList);

    formatStartInput(argv[1], &startFromTerminal);

    formatEndInput(argv[2], &endFromTerminal);

    outputData(eventList, endFromTerminal, startFromTerminal);

    fclose(inputfile);

    exit(0);

}
