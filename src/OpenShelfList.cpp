#include "Data/OpenShelfList.h"

#include <stdlib.h>

#include "Data/Shelf.h"

typedef struct node {
   Shelf* shelf;
   struct node *next;
   struct node *potential_next;

   node(struct node* pot_next) {
       shelf = nullptr;
       next = nullptr;
       potential_next = pot_next;
   }
} node_t;

node_t sixt(nullptr);
node_t fifth(&sixt);
node_t fourth(&fifth);
node_t third(&fourth);
node_t second(&third);
node_t first(&second);

OpenShelfList::OpenShelfList()
: _head{nullptr}, _tail{nullptr} 
{}

const bool OpenShelfList::insert(Shelf &shelf) {

    if (this->_head == nullptr) {
        first.shelf = &shelf;
        this->_head = &first;
        this->_tail = &first;
        return true;
    }
    if (this->_tail->potential_next == nullptr) {
        return false;
    }
    this->_tail->next = this->_tail->potential_next;
    this->_tail = this->_tail->potential_next;
    this->_tail->shelf = &shelf;
    return true; 
}

void OpenShelfList::remove(const Shelf &shelf) {
    node_t *current = this->_head;

    while (current->next != nullptr) {
        if (current->next->shelf == &shelf) {
            current->next = current->next->next;
        }
        current = current->next;
    }

    // Current head might still containt shelf
    if (this->_head->shelf == &shelf) {
       this->_head = this->_head->next; 
    }
}

const node_t* OpenShelfList::get_first() const {
    return this->_head;
}

const node_t* OpenShelfList::get_next(const node_t &node) const {
    return node.next;
}

Shelf& OpenShelfList::get_shelf(const node_t &node) const {
    return *node.shelf;
}