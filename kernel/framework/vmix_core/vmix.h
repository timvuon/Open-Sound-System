/*
 * Purpose: Definitions for the vmix driver
 */
#define COPYING2 Copyright (C) Hannu Savolainen and Dev Mazumdar 2006. All rights reserved.

#define SUPPORTED_FORMATS (AFMT_S16_NE | AFMT_S16_OE | AFMT_S32_NE | AFMT_S32_OE)

#define MAX_INSTANCES		8
#define MAX_OUTDEVS		16
#define MAX_LOOPDEVS		4
#define MAX_PLAY_CHANNELS	12
/* MAX_REC_CHANNELS must be less or equal than MAX_PLAY_CHANNELS */
#define MAX_REC_CHANNELS	12
#define CHBUF_SAMPLES		2048	/* Max samples (frames) per fragment */

extern int vmix_multich_enable;

typedef struct _vmix_devc_t vmix_devc_t;
typedef struct _vmix_mixer_t vmix_mixer_t;
typedef struct _vmix_portc_t vmix_portc_t;
typedef struct _vmix_engine_t vmix_engine_t;

struct _vmix_portc_t		/* Audio device specific data */
{
  int num;
  vmix_devc_t *devc;
  vmix_mixer_t *mixer;
  int dev_type;
#define DT_IN		1
#define DT_OUT		2
#define DT_LOOP		3

  int disabled_modes;

  int fmt, bits;
  int channels;
  int rate;

  int audio_dev;
  int open_mode;
  int trigger_bits;

  int play_dma_pointer;
  int play_choffs;		/* Index of the first channel on multich play engines */
  int rec_choffs;		/* Index of the first channel on multich rec engines */
#ifdef VMIX_USE_FLOAT
  float play_dma_pointer_src;
#endif
  int rec_dma_pointer;
  int volume[2]; /* Left and right ch volumes */
  int vu[2];

  void (*play_mixing_func) (vmix_portc_t * portc, int nsamples);
  void (*rec_mixing_func) (vmix_portc_t * portc, int nsamples);
  int do_src;
};

#ifdef VMIX_USE_FLOAT
   typedef float vmix_sample_t;
#else
   typedef int vmix_sample_t;
#endif

typedef void (*converter_t) (vmix_engine_t * engine, void *outbuf,
			     vmix_sample_t * chbufs[], int channels,
			     int samples);

struct _vmix_engine_t
{
  int rate, channels, fmt, bits;
  int max_playahead;
  int fragsize;
  int samples_per_frag;

  converter_t converter;
  vmix_sample_t *chbufs[MAX_PLAY_CHANNELS];
  int limiter_statevar;

/*
 * Mixer volumes, etc.
 */
  int outvol;
  int vu[2];
  int num_active_outputs;
};

struct _vmix_mixer_t		/* Instance specific data */
{
  vmix_devc_t *devc;
  int instance_num;
  oss_device_t *osdev;
  oss_device_t *master_osdev;
  oss_mutex_t mutex;

  int installed_ok;

  int open_devices;
  struct fileinfo master_finfo, input_finfo;
  int masterdev_opened;

  int vmix_flags;		/* Copy of adev[master]->vmix_flags */

/*
 * Config options for this instance
 */
  int masterdev;
  int inputdev;
  int numoutputs;
  int numloops;
  int rate;

  int src_quality;		/* Control panel setting */

  vmix_engine_t play_engine, record_engine;

  vmix_portc_t *client_portc[MAX_OUTDEVS];
  vmix_portc_t *loop_portc[MAX_LOOPDEVS];

  int num_clientdevs, num_loopdevs;

/*
 * Mixer interface
 *
 * Mixer device numbers for the master audio devices
 */
  int output_mixer_dev;
  int input_mixer_dev;
  int first_input_mixext;
  int first_output_mixext;
};

struct _vmix_devc_t
{
  oss_device_t *osdev;

  /*
   * Instances
   */
  int num_mixers;
  vmix_mixer_t *mixers[MAX_INSTANCES];

  unsigned long long card_mask;
};

extern vmix_devc_t *vmix_devc;	/* Global devc structure for all instances */

extern void vmix_setup_play_engine (vmix_mixer_t * mixer, adev_t * adev,
				    dmap_t * dmap);
extern void vmix_setup_record_engine (vmix_mixer_t * mixer, adev_t * adev,
				      dmap_t * dmap);
extern void finalize_record_engine (vmix_mixer_t * mixer, int fmt,
				    adev_t * adev, dmap_p dmap);

extern void vmix_outmix_16ne (vmix_portc_t * portc, int nsamples);
extern void vmix_outmix_16oe (vmix_portc_t * portc, int nsamples);
extern void vmix_outmix_32ne (vmix_portc_t * portc, int nsamples);
extern void vmix_outmix_32oe (vmix_portc_t * portc, int nsamples);
#ifdef VMIX_USE_FLOAT
extern void vmix_outmix_float (vmix_portc_t * portc, int nsamples);
#endif

#ifdef VMIX_USE_FLOAT
/*
 * For the time being these routines will only work in floating point.
 */
extern void vmix_outmix_16ne_src (vmix_portc_t * portc, int nsamples);
extern void vmix_outmix_16oe_src (vmix_portc_t * portc, int nsamples);
extern void vmix_outmix_32ne_src (vmix_portc_t * portc, int nsamples);
extern void vmix_outmix_32oe_src (vmix_portc_t * portc, int nsamples);
extern void vmix_outmix_float_src (vmix_portc_t * portc, int nsamples);
#endif

extern void vmix_rec_export_16ne (vmix_portc_t * portc, int nsamples);
extern void vmix_rec_export_16oe (vmix_portc_t * portc, int nsamples);
extern void vmix_rec_export_32ne (vmix_portc_t * portc, int nsamples);
extern void vmix_rec_export_32oe (vmix_portc_t * portc, int nsamples);
#ifdef VMIX_USE_FLOAT
extern void vmix_rec_export_float (vmix_portc_t * portc, int nsamples);
#endif

#define DB_SIZE	50
#define VMIX_VOL_SCALE	100

#ifdef VMIX_USE_FLOAT
   extern const float vmix_db_table[DB_SIZE + 1];
#else
   extern const int vmix_db_table[DB_SIZE + 1];
#endif

#ifdef VMIX_MAIN
#include "db_scale.h"
#endif

#ifdef SWAP_SUPPORT
/*
 * Endianess swapping functions
 */
static __inline__ short
bswap16 (short x)
{
  short y = 0;
  unsigned char *a = ((unsigned char *) &x) + 1;
  unsigned char *b = (unsigned char *) &y;

  *b++ = *a--;
  *b++ = *a--;

  return y;
}

static __inline__ int
bswap32 (int x)
{

  int y = 0;
  unsigned char *a = ((unsigned char *) &x) + 3;
  unsigned char *b = (unsigned char *) &y;

  *b++ = *a--;
  *b++ = *a--;
  *b++ = *a--;
  *b++ = *a--;

  return y;
}
#endif