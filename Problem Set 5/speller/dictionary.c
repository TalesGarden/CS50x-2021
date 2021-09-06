// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "dictionary.h"
#include <string.h>
#include <ctype.h>



#define PRIME 31
int sizeOfDictionary = 0;

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 256;

// Hash table
node *table[N];

//prototype
bool insertIntoHashTable(node *no, int key);
void freeMemory(node *list);

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    int size_word = strlen(word);
    char word_copy[ size_word + 1 ];

    for (int i = 0; i < size_word; ++ i)
    {
        word_copy[i] = tolower(word[i]);
    }

    word_copy[size_word] = '\0';

    int hashKeyWord = hash(word_copy);

    if (table[hashKeyWord] == NULL)
    {
        return false;
    }
    node *iterator = table[hashKeyWord];

    while (iterator)
    {
        if (strcmp(iterator->word, word_copy) == 0)
        {
            return true;
        }
        iterator = iterator->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    unsigned int hashValue = 0;
    int lenght = strlen(word);

    for (int i = 0; i < lenght; ++i)
    {
        hashValue = (hashValue * PRIME + word[i]) % N;
        /*
            h_value = (h_value + (word[i] - 'a' + 1) * p_pow) % N;
            p_pow = (p_pow * PRIME) % N;  // from https://cp-algorithms.com/string/string-hashing.html
        */
    }
    return hashValue;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    char wordBuffer[LENGTH + 1];

    //seting pointers to NULL in the hash table
    for (int i = 0; i < N ; i++)
    {
        table[i] = NULL;
    }

    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        printf("Error Opening the file ");
        return false;
    }
    int hashKey = 0;

    while (fscanf(file, "%s", wordBuffer) != EOF)
    {
        wordBuffer[LENGTH] = '\0';
        //while (fgets(wordBuffer, LENGTH + 1, file))
        //{
        //  wordBuffer[LENGTH] = '\0';
        //Removing trailing newline character from fgets() input
        //wordBuffer[strcspn(wordBuffer, "\n")] = 0;


        //create a no to insert into the hash table
        node *no = malloc(sizeof(node));

        if (no == NULL)
        {
            unload();
            return false;
        }

        strcpy(no->word, wordBuffer);
        no->next = NULL;
        hashKey = hash(no->word);
        insertIntoHashTable(no, hashKey);



    }
    fclose(file);
    // TODO
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return sizeOfDictionary;

}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{

    for (int i = 0; i < N; ++i)
    {
        if (table[i] == NULL)
        {
            continue;
        }

        freeMemory(table[i]);
    }

    sizeOfDictionary = 0;
    return true;
}

bool insertIntoHashTable(node *no, int key)
{
    if (no == NULL)
    {
        return false;
    }

    if (table[key] == NULL)
    {
        table[key] = no;
        sizeOfDictionary ++;
        return true;
    }

    node *iterator = table[key];
    while (iterator)
    {
        if (iterator->next == NULL)
        {
            iterator = no;
            sizeOfDictionary++;
            return true;
        }
        iterator = iterator->next;
    }


    return false;;
}

void freeMemory(node *list)
{
    if (list == NULL)
    {
        return;
    }

    freeMemory(list->next);
    free(list);
    /*
    node* tmp;

    while(list != NULL)
    {
        tmp = list;
        list = list->next;
        free(tmp);
    }
    */
}
