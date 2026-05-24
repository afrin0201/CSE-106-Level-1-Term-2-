#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int element;
    struct node *next; // stores location
    struct node *prev; // stores location
} node;

typedef struct 
{
    // declare head, tail, cur and other variables you need
    node *head;
    node *tail;
    node *cur;
    int size;
} linkedList;

void init(linkedList *list)
{
    // implement initialization
    list->head = NULL;
    list->tail = NULL;
    list->cur = NULL;
    list->size = 0;
}

void free_list(linkedList *list)
{
    // implement destruction of list
    node *temp;
    while (list->head != NULL)
    {
        temp = list->head;
        list->head = list->head->next;
        free(temp);
    }
    list->tail = list->cur = NULL;
    list->size = 0;
}

void print(linkedList *list)
{
    // implement list printing
    if (list->size == 0)
    {
        printf(".\n");
    }
    else
    {
        node *temp = list->head;
        int count = list->size;
        while (temp != NULL)
        {
            if (temp == list->cur)
                printf("%d| ", temp->element);
            else
                printf("%d ", temp->element);
            temp = temp->next;
        }
        printf("\n");
    }
}

void insert(int item, linkedList *list)
{
    // implement insert function
    node *newNode = (node *)malloc(sizeof(node));
    newNode->element = item;
    newNode->next = NULL;
    newNode->prev = NULL;

    if (list->size == 0)
    {
        list->head = list->tail = list->cur = newNode;
    }
    else if (list->tail == list->cur)
    {
        newNode->prev = list->tail;
        list->tail->next = newNode;
        list->tail = newNode;
        list->cur = newNode;
    }
    else
    {
        newNode->next = list->cur->next;
        newNode->prev = list->cur;
        list->cur->next->prev = newNode;
        list->cur->next = newNode;
        list->cur = newNode;
    }
    list->size++;
    print(list);
}

int delete_cur(linkedList *list)
{
    // implement deletion of current index function
    if (list->size == 0)
        return 0;
    else if (list->cur == list->tail)
    {
        int elem = list->tail->element;
        node *del = list->tail;
        list->tail = list->tail->prev;
        list->tail->next = NULL;
        list->cur = list->tail;
        free(del);
        return elem;
    }
    else if (list->cur == list->head)
    {
        int elem = list->head->element;
        node *del = list->head;
        list->head = list->head->next;
        list->cur = list->head;
        free(del);
        return elem;
    }
    else
    {
        int elem = list->cur->element;
        node *del = list->cur;
        list->cur->prev->next = list->cur->next;
        list->cur->next->prev = list->cur->prev;
        list->cur = list->cur->next;
        free(del);
        return elem;
    }
    print(list);
}

void append(int item, linkedList *list)
{
    // implement append function
    node *newNode = (node *)malloc(sizeof(node));
    newNode->element = item;
    newNode->prev = list->tail;
    newNode->next = NULL;
    if (list->size == 0)
    {
        list->head = newNode;

    }
    else
    {
        list->tail->next = newNode;
        list->tail=newNode;
    }
    list->size++;
    print(list);
}

int size(linkedList *list)
{
    // implement size function
    return list->size;
}

void prev(int n, linkedList *list)
{
    // implement prev

    while (n--)
    {
        if (list->cur->prev == NULL)
        {
            break;
        }
        list->cur = list->cur->prev;
    }
    print(list);
}

void next(int n, linkedList *list)
{
    // implement next function
    while (n--)
    {
        if (list->cur->next == NULL)
        {
            break;
        }
        list->cur = list->cur->next;
    }
    print(list);
}

int is_present(int n, linkedList *list)
{
    // implement presence checking function
    node *temp = list->head;
    while (temp != NULL)
    {
        if (temp->element == n)
            return 1;
            temp=temp->next;
    }
    return 0;
}

void clear(linkedList *list)
{
    // implement list clearing function
    free_list(list);
    init(list);
}

void delete_item(int item, linkedList *list)
{
    // implement item deletion function
    node* temp=list->head;
    while(temp!=NULL){
          if (temp->element==item){
             temp->prev->next=temp->next->prev;
             temp->next->prev=temp->prev->next;
             free(temp);
             temp=temp->next;
          }
    }
    print(list);
}

void swap_ind(int ind1, int ind2, linkedList *list)
{
    // implement swap function
    int count=0;
    node* swap1=NULL;
    node* swap2=NULL;
    node*temp=list->head;
    while(temp!=NULL){
       count++;
       if (count==ind1){
        swap1=temp;
       }
       else if (count== ind2){
        swap2=temp;
        
       }
       temp=temp->next;
    }
      int x=swap1->element;
      swap1->element=swap2->element;
      swap2->element=x;
      print(list);

}

// you can define helper functions you need