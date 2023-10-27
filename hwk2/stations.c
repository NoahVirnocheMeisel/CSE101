#include "stations.h"
#include "Queue.c"


Station *add_station(char *dish, int num_serv, Queue *line) {
  Station *S = calloc(1, sizeof(Station));
  s->dish_name = dish;
  s->numberOfServings = num_serv;
  s->line = line;
  return s;
}

void close_station(Station **s) {
  if (s != NULL && *s != NULL) {
    destructQueue(s->line);
    free(*s);
    *s = NULL;
    s = NULL
  }
}

char *get_name(Station *s) { return s->dish_name; }

int get_servings(Station *) { return s->numberOfServings; }

Queue *get_line(Station *s) { return s->line; }

void restock_station(Station *s, int extra_servings) {
  s->numberOfServings = s->numberOfServings + extra_servings;
}