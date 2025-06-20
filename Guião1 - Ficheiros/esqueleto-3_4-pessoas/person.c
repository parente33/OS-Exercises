#include "person.h"

#define FILE_NAME "people.dat"

void add_person(const char *name, int age) {
    int fd = open(FILE_NAME, O_WRONLY | O_CREAT | O_APPEND, 0644);
        if (fd == -1) {
            perror("Error opening file");
            exit(EXIT_FAILURE);
        }
        Person person;
        strcpy(person.name,name);
        person.name[sizeof(person.name)] = '\0';
        person.age = age;

        int control = write(fd,&person,sizeof(Person));
        if (control <= 0) {
            perror("Error writing to file");
            exit(EXIT_FAILURE);
        }
        off_t file_size = lseek(fd,(size_t)0,SEEK_END);
        int pos = file_size/sizeof(Person); // nº de registos
        printf("Register %d\n", pos);
        close(fd);
}

void list_people(int count) {
    int fd = open(FILE_NAME, O_RDONLY);
    if (fd == -1) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    Person person;
    for (int i = 0; i < count && read(fd,&person,sizeof(Person)) > 0; i++) {
        printf("Name: %s, Age: %d\n", person.name, person.age);
    }
    close(fd);
}

void update_person_by_name(const char *name, int age) {
    int fd = open(FILE_NAME, O_RDWR);
    if (fd == -1) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    Person person;
    while(read(fd,&person,sizeof(Person)) > 0) {
        if (!strcmp(person.name,name)) {
            person.age = age;
            lseek(fd,-(sizeof(Person)),SEEK_CUR); // Repõe o offset para 1 atrás
            int control = write(fd,&person,sizeof(Person));
            if (control <= 0) {
                perror("Error updating record");
                exit(EXIT_FAILURE);
            }
            break;
        }
    }
    close(fd);
}

void update_person_by_position(int position, int age) {
    int fd = open(FILE_NAME, O_RDWR);
    if (fd == -1) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    Person person;
    for (int counter = 0; counter < position; counter++) {
        int c = read(fd,&person,sizeof(Person));
        if (c <= 0) {
            printf("No record found at position %d\n", position);
            close(fd);
            return;
        }
    }
    person.age = age;
    lseek(fd,-(sizeof(Person)),SEEK_CUR);
    int control = write(fd,&person,sizeof(Person));
    if (control <= 0) {
        perror("Error updating record");
        exit(EXIT_FAILURE);
    }
    close(fd);
}