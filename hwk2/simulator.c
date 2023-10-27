#include "List.h"
#include "Queue.h"
#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define LEN 100 // code to create queue of array length = 100

FILE *user_out;


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
  fprintf(user_out,"%s\n", s); // print string starting from s
}

void printStations(void *stat) {
  Station *s = stat;
  fprintf(user_out,"%s\n", get_name(s));
}
//Goes through and prints elements of a queue by acessing the array. Only way I could think to do this without changing printQueue implementation.
void printStationQueue(void *station) {
  for (int i = 0; i < count(get_line(station));i++) {
	  fprintf(user_out,"%s\n",(get_line(station)->array)[i]);
  }
  if(count(get_line(station)) > 0) {
     fprintf(user_out,"\n");
  }
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

  ListPtr stations_list = createList(printStationQueue);

  for (int i = 0; i < station_num; i++) {
    scanf("%s %d", station_name, &num_dishes);
    appendList(stations_list,
               add_station(strdup(station_name), num_dishes, initializeQueue(0, NULL)));
  }

  ListPtr people_list = createList(printString);
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
  numberOfPeople = 0;


  while (true) {
    int command;
    bool first_command = true;
    char station_name[50];
    strcpy(station_name,"");
    int num_dishes;
    char person_name[50];
    char error_string[50];

    //checks if our command is good or not
    //this code is not working as intended. 
    do {
      if (!first_command) {
        printf("Invalid command, please type a number between 1 and 7\n");
      }
      first_command = false;
      command = 0;
      if (scanf("%d ", &command ) == 0) {
        scanf("%s",error_string);
      };
    }while(command < 1 && command > 7);

    switch (command) {
    //Add a person to a station
    case 1:
      scanf("%s %s", person_name, station_name);
      Station *s = access_station_by_name(stations_list, station_name, station_num);
      if (s!= NULL) {
      Queue *q = get_line(s);
      enqueue(q,strdup(person_name));
      }
      break;
    //Add(or remove) dishes to a station
    case 2:
      int dishes_to_add = 0;
      scanf("%s %d", station_name, &dishes_to_add);
      s = access_station_by_name(stations_list, station_name, station_num);
      if (s != NULL) {
      restock_station(s,dishes_to_add);
      }
      break;
    //Tries to remove a person from the a station queue
    case 3:
      scanf("% s % s", person_name, station_name);
      s = access_station_by_name(stations_list, station_name, station_num);
      Queue *q = get_line(s);
      if (s != NULL) {
      if (strcmp(front(q),person_name) == 0) {
        appendList(people_list,front(q));
        numberOfPeople++;
        dequeue(q);
      }
      }
      break;
    //Tries to remove a person from the dining hall
    case 4:
      scanf("%s",person_name);
      for (int i = 0; i < station_num;i++){
        s = getList(stations_list,i);
        if (s != NULL) {
          if(strcmp(front(q),person_name) == 0) {
            dequeue(q);
            numberOfPeople--;
            break;
          }
        }
      }
      for (int i = 0; i < numberOfPeople;i++) {
        if (strcmp(person_name,getList(people_list,i)) == 0) {
          deleteList(people_list,i);
          numberOfPeople--;
          break;
      }
      }
      printf("Person is not in the front of a line. They are not leaving!\n");
      break;
    //Serves all the patrons of a specific Station
    case 5:
      scanf("%s",station_name);
      s = access_station_by_name(stations_list, station_name, station_num);
      while (get_servings(s) > 0 && count(get_line(s)) > 0) {
        Queue *q = get_line(s);
        appendList(people_list,front(q));
        numberOfPeople++;
        restock_station(s,-1);
        dequeue(q);
      }
      break;
    //Goes station by station and writes out all the people at the given station
    case 6:
      char outfile[50];
      scanf("%s",outfile);
      user_out = fopen(outfile,"w");
      printList(stations_list);
      printList(people_list);
      fclose(user_out);
      break;
    //Closes the dining hall... Permanentley!!!
    case 7:
      for (int i = 0; i < station_num; i++) {
        s = getList(stations_list,i);
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
//
//Goes through the stations and checks if the station name is the same as the person name
Station *access_station_by_name(ListPtr station_list, char *station_name,int number_of_stations) {
  for (int i = 0; i < number_of_stations; i++) {
    Station *current_station = getList(station_list,i);
    char *name = get_name(current_station);
    if (strcmp(station_name,name) == 0) {
      return current_station;
    }
  }
  return NULL;
}

//initalizes the station
Station *add_station(char *dish, int num_serv, Queue *line) {
  Station *S = calloc(1, sizeof(Station));
  S->dish_name = dish;
  S->numberOfServings = num_serv;
  S->line = line;
  return S;
}

//closes a station
void close_station(Station **s) {
  if (s != NULL && *s != NULL) {
    destructQueue(&(*s)->line);
    free((*s)->dish_name);
    *s = NULL;
    s = NULL;
  }
}
//returns the name of the dish in our station
char *get_name(Station *s) { return s->dish_name; }

//returns the number of servings at a station
int get_servings(Station *s) { return s->numberOfServings; }

//
Queue *get_line(Station *s) { return s->line; }

void restock_station(Station *s, int extra_servings) {
  s->numberOfServings = s->numberOfServings + extra_servings;
}
