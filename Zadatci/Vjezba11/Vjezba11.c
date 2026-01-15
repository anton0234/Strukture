#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASH_SIZE 11
#define MAX 64

/* ===== STRUKTURE ===== */

typedef struct _city {
    char name[MAX];
    int population;
    struct _city* left;
    struct _city* right;
} City;

typedef struct _country {
    char name[MAX];
    City* cities;
    struct _country* next;
} Country;

/* ===== HASH FUNKCIJA ===== */

int hashFunction(char* countryName) {
    return ((int)countryName[0]) % HASH_SIZE;
}

/* ===== BST GRADOVA ===== */

City* createCity(char* name, int population) {
    City* c = (City*)malloc(sizeof(City));
    strcpy(c->name, name);
    c->population = population;
    c->left = c->right = NULL;
    return c;
}

City* insertCity(City* root, char* name, int population) {
    if (!root)
        return createCity(name, population);

    if (population < root->population ||
        (population == root->population && strcmp(name, root->name) < 0))
        root->left = insertCity(root->left, name, population);
    else
        root->right = insertCity(root->right, name, population);

    return root;
}

void printCities(City* root) {
    if (!root) return;
    printCities(root->left);
    printf("    %s (%d)\n", root->name, root->population);
    printCities(root->right);
}

void printCitiesAbove(City* root, int limit) {
    if (!root) return;
    printCitiesAbove(root->left, limit);
    if (root->population > limit)
        printf("    %s (%d)\n", root->name, root->population);
    printCitiesAbove(root->right, limit);
}

/* ===== DRŽAVE ===== */

Country* createCountry(char* name) {
    Country* c = (Country*)malloc(sizeof(Country));
    strcpy(c->name, name);
    c->cities = NULL;
    c->next = NULL;
    return c;
}

void insertCountry(Country* table[], char* name) {
    int index = hashFunction(name);
    Country* newCountry = createCountry(name);

    if (!table[index] || strcmp(name, table[index]->name) < 0) {
        newCountry->next = table[index];
        table[index] = newCountry;
        return;
    }

    Country* current = table[index];
    while (current->next && strcmp(name, current->next->name) > 0)
        current = current->next;

    newCountry->next = current->next;
    current->next = newCountry;
}

/* ===== UČITAVANJE GRADOVA ===== */

void loadCities(Country* country, char* filename) {
    FILE* f = fopen(filename, "r");
    if (!f) {
        printf("Ne mogu otvoriti %s\n", filename);
        return;
    }

    char city[MAX];
    int pop;

    while (fscanf(f, "%s %d", city, &pop) == 2)
        country->cities = insertCity(country->cities, city, pop);

    fclose(f);
}

/* ===== UČITAVANJE DRŽAVA ===== */

void loadCountries(Country* table[]) {
    FILE* f = fopen("drzave.txt", "r");
    if (!f) {
        printf("Ne mogu otvoriti drzave.txt\n");
        return;
    }

    char country[MAX], file[MAX];

    while (fscanf(f, "%s %s", country, file) == 2) {
        insertCountry(table, country);

        int index = hashFunction(country);
        Country* c = table[index];
        while (c && strcmp(c->name, country))
            c = c->next;

        if (c)
            loadCities(c, file);
    }

    fclose(f);
}

/* ===== ISPIS ===== */

void printTable(Country* table[]) {
    for (int i = 0; i < HASH_SIZE; i++) {
        Country* c = table[i];
        if (c)
            printf("\n[Hash %d]\n", i);

        while (c) {
            printf("%s:\n", c->name);
            printCities(c->cities);
            c = c->next;
        }
    }
}

/* ===== PRETRAGA ===== */

void searchCities(Country* table[]) {
    char country[MAX];
    int limit;

    printf("\nUnesite drzavu: ");
    scanf("%s", country);

    printf("Unesite minimalan broj stanovnika: ");
    scanf("%d", &limit);

    int index = hashFunction(country);
    Country* c = table[index];

    while (c && strcmp(c->name, country))
        c = c->next;

    if (!c) {
        printf("Drzava ne postoji.\n");
        return;
    }

    printf("\nGradovi s vise od %d stanovnika:\n", limit);
    printCitiesAbove(c->cities, limit);
}

/* ===== MAIN ===== */

int main() {
    Country* table[HASH_SIZE] = { NULL };

    loadCountries(table);
    printTable(table);
    searchCities(table);

    return 0;
}
