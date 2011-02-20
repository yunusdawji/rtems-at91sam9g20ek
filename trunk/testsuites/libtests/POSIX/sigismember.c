/*
 * Copyright (c) 2009 by
 * Ralf Corsépius, Ulm, Germany. All rights reserved.
 *
 * Permission to use, copy, modify, and distribute this software
 * is freely granted, provided that this notice is preserved.
 */

#include <signal.h>

int
main (void)
{
  sigset_t set;
  int status;
  status = sigismember(&set, 21);

  return status;
}
