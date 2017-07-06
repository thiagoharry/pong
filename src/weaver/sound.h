/*506:*/
#line 11117 "cweb/weaver.w"

#ifndef _sound_h_
#define _sound_h_
#ifdef __cplusplus
extern"C"{
#endif
#include <AL/al.h> 
#include <AL/alc.h> 
#include "weaver.h"
/*66:*/
#line 1910 "cweb/weaver.w"

#include "conf_begin.h"
#include "../../conf/conf.h"
#include "conf_end.h"
/*:66*/
#line 11126 "cweb/weaver.w"

/*511:*/
#line 11177 "cweb/weaver.w"

void _initialize_sound(void);
/*:511*//*513:*/
#line 11196 "cweb/weaver.w"

void _finalize_sound(void);
/*:513*//*523:*/
#line 11322 "cweb/weaver.w"

bool _select_sound_device(int position);
/*:523*//*527:*/
#line 11354 "cweb/weaver.w"

int _current_sound_device(void);
/*:527*//*557:*/
#line 11954 "cweb/weaver.w"

struct sound{
unsigned long size;
int channels,freq,bitrate;
ALuint _data;
bool loaded;
};
/*:557*//*558:*/
#line 11971 "cweb/weaver.w"

struct sound*_new_sound(char*filename);
/*:558*//*565:*/
#line 12165 "cweb/weaver.w"

void _play_sound(struct sound*snd);
/*:565*//*569:*/
#line 12200 "cweb/weaver.w"

void _destroy_sound(struct sound*snd);
/*:569*//*574:*/
#line 12257 "cweb/weaver.w"

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
/*:574*//*575:*/
#line 12295 "cweb/weaver.w"

#if defined(W_MULTITHREAD) && W_TARGET == W_ELF && W_THREAD_POOL >  0
struct _thread_file_info _file_list[W_THREAD_POOL];
pthread_t _thread_list[W_THREAD_POOL];
int _file_list_count;
pthread_mutex_t _file_list_count_mutex;
#endif
/*:575*//*578:*/
#line 12366 "cweb/weaver.w"

#if defined(W_MULTITHREAD) && W_TARGET == W_ELF && W_THREAD_POOL >  0
void*_file_list_thread(void*p);
#endif
/*:578*//*581:*/
#line 12410 "cweb/weaver.w"

#if defined(W_MULTITHREAD) && W_TARGET == W_ELF
void _multithread_load_file(const char*filename,void*snd,
void*(*process)(void*),
void*(*onload)(void*),
void*(*onerror)(void*));

#endif
/*:581*/
#line 11127 "cweb/weaver.w"

#ifdef __cplusplus
}
#endif
#endif
/*:506*/
