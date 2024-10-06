#include "sortedset.h"

#define BASE_SIZE(elem_count, elem_size) elem_count * (elem_size + 2 * sizeof(int)) + sizeof(int)

/*
* Function: SetNew
* Usage: SetNew(&stringSet, sizeof(char *), StringPtrCompare);
*
SetNew(&constellations, sizeof(pointT), DistanceCompare);
* ----------------
* SetNew allocates the requisite space needed to manage what
* will initially be an empty sorted set. More specifically, the
* routine allocates space to hold up to 'kInitialCapacity' (currently 4)
* client elements.
*/


static const int kInitialCapacity = 4;
void SetNew(sortedset *set, int elemSize, int (*cmpfn)(const void *, const void *), void (*freefn)(const void *))
{
    set->allocated_length = kInitialCapacity;
    set->elem_size = elemSize;
    set->cmp_fn = cmpfn;
    set->free_fn = freefn;
    set->logical_length = 0;
    set->base = malloc(BASE_SIZE(set->allocated_length, set->elem_size));
    assert(set->base);
    *(int *) set->base = -1;
}

/*
* Function: SetSearch
* Usage: if (SetSearch(&staffSet, &lecturer) == NULL)
*
printf("musta been fired");
* -------------------
* SetSearch searches for the specified client element according
* the whatever comparison function was provided at the time the
* set was created. A pointer to the matching element is returned
* for successful searches, and NULL is returned to denote failure.
*/
void *SetSearch(sortedset *set, const void *elemPtr)
{
    int *index_ptr = FindNode(set, elemPtr);

    if (*index_ptr == -1) {
        return NULL;
    }

    void *target = (char *) set->base + sizeof(int) + (*index_ptr) * (set->elem_size + 2 * sizeof(int));
    return target;
}
/*
* Function: SetAdd
* Usage: if (!SetAdd(&friendsSet, &name)) free(name);
* ----------------
* Adds the specified element to the set if not already present.
* present, the client element is not copied into the set. true
* is returned if and only if the element at address elemPtr
* was copied into the set.
*/
bool SetAdd(sortedset *set, const void *elemPtr)
{
    int *index_ptr = FindNode(set, elemPtr);

    if (*index_ptr != -1) {
        return false;
    }

    if (set->allocated_length == set->logical_length) {
        set->allocated_length *= 2;

        set->base = realloc(set->base, BASE_SIZE(set->allocated_length, set->elem_size));
        assert(set->base);
    }

    void *target = (char *) set->base + sizeof(int) + set->logical_length * (set->elem_size + 2 * sizeof(int));

    memcpy(target, elemPtr, set->elem_size);

    int *target_children = (int *) ((char *) target + set->elem_size);
    
    target_children[0] = target_children[1] = -1;

    *index_ptr = set->logical_length;
    set->logical_length++;
}

/**
* Function: FindNode
* Usage: ip = FindNode(set, elem);
*
if (*ip == -1) printf("ip points where this element belongs!");
* ------------------
* FindNode descends through the underlying binary search tree of the
* specified set and returns the address of the offset into raw storage
* where the specified element resides. If the specified element isn't
* in the set, FindNode returns the address of the –1 that would be updated
* to contain the index of the element being sought if it were the
* element to be inserted——that is, the address of the –1 that ended
* the search.
*/
static int *FindNode(sortedset *set, const void *elem)
{

    int *current_ptr = set->base;

    while (true) {
        int current_element_index = *current_ptr;

        if (current_element_index == -1) {
            return current_ptr;
        }

        void *current_element = 
            ((char *) set->base + sizeof(int)) 
            + current_element_index * (2 * sizeof(int) + set->elem_size);

        int ret = set->cmp_fn(current_element, elem);

        if (ret == 0) {
            return current_ptr;
        } else if (ret > 0) {
            current_ptr = (int *)((char *) current_element + set->elem_size);
        } else {
            current_ptr = (int *)((char *) current_element + set->elem_size + sizeof(int));
        }
    }

    //unreachable
    assert(0);
    return NULL;
}

void destruct(sortedset *set)
{
    // yvela elementze gadavlaa sachiro da freeFn-is gamodzaxeba
    free(set->base);
}