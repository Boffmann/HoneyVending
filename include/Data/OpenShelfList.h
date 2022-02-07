#ifndef _SHELF_LIST_H_
#define _SHELF_LIST_H_

#include <stdint.h>

typedef struct node node_t;
class Shelf;

class OpenShelfList {

public:
    OpenShelfList();

    const bool insert(Shelf&);

    /**
     * Removes all occurences of the value
     */
    void remove(const Shelf&);

    const node_t* get_first() const;
    const node_t* get_next(const node_t&) const;
    Shelf& get_shelf(const node_t&) const;

private:
    node_t *_head;
    node_t *_tail;
};



#endif