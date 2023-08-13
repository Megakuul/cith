#include <cith.h>

#define ALLOC_PERR "Failed to allocate new element"

cres poolinit(cpool &c, int size) {
  cres res = {NULL};
  
  c->poolsize = size;
  c->nextpool = NULL;
  vecinit(&c->free_list);
  
  void *data = malloc(c->poolsize);
  if (!data) {
    res.e = ALLOC_PERR;
    return res;
  }

  c->data = data;

  cblock initialblock = {c->poolsize, data};
  return vecpush(&c->free_list, &initialblock, sizeof(initialblock));
}

cres_void_ptr poolalloc(cpool &c, int size) {

}

cres_void_ptr poolrealloc(cpool &c, void* ptr, int size) {

}

void poolfree(cpool &c, void* element) {

}

void pooldestroy(cpool &c) {

}
