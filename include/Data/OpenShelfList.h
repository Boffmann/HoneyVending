#ifndef _HV_OPEN_SHELF_LIST_H_
#define _HV_OPEN_SHELF_LIST_H_

#include <stdint.h>

class Shelf;

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

class OpenShelfList {

public:
    OpenShelfList();

    bool insert(Shelf&);

    /**
     * Removes all occurences of the value
     */
    void remove(const Shelf&);

    //void reset(void);

    void print(void) const;

    const node_t* get_first() const;
    const node_t* get_next(const node_t*) const;
    Shelf& get_shelf(const node_t*) const;

private:
    node_t *_head;
    node_t *_tail;

    node_t _sixt;
    node_t _fifth;
    node_t _fourth;
    node_t _third;
    node_t _second;
    node_t _first;
};

#endif
