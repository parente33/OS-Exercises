#ifndef PERSON_H_
#define PERSON_H_

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>

typedef struct person {
    char name[200];
    int age;
} Person;

void add_person(const char *name, int age);
void list_people(int count);
void update_person_by_name(const char *name, int age);
void update_person_by_position(int position, int age);

#endif // PERSON_H_