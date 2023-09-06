#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "compat/sys/queue.h"

static void singly_linked_test(void)
{
    struct student
    {
        SLIST_ENTRY(student) next;
        const char *name;
        int id;
    }   
        students [] =
    {
        {.name = "student6", 6},
        {.name = "student3", 3},
        {.name = "student4", 4},
    };

    struct student s1 = {.name = "student1", .id = 1};
    struct student s2 = {.name = "student2", .id = 2};

    SLIST_HEAD(sdt_slist, student) *head;
    struct student *var = NULL;
    int i;

    head = calloc(1, sizeof(*head));
    SLIST_INIT(head);

    assert(SLIST_EMPTY(head));

    SLIST_FIRST(head) = &students[0];

    for (i = 0; i < 2; i++)
        SLIST_NEXT(students + i, next) = &students[i + 1];
    
    SLIST_INSERT_AFTER(&students[0], &s2, next);

    SLIST_REMOVE_HEAD(head, next);

    SLIST_INSERT_HEAD(head, &s1, next);

    SLIST_FOREACH(var, head, next)
        printf("name : %s, id : %d\n", var->name, var->id);

    free(head);
    printf("[%s] end !!!\n\n", __func__);
    return ;
}

static void list_test(void)
{
    struct student
    {
        LIST_ENTRY(student) next;
        const char *name;
        int id;
    }
        students [] =
    {
        {.name = "student5", 5},
        {.name = "student3", 3},
        {.name = "student4", 4},
    };
    
    struct student s0 = {.name = "student0", .id = 0};
    struct student s1 = {.name = "student1", .id = 1};
    struct student s2 = {.name = "student2", .id = 2};

    struct student *var = NULL;
    int i;
    LIST_HEAD(sdt_list, student) *head;
    head = calloc(1, sizeof(*head));
    LIST_INIT(head);

    LIST_FIRST(head) = &students[0];

    for (i = 0; i < 2; i++)
        LIST_NEXT(students+i, next) = students+i+1;

    LIST_INSERT_AFTER(LIST_FIRST(head), &s1, next);

    LIST_INSERT_BEFORE(students + 1, &s2, next);

    LIST_INSERT_HEAD(head, &s0, next);
    
    LIST_REMOVE(&students[0], next);

    /* todo LIST_REPLACE */

    LIST_FOREACH(var, head, next)
        printf("name : %s, id : %d\n", var->name, var->id);

    free(head);
    printf("[%s] end !!!\n\n", __func__);
    return ;
}

int main(int argc, char **argv)
{
    singly_linked_test();

    list_test();

    return 0;
}