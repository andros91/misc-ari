
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "item.h"

/*
** Create an item
**
*/
ITEM *item_create(void *data, long size)
{
  ITEM *pl = NULL;

  if ( data && size > 1 ) {
    pl = (ITEM *) calloc(sizeof(ITEM), 1LU);
    if ( pl ) {
      pl->i_data = (void *) calloc(size, 1LU);
      if ( pl->i_data ) {
	memcpy(pl->i_data, data, size);
	pl->i_size = size;
      } else {
	free(pl);
	pl = NULL;
      }
    }
  }

  return pl;
}

/*
** Delete an item, or a list of items
**
*/
long item_delete(ITEM *pl)
{
  long count = 0;
  
  if ( pl ) {
    count = 1 + item_delete(pl->i_next);
    if ( pl->i_data )
      free(pl->i_data);
    /*
    ** just for safety, all the members are set to 0
    */
    pl->i_data = NULL;
    pl->i_size = 0;
    pl->i_next = NULL;

    free(pl);
  }

  return count;
}

