
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum
{
	Integer,
	String,
	List,
	Nil
} nodeType;

/**
creates a new string first + second
*/
char *ConcatStrings(const char *first, const char *second);

/**
recursively concats all string nodeTypes
*/
char *ConcatAll(nodeType *list);

char *ConcatStrings(const char *first, const char *second)
{
    int size = 1;
    size += strlen(first);
    size += strlen(second);

    char* head = malloc(size);
    strcpy(head, first);
    strcat(head, second);

    return head;
}



char *ConcatAll(nodeType *list)
{
    nodeType t = *list;

    if(t == Nil || t == Integer){
        return strdup("");
    }

    if(t == String){
        return strdup((char*)(list + 1));
    }

    nodeType **node_ptrs = (nodeType **) (list + 1);

    char *first_result = ConcatAll(node_ptrs[0]);
    char *second_result = ConcatAll(node_ptrs[1]);

    char *result = ConcatStrings(first_result, second_result);

    free(first_result);
    free(second_result);

    return result;
}

int main() {
    nodeType *stringNodes[32] = {};
    nodeType *intNodes   [32] = {};
    nodeType *listNodes  [32] = {};

    nodeType  nilNode = Nil;


    for (int i = 0; i < 32; i++) {
        char some_string[32] = {};

        sprintf(some_string, "test%d", i);

        
        nodeType *ptr = malloc(sizeof(nodeType) + strlen(some_string) + 1);

        *ptr = String;

        strcpy((char *)(ptr + 1), some_string);
        stringNodes[i] = ptr;
    }

    for (int i = 0; i < 32; i++) {
        
        nodeType *ptr = malloc(sizeof(nodeType) + sizeof(int));
        *ptr = Integer;

        memcpy(ptr + 1, &i, sizeof(int));

        intNodes[i] = ptr;
    }


    for (int i = 0; i < 32; i++) {
        
        nodeType *ptr = malloc(sizeof(nodeType) + 2 * sizeof(void *));
        *ptr = List;
        
        // set both pointers to nil

        ((nodeType **) (ptr + 1))[0] = &nilNode;
        ((nodeType **) (ptr + 1))[1] = &nilNode; 
        
        listNodes[i] = ptr;
    }

    for (int i = 0; i < 31; i++) {
        // connect all lists to eachother
        ((nodeType **) (listNodes[i] + 1))[1] = listNodes[i + 1]; 

        // even lists point to strings, odds point to ints
        if ( i % 2 == 0) {
            ((nodeType **) (listNodes[i] + 1))[0] = stringNodes[i]; 
        } else {
            ((nodeType **) (listNodes[i] + 1))[0] = intNodes[i]; 
        }
    }

    printf("%s\n", ConcatAll(listNodes[0]));
}