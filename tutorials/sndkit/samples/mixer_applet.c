/*
 * Purpose: A sample program for developing a simple mixer applet.
 * Copyright (C) 4Front Technologies, 2007. Released under GPLv2/CDDL.
 *
 * This program is not usefull by itself. It just demonstrates techniques that
 * can be used when developing very simple mixer applets that control just
 * the key volumes in the system.
 *
 * The full OSS 4.0 mixer API is rather complex and designed for allmighty
 * master mixer applications. However there is a subset of the API that can be
 * used rather easily. This subset is limited to control of the main output volume,
 * audio/wave/pcm playback volume and/or recording input level. It cannot be
 * used for anything else.
 *
 *
 * This program demonstrates three main techniques to be used by mixer applets:
 *
 * 1) How to find the default mixer device that controls the primary
 *    sound card/device in the system. This device is connected to the
 *    primary (desktop) speakers and the default system sounds/beep are
 *    directed to it. Normally this device is the audio chip installed on
 *    the motherboard of the computer.
 *
 * 2) How to find out the main, pcm and recording volume controls for
 *    the given device.
 *
 * 3) How to read the current volume and how to change it.
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/soundcard.h>
#include <time.h>
#include <errno.h>

oss_sysinfo sysinfo;

static int mixer_dev = -1;	/* Use the default mixer */

int
find_default_mixer (int mixer_fd)
{
  int default_mix = -1;
  int best_pri = -2;

  oss_mixerinfo mi;

  int i;

/*
 * The default mixer device in the system can be found by checking the
 * priority parameter of all mixer devices in the system. The device with the
 * highest priority value is the winner. If there are multiple devices with the
 * same priority then the first one should be selected.
 *
 * Note that there should be some method for selecting the mixer device number.
 * In many cases the user actually wants to use some other mixer than the
 * motherboard one.
 */

  for (i = 0; i < sysinfo.nummixers; i++)
    {
      mi.dev = i;

      if (ioctl (mixer_fd, SNDCTL_MIXERINFO, &mi) == -1)
	{
	  perror ("SNDCTL_MIXERINFO");
	  continue;
	}

      if (mi.priority < -1)	/* Not suitable default mixer */
	continue;

      if (mi.priority > best_pri)
	{
	  default_mix = i;
	  best_pri = mi.priority;
	}
    }

  return default_mix;
}

void
show_control (int mixer_fd, char *name, int mixer_dev, int ctl)
{
  oss_mixext ext;
  oss_mixer_value val;

/*
 * Obtain the mixer extension definition. It might be a good idea to cache
 * this info in global variables so that doesn't need to be reloaded
 * every time. 
 *
 * Reloading this info every time may cause serious troubles because in that
 * way the application cannot be noticed after the mixer interface has changed.
 */

  ext.dev = mixer_dev;
  ext.ctrl = ctl;

  if (ioctl (mixer_fd, SNDCTL_MIX_EXTINFO, &ext) == -1)
    {
      perror ("SNDCTL_MIX_EXTINFO");
      exit (-1);
    }

/*
 * Have to initialize the dev, ctl and timestamp fields before reading the
 * actual value.
 */

  val.dev = mixer_dev;
  val.ctrl = ctl;
  val.timestamp = ext.timestamp;

  if (ioctl (mixer_fd, SNDCTL_MIX_READ, &val) == -1)
    {
      if (errno == EIDRM)
	{
/*
 * Getting errno=EIDRM tells that the mixer struicture has been changed. This
 * may happen for example if new firmware gets loaded to the device. In such 
 * case the application should start from the beginning and to load all
 * the information again.
 *
 */
	  fprintf (stderr, "Mixer structure changed. Please try again\n");
	  exit (-1);
	}

      perror ("SNDCTL_MIX_READ");
      exit (-1);
    }

  printf ("%s (%s) ", name, ext.extname);

  switch (ext.type)
    {
    case MIXT_MONOSLIDER:
      printf ("monoslider %d ", val.value & 0xff);
      break;

    case MIXT_STEREOSLIDER:
      printf ("stereoslider %d:%d ", val.value & 0xff,
	      (val.value >> 8) & 0xff);
      break;

    case MIXT_SLIDER:
      printf ("slider %d ", val.value);
      break;

    case MIXT_MONOSLIDER16:
      printf ("monoslider %d ", val.value & 0xffff);
      break;

    case MIXT_STEREOSLIDER16:
      printf ("stereoslider %d:%d ", val.value & 0xffff,
	      (val.value >> 16) & 0xffff);
      break;

/*
 * Sometimes there may be just a MUTE control instead of a slider. However
 * it's also possible that there is both mute and a slider. This simple
 * sample program cannot handle that case but real-life applications should be
 * able to do it.
 */
    case MIXT_ONOFF:
      printf ("enum (mute?) %d ", val.value);
      break;

    default:
      printf ("Unknown control type (%d), value=0x%08x ", ext.type,
	      val.value);
    }

  printf ("\n");
}

int
main (int argc, char *argv[])
{
  int mixer_fd = -1;
  int i, n;

  int mainvol_ctl = -1;
  int pcmvol_ctl = -1;
  int recvol_ctl = -1;
  int monvol_ctl = -1;

/*
 * Get the mixer device number from command line.
 */
  if (argc > 1)
    mixer_dev = atoi (argv[1]);


/*
 * Open /dev/mixer. This device file can be used regardless of the actual
 * mixer device number.
 */

  if ((mixer_fd = open ("/dev/mixer", O_RDWR, 0)) == -1)
    {
      perror ("Cannot open /dev/mixer");
      exit (-1);
    }

/*
 * Get OSS system info to a global buffer.
 */

  if (ioctl (mixer_fd, SNDCTL_SYSINFO, &sysinfo) == -1)
    {
      perror ("SNDCTL_SYSINFO");
      exit (-1);
    }

/*
 * Check the mixer device number.
 */

  if (mixer_dev == -1)
    mixer_dev = find_default_mixer (mixer_fd);

  if (mixer_dev < 0 || mixer_dev >= sysinfo.nummixers)
    {
      fprintf (stderr, "Nonexistent mixer device %d\n", mixer_dev);
      exit (-1);
    }

  printf ("Using OSS mixer device %d\n", mixer_dev);

/*
 * The second step is to find the main volume, audio/pcm playback volume and
 * recording level controls.
 *
 * It's important to understand that many mixer devices don't have such
 * controls. This is perfectly normal and the mixer applet must be able to
 * handle this. Aborting or displaying loud error message should be avoided.
 *
 * It's also possible that some mixers have multiple main volume, pcm or
 * record level controls. In such case the application can support all of
 * of them or select just the first one. Having multiple controls means that
 * the device hase multiple sets of speakers or audio devices and each of
 * them has separate volume controls.
 */

  n = mixer_dev;
  if (ioctl (mixer_fd, SNDCTL_MIX_NREXT, &n) == -1)
    {
      perror ("SNDCTL_MIX_NREXT");
      exit (-1);
    }

  for (i = 0; i < n; i++)
    {
      oss_mixext ext;

      ext.dev = mixer_dev;
      ext.ctrl = i;

      if (ioctl (mixer_fd, SNDCTL_MIX_EXTINFO, &ext) == -1)
	{
	  perror ("SNDCTL_MIX_EXTINFO");
	  exit (-1);
	}

/*
 * The MIXF_MAINVOL, MIXF_PCMVOL and MIXF_RECVOL flags are used to mark
 * potential main volume, pcm and recording level controls. This makes it
 * possible to implement support for these common types of controls without
 * having to implement fully featured mixer program.
 *
 * Mixer applets using this simplified interface must ignore all mixer controls
 * that don't have any of these three flags. This is an absolute requirement.
 * Breaking it will cause serious problems.
 */

      if (ext.
	  flags & (MIXF_MAINVOL | MIXF_PCMVOL | MIXF_RECVOL | MIXF_MONVOL))
	{
	  printf ("Mixer control %d is ", i);

	  if (ext.flags & MIXF_MAINVOL)
	    {
	      printf ("Mainvol ");

	      if (mainvol_ctl == -1)
		mainvol_ctl = i;
	    }

	  if (ext.flags & MIXF_PCMVOL)
	    {
	      printf ("PCMvol ");

	      if (pcmvol_ctl == -1)
		pcmvol_ctl = i;
	    }

	  if (ext.flags & MIXF_RECVOL)
	    {
	      printf ("Recvol ");

	      if (recvol_ctl == -1)
		recvol_ctl = i;
	    }

	  if (ext.flags & MIXF_MONVOL)
	    {
	      printf ("Monvol ");

	      if (recvol_ctl == -1)
		recvol_ctl = i;
	    }

	  printf ("%s\n", ext.extname);
	}
    }

/*
 * Now we have selected the mixer controls. Next show their values.
 * Since setting the value is pretty much identical to reading them we don't
 * demonstrate it in this program.
 */
  printf ("\n");

  if (mainvol_ctl >= 0)
    show_control (mixer_fd, "Vol", mixer_dev, mainvol_ctl);
  else
    printf ("No main volume control available\n");

  if (pcmvol_ctl >= 0)
    show_control (mixer_fd, "Pcm", mixer_dev, pcmvol_ctl);
  else
    printf ("No pcm volume control available\n");

  if (recvol_ctl >= 0)
    show_control (mixer_fd, "Rec", mixer_dev, recvol_ctl);
  else
    printf ("No rec volume control available\n");

  if (monvol_ctl >= 0)
    show_control (mixer_fd, "Mon", mixer_dev, monvol_ctl);
  else
    printf ("No monitor volume control available\n");

  close (mixer_fd);

  exit (0);
}