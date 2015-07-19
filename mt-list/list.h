
#ifndef __LIST_H__
#define __LIST_H__

#include <pthread.h>

#include "item.h"

typedef struct list_t LIST;

struct list_t {
  pthread_mutex_t *l_lock;
  ITEM            *l_head;			/* head list pointer */
  ITEM            *l_tail;			/* tail list pointer */
  long             l_count;		/* number of elements */
};

extern LIST *list_create(void);
extern long  list_insert(LIST *list, void *data, long len); /* add at head */
extern long  list_append(LIST *list, void *data, long len); /* add at tail */
extern long  list_gethead(LIST *list, void *data, long *dlen); /* get first */
extern long  list_delete(LIST *list); /* delete all the list */
extern void  list_dump(LIST *list);
extern long  list_count(LIST *list);

#endif

