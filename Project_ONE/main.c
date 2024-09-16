/////////////////Rawand Bawatneh 1211403//////////////
// Include necessary libraries
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
// Define constants
#define true 1
#define false 0
#define MAX_CITY_LENGTH 50
// Define structs for cities and towns
typedef struct  Cnode{
    char city [50];
   struct Cnode *next;
    struct Cnode *prev;
    struct town *town;
}Cnode;
typedef struct Tnode{
    char town [50];
    int pop;
    struct Tnode *next;
}Tnode;
typedef struct town {
    Tnode* head;
    Tnode* tail;
}town;
typedef struct cities {
    Cnode* head;
    Cnode* tail;
 }cities;
 // Function prototypes
void add_sorted (town *t,Tnode *tow);
Cnode *search(cities *list, char c[]);
bool searchBool(cities *list, char c[]);
void printTown (cities *DLL);
void add_towns(cities *city);
void print (cities *DLL);
void add_cities(cities *p);
void RADIX_SORT (int array [],int size);
void countingSort(int arr [],int size ,int place);
int getMaxElem(int arr [],int n);
void sortDLL(cities* DLL);
int count_nodes (cities *DLL);
void remove_duplicates(cities* DLL);
void add_to_DLL(char c[], cities *p) ;
void print_as_formatted();
void load_file ();
void add_new_district(cities *sortedDLL);
void add_new_town(cities *DLL);
void DelTown(cities *DLL);
Tnode * searchTown(town *list, char x[]);
void print_dis_pop(cities *DLL);
void changeTownPopulation(cities *DLL);
void output (cities *DLL);
int getTotalPopulation(town *townList);
void deleteDistrictInfo(cities *DLL, const char *districtName);
void menu();
// Load data from file
void load_file (){
FILE *fptr=fopen("districts.txt","r");
    if (fptr == NULL) {
        printf("The file is not opened. The program will now exit.");
        exit(0);
        }
    else {
        printf("The file is opened :)\n");

    }
fclose(fptr);

}
// Print data as formatted
void print_as_formatted() {
    FILE *fptr = fopen("districts.txt", "r");
    if (fptr == NULL) {
        printf("Error: Unable to open file. The program will now exit.\n");
        exit(1);
    } else {
        char singleLine[150];
        while (fgets(singleLine, sizeof(singleLine), fptr) != NULL) {
            printf("%s", singleLine);
        }
        fclose(fptr);
    }
}
// Add a city to the cities doubly linked list
void add_to_DLL(char c[], cities* p) {
    Cnode* n = (Cnode *)malloc(sizeof(Cnode));
    if (n == NULL) {
        return;
    }
    for (int i = 0; i < strlen(c); i++) {
        n->city[i] = c[i];
    }
    n->city[strlen(c)] = '\0';
    n->next = NULL;
    n->prev = NULL;

    if (p->head == NULL) {
        p->head = n;
        p->tail = n;
    } else {

        p->tail->next = n;
        n->prev = p->tail;
        p->tail = n;
    }
}
// Remove duplicate cities from the cities doubly linked list
void remove_duplicates(cities* DLL) {
    if (DLL == NULL || DLL->head == NULL) {
        return;
    }

    Cnode* current = DLL->head;
    Cnode* next;

    while (current != NULL) {
        next = current->next;
        while (next != NULL) {
            if (strcmp(current->city, next->city) == 0) {
                Cnode* temp = next;
                if (temp->next != NULL) {
                    temp->next->prev = temp->prev;
                }
                if (temp->prev != NULL) {
                    temp->prev->next = temp->next;
                }
                next = next->next;
                free(temp);
            } else {
                next = next->next;
            }
        }
        current = current->next;

    }
}
// Count the number of nodes in the cities doubly linked list
int count_nodes (cities *DLL){
    Cnode *ptr = DLL->head;
    int count = 0;
    while (ptr != NULL){
     count++;
        ptr=ptr->next;
    }
    return count;
}
// Sort cities using Radix Sort
void sortDLL(cities* DLL) {
    int c = count_nodes(DLL);
    int array[c];
    Cnode* p = DLL->head;
    int index = 0;
    while (p != NULL) {
        char first_char = p->city[0];
        int ascii_code = (int)first_char;
        array[index++] = ascii_code;
        p = p->next;
    }

    RADIX_SORT(array, c);

    Cnode* nodes[26];
    for (int i = 0; i < 26; i++) {
        nodes[i] = NULL;
    }

    p = DLL->head;
    while (p != NULL) {
        char first_char = p->city[0];
        int i;
        for (i = 0; i < c; i++) {
            if ((int)first_char == array[i]) {
                break;
            }
        }
        if (nodes[i] == NULL) {
            nodes[i] = p;
        } else {
            int j;
            for (j = i + 1; j < 26; j++) {
                if (nodes[j] == NULL) {
                    nodes[j] = p;
                    break;
                }
            }
        }
        p = p->next;
    }

    DLL->head = NULL;
    DLL->tail = NULL;
    for (int i = 0; i < 26; i++) {
        if (nodes[i] != NULL) {
            if (DLL->head == NULL) {
                DLL->head = nodes[i];
                DLL->tail = nodes[i];
            } else {
                DLL->tail->next = nodes[i];
                nodes[i]->prev = DLL->tail;
                DLL->tail = nodes[i];
            }
        }
    }
    if (DLL->tail != NULL)
        DLL->tail->next = NULL;
}
// Get the maximum element in an array
int getMaxElem(int arr [],int n){
    int i;
    int max_ele=arr[0];
    for (i=1;i<n;i++)
        if (arr[i]>max_ele)
        max_ele=arr[i];
    return max_ele;
}
// Perform counting sort on an array
void countingSort(int arr [],int size ,int place){
    int i;
    int output[size+1];
    int max =(arr[0]/place)%10;

    for (int i=1;i<size;i++){
    if (((arr[i]/place)%10) > max)
        max=arr[i];
    }
    int count [max + 1];

    for ( i=0;i<max;++i)
        count[i] = 0;
    for(int i=0;i<size;i++)
        count[(arr[i])/place%10]++;

    for ( i=1; i<10;i++)
        count[i] +=count [i-1];
    for ( i =size-1;i>=0;i--){
        output[count[(arr[i]/place)%10]-1] = arr[i];
        count [(arr[i]/place)%10]--;

    }
    for ( i=0;i<size;i++)
        arr[i]=output[i];

}
// Function for Radix sort algorithm
void RADIX_SORT (int array [],int size){
    int place;
    int max =getMaxElem(array,size);
    for (place = 1;max/place>0;place *= 10)
        countingSort(array,size,place);

}
// Function to add cities from file to the cities list
void add_cities(cities *p) {
    FILE *fptr = fopen("districts.txt", "r");
    if (fptr == NULL || p == NULL) {
        printf("Error: Unable to open file or allocate memory.\n");
        exit(1);
    } else {
        p->head = NULL;
        p->tail = NULL;
        char singleLine[150];
        char d[] = " | ";
        while (fgets(singleLine, sizeof(singleLine), fptr)) {
    char *portion = strtok(singleLine, d);
    add_to_DLL(portion, p);
    p->tail->town = (town*)malloc(sizeof(town));
    if (p->tail->town == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    p->tail->town->head = NULL;
    p->tail->town->tail = NULL;
}
        fclose(fptr);
       remove_duplicates(p);
       sortDLL(p);

    }
}
// Function to print cities
void print (cities* DLL){

    Cnode* ptr = DLL->head;
    while (ptr != NULL){

        printf ("%s ",ptr->city);
        ptr = ptr->next;
    }
}
// Function to add towns to cities from file
void add_towns(cities* city) {
    FILE* fptr = fopen("districts.txt", "r");
    if (fptr == NULL) {
        printf("Error opening file\n");
        exit(1);
    }

    char singleLine[150];
    char d[] = " | ";
    while (fgets(singleLine, sizeof(singleLine), fptr) != 0) {
        char* city_name = strtok(singleLine, d);
        char* town_name = strtok(NULL, d);
        char* population_str = strtok(NULL, d);
        int population = atoi(population_str);
        if (population == 0) {
            town_name = strcat(town_name, " Hanoon");
            population_str = strtok(NULL, d);
            population = atoi(population_str);
        }
        Cnode* c = search(city, city_name);
        if (c != NULL) {
            if (!searchTown(c->town, town_name)) {
                Tnode* tow = (Tnode*)malloc(sizeof(Tnode));
                if (tow == NULL) {
                    printf("Memory allocation failed\n");
                    exit(1);
                }
                strncpy(tow->town, town_name, MAX_CITY_LENGTH - 1);
                tow->town[MAX_CITY_LENGTH - 1] = '\0';
                tow->pop = population;
                tow->next = NULL;

                if (c->town == NULL) {
                    c->town = (town*)malloc(sizeof(town));
                    if (c->town == NULL) {
                        printf("Memory allocation failed\n");
                        exit(1);
                    }
                    c->town->head = tow;
                    c->town->tail = tow;
                } else {
                    add_sorted(c->town, tow);
                }
            }
        }
    }

    fclose(fptr);
}
// Function to search for a city in the cities list
bool searchBool(cities* list, char c[]) {
    Cnode* ptr = list->head;
    while (ptr != NULL) {
        if (strcmp(ptr->city, c) == 0) {
            return true;
        }
        ptr = ptr->next;
    }
    return false;
}
// Function to search for a city  in the cities list and return poiter
Cnode* search(cities* list, char c[]) {
    Cnode* ptr = list->head;
    while (ptr != NULL) {
        if (strcmp(ptr->city, c) == 0) {
            return ptr;
        }
        ptr = ptr->next;
    }
    return NULL;
}
// Function to add a town node to a town list in sorted order by population
void add_sorted(town* t, Tnode* tow) {
    if (t->head == NULL || tow->pop <= t->head->pop) {
        tow->next = t->head;
        t->head = tow;
        if (t->tail == NULL) {
            t->tail = tow;
        }
        return;
    }
    Tnode* curr = t->head;
    while (curr->next != NULL && curr->next->pop < tow->pop) {
        curr = curr->next;
    }
    tow->next = curr->next;
    curr->next = tow;
    if (tow->next == NULL) {
        t->tail = tow;
    }
}
// Function to print cities and their towns
void printTown(cities *DLL) {
    Cnode* ptr = DLL->head;
    while (ptr != NULL) {
        printf("%s District\n", ptr->city);
        Tnode* townPtr = ptr->town->head;
        while (townPtr != NULL) {
            printf("%s,%d\n", townPtr->town, townPtr->pop);
            townPtr = townPtr->next;
        }
        ptr = ptr->next;
    }
}
// Function to add a new district to the cities list
void add_new_district(cities *sortedDLL) {
    sortDLL(sortedDLL);
    Cnode *newNode = (Cnode *)malloc(sizeof(Cnode));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }

    printf("Insert district name:\n");

    scanf("%49s", newNode->city);

    newNode->city[49] = '\0';
    newNode->next = NULL;
    newNode->prev = NULL;
    if (sortedDLL->head == NULL) {
        sortedDLL->head = newNode;
        sortedDLL->tail = newNode;
        return;
    }
    if (strcmp(newNode->city, sortedDLL->head->city) <= 0) {
        newNode->next = sortedDLL->head;
        sortedDLL->head->prev = newNode;
        sortedDLL->head = newNode;
        return;
    }

    Cnode *current = sortedDLL->head->next;
    while (current != NULL) {
        if (strcmp(newNode->city, current->city) <= 0) {
            newNode->next = current;
            newNode->prev = current->prev;
            current->prev->next = newNode;
            current->prev = newNode;
            return;
        }
        current = current->next;
    }

    sortedDLL->tail->next = newNode;
    newNode->prev = sortedDLL->tail;
    sortedDLL->tail = newNode;
}
// Function to add a new town to a district
void add_new_town(cities *DLL) {
    char strCity[MAX_CITY_LENGTH];
    printf("Enter the district name to add town:\n");
    scanf("%49s", strCity);
    strCity[MAX_CITY_LENGTH - 1] = '\0';
    Cnode *curr = search(DLL, strCity);

    if (curr == NULL) {
        printf("District not found.\n");
        return;
    }

    Tnode *newTown = (Tnode *)malloc(sizeof(Tnode));
    if (newTown == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }

    printf("Insert the name of the town and its population consecutively:\n");
    scanf("%49s", newTown->town);

    printf("Enter the population:\n");
    scanf("%d", &(newTown->pop));

    newTown->town[MAX_CITY_LENGTH - 1] = '\0';

    newTown->next = NULL;

    if (curr->town == NULL) {
        curr->town = (town *)malloc(sizeof(town));
        if (curr->town == NULL) {
            printf("Memory allocation failed!\n");
            free(newTown);
            return;
        }
        curr->town->head = NULL;
        curr->town->tail = NULL;
    }
    add_towns(DLL);
    add_sorted(curr->town, newTown);
}
// Function to delete a town from a district
void DelTown(cities *DLL) {
    char strCity[MAX_CITY_LENGTH];
    char deleteTown[MAX_CITY_LENGTH];

    printf("Enter the district name to delete a town from:\n");
    scanf("%49s", strCity);
    strCity[MAX_CITY_LENGTH - 1] = '\0';
    Cnode *curr = search(DLL, strCity);

    if (curr == NULL) {
        printf("District not found.\n");
        return;
    }

    printf("Enter the name of the town you want to delete:\n");
    scanf("%49s", deleteTown);
    deleteTown[MAX_CITY_LENGTH - 1] = '\0';
        add_towns(DLL);
    if (curr->town == NULL || curr->town->head == NULL) {
        printf("No towns found in the district.\n");
        return;
    }
    Tnode *target = searchTown(curr->town, deleteTown);
    if (target == NULL) {
        printf("Town '%s' is not in the list.\n", deleteTown);
    } else if (target == curr->town->head) {
        curr->town->head = curr->town->head->next;
        free(target);
    } else {
        Tnode *prev = curr->town->head;
        while (prev->next != target) {
            prev = prev->next;
        }
        prev->next = target->next;
        free(target);
    }
}
// Function to search for a town in a town list
Tnode *searchTown(town *list, char x[]) {
    Tnode *ptr = list->head;
    Tnode *target = NULL;

    while (ptr != NULL) {
        if (strcmp(ptr->town, x) == 0) {
            target = ptr;
            break;
        }
        ptr = ptr->next;
    }
    return target;
}
// Function to delete all information related to a district
void deleteDistrictInfo(cities *DLL, const char *districtName) {
    Cnode *prev = NULL;
    Cnode *current = DLL->head;

    while (current != NULL) {
        if (strcmp(current->city, districtName) == 0) {
            Tnode *townPtr = current->town->head;
            while (townPtr != NULL) {
                Tnode *tempTown = townPtr;
                townPtr = townPtr->next;
                free(tempTown);
            }
            free(current->town);
            current->town = NULL;
            if (prev == NULL) {
                DLL->head = current->next;
                if (DLL->head != NULL) {
                    DLL->head->prev = NULL;
                }
            } else {
                prev->next = current->next;
                if (current->next != NULL) {
                    current->next->prev = prev;
                }
            }
            free(current);
            printf("Information for %s district has been deleted along with its towns and list has been updated.\n", districtName);
            return;
        }
        prev = current;
        current = current->next;
    }
    printf("%s district does not exist in the data.\n", districtName);
}
// Function to delete all information related to a district by user input
void deleteAll(cities *DLL) {
    char districtName[MAX_CITY_LENGTH];
    printf("Enter the name of the district to delete it's information: ");
    scanf("%49s", districtName);

    deleteDistrictInfo(DLL, districtName);
}
// Function to calculate total population, maximum, and minimum town population
void calc_pop(cities *DLL) {
    Cnode *temp = DLL->head;
    add_towns(DLL);
    int sum = 0;
    int max_population = INT_MIN;
    int min_population = INT_MAX;

    while (temp != NULL) {
        Tnode *headTown = temp->town->head;
        while (headTown != NULL) {
            sum += headTown->pop;
            if (headTown->pop > max_population) {
                max_population = headTown->pop;
            }
            if (headTown->pop < min_population) {
                min_population = headTown->pop;
            }

            headTown = headTown->next;
        }
        temp = temp->next;
    }

    printf("Total population of all towns: %d\n", sum);
    printf("Maximum town population: %d\n", max_population);
    printf("Minimum town population: %d\n", min_population);
}
// Function to print the total population of each district
void print_dis_pop(cities *DLL) {
    add_towns(DLL);
    Cnode *ptr = DLL->head;
    while (ptr != NULL) {
        int totalPopulation = 0;
        Tnode *temp = ptr->town->head;
        while (temp != NULL) {
            totalPopulation += temp->pop;
            temp = temp->next;
        }
        printf("%s District, Population = %d\n", ptr->city, totalPopulation);
        ptr = ptr->next;
    }
}
// Function to change the population of a town
void changeTownPopulation(cities *DLL) {
    add_towns(DLL);
    char district[MAX_CITY_LENGTH];
    char town[MAX_CITY_LENGTH];
    int newPopulation;
    printf("Enter the district name: ");
    scanf("%49s", district);
    district[MAX_CITY_LENGTH - 1] = '\0';
    Cnode *currDistrict = search(DLL, district);
    if (currDistrict == NULL) {
        printf("District not found.\n");
        return;
    }
    printf("Enter the name of the town: ");
    scanf("%49s", town);
    town[MAX_CITY_LENGTH - 1] = '\0';
    Tnode *currTown = searchTown(currDistrict->town, town);
    if (currTown == NULL) {
        printf("Town not found in the district.\n");
        return;
    }

    printf("Enter the new population: ");
    scanf("%d", &newPopulation);
    currTown->pop = newPopulation;
    printf("Population of town '%s' in district '%s' updated successfully.\n", town, district);
}
// Function to calculate the total population
int getTotalPopulation(town *townList) {
    int totalPopulation = 0;
    Tnode* townPtr = townList->head;
    while (townPtr != NULL) {
        totalPopulation += townPtr->pop;
        townPtr = townPtr->next;
    }
    return totalPopulation;
}
// Function to output the current state of the cities list to a file
void output(cities* DLL) {
    FILE* outputFile = fopen("sorted_districts.txt", "w");
    if (outputFile == NULL) {
        printf("Error: Unable to create output file.\n");
        return;
    }
    add_towns(DLL);
    Cnode* ptr = DLL->head;
    while (ptr != NULL) {
        fprintf(outputFile, "%s District, Population = %d\n", ptr->city, getTotalPopulation(ptr->town));
        Tnode* townPtr = ptr->town->head;
        while (townPtr != NULL) {
            fprintf(outputFile, "%s,%d\n", townPtr->town, townPtr->pop);
            townPtr = townPtr->next;
        }
        ptr = ptr->next;
    }

    fclose(outputFile);
    printf("Data has been saved to sorted_districts.txt successfully.\n");
}
// Function to print the menu of options
void menu (){
printf("\nPlease choose your desired option from the menu.\n" );
printf("1. Load the input file (Palestinian districts and their town with population).\n");
printf("2. Print the loaded information before sorting (as in the input file format).\n");
printf("3. Sort the districts alphabetically using Radix sort.\n");
printf("4. Sort the towns for each district based on population in ascending order.\n");
printf("5. Print the sorted information.\n");
printf("6. Add a new district to the list of sorted districts (and sort the list)\n");
printf("7. Add a new town to a certain district.\n");
printf("8. Delete a town from a specific district.\n");
printf("9. Delete a complete district; here, you must delete all towns belonging to that district before deleting it.\n");
printf("10.Calculate the population of Palestine, the max and min town population.\n");
printf("11.Print the districts and their total population (without towns details).\n");
printf("12.Change the population of a town, after prompting the user to enter the district name.\n");
printf("13.Save to output file.\n");
printf("14.Exit\n");

}

int main() {
    cities *p = (cities *)malloc(sizeof(cities));
    p->head=NULL;
    p->tail=NULL;
    add_cities(p);
    menu();

    int s;
    scanf("%d", &s);
    while (s != 14) {
        switch (s) {
            case 1:
                load_file();
                break;
            case 2:
                print_as_formatted();
                break;
            case 3:
                add_cities(p);
                printf("Sort the districts alphabetically using Radix sort has done successfully :)\n");
                break;
            case 4:
                printf("\nSort the towns for each district based on population in ascending order has done successfully:)\n");
                break;
            case 5:
                add_towns(p);
                printTown(p);
                break;
            case 6:
                add_new_district(p);
                print(p);
                break;
            case 7:
                add_new_town(p);
                printTown(p);
                break;
            case 8:
                DelTown(p);
                printTown(p);
                break;
            case 9:
                deleteAll(p);
                break;
            case 10:
                calc_pop(p);
                break;
            case 11:
                print_dis_pop(p);
                break;
            case 12:
                changeTownPopulation(p);
                break;
            case 13:
                 output (p);
                 break;
            default:
                printf("Invalid option. Please try again.\n");
                break;
        }

        menu();
        scanf("%d", &s);
    }

    free(p);
    return 0;
}
