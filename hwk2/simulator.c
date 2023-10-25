#include "List.h"
#include "Queue.h"
#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LEN 100 // code to create queue of array length = 100

typedef struct Station {
  char *dish_name;
  int numberOfServings;
  Queue *line;
} Station;
Station *add_station(char *dish, int num_serv, Queue *line);

// frees the memory taken up by the station struct
void close_station(Station **s);

// returns the name of the station
char *get_name(Station *s);

// returns the number of servings at station
int get_servings(Station *);

// returns the queue pointer of the station
Queue *get_line(Station *s);

// function to add a number of servings(or potentially remove) to a Sation *s
void restock_station(Station *s, int extra_servings);

void printString(void *str) {
  char *s = str;       // "casting" void * to char *
  printf("%s    ", s); // print string starting from s
}

void printStations(void *stat) {
  Station *s = stat;
  printf("%s\n", get_name(s));
}
int main(int argc, char **argv) {
  // creates a new station struct.



  Station *access_station_by_name(ListPtr station_list, char *station_name,
                                  int number_of_stations);
  // code to create queue
  char filename[50];
  char station_name[50];
  int num_dishes;
  int station_num;
  scanf("%d", &station_num);

  ListPtr stations_list = createList(printStations);

  for (int i = 0; i < station_num; i++) {
    scanf("%s %d", station_name, &num_dishes);
    appendList(stations_list,
               add_station(strdup(station_name), num_dishes, initializeQueue(0, NULL)));
  }

  ListPtr people_list = createList(printStations);
  scanf("%s", filename);
  FILE *people_file = fopen(filename, "r");
  char word[50];
  int numberOfPeople;
  fscanf(people_file,"%d",&numberOfPeople);
  for (int i = 0; i < numberOfPeople;i++) {
    fscanf(people_file,"%s %s",word,station_name);
    Station *s = access_station_by_name(stations_list,station_name,station_num);
    Queue *q = get_line(s);
    enqueue(q,strdup(word));
  }
  fclose(people_file);


  while (true) {
    int command = -1;
    bool first_command = true;
    char *station_name;
    int num_dishes;
    char *person_name;

    //checks if our command is good or not
    do {
      if (!first_command) {
        printf("Invalid command, please type a number between 1 and 7");
      }
      first_command = false;
      scanf("%d", &command);
    } while (command < 1 || command > 7);

    switch (command) {

    case 1:
      scanf("%s %s", person_name, station_name);
      enqueue(get_line(access_station_by_name(stations_list, station_name, station_num)),person_name);
      break;
    case 2:
      int dishes_to_add = 0;
      scanf("% s % d", station_name, &dishes_to_add);
      restock_station(
          access_station_by_name(stations_list, station_name, station_num),
          dishes_to_add);
      break;
    case 3:
      scanf("% s % s", person_name, station_name);
      break;
    case 4:
      break;
    case 5:
      break;
    case 6:
      for (int i = 0; i < station_num;i++){
        printQueue(get_line(getList(stations_list,i)));
      }
      printList(people_list);
      break;
    case 7:
      for (int i = 0; i < station_num; i++) {
        Station* s = getList(stations_list,i);
        close_station(&s);
      }
      destroyList(&stations_list);
      destroyList(&people_list);
      return 0;
      break;
    }
  }

  // code to read and process input

  // code to free memory allocated to queue
}


//Helper functions and the Station struct. Normally would put in a separate file but not supposed to edit Makefile

//find(LL *L,void *target,bool(*matcher)(void *, void*));
//for each node:
// if (matcher(target,cur->data)):
// return cur->data

//bool station_match(void * target,void *data):
// char *name = (char *)target
// Station* s = (station*)data
//return strcmp(name, s->name)
Station *access_station_by_name(ListPtr station_list, char *station_name,int number_of_stations) {
  for (int i = 0; i < number_of_stations; i++) {
    Station *current_station = getList(station_list,i);
    if (strcmp(station_name, get_name(current_station)) == 0) {
      return current_station;
    }
  }
}
Station *add_station(char *dish, int num_serv, Queue *line) {
  Station *S = calloc(1, sizeof(Station));
  S->dish_name = dish;
  S->numberOfServings = num_serv;
  S->line = line;
  return S;
}

void close_station(Station **s) {
  if (s != NULL && *s != NULL) {
    destructQueue(&(*s)->line);
    free((*s)->dish_name);
    free(*s);
    *s = NULL;
    s = NULL;
  }
}

char *get_name(Station *s) { return s->dish_name; }

int get_servings(Station *s) { return s->numberOfServings; }

Queue *get_line(Station *s) { return s->line; }

void restock_station(Station *s, int extra_servings) {
  s->numberOfServings = s->numberOfServings + extra_servings;
}