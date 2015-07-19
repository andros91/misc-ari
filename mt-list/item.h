
#ifndef __ITEM_H__
#define __ITEM_H__

typedef struct item_t ITEM;

struct item_t {
  ITEM *i_next;
  void *i_data;
  long  i_size;
};

extern ITEM *item_create(void *d, long sz);
extern long  item_delete(ITEM *item);

#endif

