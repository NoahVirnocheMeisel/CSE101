/*You start off by reading the busconfig.in file from stdin.
The first line will contain the list of all the bus stops. The maximum stops can be 26 (Anywhere from A-Z). In the provided example, we have 3 stops (A, B, C)
*/
#include <stdio.h>
#include <stdlib.h>
#include "Heap.h"
#include "PriorityQueue.h"
#include <string.h>
#include <stdbool.h>
typedef struct Bus{
    char *name;
    int business_seats;
    int economy_seats;
    int current_stop_index;
    char *stops;
    int num_passengers;
    Person* passengers;
    Heap* business_passengers;
    Heap* economey_passengers;
    char *fileName;
    int general_stop_index;
}Bus;


typedef struct Stop {
  Heap* economey_heap;
  Heap* business_heap;
}Stop;

Bus * makeABus(char *name,int business_seats,int economy_seats,int current_stop_index,char *stops,char *fileName) {
    Bus *b = calloc(1,sizeof(Bus));
    b->name = name;
    b->business_seats = business_seats;
    b->economy_seats = economy_seats;
    b->current_stop_index = current_stop_index;
    b->stops = stops;
    b->num_passengers = 0;
    b->passengers = NULL;
    b->fileName = fileName;
    b->economey_passengers = initializeHeap(NULL,1,0);
    b->business_passengers = initializeHeap(NULL,1,0);
    b->general_stop_index = current_stop_index;
    return b;
}
void freePerson(Person *p) {
    free((p->type));
    free(p->destinations);
    free(p);
    p = NULL;
}
Stop *makeAStop(Heap *economy,Heap*business) {
  Stop *s = calloc(1,sizeof(Stop));
  s->economey_heap = economy;
  s->business_heap = business;
  return s;
}
enum potential_stops{A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z};
int main(void) {

void freePerson(Person *p);
void DeloadBusSection(int*seats,int current_stop_index,int *number_of_people_still_here,Heap*passengers,Heap* current_stop, Bus *b);
Person make_person_from_string(char *string_info);
//read in the busconfig.in from stdin
char filename[50];
scanf("%s", filename);
FILE *busconfig = fopen(filename, "r");
char bus_stop_config[52];
fscanf(busconfig,"%s",bus_stop_config);
char *tok;
char *bus_stops = calloc(26,sizeof(char));
tok = strtok(bus_stop_config,",");
int index = 0;
//process the names of each stop and stores them in an array so that we know 
Stop* stop_list[26];
while (tok != 0 && index < 26 ) {
    bus_stops[index] = index+65;
    tok = strtok(0,",");
    index++;
}
printf("%s\n",bus_stops);
//temp person used throughout the entire program
Person p;

//set up our bus list
int numberBuses;
char bussin[100];
fscanf(busconfig,"%d",&numberBuses);
char *name;
int business_seats;
int economy_seats;
char current_stop_index;
char *stops;
Bus*ListOfBus[numberBuses];
char *FileStores[numberBuses];
FILE* BusOutFiles[numberBuses];
//loops through each line of bus file and splits the bus information into strings for each field.
for (int i = 0; i < numberBuses;i++) {
    fscanf(busconfig,"%s",bussin);
    //name = strdup();
    char *longer_name = strcat(strdup(strtok(bussin,"|")),".out");
    //BusOutFiles[i] = fopen(FileStores[i],"w");
    business_seats = atoi(strtok(0,","));
    economy_seats = atoi(strtok(0,"|,"));
    char *temp  = strtok(0,",|");
    for (int i = 0;i < 26; i++) {
      if(bus_stops[i] == temp[0]) {
        current_stop_index = i;
        printf("CurrentStopIndex:%d\n",current_stop_index);
        break;
      }
    }
    stops = strdup(strtok(0,",|"));
    ListOfBus[i] = makeABus(name,business_seats,economy_seats,current_stop_index,stops,longer_name);
}


fclose(busconfig);


// for (int i = 0; i < numberBuses; i ++) {
//   printf("%s %d %d %c %s\n",ListOfBus[i]->name, ListOfBus[i]->business_seats,ListOfBus[i]->economy_seats,bus_stops[ListOfBus[i]->current_stop_index],ListOfBus[i]->stops);

// }
char stop_file_name[50];
int stop_index = 0; //used to track which stop we are adding to our stop_array

//Runs through the rest of stdin and reads stop files. For each stop file parse
//the people strings and assemble two arrays for business and economey class passengers
//Once we hit EOF for our stop, the two differnt Person arrays are used to create
//two different heaps which are stored in a Stop *, which itself is added to our 
//Stop ** for easy access later on.
int number_of_people_still_here = 0;
while (scanf("%s",stop_file_name) > 0) {
  Heap *business_heap;
  Heap *economey_heap;
  Person eco_list[50];
  Person business_list[50];
  int business_index = 0;
  int economey_index = 0;
  FILE *stop_file = fopen(stop_file_name,"r");
  char string_info[100];
  while(fscanf(stop_file,"%s",string_info) > 0) {
    p = make_person_from_string(string_info);
    number_of_people_still_here++;
    if (p.type == "business") {
      //business_list = (Person*)realloc(business_list,business_index);
      business_list[business_index] = p;
      business_index++;
    } else {
      //eco_list = (Person*)realloc(eco_list,economey_index);
      eco_list[economey_index] = p;
      economey_index++;
    }
  }
  business_heap = initializeHeap(business_list,business_index+1,business_index);
  economey_heap = initializeHeap(eco_list,economey_index+1,economey_index);
  stop_list[stop_index] =  makeAStop(economey_heap,business_heap);
  stop_index++;
  //use function to make a person.
}
for (int i = 0; i < stop_index;i++) {
   printf("%s \n",getMax((stop_list[i])->economey_heap)->name);
}
//set each Stop to a value from 0-25 so we can acess stops in our stop_list without having
//to do conversions
int run = 0;
//for each bus, move it to the next stop and pick up/drop off passengers
if (numberBuses == 0) {
  return 0;
}

for (int i = 0; i < numberBuses;i++) {
  FILE *f = fopen(ListOfBus[i]->fileName,"w");
  fprintf(f,"");
  fclose(f);
}
current_stop_index = 0;
//PROGRAM LOOP
while(number_of_people_still_here > 0) {
for (int i = 0; i < numberBuses;i++) {
  //printf("BUS NUMBER: %d\n",i);
  FILE *f = fopen(ListOfBus[i]->fileName,"a");
  Heap *temp_passenger_heap = initializeHeap(NULL,1,0);
  Bus *CurrentBus = ListOfBus[i];
  //Prints the state of the bus
  //TODO: output files
  fprintf(f,"%d|",run);
  if (size(CurrentBus->business_passengers) > 1 || size(CurrentBus->economey_passengers) > 1) {
    for(int i = 1; i < size(CurrentBus->business_passengers);i++) {
        fprintf(f,"%s(%s) ",((CurrentBus->business_passengers->arr)[i]).name,((CurrentBus->business_passengers->arr)[i]).type);
    }
    for(int i = 1; i < size(CurrentBus->economey_passengers);i++) {
        fprintf(f,"%s(%s) ",((CurrentBus->economey_passengers->arr)[i]).name,((CurrentBus->economey_passengers->arr)[i]).type);
    }
  }else {
      fprintf(f,"Empty");
  }
  fprintf(f,"\n");
  //Print Conditional For start of each Bus State
  fclose(f);
  //deloads and then Picks up from current stop and goes to the next stop. We are starting at 0
  //and using 0 based indexing so it is neccesary to increment index after getting our stop




  //deload people
  int new_bus_passengers = 0;

  //THOUGHT: Current Stop Index is starting at A. Busses don't necesarily start there.
  int cont = 1;
  printf("Bus: %c Stop:%c\n",CurrentBus->stops[CurrentBus->current_stop_index],bus_stops[CurrentBus->general_stop_index]);
  if (CurrentBus->stops[CurrentBus->current_stop_index] ==bus_stops[CurrentBus->general_stop_index]) {
  Stop *current_stop = stop_list[CurrentBus->current_stop_index];
//Create A current Bus and a Current Stop
  //If Current Bus stops at the current stop, continue. Do nothing otherwise
  //Deload the bus. To do this, go through each member of the heap and see if the

  //DELOAD THE ECONOMEY PASSENGERS
  Person*array_persons[size(CurrentBus->economey_passengers)-1];
  int index_tracking = 0;
  int hold_this = size(CurrentBus->economey_passengers);
  for (int passenger_element = 1; passenger_element < hold_this;passenger_element++) {
    int cool_tracker = 1;
    Person *P = extractMax(CurrentBus->economey_passengers);
    printf("Name: %s IndexedVal: %d Strlen: %d\n",P->name,P->destinations[0],strlen(P->destinations)-1);
    if (P->destinations[0] >= strlen(P->destinations)-1) {
    CurrentBus->economy_seats++;
    number_of_people_still_here--;
    free(P);
    } else {
      for (int i = 0; i < strlen(CurrentBus->stops);i++) {
        if(P->destinations[P->destinations[0]] == CurrentBus->stops[i]) {
          array_persons[index_tracking] = P;
          index_tracking++;
          cool_tracker = 0;
          break;
        }
      }
    if(cool_tracker){
      insert(current_stop->economey_heap,P);
      CurrentBus->economy_seats++;
    }
    }
  }
  for(int i = 0; i < index_tracking;i++) {
    insert(CurrentBus->economey_passengers,array_persons[i]);
  }
  //LOADING BUSINESS PASSENGERS
  while(getMax(current_stop->business_heap) != NULL && CurrentBus->business_seats > 0) {
    Person* p = extractMax(current_stop->business_heap);
    int tracker = 1;
    for (int stops_index = 0; stops_index < strlen(CurrentBus->stops);stops_index++ ) {
    if ((p->destinations)[(p->destinations)[0]] == (CurrentBus->stops)[stops_index]) {
      insert(CurrentBus->business_passengers,p);
      CurrentBus->num_passengers++;
      CurrentBus->business_seats--;
      (p->destinations[0])++;
      tracker = 0;
      break;
     }
   }
   if (tracker) {
    insert(temp_passenger_heap,p);
   }
   }
   for (int i = 1; i < size(temp_passenger_heap);i++){
    insert(current_stop->business_heap,&(temp_passenger_heap->arr[i]));
    extractMax(temp_passenger_heap);
   }
  
  //LOAD ECONOMEY PASSENGERS
   while(size(current_stop->economey_heap) > 1 && CurrentBus->economy_seats > 0) {
    Person *p = extractMax(current_stop->economey_heap);
    int tracker = 1;
    for (int stops_index = 0; stops_index < strlen(CurrentBus->stops);stops_index++ ) {
    if ((p->destinations)[(p->destinations)[0]] == (CurrentBus->stops)[stops_index]) {
      //CurrentBus->passengers[CurrentBus->num_passengers] = p;
      insert(CurrentBus->economey_passengers,p);
      CurrentBus->num_passengers++;
      (CurrentBus->economy_seats)--;
      (p->destinations[0])++;
      tracker = 0;
      break;
     }
   }
   if (tracker) {
    insert(temp_passenger_heap,p);
   }
   }
   for (int i = 1; i < size(temp_passenger_heap);i++){
    insert(current_stop->economey_heap,&(temp_passenger_heap->arr[i]));
    extractMax(temp_passenger_heap);
   }
   //printHeap(CurrentBus->business_passengers);
   //printHeap(CurrentBus->economey_passengers);
   //printf("\n");
   destructHeap(&temp_passenger_heap);
   //printf("%d\n",strlen(CurrentBus->stops));
   CurrentBus->current_stop_index = (CurrentBus->current_stop_index + 1);
   if (CurrentBus->current_stop_index > strlen(CurrentBus->stops)-1){
    CurrentBus->current_stop_index = 0;
     }
   }
   CurrentBus->general_stop_index = CurrentBus->general_stop_index +1;
   if (CurrentBus->general_stop_index > strlen(bus_stops)-1) {
    CurrentBus->general_stop_index = 0;
   }
  }//BUS LOOP
  run++;
  }
//Total LOOP


for(int i = 0; i < numberBuses;i++) {
  destructHeap(&ListOfBus[i]->economey_passengers);
  destructHeap(&ListOfBus[i]->business_passengers);
  //free(ListOfBus[i]->name);
  free(ListOfBus[i]->stops);
}

//Now we do stuff for our stops


//for each bus do each operation

//when a bus shows up at stop,add people to the bus if they want to go on that bus and there is space for each queue
//If someone doesn't want to get on the bus add to temp array

//Use an array for a persons destinations, and prepend to that array an integer starting at 0 that says what stop they are at.


//END OF MAIN

}
// void DeloadBusSection(int*seats,int current_stop_index,int *number_of_people_still_here,Heap*passengers,Heap* current_stop, Bus * b) {
// Person* p;
// int add_amount = 0;
// Heap *temp_passenger_heap = initializeHeap(NULL,1,0);
// if(size(passengers) > 1) {
// int numberOfPassengers = size(passengers);
// for (int i = 1; i < numberOfPassengers;i++) {
//     int tracker = 1;
//     //p = CurrentBus->passengers[i];
//     p = (extractMax(passengers));
//     printf("PERSON WE SENDING: %s\n",p->name);
//     printf(" COmparing Charecters: %d %d\n",p->destinations[(p->destinations)[0]-1],current_stop_index+65);
//     printf("Comparing 0 and len:%d %d\n",p->destinations[0],strlen(p->destinations));

//     if(p->destinations[p->destinations[0]-1] == current_stop_index+65) {
//       tracker = 0;
//       //get off the bus
//       (*seats) = *seats + 1;
//       b->num_passengers--;
//       if (p->destinations[0] >= strlen(p->destinations)-1) {
//         (*number_of_people_still_here)--;
//         free(p);
//       } else {
//         insert(current_stop,p);
//       }
//       }
//   if (tracker) {
//     insert(temp_passenger_heap,p);
//    }
//   }
//    for (int i = 1; i < size(temp_passenger_heap);i++){
//     Person *here_we_go = extractMax(temp_passenger_heap);
//     insert(current_stop,here_we_go);
//    }
//   printf("Seat:%d\n",*seats);
// }
// destructHeap(&temp_passenger_heap);
// }




Person make_person_from_string(char*string_info) {
    char *stops_with_commas;
    int age;
    char *name;
    char *type;
    name = strdup(strtok(string_info,"|"));
    stops_with_commas = strdup(strtok(0,"|"));
    int w = 1;
    char *stops = calloc(strlen(stops_with_commas)+2,sizeof(char));
    //printf("%d\n",strlen(stops_with_commas));
    //this is a very important thing to remember, index is 0 for all the People.
    //used to track what stop they are at in their own array of destinations.
    //This method is kind of scuffed but it is straightforwarda and should work
    stops[0] = 1; //HERE!!
    for (int i = 0; i < strlen(stops_with_commas); i++ ) {
      if (stops_with_commas[i] != 44) {
        stops[w] = stops_with_commas[i];
        w++;
      }
    }
    stops[w] = 0;
    age = atoi(strtok(0,"|"));
    type = strdup(strtok(0,"|"));
  Person p;
  p.age = age;
  p.type = type;
  p.name = name;
  p.destinations = stops;
  return p;
}
/*
The next line contains the number of buses (lets say x)
You will read x lines from this point, each line denoting a bus.
Read each line and initialize each bus item, using the above methodology for initializing buses

You then read a file for each stop
Each line will contain information about each passenger.
Each of the items has their own significance. For example, the 3rd column, denoting the age of the person will be used as their priority

Each person will have a list of destinations they would like to go to. Within that list, there would be a next destination that they would like to go to.
Each bus will have a list of valid destinations it can go to. Each person will also have a list of destinations. If a person's next destination does not match the valid destinations of a bus, the bus does not consider loading that person.
Because of this, lets say a bus reaches a station, but the people with top n priorities have their next destinations which are not valid destinations as per the bus. So they get removed and added to a temp priority queue, till all the seats of the bus have been filled by people whose next destination is a valid destination for the bus, based on their ages, or there are no more people left in the main priority queue. Once one of these two conditions is met, people are shifted back from the temp priority queue to the main priority queue.
There will be 2 priority queues per stop, one for the business class people, one for the economy class passengers.

Each of the buses will have a starting stop. After every time stamp, each bus stops at the next possible stop. All the bus keep doing this moving from one stop to the next, till there are no more people left in the system.
When a bus reaches a stop, it writes down its current state in its respective outfile. The state includes the current timestamp in the first column, followed by the name and type of seat of all the people in the bus currently.
The names and seat types are written based on the type of ticket and age. Business class people with the highest age are written first, followed by business class people with lower age, followed by economy class people with higher age, followed by economy class people with lower age.

After writing the state, the bus checks if its a valid stop for it. If it is:
it first drops of people who have that stop as their next destination, and removes that destinaton from each of their destination lists.
It then loads all the people who have one of the valid destinations of the bus as their next destination
If its not a valid stop, the bus continues moving.
You handle buses per stop one by one, starting from bus0 and so on. There can be multiple buses reaching the same stop, or each bus reaching a different stop. You need to track the current stop of each bus. Regardless of how many buses are reaching the stop at the same time, you handle each bus starting from bus0, bus1 and so on.
This continues, till all the people in the system have been dropped to all their destinations.*/


//OLD STRUCTURE FOR THE LOADING PROCESS
// while(getMax(current_stop->business_heap) != NULL && CurrentBus->business_seats > 0) {
  //   printf("MAX NAME: %s\n",getMax(current_stop->business_heap)->name);
  //   p = *extractMax(current_stop->business_heap);
  //   for (int stops_index = 0; i < strlen(CurrentBus->stops);stops_index++ ) {
  //   if (p.destinations[p.destinations[0]] == CurrentBus->stops[stops_index]) {
  //     CurrentBus->passengers[CurrentBus->num_passengers] = p;
  //     CurrentBus->num_passengers++;
  //     p.destinations[0]++;
  //     CurrentBus->business_seats--;
  //     break;
  //    }
  //  }
  //  insert(temp_passenger_heap,&p);
  //  for (int i = 0; i < size(temp_passenger_heap);i++){
  //   insert(current_stop->business_heap,&(temp_passenger_heap->arr[i]));
  //   extractMax(temp_passenger_heap);
  //  }
  // }