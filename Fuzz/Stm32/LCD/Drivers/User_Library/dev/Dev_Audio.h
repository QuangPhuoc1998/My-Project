#ifndef _DEV_AUDIO_H_
#define _DEV_AUDIO_H_

#include "main.h"

#define RECORD_BUFFER_SIZE  (6400)
#define DEFAULT_VOL					(50)

void Dev_AudioInit(void);
void Dev_AudioHandler(void);

#endif //_DEV_AUDIO_H_
