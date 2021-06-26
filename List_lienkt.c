#include "Status.h"
#include "List.h"

prFun pr;

List * newList (compFun comp, prFun pr) {
    List * l = (List *)malloc(sizeof(List));
    if(!l) return 0;

    l->nelts = 0;
    l->head = 0;
    l->comp = comp;
    l->pr = pr;

    return l;
}

void delList (List* l){
    free(l);
}

status nthInList (List* l, int n, void* res) {
    if(l->nelts <= 0 || l->nelts < n+1 ) return ERRINDEX;

    Node * tmp = l->head;

    for (int i = 0; i < n; i++) {
        tmp = tmp->next; 
    }
    *(void**)res = tmp->val;

    return OK;
}

status addListAt (List* l, int n, void* e) {
    if(l->nelts <= 0 || l->nelts < n ) return ERRINDEX;

    Node * tmp = l->head;

    if (n == 0) {
        l->head->val = e;
        l->head->next = tmp;
    } else {
        for (int i = 1; i < n; i++) {
            tmp = tmp->next; 
        }
        Node * newNode;
        newNode->val = e;
        newNode->next = tmp->next;
        tmp->next = newNode;
    }

    return OK;
}

status remFromListAt (List* l, int n, void* res) {
    if(l->nelts <= 2 || l->nelts < n+1 ) return ERRINDEX;

    Node * tmp = l->head;

    if (n == 0) {
        *(void**)res = l->head->val;
        l->head->val = tmp->val;
        l->head->next = tmp->next;
    } else {
        for (int i = 1; i < n; i++) {
            tmp = tmp->next; 
        }
        *(void**)res = tmp->next->val;
        Node * tmp2 = tmp->next->next;
        tmp->next = tmp2;
    }

    return OK;
}

status remFromList (List* l, void* e) {
    if(l->nelts <= 2) return ERRINDEX;

    Node * tmp = l->head;

    if (l->head->val == e) {
        l->head = tmp->next;
    } else {
        for (int i = 1; tmp->next->val != e; i++) {
            tmp = tmp->next; 
        }
        Node * tmp2 = tmp->next->next;
        tmp->next = tmp2;
    }
    
    return OK;
}

status 	displayList	(List* l) {
    Node * tmp = l->head;
    for (int i = 1; i < l->nelts ; i++) {
        printf(" %d: ", tmp->val);
        tmp = tmp->next; 
    }
}

void forEach (List* l,void(*f)(void*)) {

}

int	lengthList	(List* l) {
    return l->nelts;
}

status	addList	(List* l, void* e) {
    if(l->nelts <= 0) return ERRINDEX;

    Node * tmp = l->head;

    for (int i = 1; i < l->nelts; i++) {
        tmp = tmp->next; 
    }
    Node * newNode;
    newNode->val = e;
    newNode->next = NULL;
    tmp->next = newNode;

    return OK;
}

Node* isInList (List* l, void* e) {
    if(l->nelts <= 2) return ERRINDEX;

    Node * tmp = l->head;

    for (int i = 1; i < l->nelts; i++) {
        if (tmp->val == e) {
            return 1;
        }
        tmp = tmp->next; 
    }

    return 0;
}

void* firstThat (List* l, int(*f)(void*));

List* allThat (List* l, int(*f)(void*));