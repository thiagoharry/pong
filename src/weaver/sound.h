/*539:*/
#line 11739 "cweb/weaver.w"

#ifndef _sound_h_
#define _sound_h_
#ifdef __cplusplus
extern"C"{
#endif
#include <AL/al.h> 
#include <AL/alc.h> 
#include "weaver.h"
/*66:*/
#line 1928 "cweb/weaver.w"

#include "conf_begin.h"
#include "../../conf/conf.h"
#include "conf_end.h"
/*:66*/
#line 11748 "cweb/weaver.w"

/*544:*/
#line 11799 "cweb/weaver.w"

void _initialize_sound(void);
/*:544*//*546:*/
#line 11818 "cweb/weaver.w"

void _finalize_sound(void);
/*:546*//*556:*/
#line 11945 "cweb/weaver.w"

bool _select_sound_device(int position);
/*:556*//*560:*/
#line 11978 "cweb/weaver.w"

int _current_sound_device(void);
/*:560*//*588:*/
#line 12573 "cweb/weaver.w"

struct sound{
unsigned long size;
int channels,freq,bitrate;
ALuint _data;
bool loaded;
};
/*:588*//*589:*/
#line 12590 "cweb/weaver.w"

struct sound*_new_sound(char*filename);
/*:589*//*597:*/
#line 12788 "cweb/weaver.w"

void _play_sound(struct sound*snd);
/*:597*//*601:*/
#line 12823 "cweb/weaver.w"

void _destroy_sound(struct sound*snd);
/*:601*//*760:*/
#line 16804 "cweb/weaver.w"

#if W_TARGET == W_ELF
#include <semaphore.h> 
#ifndef W_DISABLE_MP3
#include <mpg123.h> 
#endif
#endif
/*:760*//*762:*/
#line 16832 "cweb/weaver.w"

struct _music_data{
char filename[W_MAX_SUBLOOP][256];
int status[W_MAX_SUBLOOP];
float volume[W_MAX_SUBLOOP];
bool loop[W_MAX_SUBLOOP];
#if W_TARGET == W_ELF
unsigned char*buffer;
size_t buffer_size;

pthread_t thread;
sem_t semaphore;
#ifndef W_DISABLE_MP3

mpg123_handle*mpg_handle;
#endif

ALuint sound_source,openal_buffer[2];
#endif
};
/*:762*//*763:*/
#line 16856 "cweb/weaver.w"

extern struct _music_data _music[W_MAX_MUSIC];
#ifdef W_MULTITHREAD


extern pthread_mutex_t _music_mutex;
#endif
/*:763*//*765:*/
#line 16876 "cweb/weaver.w"

#define _NOT_LOADED 0
#define _PLAYING    1
#define _PAUSED     2
/*:765*//*770:*/
#line 16988 "cweb/weaver.w"

bool _play_music(char*,bool);
/*:770*//*774:*/
#line 17067 "cweb/weaver.w"

bool _pause_music(char*);
/*:774*//*778:*/
#line 17122 "cweb/weaver.w"

bool _resume_music(char*);
/*:778*//*780:*/
#line 17167 "cweb/weaver.w"

bool _stop_music(char*);
/*:780*//*784:*/
#line 17225 "cweb/weaver.w"

float _get_volume(char*);
/*:784*//*788:*/
#line 17258 "cweb/weaver.w"

float _increase_volume(char*,float);
/*:788*//*798:*/
#line 17496 "cweb/weaver.w"

#if W_TARGET == W_ELF && !defined(W_DISABLE_MP3)
void*_music_thread(void*);
#endif
/*:798*/
#line 11749 "cweb/weaver.w"

#ifdef __cplusplus
}
#endif
#endif
/*:539*/
