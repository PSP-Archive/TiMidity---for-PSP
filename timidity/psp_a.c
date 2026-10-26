/*
    TiMidity++ -- MIDI to WAVE converter and player
    Copyright (C) 1999-2002 Masanao Izumo <mo@goice.co.jp>
    Copyright (C) 1995 Tuukka Toivonen <tt@cgs.fi>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif /* HAVE_CONFIG_H */
#include "timidity.h"

#include <pspaudiolib.h>
#include <pspaudio.h>
#include <pspdebug.h>
#include <psptypes.h>
#include <string.h>

#include "output.h"

static int open_output(void);
static void close_output(void);
static int output_data(char *buf, int32 bytes);
static int acntl(int request, void *arg);

typedef struct a {
	unsigned char buff[PSP_NUM_AUDIO_SAMPLES*4];
	int ready;
} buff_t;

#define BUFF_LIST_SIZE 16
volatile buff_t buff_list[BUFF_LIST_SIZE];

PlayMode psp_play_mode = {
    DEFAULT_RATE,
    PE_16BIT|PE_SIGNED,
    PF_PCM_STREAM,
    -1,
    {0,0,0,0,0},
    "PlayStation Portable(PSP)", 'p',
    NULL,
    open_output,
    close_output,
    output_data,
    acntl
};



/* This function gets called by pspaudiolib every time the
   audio buffer needs to be filled. The sample format is
   16-bit, stereo. */
void audioCallback(void* buf, unsigned int length) {

	int bytes = length*4;
	int len;

	static int curr = 0;
	static unsigned char *buff = buff_list[0].buff;
	static int buffsize = sizeof(buff_list[0].buff);

	while( bytes > 0 ){
		if( buff_list[curr].ready ){
			len = (bytes < buffsize)?bytes:buffsize;
			memcpy(buf,buff,len);
			buff += len;
			buffsize -= len;
			buf += len;
			bytes -= len;
			if(buffsize <= 0){
				buff_list[curr].ready = 0;
				curr = ( curr + 1 ) % BUFF_LIST_SIZE;
				buff = buff_list[curr].buff;
				buffsize = sizeof(buff_list[curr].buff);
			}
		}else{
			memset(buf,0,bytes);
			buf += bytes;
			bytes -= bytes;
//			pspDebugScreenPrintf("-");
		}
	}
}

#include <psputils.h>
#include <psppower.h>
clock_t measure_start=0;
clock_t measure_stop1=0;
float measure_max = 0;

static int output_data(char *buf, int32 bytes){ 
	
	int len;
	float busy_per;
	int i;

	static int curr = 0;
	static unsigned char *buff = buff_list[0].buff;
	static int buffsize = sizeof(buff_list[0].buff);

	measure_stop1 = sceKernelLibcClock();

	busy_per =(float)((measure_stop1-measure_start)*441)/(2500*bytes);

	while( bytes > 0 ){
		if( buff_list[curr].ready == 0 ){
			len = (bytes < buffsize)?bytes:buffsize;
			memcpy(buff,buf,len);
			buff += len;
			buffsize -= len;
			buf += len;
			bytes -= len;
			if(buffsize <= 0){
				buff_list[curr].ready = 1;
				curr = ( curr + 1 ) % BUFF_LIST_SIZE;
				buff = buff_list[curr].buff;
				buffsize = sizeof(buff_list[curr].buff);
			}

		}
	}

	if(measure_start!=0){
		pspDebugScreenSetXY(0,pspDebugScreenGetY());
		if(busy_per>measure_max)measure_max = busy_per;
		pspDebugScreenPrintf("CPU:%5.1f%%(MAX:%5.1f%%)|", busy_per*100,measure_max*100);
		if(busy_per > 1.0 )busy_per = 1;
		for(i=0;i<=(int)(busy_per*40);i++)pspDebugScreenPrintf("-");
		for(;i<=40;i++)pspDebugScreenPrintf(" ");
		pspDebugScreenPrintf("|");
	}

	measure_start = sceKernelLibcClock();

	return 0;
}


static int open_output(void){
	int i;
	pspAudioInit();
	pspAudioSetChannelCallback(0, audioCallback);
	psp_play_mode.fd = 0;
	for(i=0;i<BUFF_LIST_SIZE;i++){
		buff_list[i].ready = 0;
	}
	return 0;
}

static void close_output(void)
{
	psp_play_mode.fd = -1;
	pspAudioEndPre();
	pspAudioEnd();
}

static int acntl(int request, void *arg)
{
	switch(request){
		case PM_REQ_MIDI:
		/* ARG: MidiEvent
		 * Send MIDI event.
		 * If PF_MIDI_EVENT is setted, acntl() is called
		 * with this request.
		 */
			return -1;

		case PM_REQ_INST_NAME:
		/* ARG: char**
		 * Get Instrument name of channel.
		 */
			return -1;

		case PM_REQ_DISCARD:
		/* ARG: not-used
		 * Discard the audio device buffer and returns
		 * immediatly.
		 */
			return 0;

		case PM_REQ_FLUSH:
		/* ARG: not-used
		 * Wait until all audio data is out.
		 */
			return -1;

		case PM_REQ_GETQSIZ:
		/* ARG: int
		 * Get maxmum device queue size in bytes.
		 * If acntl() returns -1,
		 * timidity automatically estimate the size
		 * using adhoc implementation.
		 * This request is used for trace mode.
		 */
			return -1;

		case PM_REQ_SETQSIZ:
		/* ARG: int (in-out)
		 * Set maxmum device queue size in bytes.
		 * The specified ARG is updated new queue size.
		 */
			return -1;

		case PM_REQ_GETFRAGSIZ:
		/* ARG: int
		 * Get device fragment size in bytes.
		 */
//			*((int*)arg) = PSP_NUM_AUDIO_SAMPLES*4;
			return -1;

		PM_REQ_RATE:
		/* ARG: int
		 * Change the sample rate.
		 */
			return -1;

		PM_REQ_GETSAMPLES:
		/* ARG: int
		 * Get the current play samples.
		 * Play samples must be initialized to zero if
		 * PM_REQ_DISCARD/PM_REQ_FLUSH/PM_REQ_PLAY_START
		 * request is receved.
		 */
			return -1;

		PM_REQ_PLAY_START:
		/* ARG: not-used
		 * PM_REQ_PLAY_START is called just before playing.
		 */
			return -1;

		PM_REQ_PLAY_END:
		/* ARG: not-used
		 * PM_REQ_PLAY_END is called just after playing.
		 */
			return -1;

		PM_REQ_GETFILLABLE:
		/* ARG: int
		 * Get fillable device queue size
		 */
			return -1;

		PM_REQ_GETFILLED:
		/* ARG: int
		 * Get filled device queue size
		 */
			return -1;

		PM_REQ_OUTPUT_FINISH:
		 /* ARG: not-used
		  * PM_REQ_OUTPUT_FINISH calls just after the last
		  * output_data(), and TiMidity would into
		  * waiting to flush the audio buffer.
		  */
			return -1;
	}
	return -1;
}

