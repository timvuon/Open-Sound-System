#define COPYING Copyright (C) 4Front Technologies 2007. All rights reserved.
/* Codec index is 0 */
/* Codec vendor 11d4:1988 */
/* HD codec revision 1.0 (4.0) (0x00100400) */
/* Subsystem ID 104381e1 */
/* Default amplifier caps: in=80000000, out=00052727 */
#include "hdaudio_cfg.h"
#include "hdaudio.h"
#include "hdaudio_codec.h"
#include "hdaudio_dedicated.h"

int
hdaudio_Asus_P4B_E_mixer_init (int dev, hdaudio_mixer_t * mixer, int cad,
			       int top_group)
{
  int wid;
  int ctl = 0;
  codec_t *codec = mixer->codecs[cad];

  DDB (cmn_err (CE_CONT, "hdaudio_Asus_P4B_E_mixer_init got called.\n"));

  HDA_OUTAMP (0x04, top_group, "front", 90);
  HDA_OUTAMP (0x0a, top_group, "side", 90);
  HDA_OUTAMP (0x05, top_group, "center/LFE", 90);
  HDA_OUTAMP (0x06, top_group, "rear", 90);
  HDA_OUTAMP (0x03, top_group, "headphone", 90);
  HDA_OUTAMP (0x21, top_group, "input-mix", 90);
  HDA_OUTAMP (0x10, top_group, "pcbeep", 90);

  /* Handle misc widgets */
  {
    int n, group, misc_group;

    n = 0;

    HDA_GROUP (group, top_group, "input-mix");

    //if (HDA_MISC_GROUP(0x20, group, misc_group, "input-mix", n, "misc", 4))       /* Misc widget 0x20 */
    {
      /* Src 0x39=fppink-micboost */
      /* Src 0x33=blue-insel */
      /* Src 0x38=fpgreen-micboost */
      /* Src 0x3d=green-micboost */
      /* Src 0x34=pink-insel */
      /* Src 0x3b=black-micboost */
      /* Src 0x18=cd */
      /* Src 0x1a=beep */
      HDA_INAMP (0x20, 0, group, "fp-pink", 90);	/* From widget 0x39 */
      HDA_INAMP (0x20, 1, group, "blue", 90);	/* From widget 0x33 */
      HDA_INAMP (0x20, 2, group, "fp-green", 90);	/* From widget 0x38 */
      HDA_INAMP (0x20, 3, group, "green", 90);	/* From widget 0x3d */
      HDA_INAMP (0x20, 4, group, "pink", 90);	/* From widget 0x34 */
      HDA_INAMP (0x20, 5, group, "black", 90);	/* From widget 0x3b */
      HDA_INAMP (0x20, 6, group, "cd", 90);	/* From widget 0x18 */
      HDA_INAMP (0x20, 7, group, "pcbeep", 90);	/* From widget 0x1a */

#if 0
      // This seems to be unnecessary selector
      /* Widget 0x33 (blue-insel) */
      /* Src 0x3a=blue-micboost */
      /* Src 0x25=grey */
      /* Src 0x24=orange */
      if (HDA_SELECT (0x33, "src", ctl, group, -1))
	{
	  HDA_CHOICES (ctl, "blue grey orange");
	}
#endif

#if 0
      // This seems to be unnecessary selector
      /* Widget 0x34 (pink-insel) */
      /* Src 0x3c=pink-micboost */
      /* Src 0x25=grey */
      /* Src 0x24=orange */
      if (HDA_SELECT (0x34, "src", ctl, group, -1))
	{
	  HDA_CHOICES (ctl, "pink grey orange");
	}
#endif
    }
  }
  /* Handle ADC widgets */
  {
    int n, group, rec_group;

    n = 0;

    HDA_GROUP (rec_group, top_group, "record");

#if 0
    if (HDA_ADC_GROUP (0x07, group, rec_group, "spdin", n, "record", 4))	/* ADC widget 0x07 */
      {
	/* Src 0x1c=spdif-in */
      }
#endif

    if (HDA_ADC_GROUP (0x08, group, rec_group, "rec1", n, "record", 4))	/* ADC widget 0x08 */
      {
	/* Src 0xc=rec1-src */

	/* Widget 0x0c (rec1-src) */
	/* Src 0x38=fpgreen-micboost */
	/* Src 0xbc= (0x3c=porte-boost?) */
	/* Src 0x18=int-black */
	/* Src 0x24=orange */
	/* Src 0x25=grey */
	/* Src 0x3d=green-micboost */
	/* Src 0x20=input-mix */
	if (HDA_SELECT (0x0c, "src", ctl, group, -1))
	  {
	    HDA_CHOICES (ctl, "fp-green pink cd orange grey green input-mix");
	  }
	HDA_OUTAMP (0x0c, group, "-", 90);
      }

    if (HDA_ADC_GROUP (0x09, group, rec_group, "rec2", n, "record", 4))	/* ADC widget 0x09 */
      {
	/* Src 0xd=rec2-src */

	/* Widget 0x0d (rec2-src) */
	/* Src 0x38=fpgreen-micboost */
	/* Src 0xbc= (0x3c=porte-boost?) */
	/* Src 0x18=int-black */
	/* Src 0x24=orange */
	/* Src 0x25=grey */
	/* Src 0x3d=green-micboost */
	/* Src 0x20=input-mix */
	if (HDA_SELECT (0x0d, "src", ctl, group, -1))
	  {
	    HDA_CHOICES (ctl, "fp-green pink cd orange grey green input-mix");
	  }
	HDA_OUTAMP (0x0d, group, "-", 90);
      }

    if (HDA_ADC_GROUP (0x0f, group, rec_group, "rec3", n, "record", 4))	/* ADC widget 0x0f */
      {
	/* Src 0xe=rec3-src */

	/* Widget 0x0e (rec3-src) */
	/* Src 0x38=fpgreen-micboost */
	/* Src 0xbc= (0x3c=porte-boost?) */
	/* Src 0x18=int-black */
	/* Src 0x24=orange */
	/* Src 0x25=grey */
	/* Src 0x3d=green-micboost */
	/* Src 0x20=input-mix */
	if (HDA_SELECT (0x0e, "src", ctl, group, -1))
	  {
	    HDA_CHOICES (ctl, "fp-green pink cd orange grey green input-mix");
	  }
	HDA_OUTAMP (0x0e, group, "-", 90);
      }
  }

  /* Handle PIN widgets */
  {
    int n, group, pin_group;

    n = 0;

    HDA_GROUP (pin_group, top_group, "connector");

    if (HDA_PIN_GROUP (0x11, group, pin_group, "fp-green", n, "connector", 4))	/* Pin widget 0x11 */
      {
	/* Src 0x22=headphon-mix */
	if (HDA_PINSELECT (0x11, ctl, group, "mode", -1))
	  HDA_CHOICES (ctl, "headphone-out input");
	HDA_OUTMUTE (0x11, group, "inmute", UNMUTE);

	/* Widget 0x22 (headphon-mix) */
	/* Src 0x37=fpgreen-outsel */
	/* Src 0x21=input-mix */
	{
	  int amp_group;

	  HDA_GROUP (amp_group, group, "mute");
	  HDA_INMUTE (0x22, 0, amp_group, "headphone", UNMUTE);	/* From widget 0x37 */
	  HDA_INMUTE (0x22, 1, amp_group, "input-mix", UNMUTE);	/* From widget 0x21 */
	}
	/* Widget 0x38 (fpgreen-micboost) */
	/* Src 0x11=fp-green */
	HDA_OUTAMP (0x38, group, "micboost", 90);
      }

    if (HDA_PIN_GROUP (0x14, group, pin_group, "fp-pink", n, "connector", 4))	/* Pin widget 0x14 */
      {
	/* Src 0x2b=fp-mic-mix */
	if (HDA_PINSELECT (0x14, ctl, group, "mode", -1))
	  HDA_CHOICES (ctl, "headphone-out input");
	HDA_OUTMUTE (0x14, group, "inmute", UNMUTE);

	/* Widget 0x2b (fp-mic-mix) */
	/* Src 0x30=fppink-outsel */
	/* Src 0x21=input-mix */
	{
	  int amp_group;

	  HDA_GROUP (amp_group, group, "mute");
	  HDA_INMUTE (0x2b, 0, amp_group, "headphone", UNMUTE);	/* From widget 0x30 */
	  HDA_INMUTE (0x2b, 1, amp_group, "input-mix", UNMUTE);	/* From widget 0x21 */
	}
	/* Widget 0x39 (fppink-micboost) */
	/* Src 0x14=fp-pink */
	HDA_OUTAMP (0x39, group, "micboost", 90);
      }

    if (HDA_PIN_GROUP (0x12, group, pin_group, "green", n, "connector", 0))	/* Pin widget 0x12 */
      {
	/* Src 0x29=front-mix */
	if (HDA_PINSELECT (0x12, ctl, group, "mode", -1))
	  HDA_CHOICES (ctl, "front-out input");
	HDA_OUTMUTE (0x12, group, "inmute", UNMUTE);

	/* Widget 0x29 (front-mix) */
	/* Src 0x4=front */
	/* Src 0x21=input-mix */
	{
	  int amp_group;

	  HDA_GROUP (amp_group, group, "mute");
	  HDA_INMUTE (0x29, 0, amp_group, "front", UNMUTE);	/* From widget 0x04 */
	  HDA_INMUTE (0x29, 1, amp_group, "input-mix", UNMUTE);	/* From widget 0x21 */
	}
	/* Widget 0x3d (green-micboost) */
	/* Src 0x12=green */
	HDA_OUTAMP (0x3d, group, "micboost", 90);
      }

    if (HDA_PIN_GROUP (0x13, group, pin_group, "int-black", n, "connector", 4))	/* Pin widget 0x13 */
      {
	/* Src 0x2d=mono-mixdown */
	if (HDA_PINSELECT (0x13, ctl, group, "mode", -1))
	  HDA_CHOICES (ctl, "mono-out input");
	HDA_OUTAMP (0x13, group, "invol", 90);

	/* Widget 0x2d (mono-mixdown) */
	/* Src 0x1e=mono-mix */

	/* Widget 0x1e (mono-mix) */
	/* Src 0x36=mono-sel */
	/* Src 0x21=input-mix */
	{
	  int amp_group;

	  HDA_GROUP (amp_group, group, "mute");
	  HDA_INMUTE (0x1e, 0, amp_group, "mono", UNMUTE);	/* From widget 0x36 */
	  HDA_INMUTE (0x1e, 1, amp_group, "input-mix", UNMUTE);	/* From widget 0x21 */
	}
      }

    if (HDA_PIN_GROUP (0x15, group, pin_group, "blue", n, "connector", 4))	/* Pin widget 0x15 */
      {
	/* Src 0x2c=linein-mix */
	if (HDA_PINSELECT (0x15, ctl, group, "mode", -1))
	  HDA_CHOICES (ctl, "front-out input");
	HDA_OUTMUTE (0x15, group, "inmute", UNMUTE);

	/* Widget 0x2c (linein-mix) */
	/* Src 0x31=blue-outsel */
	/* Src 0x21=input-mix */
	{
	  int amp_group;

	  HDA_GROUP (amp_group, group, "mute");
	  HDA_INMUTE (0x2c, 0, amp_group, "front", UNMUTE);	/* From widget 0x31 */
	  HDA_INMUTE (0x2c, 1, amp_group, "input-mix", UNMUTE);	/* From widget 0x21 */
	}
	/* Src 0x15=linein */
	HDA_OUTAMP (0x3a, group, "micboost", 90);
      }

    if (HDA_PIN_GROUP (0x16, group, pin_group, "black", n, "connector", 4))	/* Pin widget 0x16 */
      {
	/* Src 0x2a=rear-mix */
	if (HDA_PINSELECT (0x16, ctl, group, "mode", -1))
	  HDA_CHOICES (ctl, "rear-out input");
	HDA_OUTMUTE (0x16, group, "inmute", UNMUTE);

	/* Widget 0x2a (rear-mix) */
	/* Src 0x6=rear */
	/* Src 0x21=input-mix */
	{
	  int amp_group;

	  HDA_GROUP (amp_group, group, "mute");
	  HDA_INMUTE (0x2a, 0, amp_group, "rear", UNMUTE);	/* From widget 0x06 */
	  HDA_INMUTE (0x2a, 1, amp_group, "input-mix", UNMUTE);	/* From widget 0x21 */
	}
	/* Widget 0x3b (black-micboost) */
	/* Src 0x16=black */
	HDA_OUTAMP (0x3b, group, "micboost", 90);
      }

    if (HDA_PIN_GROUP (0x17, group, pin_group, "pink", n, "connector", 0))	/* Pin widget 0x17 */
      {
	/* Src 0x26=mic-mix */
	if (HDA_PINSELECT (0x17, ctl, group, "mode", -1))
	  HDA_CHOICES (ctl, "center/LFE-out input");
	HDA_OUTMUTE (0x17, group, "inmute", UNMUTE);

	/* Widget 0x26 (mic-mix) */
	/* Src 0x32=pink-outsel */
	/* Src 0x21=input-mix */
	{
	  int amp_group;

	  HDA_GROUP (amp_group, group, "mute");
	  HDA_INMUTE (0x26, 0, amp_group, "center/LFE", UNMUTE);	/* From widget 0x32 */
	  HDA_INMUTE (0x26, 1, amp_group, "input-mix", UNMUTE);	/* From widget 0x21 */
	}
	/* Src 0x17=mic */
	HDA_OUTAMP (0x3c, group, "micboost", 90);
      }

#if 0
    if (HDA_PIN_GROUP (0x18, group, pin_group, "int-black", n, "connector", 4))	/* Pin widget 0x18 */
      {
	if (HDA_PINSELECT (0x18, ctl, group, "mode", -1))
	  HDA_CHOICES (ctl, "input");
      }

    if (HDA_PIN_GROUP (0x1a, group, pin_group, "int-black", n, "connector", 4))	/* Pin widget 0x1a */
      {
	if (HDA_PINSELECT (0x1a, ctl, group, "mode", -1))
	  HDA_CHOICES (ctl, "input");
      }
#endif

    if (HDA_PIN_GROUP (0x24, group, pin_group, "orange", n, "connector", 4))	/* Pin widget 0x24 */
      {
	/* Src 0x27=center/LFE-mix */
	if (HDA_PINSELECT (0x24, ctl, group, "mode", -1))
	  HDA_CHOICES (ctl, "center/LFE-out input");
	HDA_OUTMUTE (0x24, group, "inmute", UNMUTE);

	/* Widget 0x27 (center/LFE-mix) */
	/* Src 0x5=center/LFE */
	/* Src 0x21=input-mix */
	{
	  int amp_group;

	  HDA_GROUP (amp_group, group, "mute");
	  HDA_INMUTE (0x27, 0, amp_group, "center/LFE", UNMUTE);	/* From widget 0x05 */
	  HDA_INMUTE (0x27, 1, amp_group, "input-mix", UNMUTE);	/* From widget 0x21 */
	}
      }

    if (HDA_PIN_GROUP (0x25, group, pin_group, "grey", n, "connector", 4))	/* Pin widget 0x25 */
      {
	/* Src 0x28=side-mix */
	if (HDA_PINSELECT (0x25, ctl, group, "mode", -1))
	  HDA_CHOICES (ctl, "side-out input");
	HDA_OUTMUTE (0x25, group, "inmute", UNMUTE);

	/* Widget 0x28 (side-mix) */
	/* Src 0xa=side */
	/* Src 0x21=input-mix */
	{
	  int amp_group;

	  HDA_GROUP (amp_group, group, "mute");
	  HDA_INMUTE (0x28, 0, amp_group, "side", UNMUTE);	/* From widget 0x0a */
	  HDA_INMUTE (0x28, 1, amp_group, "input-mix", UNMUTE);	/* From widget 0x21 */
	}
      }
  }
  return 0;
}