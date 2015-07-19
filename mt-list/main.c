//
//  main.c
//  List
//
//  Created by André on 26/04/2014.
//  Copyright (c) 2014 André. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "list.h"

LIST *list = NULL;

static void *prod(void *);
static void *cons(void *);

int main(int ac, char *av[]) {
  pthread_t *t1, *t2;

  srandom((unsigned)time(0));

  t1 = (pthread_t *)calloc(sizeof(pthread_t), 1LU);
  t2 = (pthread_t *)calloc(sizeof(pthread_t), 1LU);

  list = list_create();

  pthread_create(t1, NULL, prod, NULL);
  pthread_create(t2, NULL, cons, NULL);

  pthread_join(*t2, NULL);
  pthread_join(*t1, NULL);

  list_delete(list);

  fprintf(stderr, "END\n");
  return 0;
}

static void *prod(void *a) {
  long i;

  for ( i = 1; i <= 20000; ++i ) {
    list_append(list, (void *)&i, sizeof(i));
      printf("app i=[%ld] count=[%ld]\n", i, list_count(list));
  }

  return NULL;
}

static void *cons(void *a) {
  long d, dlen = sizeof(d);
  long rval;
long i = 0;
  while ( 1 ) {
    dlen = sizeof(d);
    rval = list_gethead(list, (void *)&d, &dlen);
    if ( ! rval )
      printf("get d=[%ld] dlen=[%ld] count=[%ld]\n", d, dlen, list_count(list));
    else {
      printf("--- empty ---\n");
      break;
    }
    if ( ++i % 13 == 0 )
      usleep(random()%1000000);	
  }

  return NULL;
}
