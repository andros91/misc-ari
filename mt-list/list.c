
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

/*
** create the root structure of the list
**
*/
LIST *list_create(void)
{
  LIST *pl = NULL;

  pl = (LIST *) calloc(sizeof(LIST), 1LU);
  if ( pl ) {
    pl->l_lock = (pthread_mutex_t *) calloc(sizeof(pthread_mutex_t), 1LU);
    if ( pl->l_lock ) {
      if ( pthread_mutex_init(pl->l_lock, NULL) != 0 ) {
	free(pl->l_lock);
	free(pl);
      }
    } else
      free(pl);
  }

  return pl;
}

/*
** recursively delete all the list
**
*/
long list_delete(LIST *list)
{
  long cnt = 0L;

  if ( list ) {
    pthread_mutex_destroy(list->l_lock);
    cnt = item_delete(list->l_head);
    free(list->l_lock);
    list->l_lock = NULL;
    list->l_head = list->l_tail = NULL;
    list->l_count = 0;
    free(list);
  }
  
  return cnt;
}

/*
** insert data at head of list
** return -1 if error, or elements count
*/
long list_insert(LIST *list, void *data, long len)
{
  long rval = -1L;
  
  if ( list ) {
    pthread_mutex_lock(list->l_lock);
    if ( data && len > 0 ) {
      ITEM *pit = item_create(data, len);
      if ( pit ) {
	pit->i_next = list->l_head;
	if ( ! list->l_tail )	/* single item is pointed to by head and tail */
	  list->l_tail = pit;
	list->l_head = pit;
	list->l_count++;	/* increment the item count */
	rval = list->l_count;
      }
    }
    pthread_mutex_unlock(list->l_lock);
  }

  return rval;
}

/*
** insert data at tail of the list
** return -1 if error, or elements count
*/
long list_append(LIST *list, void *data, long len)
{
  long rval = -1L;
  
  if ( list ) {
    pthread_mutex_lock(list->l_lock);
    if ( data && len > 0 ) {
      ITEM *pit = item_create(data, len);
      if ( pit ) {
	if ( list->l_tail )
	  list->l_tail->i_next = pit;
	list->l_tail = pit;
	if ( ! list->l_head )	/* single item is pointed to by head and tail */
	  list->l_head = pit;
	list->l_count++;	/* increment the item count */
	rval = list->l_count;
      }
    }
    pthread_mutex_unlock(list->l_lock);
  }

  return rval;
}

/*
** get the head of list
**
*/
long  list_gethead(LIST *list, void *data, long *dlen)
{
  long rval = -1L;
  
  if ( data && dlen && *dlen > 0 ) {
    if ( list ) {
      pthread_mutex_lock(list->l_lock);
      if ( list->l_head && list->l_head->i_data && list->l_head->i_size <= *dlen ) {
	ITEM *pi = list->l_head;
	memcpy(data, pi->i_data, pi->i_size);
	*dlen = pi->i_size;
	if ( list->l_head != list->l_tail ) /* more than 1 items */
	  list->l_head = pi->i_next;
	else			/* single item */
	  list->l_head = list->l_tail = NULL;

	pi->i_next = NULL;
	item_delete(pi);
	
	list->l_count--;
	rval = 	0L;
      }
      pthread_mutex_unlock(list->l_lock);
    }
  }

  return rval;
}

/*
** return the number of item in the list
** return -1 if error
**
*/
long list_count(LIST *list)
{
  long cnt = -1L;

  if ( list ) {
    pthread_mutex_lock(list->l_lock);
    cnt = list->l_count;
    pthread_mutex_unlock(list->l_lock);
  }

  return cnt;
}

/*
**
**
*/
void list_dump(LIST *list)
{
  if ( list ) {
    ITEM *p = NULL;
    long cnt = 0L;

    pthread_mutex_lock(list->l_lock);
    fprintf(stderr, "dumping [%ld] elements\n", list->l_count);
    for ( p = list->l_head; p ; p = p->i_next ) {
      fprintf(stderr, "%6ld [%.*s] %6ld bytes\n",
	      ++cnt, (int)p->i_size, (char *)p->i_data, p->i_size);
    }
    pthread_mutex_unlock(list->l_lock);
  }
}
