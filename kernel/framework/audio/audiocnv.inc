/*
 * Purpose: Helper functions used by audiofmt.c
 */
#define COPYING3 Copyright (C) Hannu Savolainen and Dev Mazumdar 1996-2005. All rights reserved.

/*ARGSUSED*/
static int
cnv_F8bits_T16bits (adev_p adev, dmap_p dmap, void **srcp, int *srcl,
		    void **tgtp, sample_parms * source, sample_parms * target)
{
  unsigned char *p1 = *srcp;
  short *p2 = *tgtp;
  int len = *srcl;
  int i, l;

  VMEM_CHECK (p1, len);
  VMEM_CHECK (p2, len * 2 / 1);

  l = len / 1;
  for (i = 0; i < l; i++)
    p2[i] = ((int) p1[i] - 128) << 8;

  *srcl = len * 2 / 1;
  *srcp = p2;
  *tgtp = p1;

  return 0;
}

/*ARGSUSED*/
static int
cnv_F8bits_T32bits (adev_p adev, dmap_p dmap, void **srcp, int *srcl,
		    void **tgtp, sample_parms * source, sample_parms * target)
{
  unsigned char *p1 = *srcp;
  int *p2 = *tgtp;
  int len = *srcl;
  int i, l;

  VMEM_CHECK (p1, len);
  VMEM_CHECK (p2, len * 4 / 1);

  l = len / 1;
  for (i = 0; i < l; i++)
    p2[i] = ((int) p1[i] - 128) << 24;

  *srcl = len * 4 / 1;
  *srcp = p2;
  *tgtp = p1;

  return 0;
}

/*ARGSUSED*/
static int
cnv_F16bits_T8bits (adev_p adev, dmap_p dmap, void **srcp, int *srcl,
		    void **tgtp, sample_parms * source, sample_parms * target)
{
  short *p1 = *srcp;
  unsigned char *p2 = *tgtp;
  int len = *srcl;
  int i, l;

  VMEM_CHECK (p1, len);
  VMEM_CHECK (p2, len * 1 / 2);

  l = len / 2;
  for (i = 0; i < l; i++)
    p2[i] = (((int) p1[i]) >> 8) + 128;

  *srcl = len * 1 / 2;
  *srcp = p2;
  *tgtp = p1;

  return 0;
}

/*ARGSUSED*/
static int
cnv_F16bits_T32bits (adev_p adev, dmap_p dmap, void **srcp, int *srcl,
		     void **tgtp, sample_parms * source,
		     sample_parms * target)
{
  short *p1 = *srcp;
  int *p2 = *tgtp;
  int len = *srcl;
  int i, l;

  VMEM_CHECK (p1, len);
  VMEM_CHECK (p2, len * 4 / 2);

  l = len / 2;
  for (i = 0; i < l; i++)
    p2[i] = ((int) p1[i]) << 16;

  *srcl = len * 4 / 2;
  *srcp = p2;
  *tgtp = p1;

  return 0;
}

/*ARGSUSED*/
static int
cnv_F32bits_T8bits (adev_p adev, dmap_p dmap, void **srcp, int *srcl,
		    void **tgtp, sample_parms * source, sample_parms * target)
{
  int *p1 = *srcp;
  unsigned char *p2 = *tgtp;
  int len = *srcl;
  int i, l;

  VMEM_CHECK (p1, len);
  VMEM_CHECK (p2, len * 1 / 4);

  l = len / 4;
  for (i = 0; i < l; i++)
    p2[i] = (((int) p1[i]) >> 24) + 128;

  *srcl = len * 1 / 4;
  *srcp = p2;
  *tgtp = p1;

  return 0;
}

/*ARGSUSED*/
static int
cnv_F32bits_T16bits (adev_p adev, dmap_p dmap, void **srcp, int *srcl,
		     void **tgtp, sample_parms * source,
		     sample_parms * target)
{
  int *p1 = *srcp;
  short *p2 = *tgtp;
  int len = *srcl;
  int i, l;

  VMEM_CHECK (p1, len);
  VMEM_CHECK (p2, len * 2 / 4);

  l = len / 4;
  for (i = 0; i < l; i++)
    p2[i] = (((int) p1[i]) >> 16);

  *srcl = len * 2 / 4;
  *srcp = p2;
  *tgtp = p1;

  return 0;
}