/*508:*/
#line 11155 "cweb/weaver.w"

#include <string.h>  
#include <sys/stat.h>  
#include <sys/types.h>  
#include <time.h>  
#ifdef W_MULTITHREAD
#include <sched.h> 
#include <pthread.h> 
#endif
#include "sound.h"
#include "weaver.h"

#if W_TARGET == W_WEB
extern ALenum alGetError(void);
#endif

/*511:*/
#line 11188 "cweb/weaver.w"

static ALCdevice*default_device;
/*:511*//*532:*/
#line 11416 "cweb/weaver.w"

static ALCcontext*default_context;
/*:532*//*534:*/
#line 11441 "cweb/weaver.w"

static ALuint default_source[5];
/*:534*//*544:*/
#line 11634 "cweb/weaver.w"

static ALuint extract_wave(const char*filename,unsigned long*size,int*freq,
int*channels,int*bitrate,bool*error){
void*returned_data= NULL;
ALuint returned_buffer= 0;
FILE*fp= fopen(filename,"r");
*error= false;
if(fp==NULL){
*error= false;
return 0;
}
/*545:*/
#line 11654 "cweb/weaver.w"

{
char data[5];
data[0]= '\0';
fread(data,1,4,fp);
data[4]= '\0';
if(strcmp(data,"RIFF")){
fprintf(stderr,"WARNING: Not compatible audio format: %s\n",
filename);
fclose(fp);
*error= true;
return 0;
}
}
/*:545*//*546:*/
#line 11677 "cweb/weaver.w"

{
int i;
unsigned long multiplier= 1;
*size= 0;
for(i= 0;i<4;i++){
unsigned long size_tmp= 0;
if(fread(&size_tmp,1,1,fp)!=1){
fprintf(stderr,"WARNING: Damaged file: %s\n",
filename);
fclose(fp);
*error= true;
return 0;
}
*size+= size_tmp*multiplier;
multiplier*= 256;
}
}
/*:546*//*547:*/
#line 11702 "cweb/weaver.w"

{
char data[5];
data[0]= '\0';
fread(data,1,4,fp);
data[4]= '\0';
if(strcmp(data,"WAVE")){
fprintf(stderr,"WARNING: Not compatible audio format: %s\n",
filename);
fclose(fp);
*error= true;
return 0;
}


*size-= 4;
}
/*:547*//*548:*/
#line 11727 "cweb/weaver.w"

{
int c,i;
for(i= 0;i<8;i++){
c= getc(fp);
if(c==EOF){
fprintf(stderr,"WARNING: Damaged audio file: %s\n",
filename);
fclose(fp);
*error= true;
return 0;
}
}
*size-= 8;
}
/*:548*//*549:*/
#line 11753 "cweb/weaver.w"

{
int i,format= 0;
unsigned long multiplier= 1;
for(i= 0;i<2;i++){
unsigned long format_tmp= 0;
if(fread(&format_tmp,1,1,fp)!=1){
fprintf(stderr,"WARNING: Damaged file: %s\n",
filename);
fclose(fp);
*error= true;
return 0;
}
format+= format_tmp*multiplier;
multiplier*= 256;
}
if(format!=1){
fprintf(stderr,"WARNING: Not compatible WAVE file format: %s.\n",
filename);
fclose(fp);
*error= true;
return 0;
}


*size-= 2;
}
/*:549*//*550:*/
#line 11785 "cweb/weaver.w"

{
int i;
*channels= 0;
unsigned long multiplier= 1;
for(i= 0;i<2;i++){
unsigned long channel_tmp= 0;
if(fread(&channel_tmp,1,1,fp)!=1){
fprintf(stderr,"WARNING: Damaged file: %s\n",
filename);
fclose(fp);
*error= true;
return 0;
}
*channels+= channel_tmp*multiplier;
multiplier*= 256;
}


*size-= 2;
}
/*:550*//*551:*/
#line 11810 "cweb/weaver.w"

{
int i;
*freq= 0;
unsigned long multiplier= 1;
for(i= 0;i<4;i++){
unsigned long freq_tmp= 0;
if(fread(&freq_tmp,1,1,fp)!=1){
fprintf(stderr,"WARNING: Damaged file: %s\n",
filename);
fclose(fp);
*error= true;
return 0;
}
*freq+= freq_tmp*multiplier;
multiplier*= 256;
}


*size-= 4;
}
/*:551*//*552:*/
#line 11837 "cweb/weaver.w"

{
int c,i;
for(i= 0;i<6;i++){
c= getc(fp);
if(c==EOF){
fprintf(stderr,"WARNING: Damaged audio file: %s\n",
filename);
fclose(fp);
*error= true;
return 0;
}
}
*size-= 6;
}
/*:552*//*553:*/
#line 11857 "cweb/weaver.w"

{
int i;
*bitrate= 0;
unsigned long multiplier= 1;
for(i= 0;i<2;i++){
unsigned long bitrate_tmp= 0;
if(fread(&bitrate_tmp,1,1,fp)!=1){
fprintf(stderr,"WARNING: Damaged file: %s\n",
filename);
fclose(fp);
*error= true;
return 0;
}
*bitrate+= bitrate_tmp*multiplier;
multiplier*= 256;
}


*size-= 2;
}
/*:553*//*554:*/
#line 11884 "cweb/weaver.w"

{
int c,i;
for(i= 0;i<8;i++){
c= getc(fp);
if(c==EOF){
fprintf(stderr,"WARNING: Damaged audio file: %s\n",
filename);
fclose(fp);
*error= true;
return 0;
}
}
*size-= 8;
}
/*:554*//*555:*/
#line 11904 "cweb/weaver.w"

{
returned_data= Walloc((size_t)*size);
if(returned_data==NULL){
printf("WARNING(0): Not enough memory to read file: %s.\n",
filename);
#if W_DEBUG_LEVEL >= 1
fprintf(stderr,"WARNING (1): You should increase the value of "
"W_INTERNAL_MEMORY at conf/conf.h.\n");
#endif
fclose(fp);
*error= true;
return 0;
}
fread(returned_data,*size,1,fp);
}
/*:555*//*556:*/
#line 11926 "cweb/weaver.w"

{
ALenum status;
ALuint format= 0;

alGenBuffers(1,&returned_buffer);
status= alGetError();
if(status!=AL_NO_ERROR){
fprintf(stderr,"WARNING(0)): No sound buffer could be created. "
"alGenBuffers failed. Sound may not work.\n");
Wfree(returned_data);
*error= true;
fclose(fp);
return 0;
}

if(*bitrate==8){
if(*channels==1)format= AL_FORMAT_MONO8;
else if(*channels==2)format= AL_FORMAT_STEREO8;
}else if(*bitrate==16){
if(*channels==1)format= AL_FORMAT_MONO16;
else if(*channels==2)format= AL_FORMAT_STEREO16;
}

alBufferData(returned_buffer,format,returned_data,(ALsizei)*size,
*freq);
status= alGetError();
if(status!=AL_NO_ERROR){
fprintf(stderr,"WARNING(0)): Can't pass audio to OpenAL. "
"alBufferData failed. Sound may not work.\n");
Wfree(returned_data);
alDeleteBuffers(1,&returned_buffer);
*error= true;
fclose(fp);
return 0;
}

Wfree(returned_data);
fclose(fp);
}
/*:556*/
#line 11645 "cweb/weaver.w"

return returned_buffer;
}
/*:544*/
#line 11171 "cweb/weaver.w"

/*561:*/
#line 12104 "cweb/weaver.w"

#if W_TARGET == W_WEB
static void onerror_sound(unsigned undocumented,void*snd,
int error_code){
fprintf(stderr,"WARNING (0): Couldn't load a sound file. Code %d.\n",
error_code);
#ifdef W_MULTITHREAD
pthread_mutex_lock(&(W._pending_files_mutex));
#endif
W.pending_files--;
#ifdef W_MULTITHREAD
pthread_mutex_unlock(&(W._pending_files_mutex));
#endif
}
#endif
/*:561*//*562:*/
#line 12126 "cweb/weaver.w"

#if W_TARGET == W_WEB
static void onload_sound(unsigned undocumented,void*snd,
const char*filename){
char*ext;
bool ret= true;
struct sound*my_sound= (struct sound*)snd;

ext= strrchr(filename,'.');
if(!ext){
onerror_sound(0,snd,0);
return;
}
if(!strcmp(ext,".wav")||!strcmp(ext,".WAV")){
my_sound->_data= extract_wave(filename,&(my_sound->size),
&(my_sound->freq),
&(my_sound->channels),
&(my_sound->bitrate),&ret);
}
if(ret){
onerror_sound(0,snd,1);
return;
}
my_sound->loaded= true;
#ifdef W_MULTITHREAD
pthread_mutex_lock(&(W._pending_files_mutex));
#endif
W.pending_files--;
#ifdef W_MULTITHREAD
pthread_mutex_unlock(&(W._pending_files_mutex));
#endif
}
#endif
/*:562*//*563:*/
#line 12165 "cweb/weaver.w"

#if W_TARGET == W_WEB
static void onprogress_sound(unsigned int undocumented,void*snd,
int percent){
return;
}
#endif
/*:563*//*585:*/
#line 12546 "cweb/weaver.w"

#if defined(W_MULTITHREAD) && W_TARGET == W_ELF
static void*process_sound(void*p){
char*ext;
bool ret= true;
struct _thread_file_info*file_info= (struct _thread_file_info*)p;
struct sound*my_sound= (struct sound*)(file_info->target);
ext= strrchr(file_info->filename,'.');
if(!ext){
file_info->onerror(p);
}
else if(!strcmp(ext,".wav")||!strcmp(ext,".WAV")){
my_sound->_data= extract_wave(file_info->filename,&(my_sound->size),
&(my_sound->freq),
&(my_sound->channels),
&(my_sound->bitrate),&ret);
}
if(ret){
file_info->onerror(p);
}
else{
file_info->onload(p);
}

#if W_THREAD_POOL == 0
Wfree(p);

#endif
#ifdef W_MULTITHREAD
pthread_mutex_lock(&(W._pending_files_mutex));
#endif
W.pending_files--;
#ifdef W_MULTITHREAD
pthread_mutex_unlock(&(W._pending_files_mutex));
#endif
return NULL;
}
#endif
/*:585*//*586:*/
#line 12589 "cweb/weaver.w"

#if W_TARGET == W_ELF && defined(W_MULTITHREAD)
static void*onload_sound(void*p){
struct _thread_file_info*file_info= (struct _thread_file_info*)p;
struct sound*my_sound= (struct sound*)(file_info->target);
my_sound->loaded= true;
return NULL;
}
static void*onerror_sound(void*p){
struct _thread_file_info*file_info= (struct _thread_file_info*)p;
fprintf(stderr,"Warning (0): Failed to load sound file: %s\n",
file_info->filename);
return NULL;
}
#endif
/*:586*/
#line 11172 "cweb/weaver.w"

/*513:*/
#line 11203 "cweb/weaver.w"

void _initialize_sound(void){
default_device= alcOpenDevice(NULL);
if(default_device==NULL)
fprintf(stderr,"WARNING (0): No sound device detected.\n");
/*520:*/
#line 11263 "cweb/weaver.w"

W.number_of_sound_devices= 0;
W.sound_device_name= NULL;
/*:520*//*521:*/
#line 11278 "cweb/weaver.w"

{
char*devices,*c;
int end= 0;
c= devices= (char*)alcGetString(NULL,ALC_DEFAULT_DEVICE_SPECIFIER);
while(end!=2){
if(*c=='\0'){
end++;
if(c!=devices&&*(c-1)!='\0')
W.number_of_sound_devices++;
}
else
end= 0;
c++;
}
if(W.number_of_sound_devices==0)
goto AFTER_SOUND_INITIALIZATION;
}
/*:521*//*522:*/
#line 11302 "cweb/weaver.w"

{
char*devices,*c;
int i= 0;
W.sound_device_name= (char**)Walloc(W.number_of_sound_devices*
sizeof(char*));
if(W.sound_device_name==NULL){
fprintf(stderr,"ERROR: Not enough memory. Please, increase the value"
" of W_INTERNAL_MEMORY at conf/conf.h and try to run the "
"program again.\n");
exit(1);
}
c= devices= (char*)alcGetString(NULL,ALC_DEFAULT_DEVICE_SPECIFIER);
W.sound_device_name[0]= devices;
for(;;c++){
if(*c=='\0'){
i++;
if(i<W.number_of_sound_devices)
W.sound_device_name[i]= c+1;
else
break;
}
}
}
/*:522*//*533:*/
#line 11420 "cweb/weaver.w"

{
if(default_device){

default_context= alcCreateContext(default_device,NULL);
alcMakeContextCurrent(default_context);
}
alGetError();
}
/*:533*//*535:*/
#line 11447 "cweb/weaver.w"

{
ALenum error;
if(default_device!=NULL){
alGenSources(5,default_source);
error= alGetError();
if(error!=AL_NO_ERROR){
fprintf(stderr,"WARNING(0)): No sound source could be created. "
"alGenSources failed. Sound probably won't work.\n");
}
}
}
/*:535*/
#line 11208 "cweb/weaver.w"

AFTER_SOUND_INITIALIZATION:
return;
}
/*:513*//*515:*/
#line 11222 "cweb/weaver.w"

void _finalize_sound(void){
/*523:*/
#line 11332 "cweb/weaver.w"

{
if(W.sound_device_name!=NULL)
Wfree(W.sound_device_name);
}

/*:523*//*536:*/
#line 11463 "cweb/weaver.w"

{
alDeleteSources(5,default_source);
if(default_context!=NULL)
alcDestroyContext(default_context);
}
/*:536*/
#line 11224 "cweb/weaver.w"



alcCloseDevice(default_device);
}
/*:515*//*525:*/
#line 11348 "cweb/weaver.w"

bool _select_sound_device(int position){
if(position<0||position>=W.number_of_sound_devices)
return false;


/*537:*/
#line 11475 "cweb/weaver.w"

{
alDeleteSources(5,default_source);
if(default_context!=NULL)
alcDestroyContext(default_context);
}
/*:537*/
#line 11354 "cweb/weaver.w"

alcCloseDevice(default_device);
default_device= alcOpenDevice(W.sound_device_name[position]);
return true;
}
/*:525*//*529:*/
#line 11380 "cweb/weaver.w"

int _current_sound_device(void){
int i;
char*query;
if(W.sound_device_name==NULL)
return-1;
query= (char*)alcGetString(NULL,ALC_DEFAULT_DEVICE_SPECIFIER);
for(i= 0;i<W.number_of_sound_devices;i++)
if(!strcmp(query,W.sound_device_name[i]))
return i;
return-1;
}
/*:529*//*560:*/
#line 12003 "cweb/weaver.w"

struct sound*_new_sound(char*filename){
char*complete_path;
struct sound*snd;
#if W_TARGET == W_ELF && !defined(W_MULTITHREAD)
bool ret= true;
char*ext;
#endif
#if W_TARGET == W_WEB
char dir[]= "sound/";
#elif W_DEBUG_LEVEL >= 1
char dir[]= "./sound/";
#elif W_TARGET == W_ELF
char dir[]= W_INSTALL_DATA"/sound/";
#endif
snd= (struct sound*)Walloc(sizeof(struct sound));
if(snd==NULL){
printf("WARNING(0): Not enough memory to read file: %s.\n",
filename);
#if W_DEBUG_LEVEL >= 1
fprintf(stderr,"WARNING (1): You should increase the value of "
"W_INTERNAL_MEMORY at conf/conf.h.\n");
#endif
return NULL;
}
snd->loaded= false;
complete_path= (char*)Walloc(strlen(filename)+strlen(dir)+1);
if(complete_path==NULL){
Wfree(snd);
printf("WARNING(0): Not enough memory to read file: %s.\n",
filename);
#if W_DEBUG_LEVEL >= 1
fprintf(stderr,"WARNING (1): You should increase the value of "
"W_INTERNAL_MEMORY at conf/conf.h.\n");
#endif
return NULL;
}
strcpy(complete_path,dir);
strcat(complete_path,filename);
#if W_TARGET == W_WEB || defined(W_MULTITHREAD)
#if W_TARGET == W_WEB
mkdir("sound/",0777);
#ifdef W_MULTITHREAD
pthread_mutex_lock(&(W._pending_files_mutex));
#endif
W.pending_files++;
#ifdef W_MULTITHREAD
pthread_mutex_unlock(&(W._pending_files_mutex));
#endif
emscripten_async_wget2(complete_path,complete_path,
"GET","",(void*)snd,
&onload_sound,&onerror_sound,
&onprogress_sound);
#else 
_multithread_load_file(complete_path,(void*)snd,&process_sound,
&onload_sound,&onerror_sound);
#endif
Wfree(complete_path);
return snd;
#else

ext= strrchr(filename,'.');
if(!ext){
fprintf(stderr,"WARNING (0): No file extension in %s.\n",
filename);
return NULL;
}
if(!strcmp(ext,".wav")||!strcmp(ext,".WAV")){
snd->_data= extract_wave(complete_path,&(snd->size),
&(snd->freq),&(snd->channels),
&(snd->bitrate),&ret);
}
if(ret){
Wfree(complete_path);
Wfree(snd);
return NULL;
}
Wfree(complete_path);
snd->loaded= true;
return snd;
#endif
}
/*:560*//*567:*/
#line 12191 "cweb/weaver.w"

void _play_sound(struct sound*snd){
if(!snd->loaded)return;
int i= -1;
ALenum status= AL_NO_ERROR;

do{
i++;
if(i> 4)break;
alSourcei(default_source[i],AL_BUFFER,snd->_data);
status= alGetError();
}while(status!=AL_NO_ERROR);
alSourcePlay(default_source[i]);
}
/*:567*//*571:*/
#line 12226 "cweb/weaver.w"

void _destroy_sound(struct sound*snd){




while(snd->loaded==false&&W.pending_files> 0){
#ifdef W_MULTITHREAD
sched_yield();
#elif W_TARGET == W_ELF
{
struct timespec tim;

tim.tv_sec= 0;
tim.tv_nsec= 1000000L;
nanosleep(&tim,NULL);
}
#elif W_TARGET == W_WEB
emscripten_sleep(1);
#endif
}

alDeleteBuffers(1,&(snd->_data));
Wfree(snd);
}
/*:571*//*580:*/
#line 12393 "cweb/weaver.w"

#if defined(W_MULTITHREAD) && W_TARGET == W_ELF && W_THREAD_POOL >  0
void*_file_list_thread(void*p){
struct _thread_file_info*file_info= (struct _thread_file_info*)p;
for(;;){
pthread_mutex_lock(&(file_info->mutex));
while(!file_info->valid_info&&!file_info->_kill_switch){
pthread_cond_wait(&(file_info->condition),&(file_info->mutex));
}

if(file_info->_kill_switch){
pthread_exit(NULL);
}

file_info->process(p);
file_info->valid_info= false;
pthread_mutex_unlock(&(file_info->mutex));
}
}
#endif
/*:580*//*583:*/
#line 12453 "cweb/weaver.w"

#if defined(W_MULTITHREAD) && W_TARGET == W_ELF && W_THREAD_POOL == 0
void _multithread_load_file(const char*filename,void*snd,
void*(*process)(void*),
void*(*onload)(void*),
void*(*onerror)(void*)){
int return_code;
pthread_t thread;
struct _thread_file_info*arg;

pthread_mutex_lock(&(W._pending_files_mutex));
W.pending_files++;
pthread_mutex_unlock(&(W._pending_files_mutex));
arg= (struct _thread_file_info*)Walloc(sizeof(struct _thread_file_info));
if(arg!=NULL){



strncpy(arg->filename,filename,255);
arg->target= snd;
arg->onload= onload;
arg->onerror= onerror;
arg->process= process;
arg->valid_info= true;
}
else{
return_code= pthread_create(&thread,NULL,onerror,NULL);
if(return_code!=0){
perror("Failed while trying to create a thread to read files.");
exit(1);
}
}

return_code= pthread_create(&thread,NULL,process,(void*)arg);
if(return_code!=0){
perror("Failed while trying to create a thread to read files.");
exit(1);
}
}
#endif
/*:583*//*584:*/
#line 12498 "cweb/weaver.w"

#if defined(W_MULTITHREAD) && W_TARGET == W_ELF && W_THREAD_POOL >  0
void _multithread_load_file(const char*filename,void*snd,
void*(*process)(void*),
void*(*onload)(void*),
void*(*onerror)(void*)){
int thread_number;

pthread_mutex_lock(&(W._pending_files_mutex));
W.pending_files++;
pthread_mutex_unlock(&(W._pending_files_mutex));




pthread_mutex_lock(&(_file_list_count_mutex));
thread_number= _file_list_count;
_file_list_count= (_file_list_count+1)%W_THREAD_POOL;
pthread_mutex_unlock(&(_file_list_count_mutex));





pthread_mutex_lock(&(_file_list[thread_number].struct_mutex));
while(_file_list[thread_number].valid_info==true)
sched_yield();
strncpy(_file_list[thread_number].filename,filename,255);
_file_list[thread_number].target= snd;
_file_list[thread_number].onload= onload;
_file_list[thread_number].onerror= onerror;
_file_list[thread_number].process= process;
_file_list[thread_number].valid_info= true;
pthread_mutex_unlock(&(_file_list[thread_number].struct_mutex));


pthread_cond_signal(&(_file_list[thread_number].condition));
}
#endif
/*:584*/
#line 11173 "cweb/weaver.w"

/*:508*/
