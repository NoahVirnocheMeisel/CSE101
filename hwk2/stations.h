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