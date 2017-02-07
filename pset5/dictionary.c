/**
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "dictionary.h"

#define CHILDREN 27

//prototype of tries
typedef struct node
{
    bool is_word;
    struct node* children[CHILDREN];
}
Node;

// Returns new trie node (initialized to NULLs)
Node *getNode(void);

//Destroy any N-ary trie structures
bool destroy_trie(Node* travel);

//Global variables for other function to access
Node* trie_root;
unsigned int Num_words = 0;
int children_index= 0;    //for index in unload function

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    //iterate over each children from the root if and check if the last children is a word
    int level;
    int length = strlen(word);
    int index = 0;
    Node* pCrawl = trie_root;
    
    for (level = 0; level < length; level++)
    {
        if(word[level] == 39)
            index = 26;
        
        else
            index = tolower(word[level])- 'a';
        
        if (!pCrawl->children[index])
            return false;
            
        pCrawl = pCrawl->children[index];
    }

    return (pCrawl != NULL && pCrawl->is_word);
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    //open dictionary
    FILE* fp = fopen(dictionary, "r");
    if (fp == NULL)
    {
        printf("Could not open %s.\n", dictionary);
        return false;
    }
    
    trie_root = getNode();
    Node *pCrawl = NULL;
    
    char word[LENGTH+1];
    while(fscanf(fp, "%s", word) != EOF)
    {
        int index;
        int level;
        int length = strlen(word);
        
        pCrawl = trie_root;
        
        for(level = 0; level < length; level++)
        {
            if(word[level] == 39)
                index = 26;
                
            else    
                index = word[level] - 'a';
        
            if(!pCrawl->children[index])
                pCrawl->children[index] = getNode();
                
            pCrawl = pCrawl->children[index];
        }
        
        pCrawl->is_word = true;
        Num_words++;
    }
    
    fclose(fp);
    
    return true;
    
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    //return Num_words previusly incremented each time a word was storage
    return Num_words;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    destroy_trie(trie_root);
    
    return true;
}

Node *getNode(void)
{
    Node *pNode;
    
    pNode = (Node *)malloc(sizeof(Node));

    if (pNode)
    {

        pNode->is_word = false;
    }
    
    return pNode;
}

bool destroy_trie(Node* travel)
{
    int index;
    
    for(index = 0; index < CHILDREN; index++)
    {
        if(travel->children[index])
            destroy_trie(travel->children[index]);
    }
    
    free(travel);
    return true;
    
}
