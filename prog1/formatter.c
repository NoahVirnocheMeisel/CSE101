#include "List.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define OPTIONS "i:"

// string function for linked list, copied from hwk1.c
void printString(void *str) {
  char *s = str;    // "casting" void * to char *
  printf("%s ", s); // print string starting from s
}

int main(void) {
  char inputName[100];
  // read the file name
  scanf("%s", inputName);

  // main program loop. Will only end if user types exit.
  while (true) {
    // declaring some variables and resetting them. variables
    int used = 0;
    int buffer = 0;
    ListPtr t_list = createList(printString);
    char word[256];
    // opens and closes the file.
    FILE *infile = fopen(inputName, "r");
    while (fscanf(infile, "%s", word) == 1) {
      appendList(t_list, strdup(word));
    }
    fclose(infile);
    char command[100];
    char F = 0;
    int space = 30;
    char line[space];
    strcpy(line, "");
    char file_name[100];

    // command validity checker
    while (true) {
      scanf("%s ", command);
      if (strcmp(command, "exit") == 0 || strcmp(command, "quit") == 0) {
        destroyList(&t_list);
        return 0;
      }
      if (strcmp(command, "exit") != 0 && strcmp(command, "quit") != 0 &&
          strcmp(command, "format") != 0) {
        printf("Invalid command '%s'. Please use the 'format <Justification> "
               "<Width>' format, such as 'format L 50', or exit using "
               "'quit'/'exit'.\n",
               command);
      }
      if (strcmp(command, "format") == 0) {
        break;
      }
    }
    // given that we have a valid command(as checked for above) takes the format
    // style and line size.
    scanf("%c %d", &F, &space);
    sprintf(file_name, "test.%c%d", F, space);
    FILE *out_file = fopen(file_name, "w");

    // Meat and potatoes of the program. Essentially using our linked-list like
    // a queue and going through it to assemble each line.

    // outer loop to check if list is empty.
    while (getList(t_list, 0) != NULL) {
      // inner line loop
      while (used <= space && getList(t_list, 0) != NULL) {
        // add new word length to line
        used += strlen(getList(t_list, 0));
        // see if word fits
        if (used <= space) {
          // see if word + next word and a space fits into the line or if the
          // next word is NULL
          if (used + strlen(getList(t_list, 1)) + 1 <= space &&
              getList(t_list, 1) != getList(t_list, 0)) {
            strcat(line, getList(t_list, 0));
            deleteList(t_list, 0);
            used++;
            strcat(line, " ");
            // if it doesn't fit with space and word, just add the word and exit
            // because we need to start a new line now.
          } else {
            strcat(line, getList(t_list, 0));
            deleteList(t_list, 0);
            break;
          }
          // word doesn't fit at all, remove its length and exit the inner loop
        } else {
          used -= strlen(getList(t_list, 0));
          break;
        }
      }
      // set the size of our line buffer
      buffer = 0;
      buffer = space - used;

      // checks which format we are using, and prints that format.

      // L format
      if (F == 76) {
        fprintf(out_file, "%s\n", line);
      }
      // R format
      if (F == 82) {
        for (int i = 0; i < buffer; i++) {
          fprintf(out_file, " ");
        }
        fprintf(out_file, "%s\n", line);
      }
      // C format
      if (F == 67) {
        for (int i = 0; i < (buffer / 2); i++) {
          fprintf(out_file, " ");
        }
        fprintf(out_file, "%s", line);
        fprintf(out_file, "\n");
      }
      // resets used and makes the line empty.
      used = 0;
      strcpy(line, "");
    }
    // we have reached the end of our main loop. destroy our now empty list and
    // close our file we are writing to.
    used = 0;
    destroyList(&t_list);
    fclose(out_file);
  }
  return 0;
}