#include <cith.h>

#define ALLOC_PERR "Failed to allocate new element"

cres poolinit(cpool *c, int size) {
  cres res = {NULL};
  
  c->poolsize = size;
  c->nextpool = NULL;
  vecinit(&c->blockmap);
  
  void *data = malloc(c->poolsize);
  if (!data) {
    res.e = ALLOC_PERR;
    return res;
  }

  c->data = data;

  cblock initialblock = {true, c->poolsize, data};
  return vecpush(&c->blockmap, &initialblock, sizeof(initialblock));
}

cres_void_ptr poolalloc(cpool *c, int size) {
  cres_void_ptr res = {NULL, NULL};

  cblock *curblock;
  int i;

  for (i = 0; i<c->blockmap.size; i++) {
    curblock = (cblock*)vecget(&c->blockmap, i).r;
    curblock = curblock->free && curblock->size >= size ?
      curblock : NULL;

    if (curblock!=NULL) break;
  }
  
  if (!curblock) {
    printf("There is a need for a new pool currentblocks: %zu\n", c->blockmap.size);
    return res;
  }

  cblock thisblock = (cblock){false, size, curblock->ptr};
  vecpush(&c->blockmap, &thisblock, sizeof(thisblock));

  cblock nextblock = (cblock){true, curblock->size-size, thisblock.ptr+size};
  vecpush(&c->blockmap, &nextblock, sizeof(nextblock));

  vecdel(&c->blockmap, i);

  res = (cres_void_ptr){NULL, thisblock.ptr};
  return res;
}

cres_void_ptr poolrealloc(cpool *c, void* ptr, int size) {

}

void poolfree(cpool *c, void* element) {

}

void pooldestroy(cpool *c) {

}
