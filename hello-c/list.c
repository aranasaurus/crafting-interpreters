#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct node {
  struct node *prev;
  struct node *next;
  char *data;
};
typedef struct node Node;

typedef struct {
  Node *first;
  Node *last;
} List;

void insertBefore(List *list, Node *second, Node *first) {
  first->prev = second->prev;
  first->next = second;
  if (first->prev == NULL) {
    list->first = first;
  } else {
    first->prev->next = first;
  }
  second->prev = first;
}

void insertAfter(List *list, Node *first, Node *second) {
  second->prev = first;
  second->next = first->next;
  if (second->next == NULL) {
    list->last = second;
  } else {
    second->next->prev = second;
  }
  first->next = second;
}

void insertFirst(List *list, Node *item) {
  if (list->first != NULL) {
    insertBefore(list, list->first, item);
    return;
  }
  list->first = item;
  list->last = item;
}

void insertLast(List *list, Node *item) {
  if (list->last != NULL) {
    insertAfter(list, list->last, item);
    return;
  }
  list->first = item;
  list->last = item;
}

int removeItem(List *list, Node *toBeRemoved) {
  if (toBeRemoved == list->first) {
    if (list->first == list->last) {
      list->first = NULL;
      list->last = NULL;
    } else {
      list->first = toBeRemoved->next;
      list->first->prev = NULL;
      toBeRemoved->next = NULL;
    }
    return 1;
  }

  if (toBeRemoved == list->last) {
    list->last = toBeRemoved->prev;
    list->last->next = NULL;
    toBeRemoved->prev = NULL;
    return 1;
  }

  Node *item = list->first;
  while (item != NULL) {
    if (item == toBeRemoved) {
      item->prev->next = item->next;
      item->next->prev = item->prev;
      item->next = NULL;
      item->prev = NULL;
      return 1;
    }
    item = item->next;
  }
  return 0;
}

int isInList(List *list, char *value) {
  Node *item = list->first;
  while (item != NULL) {
    if (strcmp(value, item->data) == 0) {
      return 1;
    }
    item = item->next;
  }
  return 0;
}

List *createList() {
  List *list = malloc(sizeof(List));
  list->first = NULL;
  list->last = NULL;
  return list;
}

Node *createItem(char *data) {
  Node *item = malloc(sizeof(Node));
  item->prev = NULL;
  item->next = NULL;
  item->data = strdup(data);
  return item;
}

int main() {
  List *list = createList();
  Node *item = createItem("original");

  insertFirst(list, item);
  insertAfter(list, item, createItem("after"));
  insertBefore(list, item, createItem("before"));
  insertFirst(list, createItem("first"));
  insertLast(list, createItem("last"));

  Node *temp = list->first;
  while (temp != NULL) {
    printf("%s\n", temp->data);
    temp = temp->next;
  }

  printf("'poop' %s in list\n", isInList(list, "poop") == 1 ? "is" : "isn't");
  printf("'original' %s in list\n", isInList(list, "original") == 1 ? "is" : "isn't");
  int removed = removeItem(list, item);
  printf("Removed: %i\n", removed);
  printf("'%s' %s in list\n", item->data, isInList(list, item->data) == 1 ? "is" : "isn't");
  return 0;
}

