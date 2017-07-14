/*507:*/
#line 11143 "cweb/weaver.w"

#ifndef _sound_h_
#define _sound_h_
#ifdef __cplusplus
extern"C"{
#endif
#include <AL/al.h> 
#include <AL/alc.h> 
#include "weaver.h"
/*66:*/
#line 1913 "cweb/weaver.w"

#include "conf_begin.h"
#include "../../conf/conf.h"
#include "conf_end.h"
/*:66*/
#line 11152 "cweb/weaver.w"

/*512:*/
#line 11203 "cweb/weaver.w"

void _initialize_sound(void);
/*:512*//*514:*/
#line 11222 "cweb/weaver.w"

void _finalize_sound(void);
/*:514*//*524:*/
#line 11348 "cweb/weaver.w"

bool _select_sound_device(int position);
/*:524*//*528:*/
#line 11380 "cweb/weaver.w"

int _current_sound_device(void);
/*:528*//*558:*/
#line 11989 "cweb/weaver.w"

struct sound{
unsigned long size;
int channels,freq,bitrate;
ALuint _data;
bool loaded;
};
/*:558*//*559:*/
#line 12006 "cweb/weaver.w"

struct sound*_new_sound(char*filename);
/*:559*//*566:*/
#line 12200 "cweb/weaver.w"

void _play_sound(struct sound*snd);
/*:566*//*570:*/
#line 12235 "cweb/weaver.w"

void _destroy_sound(struct sound*snd);
/*:570*//*575:*/
#line 12292 "cweb/weaver.w"

#if defined(W_MULTITHREAD) && W_TARGET == W_ELF
struct _thread_file_info{
char filename[256];
void*target;
void*(*onload)(void*);


void*(*onerror)(void*);




void*(*process)(void*);
bool valid_info;
#if W_THREAD_POOL >  0
pthread_mutex_t mutex;


pthread_mutex_t struct_mutex;
pthread_cond_t condition;
bool _kill_switch;
#endif
};
#endif
/*:575*//*576:*/
#line 12330 "cweb/weaver.w"

#if defined(W_MULTITHREAD) && W_TARGET == W_ELF && W_THREAD_POOL >  0
struct _thread_file_info _file_list[W_THREAD_POOL];
pthread_t _thread_list[W_THREAD_POOL];
int _file_list_count;
pthread_mutex_t _file_list_count_mutex;
#endif
/*:576*//*579:*/
#line 12401 "cweb/weaver.w"

#if defined(W_MULTITHREAD) && W_TARGET == W_ELF && W_THREAD_POOL >  0
void*_file_list_thread(void*p);
#endif
/*:579*//*582:*/
#line 12445 "cweb/weaver.w"

#if defined(W_MULTITHREAD) && W_TARGET == W_ELF
void _multithread_load_file(const char*filename,void*snd,
void*(*process)(void*),
void*(*onload)(void*),
void*(*onerror)(void*));

#endif
/*:582*/
#line 11153 "cweb/weaver.w"

#ifdef __cplusplus
}
#endif
#endif
/*:507*/
