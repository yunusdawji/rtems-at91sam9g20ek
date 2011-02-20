/*
 * Copyright (c) 2009 by
 * Ralf Corsépius, Ulm, Germany. All rights reserved.
 *
 * Permission to use, copy, modify, and distribute this software
 * is freely granted, provided that this notice is preserved.
 */

#include <sys/uio.h>

int
main (void)
{
  struct iovec iov;
  int count = 4;
  ssize_t ret;

  ret = writev (0, &iov, count);

  return ret;
}
