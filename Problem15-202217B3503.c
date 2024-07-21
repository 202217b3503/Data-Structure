
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>  // Include this header for INT16_MAX

#define INITIAL_CAPACITY 100

// Linked List node structure
struct node {
    char* key;
    char* value;
    struct node* next;
};

// Function to initialize a new node
void setNode(struct node* node, char* key, char* value) {
    node->key = strdup(key);   // Allocate memory and copy the key
    node->value = strdup(value);   // Allocate memory and copy the value
    node->next = NULL;
}

// HashMap structure
struct hashMap {
    int numOfElements;
    int capacity;
    struct node** arr;
};

// Function to initialize the hashMap
void initializeHashMap(struct hashMap* mp) {
    mp->capacity = INITIAL_CAPACITY;
    mp->numOfElements = 0;
    mp->arr = (struct node*)malloc(sizeof(struct node) * mp->capacity);
    for (int i = 0; i < mp->capacity; i++) {
        mp->arr[i] = NULL;
    }
}

// Hash function
int hashFunction(struct hashMap* mp, char* key) {
    int bucketIndex;
    int sum = 0;
    int factor = 31;
    for (int i = 0; i < strlen(key); i++) {
        sum = ((sum % mp->capacity) + (((int)key[i]) * factor) % mp->capacity) % mp->capacity;
        factor = (factor * 31) % INT16_MAX; // Avoid overflow
    }
    bucketIndex = sum;
    return bucketIndex;
}

// Function to insert key-value pair into hashMap
void insert(struct hashMap* mp, char* key, char* value) {
    int bucketIndex = hashFunction(mp, key);
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    setNode(newNode, key, value);

    // Handle collision by inserting at the head of the linked list
    newNode->next = mp->arr[bucketIndex];
    mp->arr[bucketIndex] = newNode;
    mp->numOfElements++;
}

// Function to delete a key-value pair from hashMap
void delete(struct hashMap* mp, char* key) {
    int bucketIndex = hashFunction(mp, key);
    struct node* prevNode = NULL;
    struct node* currNode = mp->arr[bucketIndex];

    while (currNode != NULL) {
        if (strcmp(key, currNode->key) == 0) {
            if (currNode == mp->arr[bucketIndex]) {
                mp->arr[bucketIndex] = currNode->next;
            } else {
                prevNode->next = currNode->next;
            }
            free(currNode->key);
            free(currNode->value);
            free(currNode);
            mp->numOfElements--;
            return;
        }
        prevNode = currNode;
        currNode = currNode->next;
    }
}

// Function to search for a key in the hashMap
char* search(struct hashMap* mp, char* key) {
    int bucketIndex = hashFunction(mp, key);
    struct node* bucketHead = mp->arr[bucketIndex];

    while (bucketHead != NULL) {
        if (strcmp(key, bucketHead->key) == 0) {
            return bucketHead->value;
        }
        bucketHead = bucketHead->next;
    }

    // Return static error message
    return "Oops! No data found.\n";
}

// Driver code
int main() {
    struct hashMap* mp = (struct hashMap*)malloc(sizeof(struct hashMap));
    initializeHashMap(mp);

    insert(mp, "Yogaholic", "Anjali");
    insert(mp, "pluto14", "Vartika");
    insert(mp, "elite_Programmer", "Manish");
    insert(mp, "GFG", "BITS");
    insert(mp, "decentBoy", "Mayank");

    printf("%s\n", search(mp, "elite_Programmer"));  // Manish
    printf("%s\n", search(mp, "Yogaholic"));  // Anjali
    printf("%s\n", search(mp, "pluto14"));  // Vartika
    printf("%s\n", search(mp, "decentBoy"));  // Mayank
    printf("%s\n", search(mp, "GFG"));  // BITS

    // Key is not inserted
    printf("%s\n", search(mp, "randomKey"));  // Oops! No data found.

    printf("\nAfter deletion:\n");
    delete(mp, "decentBoy");
    printf("%s\n", search(mp, "decentBoy"));  // Oops! No data found.

    // Free memory
    for (int i = 0; i < mp->capacity; i++) {
        struct node* bucketHead = mp->arr[i];
        while (bucketHead != NULL) {
            struct node* temp = bucketHead;
            bucketHead = bucketHead->next;
            free(temp->key);
            free(temp->value);
            free(temp);
        }
    }
    free(mp->arr);
    free(mp);

    return 0;
}