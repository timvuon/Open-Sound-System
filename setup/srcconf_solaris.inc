#define COPYING2 Copyright (C) Hannu Savolainen and Dev Mazumdar 2000-2006. All rights reserved.

/*#define USE_GCC*/
#define HAVE_SYSDEP
#include <sys/systeminfo.h>
static void
check_sysdep (conf_t * conf, struct utsname *un)
{
  char tmp[64];

  conf->flags |= F_USEARCH;
#ifdef USE_GCC
  strcpy (conf->ccomp, "gcc -Wall -O");
#endif
  strcpy (conf->cplusplus,
	  "CC -DNO_BUILTINS -I. -features=no%except -xvector=no");

  if (sysinfo (SI_ARCHITECTURE, tmp, sizeof (tmp)) == -1)
    {
      perror ("sysinfo SI_ARCHITECTURE");
      exit (-1);
    }
  printf ("Arch: %s\n", tmp);

  if (getenv ("SOL9") != NULL)
    strcat (conf->OSflags, "-DSOL9 ");

  if (*arch)
    strcpy (tmp, arch);
  printf ("Arch K: %s\n", tmp);
  strcpy (conf->arch, tmp);

#ifdef USE_GCC
  if (strcmp (tmp, "amd64") == 0)
    {
      strcpy (conf->OSflags, "-m64 -fno-common  -mcmodel=kernel -mno-red-zone");
      strcpy (conf->platform, "i86pc");
    }
  else if (strcmp (tmp, "sparcv9") == 0)
    {
      strcpy (conf->OSflags, "-m64");
      strcpy (conf->platform, "sparc");
    }
  else if (strcmp (tmp, "sparc") == 0)
    {
      strcpy (conf->OSflags, "-Dsparc32");
      strcpy (conf->platform, "sparc");
    }
  else if (strcmp (tmp, "i386") == 0)
    {
      strcpy (conf->OSflags, "-m32");
      strcpy (conf->platform, "i86pc");
    }
  else
    {
      strcpy (conf->OSflags, "-xarch=$(ARCH)");
      fprintf (stderr, "Cannot determine platform for '%s'\n", tmp);
      exit (-1);
    }
#else
  if (strcmp (tmp, "amd64") == 0)
    {
      strcpy (conf->OSflags, "-xarch=$(ARCH) -xmodel=kernel");
      strcpy (conf->platform, "i86pc");
    }
  else if (strcmp (tmp, "sparcv9") == 0)
    {
      strcpy (conf->OSflags, "-xarch=v9 -dalign");
      strcpy (conf->platform, "sparc");
    }
  else if (strcmp (tmp, "sparc") == 0)
    {
      strcpy (conf->OSflags, "-Dsparc32");
      strcpy (conf->platform, "sparc");
    }
  else if (strcmp (tmp, "i386") == 0)
    {
      strcpy (conf->OSflags, "-xarch=386");
      strcpy (conf->platform, "i86pc");
    }
  else
    {
      strcpy (conf->OSflags, "-xarch=$(ARCH)");
      fprintf (stderr, "Cannot determine platform for '%s'\n", tmp);
      exit (-1);
    }
#endif

  if (getenv ("SOL9") != NULL)
    strcat (conf->OSflags, " -DSOL9");
}