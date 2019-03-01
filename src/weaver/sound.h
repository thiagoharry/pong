/*543:*/
#line 11912 "./cweb/weaver.w"

#ifndef _sound_h_
#define _sound_h_
#ifdef __cplusplus
extern"C"{
#endif
#include <AL/al.h> 
#include <AL/alc.h> 
#include "weaver.h"
/*66:*/
#line 1950 "./cweb/weaver.w"

#include "conf_begin.h"
#include "../../conf/conf.h"
#include "conf_end.h"
/*:66*/
#line 11921 "./cweb/weaver.w"

/*548:*/
#line 11972 "./cweb/weaver.w"

void _initialize_sound(void);
/*:548*//*550:*/
#line 11991 "./cweb/weaver.w"

void _finalize_sound(void);
/*:550*//*560:*/
#line 12118 "./cweb/weaver.w"

bool _select_sound_device(int position);
/*:560*//*564:*/
#line 12151 "./cweb/weaver.w"

int _current_sound_device(void);
/*:564*//*592:*/
#line 12746 "./cweb/weaver.w"

struct sound{
unsigned long size;
int channels,freq,bitrate;
ALuint _data;
bool loaded;
};
/*:592*//*593:*/
#line 12763 "./cweb/weaver.w"

struct sound*_new_sound(char*filename);
/*:593*//*601:*/
#line 12961 "./cweb/weaver.w"

void _play_sound(struct sound*snd);
/*:601*//*605:*/
#line 12996 "./cweb/weaver.w"

void _destroy_sound(struct sound*snd);
/*:605*//*764:*/
#line 16974 "./cweb/weaver.w"

#if W_TARGET == W_ELF
#include <pthread.h> 
#include <semaphore.h> 
#ifndef W_DISABLE_MP3
#include <mpg123.h> 
#endif
#endif
/*:764*//*766:*/
#line 17003 "./cweb/weaver.w"

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
/*:766*//*767:*/
#line 17027 "./cweb/weaver.w"

extern struct _music_data _music[W_MAX_MUSIC];
#ifdef W_MULTITHREAD


extern pthread_mutex_t _music_mutex;
#endif
/*:767*//*769:*/
#line 17047 "./cweb/weaver.w"

#define _NOT_LOADED 0
#define _PLAYING    1
#define _PAUSED     2
#define _CLOSED     3 
/*:769*//*774:*/
#line 17160 "./cweb/weaver.w"

bool _play_music(char*,bool);
/*:774*//*778:*/
#line 17249 "./cweb/weaver.w"

bool _pause_music(char*);
/*:778*//*782:*/
#line 17304 "./cweb/weaver.w"

bool _resume_music(char*);
/*:782*//*784:*/
#line 17349 "./cweb/weaver.w"

bool _stop_music(char*);
/*:784*//*788:*/
#line 17408 "./cweb/weaver.w"

bool _close_music(void);
/*:788*//*790:*/
#line 17444 "./cweb/weaver.w"

float _get_volume(char*);
/*:790*//*794:*/
#line 17477 "./cweb/weaver.w"

float _increase_volume(char*,float);
/*:794*//*804:*/
#line 17707 "./cweb/weaver.w"

#if W_TARGET == W_ELF && !defined(W_DISABLE_MP3)
void*_music_thread(void*);
#endif
/*:804*/
#line 11922 "./cweb/weaver.w"

#ifdef __cplusplus
}
#endif
#endif
/*:543*/
