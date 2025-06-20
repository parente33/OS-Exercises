#include <stdio.h>
#include "person.h"


int main (int argc, char* argv[]) {
    if (argc < 3) {
        printf("Usage:\n");
        printf("Add new person: ./pessoas -i [name] [age]\n");
        printf("List N people: ./pessoas -l [N]\n");
        printf("Change person age: ./pessoas -u [name] [age]\n");
        printf("Change person age (v2): ./pessoas -o [position] [age]\n");
        return 1;
    }

    if (strcmp(argv[1],"-i") == 0) {
        add_person(argv[2], atoi(argv[3]));
    } else if (strcmp(argv[1],"-l") == 0) {
        list_people(argv[2]);
    } else if (strcmp(argv[1],"-u") == 0) {
        update_person_by_name(argv[2],atoi(argv[3]));
    } else if (strcmp(argv[1],"-o") == 0) {
        update_person_by_position(atoi(argv[2]), atoi(argv[3]));
    } else {
        printf("Invalid option.\n");
        return 1;
    }
    

    return 0;
}