#include <cstdio>




typedef struct Person
{
    int key;
    int age;
} Person_t;

typedef struct List
{
    struct Person people[10];    
} List_t;

void foo(List_t *ll, int key, int age)
{
    void* l2;
    /*void *vv = ll_find(ll, key);*/
    l2 = (void*)ll;
    Person_t *p = static_cast<Person_t*>(l2);
    p->age = age;
}

int main()
{
    List_t l;
    Person_t people[10];

    people[0].age = 10;
    people[0].key = 0;

    l.people[0] = people[0];

    foo(&l, 0, 11);
    printf("%d\n", l.people[0].age);

    return 0;
}

    /*bool b1 = true;
    bool b2;
    int i = b1;
    i = 7;
    b2 = i;
    b2 = b2 << 1;
    printf("%d\n", (int)b2);*/