/*
 * Purpose: Definitions for HDaudio codec chips known by OSS.
 */
#define COPYING103 Copyright (C) Hannu Savolainen and Dev Mazumdar 2007. All rights reserved.

struct codec_desc
{
  unsigned int id;
  char *name;
  unsigned long flags;
#define VF_NONE         0x00000000
#define VF_ALC88X_HACK  0x00000001      /* ALC88x requires special handling for
S/PDIF */
  char **remap;

  /*
   * Order of the output converter (DAC) widgets in multi channel mode.
   * If left to 0 then 0x76543210 (sequential order) is assumed. Some
   * motherboards are known to use their own channel ordering which can be
   * fixed using this approach.
   */
  unsigned int multich_map;
  hda_mixer_init_func mixer_init;
  unsigned int main_id; /* In the subdevices table this is used for the codec ID */
};


/*
 * Meaningful widget naming schemes for some known codecs.
 * The list is terminated by a NULL string. An empty string
 * ("") means that the automatically selected name will be used.
 */

static const char *alc880remap[] = {
  "",				/* 0 */
  "",				/* 1 */
  "front",			/* 2 */
  "rear",			/* 3 */
  "center/LFE",			/* 4 */
  "side",			/* 5 */
  "spdif-out",			/* 6 */
  "rec1",			/* 7 */
  "rec2",			/* 8 */
  "rec3",			/* 9 */
  "spdif-in",			/* 10 */
  "inputmix",			/* 11 */
  "front",			/* 12 */
  "rear",			/* 13 */
  "center/LFE",			/* 14 */
  "side",			/* 15 */
  "source-a",			/* 16 */
  "source-b",			/* 17 */
  "source-c",			/* 18 */
  "source-d",			/* 19 */
  "",				/* 20 */
  "",				/* 21 */
  "",				/* 22 */
  "",				/* 23 */
  "",				/* 24 */
  "",				/* 25 */
  "",				/* 26 */
  "",				/* 27 */
  "",				/* 28 */
  "",				/* 29 */
  "",				/* 30 */
  "",				/* 31 */
  "",				/* 32 */
  "",				/* 33 */
  "",				/* 34 */
  "",				/* 35 */
  "",				/* 36 */
  "fp-front",			/* 37 */
  NULL
};

static const char *alc883remap[] = {
  "",                           /* 0 */
  "",                           /* 1 */
  "front",                 	/* 2 */
  "rear",                  	/* 3 */
  "center/LFE",            	/* 4 */
  "side",                  	/* 5 */
  "spdif-out",                	/* 6 */
  "",                       	/* 7 */
  "rec1",                       /* 8 */
  "rec2",                      	/* 9 */
  "spdif-in",                 	/* a */
  "input-mix",                  /* b */
  "front",                      /* c */
  "rear",                       /* d */
  "center/LFE",                 /* e */
  "side",                       /* f */
  "",                   	/* 10 */
  "",                   	/* 11 */
  "",                   	/* 12 */
  "",                   	/* 13 */
  "",                           /* 14 */
  "",                           /* 15 */
  "",                           /* 16 */
  "",                           /* 17 */
  "",                       	/* 18 */
  "",                   	/* 19 */
  "",                   	/* 1a */
  "",                   	/* 1b */
  "",                         	/* 1c */
  "",                       	/* 1d */
  "",                  		/* 1e */
  "",                   	/* 1f */
  "",                           /* 20 */
  "",                           /* 21 */
  "",                           /* 22 */
  "",                           /* 23 */
  "",                           /* 24 */
  "pcm4",                       /* 25 */
  "pcm4",                       /* 26 */
  NULL
};

static const char *alc260remap[] = {
  "",				/* 0x00 */
  "",				/* 0x01 */
  "front",			/* 0x02 */
  "spdif-out",			/* 0x03 */
  "rec1",			/* 0x04 */
  "rec2",			/* 0x05 */
  "spdif-in",			/* 0x06 */
  "inputmix",			/* 0x07 */
  "speaker-mix",		/* 0x08 */
  "headphone-mix",		/* 0x09 */
  "mono-mix",			/* 0x0a */
  "",				/* 0x0b */
  "",				/* 0x0c */
  "",				/* 0x0d */
  "",				/* 0x0e */
  "speaker",			/* 0x0f */
  "headphone",			/* 0x10 */
  "mono",			/* 0x11 */
  "",				/* 0x12 */
  "",				/* 0x13 */
  "",				/* 0x14 */
  "",				/* 0x15 */
  "",				/* 0x16 */
  "beep",			/* 0x17 */
  "spdif-out",			/* 0x18 */
  "spdif-in",			/* 0x19 */
  NULL
};

static const char *alc262remap[] = {
  "",                           /* 0x00 */
  "",                           /* 0x01 */
  "speaker",               	/* 0x02 */
  "headphone",             	/* 0x03 */
  "",                       	/* 0x04 */
  "",                       	/* 0x05 */
  "spdif-out",                  /* 0x06 */
  "rec1",                       /* 0x07 */
  "rec2",                       /* 0x08 */
  "rec3",                       /* 0x09 */
  "spdif-in",                   /* 0x0a */
  "mix",                        /* 0x0b */
  "",                           /* 0x0c */
  "",                           /* 0x0d */
  "",                           /* 0x0e */
  "",                           /* 0x0f */
  "",                           /* 0x10 */
  "mono",                       /* 0x11 */
  "dmic",                       /* 0x12 */
  "",                           /* 0x13 */
  "line-out",                   /* 0x14 */
  "headphone",                  /* 0x15 */
  "mono",                       /* 0x16 */
  "beep",                       /* 0x17 */
  "",                       	/* 0x18 */
  "",                       	/* 0x19 */
  "",                   	/* 0x1a */
  "",                   	/* 0x1b */
  "",                         	/* 0x1c */
  "beep",                       /* 0x1d */
  "spdif-out",                  /* 0x1e */
  "spdif-in",                   /* 0x1f */
  NULL
};

static const char *alc662remap[] = {
  "",                           /* 0x00 */
  "",                           /* 0x01 */
  "front",                 	/* 0x02 */
  "rear",                 	/* 0x03 */
  "center/LFE",            	/* 0x04 */
  "",            		/* 0x05 */
  "spdif-out",                  /* 0x06 */
  "spdout",                     /* 0x07 */
  "rec1",                       /* 0x08 */
  "rec2",                      	/* 0x09 */
  "",                      	/* 0x0a */
  "mix",                        /* 0x0b */
  "front",                      /* 0x0c */
  "rear",                       /* 0x0d */
  "c/lfe",                      /* 0x0e */
  "",                           /* 0x0f */
  "",                           /* 0x10 */
  "",                           /* 0x11 */
  "",                           /* 0x12 */
  "",                      	/* 0x13 */
  "",                    	/* 0x14 */
  "",                     	/* 0x15 */
  "",                   	/* 0x16 */
  "",                    	/* 0x17 */
  "",                    	/* 0x18 */
  "",                    	/* 0x19 */
  "",                  		/* 0x1a */
  "",                   	/* 0x1b */
  "",                   	/* 0x1c */
  "",                      	/* 0x1d */
  "",                  		/* 0x1e */
  "",                           /* 0x1f */
  "",                           /* 0x20 */
  "",                           /* 0x21 */
  "",                           /* 0x22 */
  "",                   	/* 0x23 */
  NULL
};

static const char *alc861remap[] = {
  "",				/* 0x00 */
  "",				/* 0x01 */
  "",				/* 0x02 */
  "front",			/* 0x03 */
  "side",			/* 0x04 */
  "center/LFE",			/* 0x05 */
  "rear",			/* 0x06 */
  "spdout",			/* 0x07 */
  "rec",			/* 0x08 */
  "",				/* 0x09 */
  "",				/* 0x0a */
  "",				/* 0x0b */
  "",				/* 0x0c */
  "",				/* 0x0d */
  "",				/* 0x0e */
  "",				/* 0x0f */
  "",				/* 0x10 */
  "",				/* 0x11 */
  "",				/* 0x12 */
  "",				/* 0x13 */
  "recmix",			/* 0x14 */
  "outmix",			/* 0x15 */
  "frontmix",			/* 0x16 */
  "sidemix",			/* 0x17 */
  "c/l-mix",			/* 0x18 */
  "rearmix",			/* 0x19 */
  "line2-mix",			/* 0x1a */
  "mic2mix",			/* 0x1b */
  "line1mix",			/* 0x1c */
  "",				/* 0x1d */
  "vendor",			/* 0x1e */
  "center/LFE",			/* 0x1f */
  "side",			/* 0x20 */
  "",				/* 0x21 */
  "",				/* 0x22 */
  "beep",			/* 0x23 */
  NULL
};

static const char *cmi9880remap[] = {
  "",				/* 0 */
  "",				/* 1 */
  "",				/* 2 */
  "front",			/* 3 */
  "rear",			/* 4 */
  "side",			/* 5 */
  "center/LFE",			/* 6 */
  "spdif-out",			/* 7 */
  "",				/* 8 */
  "",				/* 9 */
  "",				/* 10 */
  "",				/* 11 */
  "",				/* 12 */
  "",				/* 13 */
  "",				/* 14 */
  "",				/* 15 */
  "",				/* 16 */
  "",				/* 17 */
  "",				/* 18 */
  "",				/* 19 */
  "",				/* 20 */
  "",				/* 21 */
  "",				/* 22 */
  "pcbeep",			/* 23 */
  "",				/* 24 */
  "",				/* 25 */
  "",				/* 26 */
  "",				/* 27 */
  "",				/* 28 */
  "",				/* 29 */
  "",				/* 30 */
  "",				/* 31 */
  NULL
};

static const char *ad1981remap[] = {
  "",				/* 0 */
  "",				/* 1 */
  "spdif",			/* 2 */
  "play",			/* 3 */
  "rec",			/* 4 */
  "",				/* 5 */
  "",				/* 6 */
  "",				/* 7 */
  "",				/* 8 */
  "",				/* 9 */
  "spdif-out",			/* a */
  "mono-sel",			/* b */
  "mic-mix",			/* c */
  "pcbeep-sel",			/* d */
  "rec-mix",			/* e */
  "mono-mix",			/* f */
  "digital-beep",		/* 10 */
  "frontmix-amp",		/* 11 */
  "mic-mixamp",			/* 12 */
  "linein-mixamp",		/* 13 */
  "powerdown",			/* 14 */
  "rec-sel",			/* 15 */
  "",				/* 16 */
  "",				/* 17 */
  "",				/* 18 */
  "",				/* 19 */
  "lineout-mixamp",		/* 1a */
  "aux-mixamp",			/* 1b */
  "mic-mixamp",			/* 1c */
  "CD-mixamp",			/* 1d */
  "fp-mic-mute",		/* 1e */
  "mic-mute",			/* 1f */
  NULL
};

static const char *ad1983remap[] = {
  "",                           /* 0 */
  "",                           /* 1 */
  "spdif",                      /* 2 */
  "play",                       /* 3 */
  "rec",                        /* 4 */
  "",                   	/* 5 */
  "",          			/* 6 */
  "",                  		/* 7 */
  "",                  		/* 8 */
  "",                  		/* 9 */
  "spdif-out",                  /* a */
  "mono-sel",                	/* b */
  "mic-boost",                  /* c */
  "linein-sel",                 /* d */
  "rec-mix",                    /* e */
  "mono-mix",                   /* f */
  "digital-beep",               /* 10 */
  "frontmix-amp",               /* 11 */
  "mic-mixamp",                 /* 12 */
  "linein-mixamp",              /* 13 */
  "rec-sel",                    /* 14 */
  "powerdown",                  /* 15 */
  NULL
};

static const char *ad1984remap[] = {
  "",                           /* 0 */
  "",                           /* 1 */
  "spdif",                      /* 2 */
  "headphone",                  /* 3 */
  "front",                 	/* 4 */
  "dig-mic1",                   /* 5 */
  "dig-mic2",                   /* 6 */
  "headphone-mix",              /* 7 */
  "rec1",                       /* 8 */
  "rec2",                       /* 9 */
  "lineout-mix",                /* a */
  "aux-mix",                    /* b */
  "rec1-sel",                  	/* c */
  "rec2-sel",                 	/* d */
  "mono-sel",                  	/* e */
  "aux-sel",                   	/* f */
  "beep",               	/* 10 */
  "",               		/* 11 */
  "",                 		/* 12 */
  "",              		/* 13 */
  "",                  		/* 14 */
  "",                  		/* 15 */
  "",                  		/* 16 */
  "",                  		/* 17 */
  "",                  		/* 18 */
  "mixer-powerdown",            /* 19 */
  "beep",                  	/* 1a */
  "spdif-out",                  /* 1b */
  "",                  		/* 1c */
  "",                  		/* 1d */
  "mono-mix",                  	/* 1e */
  "mono-downmix",               /* 1f */
  "input-mix",                  /* 20 */
  "input-mixamp",               /* 21 */
  "headphone-sel",              /* 22 */
  "dock-sel",                  	/* 23 */
  "dock-mix",                  	/* 24 */
  "dock-micboost",              /* 25 */
  "",                  		/* 26 */
  NULL
};

static const char *ad1986remap[] = {
  "",				/* 0 */
  "",				/* 1 */
  "spdif-out",			/* 2 */
  "front",			/* 3 */
  "rear",			/* 4 */
  "center/LFE",			/* 5 */
  "rec",			/* 6 */
  "recmon",			/* 7 */
  "mono-mix",			/* 8 */
  "stereo-downmix",		/* 9 */
  "headphone-sel",		/* a */
  "lineout-sel",		/* b */
  "rear-sel",			/* c */
  "center/LFE-sel",		/* d */
  "mono-sel",			/* e */
  "mic-sel",			/* f */
  "linein-sel",			/* 10 */
  "mic-src",			/* 11 */
  "rec-src"			/* 12 */
  "mic-mix",			/* 13 */
  "phone-mix",			/* 14 */
  "cd-mix",			/* 15 */
  "aux-mix",			/* 16 */
  "linein-mix",			/* 17 */
  "beep",			/* 18 */
  "digital-beep",		/* 19 */
  "",				/* 1a */
  "",				/* 1b */
  "",				/* 1c */
  "",				/* 1d */
  "",				/* 1e */
  "",				/* 1f */
  "",				/* 20 */
  "",				/* 21 */
  "",				/* 22 */
  "",				/* 23 */
  "",				/* 24 */
  "spdif-out",			/* 25 */
  "analog-powerdown",		/* 26 */
  "mic-c/LFE-mix",		/* 27 */
  "mic-linein-mix",		/* 28 */
  "c/LFE-linein-mix",		/* 29 */
  "mic-linein-c/LFE-mix",	/* 2a */
  "mic-sel",			/* 2b */
  NULL
};

static const char *ad1988remap[] = {
  "",				/* 0 */
  "",				/* 1 */ /* This is both audio-fgr and DAC???? */
  "spdout",			/* 2 */ /* Not used? */
  "headphone",			/* 3 */
  "front",			/* 4 */
  "center/LFE",			/* 5 */
  "rear",			/* 6 */
  "spdin",			/* 7 */
  "rec1",			/* 8 */
  "rec2",			/* 9 */
  "side",			/* a */
  "spdin-src",			/* b */
  "rec1-src",			/* c */
  "rec2-src",			/* d */
  "rec3-src",			/* e */
  "rec3",			/* f */
  "pcbeep",			/* 10 */
  "",				/* 11 */
  "",				/* 12 */
  "",				/* 13 */
  "",				/* 14 */
  "",				/* 15 */
  "",				/* 16 */
  "",				/* 17 */
  "",				/* 18 */
  "power-down",			/* 19 */
  "beep",			/* 1a */
  "spdif-out",			/* 1b */
  "spdif-in",			/* 1c */
  "spdifout-mix",		/* 1d */
  "mono-mix",			/* 1e */
  "main-volume",		/* 1f */
  "analog-mix",			/* 20 */
  "outamp",			/* 21 */
  "headphon-mix",		/* 22 */
  "hp-powerdown",		/* 23 */
  "",				/* 24 */
  "",				/* 25 */
  "mic-mix",			/* 26 */
  "center/LFE-mix",		/* 27 */
  "side-mix",			/* 28 */
  "front-mix",			/* 29 */
  "rear-mix",			/* 2a */
  "fp-mic-mix",			/* 2b */
  "linein-mix",			/* 2c */
  "mono-mixdown",		/* 2d */
  "",				/* 2e */
  "bias-pdown",			/* 2f */
  "fppink-outsel",		/* 30 */
  "blue-outsel",		/* 31 */
  "pink-outsel",		/* 32 */
  "blue-insel",			/* 33 */
  "pink-insel",			/* 34 */
  "",				/* 35 */
  "mono-sel",			/* 36 */
  "fpgreen-outsel",		/* 37 */
  "fpgreen-micboost",		/* 38 */
  "fppink-micboost",		/* 39 */
  "blue-micboost",		/* 3a */
  "black-micboost",		/* 3b */
  "pink-micboost",		/* 3c */
  "green-micboost",		/* 3d */
  NULL
};

#if 0
static const char *stac9200remap[] = {
  "",				/* 0 */
  "",				/* 0x01 */
  "play",			/* 0x02 */
  "rec",			/* 0x03 */
  "spdif-in",			/* 0x04 */
  "spdif-out",			/* 0x05 */
  "",				/* 0x06 */
  "playmux",			/* 0x07 */
  "",				/* 0x08 */
  "",				/* 0x09 */
  "recmux",			/* 0x0a */
  "mainvol",			/* 0x0b */
  "inputmux",			/* 0x0c */
  "",				/* 0x0d */
  "",				/* 0x0e */
  "",				/* 0x0f */
  "",				/* 0x10 */
  "",				/* 0x11 */
  "",				/* 0x12 */
  "mono-mix",			/* 0x13 */
  "beep",			/* 0x14 */
  NULL
};
#endif

static const char *stac920xremap[] = {
  "",                           /* 0 */
  "",                           /* 0x01 */
  "",                 		/* 0x02 */
  "",            		/* 0x03 */
  "",                  		/* 0x04 */
  "",                  		/* 0x05 */
  "",                  		/* 0x06 */
  "",                  		/* 0x07 */
  "",                       	/* 0x08 */
  "",                       	/* 0x09 */
  "",                           /* 0x0a */
  "",                           /* 0x0b */
  "",                           /* 0x0c */
  "",                           /* 0x0d */
  "",                           /* 0x0e */
  "",                           /* 0x0f */
  "front",                 	/* 0x10 */
  "rear",                  	/* 0x11 */
  "rec1",                       /* 0x12 */
  "rec2",                   	/* 0x13 */
  "mono-out",                   /* 0x14 */
  "mono-mix",                 	/* 0x15 */
  "cd",                 	/* 0x16 */
  "dig-mic1",                 	/* 0x17 */
  "dig-mic2", 			/* 0x18 */
  "input1-mux",                 /* 0x19 */
  "input2-mux",                 /* 0x1a */
  "rec1-vol",                   /* 0x1b */
  "rec2-vol",                   /* 0x1c */
  "rec1-mux",                   /* 0x1d */
  "rec2-mux",                  	/* 0x1e */
  "spdif-out",                  /* 0x1f */
  "spdif-in",                   /* 0x20 */
  "digital-out",                /* 0x21 */
  "digital-in",                 /* 0x22 */
  "beep",                       /* 0x23 */
  "mastervol",                  /* 0x24 */
  "",                       	/* 0x25 */
  NULL
};

static const char *stac925xremap[] = {
  "",                           /* 0 */
  "",                           /* 0x01 */
  "play",                       /* 0x02 */
  "rec",                        /* 0x03 */
  "spdif-in",                   /* 0x04 */
  "spdif-out",          	/* 0x05 */
  "output-mux",                	/* 0x06 */
  "",                    	/* 0x07 */
  "",                   	/* 0x08 */
  "rec-vol",                   	/* 0x09 */
  "",                     	/* 0x0a */
  "",                    	/* 0x0b */
  "",                   	/* 0x0c */
  "",                           /* 0x0d */
  "vol",                   	/* 0x0e */
  "input-mux",                  /* 0x0f */
  "",                           /* 0x10 */
  "",                           /* 0x11 */
  "mono-mix",                   /* 0x12 */
  "beep",                   	/* 0x13 */
  "rec-mux",                    /* 0x14 */
  "",                       	/* 0x15 */
  NULL
};

static const char *stac922xremap[] = {
  "",				/* 0 */
  "",				/* 0x01 */
  "front",			/* 0x02 */
  "center/LFE",			/* 0x03 */
  "rear",			/* 0x04 */
  "side",			/* 0x05 */
  "rec1",			/* 0x06 */
  "rec2",			/* 0x07 */
  "spdif-out",			/* 0x08 */
  "spdif-in",			/* 0x09 */
  "",				/* 0x0a */
  "",				/* 0x0b */
  "",				/* 0x0c */
  "",				/* 0x0d */
  "",				/* 0x0e */
  "",				/* 0x0f */
  "",				/* 0x10 */
  "",				/* 0x11 */
  "rec1mux",			/* 0x12 */
  "rec2mux",			/* 0x13 */
  "pcbeep",			/* 0x14 */
  "cd",				/* 0x15 */
  "mainvol",			/* 0x16 */
  "rec1vol",			/* 0x17 */
  "rec2vol",			/* 0x18 */
  "adat",			/* 0x19 */
  "i2s-out",			/* 0x1a */
  "i2s-in",			/* 0x1b */
  NULL
};

static const char *stac923xremap[] = {
  "",                           /* 0 */
  "",                           /* 0x01 */
  "front",                 	/* 0x02 */
  "center/LFE",            	/* 0x03 */
  "rear",                  	/* 0x04 */
  "side",                  	/* 0x05 */
  "headphone",                  /* 0x06 */
  "rec1",                       /* 0x07 */
  "rec2",                  	/* 0x08 */
  "rec3",                   	/* 0x09 */
  "",                           /* 0x0a */
  "",                           /* 0x0b */
  "",                           /* 0x0c */
  "",                           /* 0x0d */
  "",                           /* 0x0e */
  "",                           /* 0x0f */
  "",                   	/* 0x10 */
  "",                   	/* 0x11 */
  "cd",                    	/* 0x12 */
  "dig-mic1",                   /* 0x13 */
  "dig-mic2",                   /* 0x14 */
  "input1-mux",                 /* 0x15 */
  "input2-mux",                 /* 0x16 */
  "input3-mux",                 /* 0x17 */
  "rec1vol",                    /* 0x18 */
  "rec2vol",                    /* 0x19 */
  "rec3vol",                    /* 0x1a */
  "rec1-mux",                   /* 0x1b */
  "rec2-mux",                   /* 0x1c */
  "rec3-mux",                   /* 0x1d */
  "spdif-out",                  /* 0x1e */
  "adat",                     	/* 0x1f */
  NULL
};


static const codec_desc_t codecs[] = {
  /* Realtek HDA codecs */
  {0x10ec0260, "ALC260", VF_NONE, (char **) &alc260remap},
  {0x10ec0262, "ALC262", VF_NONE, (char **) &alc262remap}, 
  {0x10ec0268, "ALC268", VF_NONE, (char **) &alc262remap}, 
  {0x10ec0662, "ALC662", VF_NONE, (char **) &alc662remap},
  {0x10ec0861, "ALC861", VF_NONE, (char **) &alc861remap},
  {0x10ec0862, "ALC862", VF_NONE, (char **) &alc861remap},
  {0x10ec0880, "ALC880", VF_ALC88X_HACK, (char **) &alc880remap}, 
  {0x10ec0882, "ALC882", VF_ALC88X_HACK, (char **) &alc880remap}, 
  {0x10ec0883, "ALC883", VF_ALC88X_HACK, (char **) &alc883remap}, 
  {0x10ec0885, "ALC885", VF_ALC88X_HACK, (char **) &alc883remap}, 
  {0x10ec0888, "ALC888", VF_ALC88X_HACK, (char **) &alc883remap}, 

  /* CMedia HDA codecs */
  {0x13f69880, "CMI9880", VF_NONE, (char **) &cmi9880remap},
  {0x434d4980, "CMI9880", VF_NONE, (char **) &cmi9880remap},

  /* Analog Devices HDA codecs */
  {0x11d41981, "AD1981", VF_NONE, (char **) &ad1981remap, 0x76543021},
  {0x11d41983, "AD1983", VF_NONE, (char **) &ad1983remap, 0x76543021},
  {0x11d41984, "AD1984", VF_NONE, (char **) &ad1984remap, 0x76543012},
  {0x11d41986, "AD1986A", VF_NONE, (char **) &ad1986remap, 0x76540321},
  {0x11d41988, "AD1988A", VF_NONE, (char **) &ad1988remap, 0x76015432},
  {0x11d4198b, "AD1988B", VF_NONE, (char **) &ad1988remap, 0x76015432},

  /* Sigmatel HDA codecs (some of them) */
  {0x83847690, "STAC9200", VF_NONE, (char **) &stac920xremap },
  {0x838476a0, "STAC9205", VF_NONE, (char **) &stac920xremap },
  {0x838476a1, "STAC9205D", VF_NONE, (char **) &stac920xremap },
  {0x838476a2, "STAC9204", VF_NONE, (char **) &stac920xremap },
  {0x838476a3, "STAC9204D", VF_NONE, (char **) &stac920xremap },
  
  /* Apple Macbook ids */
  {0x83847880, "STAC9220 A1", VF_NONE, (char **) &stac922xremap },
  {0x83847882, "STAC9220 A2", VF_NONE, (char **) &stac922xremap },
  {0x83847680, "STAC9221 A1", VF_NONE, (char **) &stac922xremap },

  {0x83847681, "STAC9220D", VF_NONE, (char **) &stac922xremap },
  {0x83847682, "STAC9221", VF_NONE, (char **) &stac922xremap },
  {0x83847683, "STAC9221D", VF_NONE, (char **) &stac922xremap },

  {0x83847610, "STAC9230XN", VF_NONE, (char **) &stac923xremap },
  {0x83847611, "STAC9230DN", VF_NONE, (char **) &stac923xremap },
  {0x83847612, "STAC9230XT", VF_NONE, (char **) &stac923xremap },
  {0x83847613, "STAC9230DT", VF_NONE, (char **) &stac923xremap },
  {0x83847614, "STAC9229X", VF_NONE, (char **) &stac923xremap },
  {0x83847615, "STAC9229D", VF_NONE, (char **) &stac923xremap },
  {0x83847616, "STAC9228X", VF_NONE, (char **) &stac923xremap },
  {0x83847617, "STAC9228D", VF_NONE, (char **) &stac923xremap },
  {0x83847618, "STAC9227X", VF_NONE, (char **) &stac923xremap },
  {0x83847619, "STAC9227D", VF_NONE, (char **) &stac923xremap },

  {0x838476a4, "STAC9255", VF_NONE, (char **) &stac925xremap },
  {0x838476a5, "STAC9255D", VF_NONE, (char **) &stac925xremap },
  {0x838476a6, "STAC9254", VF_NONE, (char **) &stac925xremap },
  {0x838476a7, "STAC9254D", VF_NONE, (char **) &stac925xremap },

  {0x83847620, "STAC9274", VF_NONE, (char **) &stac923xremap },
  {0x83847621, "STAC9274D", VF_NONE, (char **) &stac923xremap },
  {0x83847622, "STAC9273X", VF_NONE, (char **) &stac923xremap },
  {0x83847623, "STAC9273D", VF_NONE, (char **) &stac923xremap },
  {0x83847624, "STAC9272X", VF_NONE, (char **) &stac923xremap },
  {0x83847625, "STAC9272D", VF_NONE, (char **) &stac923xremap },
  {0x83847626, "STAC9271X", VF_NONE, (char **) &stac923xremap },
  {0x83847627, "STAC9271D", VF_NONE, (char **) &stac923xremap },

  {0x83847628, "STAC9274X5NH", VF_NONE, (char **) &stac923xremap },
  {0x83847629, "STAC9274D5NH", VF_NONE, (char **) &stac923xremap },
  {0x83847662, "STAC9872AK", VF_NONE, NULL, 0x76543012},
  {0x83847664, "STAC9872K", VF_NONE, NULL, 0x76543210}, /* Vaio VGN-AR51J */

  /* Conexant */
  {0x14f15045, "CX20548", VF_NONE, NULL, 0x76543201},
  {0x14f15047, "CX20551", VF_NONE, NULL, 0x76543201},
  {0x14f12c06, "Conexant2c06", VF_NONE, NULL}, /* Modem codec (Vaio) */

  /* Unknown */
  {0, "Unknown"}
};

static const char *abit_AA8_remap[] = {
  "",				/* 0 */
  "",				/* 1 */
  "front",			/* 2 */
  "rear",			/* 3 */
  "center/LFE",			/* 4 */
  "side",			/* 5 */
  "spdif-out",			/* 6 */
  "rec1",			/* 7 */
  "rec2",			/* 8 */
  "rec3",			/* 9 */
  "spdif-in",			/* 10 */
  "inputmix",			/* 11 */
  "front",			/* 12 */
  "rear",			/* 13 */
  "center/LFE",			/* 14 */
  "side",			/* 15 */
  "out-source",			/* 16 */
  "out-source",			/* 17 */
  "out-source",			/* 18 */
  "out-source",			/* 19 */
  "green1",			/* 20 */
  "black1",			/* 21 */
  "C-L",			/* 22 */
  "surr",			/* 23 */
  "pink1",			/* 24 */
  "pink2",			/* 25 */
  "blue1",			/* 26 */
  "blue2",			/* 27 */
  "cd",				/* 28 */
  "beep",			/* 29 */
  "spdout",			/* 30 */
  "spdin",			/* 31 */
  "vendor",			/* 32 */
  "vol",			/* 33 */
  NULL
};

static const char *vaio_remap[] = {
	"",		/* 0x00 */
	"",		/* 0x01 */
	"headphone",	/* 0x02 */
	"pcm",		/* 0x03 */ // Unused
	"pcm",		/* 0x04 */ // Unused
	"speaker",	/* 0x05 */
	"rec",		/* 0x06 */
	"rec",		/* 0x07 */
	"rec",		/* 0x08 */
	"rec",		/* 0x09 */
	"headphone",	/* 0x0a */
	"speaker",	/* 0x0b */
	"speaker",	/* 0x0c */
	"mic",		/* 0x0d */
	"speaker",	/* 0x0e */
	"int-speaker",	/* 0x0f */
	"spdifout1",	/* 0x10 */
	"int-digout",	/* 0x11 */
	"spdifin",	/* 0x12 */
	"speaker",	/* 0x13 */
	"int-mic",	/* 0x14 */
	"rec",		/* 0x15 */
	"beep",		/* 0x16 */
	"vol1",		/* 0x17 */
	"spdifout",	/* 0x18 */
	NULL
};

/*
 * Table for subsystem ID's that require special handling
 */

extern int hdaudio_Asus_P4B_E_mixer_init (int dev, hdaudio_mixer_t * mixer, int cad, int top_group);
extern int hdaudio_scaleoP_mixer_init (int dev, hdaudio_mixer_t * mixer, int cad, int top_group);
extern int hdaudio_abit_AA8_mixer_init (int dev, hdaudio_mixer_t * mixer, int cad, int top_group);
extern int hdaudio_ferrari5k_mixer_init (int dev, hdaudio_mixer_t * mixer, int cad, int top_group);
extern int hdaudio_vaio_vgn_mixer_init (int dev, hdaudio_mixer_t * mixer, int cad, int top_group);

static const codec_desc_t subdevices[] = {
#if 1
  {0x98801019, "ECS 915P-A", VF_NONE, NULL, 0x76541320},
  {0x104381e1, "Asus P4B-E/AD1988A", VF_NONE, (char **) &ad1988remap, 0x76015432, hdaudio_Asus_P4B_E_mixer_init},
  {0x1043e601, "ScaleoP/ALC888", VF_ALC88X_HACK, (char **) &alc883remap, 0, hdaudio_scaleoP_mixer_init}, 

  /* Abit AA8 (at least some revisions) have bogus codec config information,
   * including the subvendor ID. */
  {0x08800000, "Abit AA8/ALC880", VF_ALC88X_HACK, (char **) &abit_AA8_remap, 0, hdaudio_abit_AA8_mixer_init}, 
  {0x10250000, "Ferrari5k/ALC883", VF_ALC88X_HACK, (char **) &alc883remap, 0, hdaudio_ferrari5k_mixer_init},
  {0x104d2200, "STAC9872K/Vaio", VF_NONE, (char**) &vaio_remap, 0x76543210, hdaudio_vaio_vgn_mixer_init, 0x83847664}, /* Vaio VGN-AR51J */
#endif
  {0, "Unknown"}
};
