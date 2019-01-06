#include "LKH.h"
#include "Segment.h"




struct hashset_st {
    size_t nbits;
    size_t mask;

    size_t capacity;
    size_t *items;
    size_t nitems;
    size_t n_deleted_items;
};

typedef struct hashset_st *hashset_t;

/* create hashset instance */
hashset_t hashset_create(void);

/* destroy hashset instance */
void hashset_destroy(hashset_t set);

size_t hashset_num_items(hashset_t set);

/* add item into the hashset.
    *
    * @note 0 and 1 is special values, meaning nil and deleted items. the
    *       function will return -1 indicating error.
    *
    * returns zero if the item already in the set and non-zero otherwise
    */
int hashset_add(hashset_t set, void *item);

/* remove item from the hashset
    *
    * returns non-zero if the item was removed and zero if the item wasn't
    * exist
    */
int hashset_remove(hashset_t set, void *item);

/* check if existence of the item
    *
    * returns non-zero if the item exists and zero otherwise
    */
int hashset_is_member(hashset_t set, void *item);



static const unsigned int prime_1 = 73;
static const unsigned int prime_2 = 5009;

hashset_t hashset_create()
{
    hashset_t set = calloc(1, sizeof(struct hashset_st));

    if (set == NULL) {
        return NULL;
    }
    set->nbits = 3;
    set->capacity = (size_t)(1 << set->nbits);
    set->mask = set->capacity - 1;
    set->items = calloc(set->capacity, sizeof(size_t));
    if (set->items == NULL) {
        hashset_destroy(set);
        return NULL;
    }
    set->nitems = 0;
    set->n_deleted_items = 0;
    return set;
}

size_t hashset_num_items(hashset_t set)
{
    return set->nitems;
}

void hashset_destroy(hashset_t set)
{
    if (set) {
        free(set->items);
    }
    free(set);
}

static int hashset_add_member(hashset_t set, void *item)
{
    size_t value = (size_t)item;
    size_t ii;

    if (value == 0 || value == 1) {
        return -1;
    }

    ii = set->mask & (prime_1 * value);

    while (set->items[ii] != 0 && set->items[ii] != 1) {
        if (set->items[ii] == value) {
            return 0;
        }
        else {
            /* search free slot */
            ii = set->mask & (ii + prime_2);
        }
    }
    set->nitems++;
    if (set->items[ii] == 1) {
        set->n_deleted_items--;
    }
    set->items[ii] = value;
    return 1;
}

static void maybe_rehash(hashset_t set)
{
    size_t *old_items;
    size_t old_capacity, ii;


    if (set->nitems + set->n_deleted_items >= (double)set->capacity * 0.85) {
        old_items = set->items;
        old_capacity = set->capacity;
        set->nbits++;
        set->capacity = (size_t)(1 << set->nbits);
        set->mask = set->capacity - 1;
        set->items = calloc(set->capacity, sizeof(size_t));
        set->nitems = 0;
        set->n_deleted_items = 0;
        assert(set->items);
        for (ii = 0; ii < old_capacity; ii++) {
            hashset_add_member(set, (void *)old_items[ii]);
        }
        free(old_items);
    }
}

int hashset_add(hashset_t set, void *item)
{
    int rv = hashset_add_member(set, item);
    maybe_rehash(set);
    return rv;
}

int hashset_remove(hashset_t set, void *item)
{
    size_t value = (size_t)item;
    size_t ii = set->mask & (prime_1 * value);

    while (set->items[ii] != 0) {
        if (set->items[ii] == value) {
            set->items[ii] = 1;
            set->nitems--;
            set->n_deleted_items++;
            return 1;
        }
        else {
            ii = set->mask & (ii + prime_2);
        }
    }
    return 0;
}

int hashset_is_member(hashset_t set, void *item)
{
    size_t value = (size_t)item;
    size_t ii = set->mask & (prime_1 * value);

    while (set->items[ii] != 0) {
        if (set->items[ii] == value) {
            return 1;
        }
        else {
            ii = set->mask & (ii + prime_2);
        }
    }
    return 0;
}

static int initialized;
static hashset_t set;

static int is_prime(int p) {
    if (!initialized) {
        initialized = 1;
        set = hashset_create();
        FILE *myFile = fopen("prime_list.txt", "r");

        for (int i = 0; i < 17802; i++)
        {
            int temp;
            fscanf(myFile, "%d", &temp);

            hashset_add(set, temp);
        }
        printf("prime list read finished.\n");
    }

    int result = hashset_is_member(set, p);

    // printf("%d %d\n", p, result);
    return result;
}

GainType Penalty_PRIME()
{
    Node *N, *NextN;
    GainType P = 0;
    int Forward = SUCC(Depot)->Id != Depot->Id + DimensionSaved;
   
    N = Depot;
    do {
        if (N->Id <= Dim) {
            NextN = Forward ? SUCC(N) : PREDD(N);

            int temp = C(N, NextN);
            if (N->Rank % 10 == 0 && !is_prime(N->Id))
                temp *= 1.1;

            P += temp;
            if (P > CurrentPenalty ||
                (P == CurrentPenalty && CurrentGain <= 0)) {
                printf("P: %d, CurrentPenalty: %d\n", P, CurrentPenalty);
                return CurrentPenalty + (CurrentGain > 0);
            }
        }
        N = Forward ? SUCC(N) : PREDD(N);
    } while (N != Depot);
    printf("P: %d, CurrentPenalty: %d\n", P, CurrentPenalty);
    return P;
}
