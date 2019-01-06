#include "LKH.h"

/*
 * Functions for computing distances (see TSPLIB).
 *
 * The appropriate function is referenced by the function pointer Distance.
 */
int Distance_1(Node * Na, Node * Nb)
{
    return 1;
}

int Distance_LARGE(Node * Na, Node * Nb)
{
    return 10000000;
}

int Distance_Asymmetric(Node * Na, Node * Nb)
{
    int n = DimensionSaved;
    if ((Na->Id <= n) == (Nb->Id <= n))
        return M;
    if (abs(Na->Id - Nb->Id) == n)
        return 0;
    return Na->Id <= n ? OldDistance(Na, Nb - n) : OldDistance(Nb, Na - n);
}

int Distance_ATSP(Node * Na, Node * Nb)
{
    int n = DimensionSaved;
    if ((Na->Id <= n) == (Nb->Id <= n))
        return M;
    if (abs(Na->Id - Nb->Id) == n)
        return 0;
    return Na->Id <= n ? Na->C[Nb->Id - n] : Nb->C[Na->Id - n];
}

int Distance_ATT(Node * Na, Node * Nb)
{
    double xd = Na->X - Nb->X, yd = Na->Y - Nb->Y;
    return (int) ceil(Scale * (sqrt((xd * xd + yd * yd) / 10.0)));
}

int Distance_CEIL_2D(Node * Na, Node * Nb)
{
    double xd = Na->X - Nb->X, yd = Na->Y - Nb->Y;
    return (int) ceil(Scale * sqrt(xd * xd + yd * yd));
}

int Distance_CEIL_3D(Node * Na, Node * Nb)
{
    double xd = Na->X - Nb->X, yd = Na->Y - Nb->Y, zd = Na->Z - Nb->Z;
    return (int) ceil(Scale * sqrt(xd * xd + yd * yd + zd * zd));
}


//struct hashset_st {
//    size_t nbits;
//    size_t mask;
//
//    size_t capacity;
//    size_t *items;
//    size_t nitems;
//    size_t n_deleted_items;
//};
//
//typedef struct hashset_st *hashset_t;
//
///* create hashset instance */
//hashset_t hashset_create(void);
//
///* destroy hashset instance */
//void hashset_destroy(hashset_t set);
//
//size_t hashset_num_items(hashset_t set);
//
///* add item into the hashset.
//    *
//    * @note 0 and 1 is special values, meaning nil and deleted items. the
//    *       function will return -1 indicating error.
//    *
//    * returns zero if the item already in the set and non-zero otherwise
//    */
//int hashset_add(hashset_t set, void *item);
//
///* remove item from the hashset
//    *
//    * returns non-zero if the item was removed and zero if the item wasn't
//    * exist
//    */
//int hashset_remove(hashset_t set, void *item);
//
///* check if existence of the item
//    *
//    * returns non-zero if the item exists and zero otherwise
//    */
//int hashset_is_member(hashset_t set, void *item);
//
//
//
//static const unsigned int prime_1 = 73;
//static const unsigned int prime_2 = 5009;
//
//hashset_t hashset_create()
//{
//    hashset_t set = calloc(1, sizeof(struct hashset_st));
//
//    if (set == NULL) {
//        return NULL;
//    }
//    set->nbits = 3;
//    set->capacity = (size_t)(1 << set->nbits);
//    set->mask = set->capacity - 1;
//    set->items = calloc(set->capacity, sizeof(size_t));
//    if (set->items == NULL) {
//        hashset_destroy(set);
//        return NULL;
//    }
//    set->nitems = 0;
//    set->n_deleted_items = 0;
//    return set;
//}
//
//size_t hashset_num_items(hashset_t set)
//{
//    return set->nitems;
//}
//
//void hashset_destroy(hashset_t set)
//{
//    if (set) {
//        free(set->items);
//    }
//    free(set);
//}
//
//static int hashset_add_member(hashset_t set, void *item)
//{
//    size_t value = (size_t)item;
//    size_t ii;
//
//    if (value == 0 || value == 1) {
//        return -1;
//    }
//
//    ii = set->mask & (prime_1 * value);
//
//    while (set->items[ii] != 0 && set->items[ii] != 1) {
//        if (set->items[ii] == value) {
//            return 0;
//        }
//        else {
//            /* search free slot */
//            ii = set->mask & (ii + prime_2);
//        }
//    }
//    set->nitems++;
//    if (set->items[ii] == 1) {
//        set->n_deleted_items--;
//    }
//    set->items[ii] = value;
//    return 1;
//}
//
//static void maybe_rehash(hashset_t set)
//{
//    size_t *old_items;
//    size_t old_capacity, ii;
//
//
//    if (set->nitems + set->n_deleted_items >= (double)set->capacity * 0.85) {
//        old_items = set->items;
//        old_capacity = set->capacity;
//        set->nbits++;
//        set->capacity = (size_t)(1 << set->nbits);
//        set->mask = set->capacity - 1;
//        set->items = calloc(set->capacity, sizeof(size_t));
//        set->nitems = 0;
//        set->n_deleted_items = 0;
//        assert(set->items);
//        for (ii = 0; ii < old_capacity; ii++) {
//            hashset_add_member(set, (void *)old_items[ii]);
//        }
//        free(old_items);
//    }
//}
//
//int hashset_add(hashset_t set, void *item)
//{
//    int rv = hashset_add_member(set, item);
//    maybe_rehash(set);
//    return rv;
//}
//
//int hashset_remove(hashset_t set, void *item)
//{
//    size_t value = (size_t)item;
//    size_t ii = set->mask & (prime_1 * value);
//
//    while (set->items[ii] != 0) {
//        if (set->items[ii] == value) {
//            set->items[ii] = 1;
//            set->nitems--;
//            set->n_deleted_items++;
//            return 1;
//        }
//        else {
//            ii = set->mask & (ii + prime_2);
//        }
//    }
//    return 0;
//}
//
//int hashset_is_member(hashset_t set, void *item)
//{
//    size_t value = (size_t)item;
//    size_t ii = set->mask & (prime_1 * value);
//
//    while (set->items[ii] != 0) {
//        if (set->items[ii] == value) {
//            return 1;
//        }
//        else {
//            ii = set->mask & (ii + prime_2);
//        }
//    }
//    return 0;
//}
//
//static int initialized;
//static hashset_t set;
//
//static int is_prime(int p) {
//    if (!initialized) {
//        initialized = 1;
//        set = hashset_create();
//        FILE *myFile = fopen("prime_list.txt", "r");
//
//        for (int i = 0; i < 17802; i++)
//        {
//            int temp;
//            fscanf(myFile, "%d", &temp);
//
//            hashset_add(set, temp);
//        }
//        printf("prime list read finished.\n");
//    }
//
//    int result = hashset_is_member(set, p);
//
//    // printf("%d %d\n", p, result);
//    return result;
//}

int Distance_EUC_2D(Node * Na, Node * Nb)
{
    double xd = Na->X - Nb->X, yd = Na->Y - Nb->Y;
    double temp = Scale * sqrt(xd * xd + yd * yd) + 0.5;
    //if (Na->Rank % 10 == 0 && !is_prime(Na->Id))
    //    temp *= 1.1;
    return (int) temp;
}

int Distance_EUC_3D(Node * Na, Node * Nb)
{
    double xd = Na->X - Nb->X, yd = Na->Y - Nb->Y, zd = Na->Z - Nb->Z;
    return (int) (Scale * sqrt(xd * xd + yd * yd + zd * zd) + 0.5);
}

int Distance_EXPLICIT(Node * Na, Node * Nb)
{
    return Na->Id < Nb->Id ? Nb->C[Na->Id] : Na->C[Nb->Id];
}

int Distance_FLOOR_2D(Node * Na, Node * Nb)
{
    double xd = Na->X - Nb->X, yd = Na->Y - Nb->Y;
    return (int) floor(Scale * sqrt(xd * xd + yd * yd));
}

int Distance_FLOOR_3D(Node * Na, Node * Nb)
{
    double xd = Na->X - Nb->X, yd = Na->Y - Nb->Y, zd = Na->Z - Nb->Z;
    return (int) floor(Scale * sqrt(xd * xd + yd * yd + zd * zd));
}

#define PI 3.141592
#define RRR 6378.388

int Distance_GEO(Node * Na, Node * Nb)
{
    int deg;
    double NaLatitude, NaLongitude, NbLatitude, NbLongitude, min,
           q1, q2, q3;
    deg = (int) Na->X;
    min = Na->X - deg;
    NaLatitude = PI * (deg + 5.0 * min / 3.0) / 180.0;
    deg = (int) Na->Y;
    min = Na->Y - deg;
    NaLongitude = PI * (deg + 5.0 * min / 3.0) / 180.0;
    deg = (int) Nb->X;
    min = Nb->X - deg;
    NbLatitude = PI * (deg + 5.0 * min / 3.0) / 180.0;
    deg = (int) Nb->Y;
    min = Nb->Y - deg;
    NbLongitude = PI * (deg + 5.0 * min / 3.0) / 180.0;
    q1 = cos(NaLongitude - NbLongitude);
    q2 = cos(NaLatitude - NbLatitude);
    q3 = cos(NaLatitude + NbLatitude);
    return (int) (RRR * acos(0.5 * ((1.0 + q1) * q2 - (1.0 - q1) * q3)) +
                  1.0);
}

#undef M_PI
#define M_PI 3.14159265358979323846264
#define M_RRR 6378388.0

int Distance_GEOM(Node * Na, Node * Nb)
{
    double lati = M_PI * (Na->X / 180.0);
    double latj = M_PI * (Nb->X / 180.0);
    double longi = M_PI * (Na->Y / 180.0);
    double longj = M_PI * (Nb->Y / 180.0);
    double q1 = cos(latj) * sin(longi - longj);
    double q3 = sin((longi - longj) / 2.0);
    double q4 = cos((longi - longj) / 2.0);
    double q2 = sin(lati + latj) * q3 * q3 - sin(lati - latj) * q4 * q4;
    double q5 = cos(lati - latj) * q4 * q4 - cos(lati + latj) * q3 * q3;
    return (int) (M_RRR * atan2(sqrt(q1 * q1 + q2 * q2), q5) + 1.0);
}

int Distance_MAN_2D(Node * Na, Node * Nb)
{
    return (int) (Scale * (fabs(Na->X - Nb->X) + fabs(Na->Y - Nb->Y)) +
                  0.5);
}

int Distance_MAN_3D(Node * Na, Node * Nb)
{
    return (int) (Scale * (fabs(Na->X - Nb->X) +
                           fabs(Na->Y - Nb->Y) + fabs(Na->Z - Nb->Z)) +
                  0.5);
}

int Distance_MAX_2D(Node * Na, Node * Nb)
{
    int dx = (int) (Scale * fabs(Na->X - Nb->X) + 0.5),
        dy = (int) (Scale * fabs(Na->Y - Nb->Y) + 0.5);
    return dx > dy ? dx : dy;
}

int Distance_MAX_3D(Node * Na, Node * Nb)
{
    int dx = (int) (Scale * fabs(Na->X - Nb->X) + 0.5),
        dy = (int) (Scale * fabs(Na->Y - Nb->Y) + 0.5),
        dz = (int) (Scale * fabs(Na->Z - Nb->Z) + 0.5);
    if (dy > dx)
        dx = dy;
    return dx > dz ? dx : dz;
}

/* Function for computing the distance in kilometers between two points on
   the Earth's surface, based on the high accuracy method by H. Andoyer,
   as described in
   
       "Astronomical Algorithms (2nd Ed.)", pg. 85, Jean Meeus (2000).
*/

static double Meeus(double lat1, double lon1, double lat2, double lon2)
{
    const double a = 6378.137;  /* equator earth radius */
    const double fl = 1 / 298.257;      /* earth flattening */
    double f, g, l, sg, sl, sf, s, c, w, r, d, h1, h2;

    if (lat1 == lat2 && lon1 == lon2)
        return 0;
    f = (lat1 + lat2) / 2;
    g = (lat1 - lat2) / 2;
    l = (lon1 - lon2) / 2;
    sg = sin(g);
    sl = sin(l);
    sf = sin(f);
    sg = sg * sg;
    sl = sl * sl;
    sf = sf * sf;
    s = sg * (1 - sl) + (1 - sf) * sl;
    c = (1 - sg) * (1 - sl) + sf * sl;
    w = atan(sqrt(s / c));
    r = sqrt(s * c) / w;
    d = 2 * w * a;
    h1 = (3 * r - 1) / 2 / c;
    h2 = (3 * r + 1) / 2 / s;
    return d * (1 + fl * (h1 * sf * (1 - sg) - h2 * (1 - sf) * sg));
}

int Distance_GEO_MEEUS(Node * Na, Node * Nb)
{
    double lat1 =
        M_PI * ((int) Na->X + 5 * (Na->X - (int) Na->X) / 3) / 180;
    double lon1 =
        M_PI * ((int) Na->Y + 5 * (Na->Y - (int) Na->Y) / 3) / 180;
    double lat2 =
        M_PI * ((int) Nb->X + 5 * (Nb->X - (int) Nb->X) / 3) / 180;
    double lon2 =
        M_PI * ((int) Nb->Y + 5 * (Nb->Y - (int) Nb->Y) / 3) / 180;
    return (int) (Meeus(lat1, lon1, lat2, lon2) + 0.5);
}

int Distance_GEOM_MEEUS(Node * Na, Node * Nb)
{
    double lat1 = M_PI * (Na->X / 180);
    double lon1 = M_PI * (Na->Y / 180);
    double lat2 = M_PI * (Nb->X / 180);
    double lon2 = M_PI * (Nb->Y / 180);
    return (int) (1000 * Meeus(lat1, lon1, lat2, lon2) + 0.5);
}

#undef min
#undef max

static double min(double a, double b)
{
    return a < b ? a : b;
}

static double max(double a, double b)
{
    return a > b ? a : b;
}

int Distance_TOR_2D(Node * Na, Node * Nb)
{
    double dx = fabs(Na->X - Nb->X);
    double dy = fabs(Na->Y - Nb->Y);
    dx = min(dx, GridSize - dx);
    dy = min(dy, GridSize - dy);
    return (int) (Scale * sqrt(dx * dx + dy * dy) + 0.5);
}

int Distance_TOR_3D(Node * Na, Node * Nb)
{
    double dx = fabs(Na->X - Nb->X);
    double dy = fabs(Na->Y - Nb->Y);
    double dz = fabs(Na->Z - Nb->Z);
    dx = min(dx, GridSize - dx);
    dy = min(dy, GridSize - dy);
    dz = min(dz, GridSize - dz);
    return (int) (Scale * sqrt(dx * dx + dy * dy + dz * dz) + 0.5);
}

int Distance_XRAY1(Node * Na, Node * Nb)
{
    double distp =
        min(fabs(Na->X - Nb->X), fabs(fabs(Na->X - Nb->X) - 360));
    double distc = fabs(Na->Y - Nb->Y);
    double distt = fabs(Na->Z - Nb->Z);
    double cost = max(distp, max(distc, distt));
    return (int) (100 * cost + 0.5);
}

int Distance_XRAY2(Node * Na, Node * Nb)
{
    double distp =
        min(fabs(Na->X - Nb->X), fabs(fabs(Na->X - Nb->X) - 360));
    double distc = fabs(Na->Y - Nb->Y);
    double distt = fabs(Na->Z - Nb->Z);
    double cost = max(distp / 1.25, max(distc / 1.5, distt / 1.15));
    return (int) (100 * cost + 0.5);
}
