#include "Queue.h"
// the Station struct holds the type of food served at each station, the number
// of servings available,  and a pointer to a queue that holds the names of the
// people in line.
typedef struct Station {
  char *dish_name;
  int numberOfServings;
  Queue *line;
} Station;

// creates a new station struct.
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

Station *access_station_by_name(ListPtr station_list, char *station_name,
                                int number_of_stations) {
  for (int i = 0; i < number_of_stations; i++) {
    Station *current_station = getList(station_list, i);
    char *name = get_name(current_station);
    if (strcmp(station_name, name) == 0) {
      return current_station;
    }
  }
  return NULL;
}

// initalizes the station
Station *add_station(char *dish, int num_serv, Queue *line) {
  Station *S = calloc(1, sizeof(Station));
  S->dish_name = dish;
  S->numberOfServings = num_serv;
  S->line = line;
  return S;
}

// closes a station
void close_station(Station **s) {
  if (s != NULL && *s != NULL) {
    destructQueue(&(*s)->line);
    free((*s)->dish_name);
    *s = NULL;
    s = NULL;
  }
}
// returns the name of the dish in our station
char *get_name(Station *s) { return s->dish_name; }

// returns the number of servings at a station
int get_servings(Station *s) { return s->numberOfServings; }

//
Queue *get_line(Station *s) { return s->line; }

void restock_station(Station *s, int extra_servings) {
  s->numberOfServings = s->numberOfServings + extra_servings;
}