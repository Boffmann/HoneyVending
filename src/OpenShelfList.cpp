#include "Data/OpenShelfList.h"

#include <stdlib.h>

#include "Data/Shelf.h"

OpenShelfList::OpenShelfList()
:   _head{nullptr},
    _tail{nullptr},
    _sixt{nullptr},
    _fifth{&_sixt},
    _fourth{&_fifth},
    _third{&_fourth},
    _second{&_third},
    _first{&_second}
{}

bool OpenShelfList::insert(Shelf &shelf) {
    node_t *current = this->_head;

    if (this->_head == nullptr) {
        this->_first.shelf = &shelf;
        this->_head = &this->_first;
        this->_tail = &this->_first;
        return true;
    }
    if (this->_tail->potential_next == nullptr) {
        return false;
    }

    while (current != nullptr) {
        if (*(current->shelf) == shelf) {
            return false;
        }
        current = current->next;
    }

    this->_tail->next = this->_tail->potential_next;
    this->_tail = this->_tail->potential_next;
    this->_tail->shelf = &shelf;
    return true; 
}

void OpenShelfList::remove(const Shelf &shelf) {
    node_t *current = this->_head;

    if (current == nullptr) {
        return;
    }

    while (current->next != nullptr) {
        if (*(current->next->shelf) == shelf) {
            current->next = current->next->next;
            // if the removed element was the last one, set tail
            if (current->next == nullptr) {
                this->_tail = current;
                break;
            }
        }
        current = current->next;
    }

    // Current head might still containt shelf
    if (this->_head->shelf == &shelf) {
       this->_head = this->_head->next; 
    }
}

/*void OpenShelfList::reset(void) {
    _head = nullptr;
    _tail = nullptr;
    _sixt.next = nullptr;
    _fifth.next = nullptr;
    _fourth.next = nullptr;
    _third.next = nullptr;
    _second.next = nullptr;
    _first.next = nullptr;
}*/

void OpenShelfList::print(void) const {
    const node_t *current = this->_head;
    printf("-------\n");

    if (current == nullptr) {
        printf("EMPTY\n");
        printf("-------\n");
        return;
    }

    while (current != nullptr) {
        printf("Contains Shelf %d\n", current->shelf->get_id());
        current = current->next;
    }
    printf("-------\n");
}

const node_t* OpenShelfList::get_first() const {
    return this->_head;
}

const node_t* OpenShelfList::get_next(const node_t *node) const {
    return node->next;
}

Shelf& OpenShelfList::get_shelf(const node_t *node) const {
    return *node->shelf;
}