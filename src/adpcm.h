/*
 * adpcm.h
 */
#ifndef SAMPL
#define SAMPL short
#endif
#ifndef LONG
#define LONG long
#endif
/* FIXME: This breaks on Alphas! */
#ifndef ULONG
#define ULONG u_long
#endif

/* default coef sets */
extern short iCoef[7][2];

/* AdpcmBlockExpandI() outputs interleaved samples into one output buffer */
extern const char *AdpcmBlockExpandI(
	int chans,          /* total channels             */
	int nCoef,
	const short *iCoef,
	const u_char *ibuff,/* input buffer[blockAlign]   */
	SAMPL *obuff,       /* output samples, n*chans    */
	int n               /* samples to decode PER channel, REQUIRE n % 8 == 1  */
);

extern void AdpcmBlockMashI(
	int chans,          /* total channels */
	const SAMPL *ip,    /* ip[n*chans] is interleaved input samples */
	int n,              /* samples to encode PER channel, REQUIRE */
	int *st,            /* input/output steps, 16<=st[i] */
	u_char *obuff,      /* output buffer[blockAlign] */
	int blockAlign,     /* >= 7*chans + n/2          */
	int opt             /* non-zero allows some cpu-intensive code to improve output */
);

/* Some helper functions for computing samples/block and blockalign */

/*
 * AdpcmSamplesIn(dataLen, chans, blockAlign, samplesPerBlock)
 *  returns the number of samples/channel which would be
 *  in the dataLen, given the other parameters ...
 *  if input samplesPerBlock is 0, then returns the max
 *  samplesPerBlock which would go into a block of size blockAlign
 *  Yes, it is confusing usage.
 */
extern ULONG AdpcmSamplesIn(
	ULONG dataLen,
	unsigned short chans,
	unsigned short blockAlign,
	unsigned short samplesPerBlock
);

/*
 * ULONG AdpcmBytesPerBlock(chans, samplesPerBlock)
 *   return minimum blocksize which would be required
 *   to encode number of chans with given samplesPerBlock
 */
extern ULONG AdpcmBytesPerBlock(
	unsigned short chans,
	unsigned short samplesPerBlock
);
