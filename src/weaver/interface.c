/*389:*/
#line 8606 "cweb/weaver.w"

#include "interface.h"
#include <stdarg.h>  
/*396:*/
#line 8705 "cweb/weaver.w"

void _flush_interfaces(void){
int i;
for(i= 0;i<W_MAX_INTERFACES;i++){
switch(_interfaces[_number_of_loops][i].type){




default:
_interfaces[_number_of_loops][i].type= W_NONE;
}
#ifdef W_MULTITHREAD
if(pthread_mutex_destroy(&(_interfaces[_number_of_loops][i]._mutex))!=
0)
perror("Finalizing interface mutex:");
#endif
}
}
/*:396*//*404:*/
#line 8835 "cweb/weaver.w"

struct interface*_new_interface(int type,int x,int y,int width,
int height,...){
int i;
va_list valist;
struct interface*new_interface= (struct interface*)1;
#ifdef W_MULTITHREAD
pthread_mutex_lock(&_interface_mutex);
#endif

for(i= 0;i<W_MAX_INTERFACES;i++)
if(_interfaces[_number_of_loops][i].type==W_NONE)
break;
if(i==W_MAX_INTERFACES){
#if W_DEBUG_LEVEL >  0
fprintf(stderr,"WARNING (1): Unable to create new interfaces. Please, "
"define W_MAX_INTERFACES as a value greater than %d at "
"conf/conf.h.\n",W_MAX_INTERFACES);
#endif
new_interface= NULL;
}
else{
_interfaces[_number_of_loops][i].type= type;
_interfaces[_number_of_loops][i].visible= true;
_interfaces[_number_of_loops][i].integer= 0;
_interfaces[_number_of_loops][i].stretch_x= false;
_interfaces[_number_of_loops][i].stretch_y= false;

_interfaces[_number_of_loops][i].r= 1.0;
_interfaces[_number_of_loops][i].g= 1.0;
_interfaces[_number_of_loops][i].b= 1.0;
_interfaces[_number_of_loops][i].a= 1.0;

_interfaces[_number_of_loops][i].x= (float)x;
_interfaces[_number_of_loops][i].y= (float)y;
_interfaces[_number_of_loops][i].rotation= 0.0;
_interfaces[_number_of_loops][i].width= (float)width;
_interfaces[_number_of_loops][i].height= (float)height;

_interfaces[_number_of_loops][i]._mode= GL_TRIANGLE_FAN;
#ifdef W_MULTITHREAD
if(pthread_mutex_init(&(_interfaces[_number_of_loops][i]._mutex),
NULL)!=0){
_interfaces[_number_of_loops][i].type= W_NONE;
perror("Initializing interface mutex:");
new_interface= NULL;
}
#endif
if(new_interface!=NULL){
switch(type){
case W_INTERFACE_PERIMETER:
_interfaces[_number_of_loops][i]._mode= GL_LINE_LOOP;

case W_INTERFACE_SQUARE:
va_start(valist,height);
_interfaces[_number_of_loops][i].r= va_arg(valist,double);
_interfaces[_number_of_loops][i].g= va_arg(valist,double);
_interfaces[_number_of_loops][i].b= va_arg(valist,double);
_interfaces[_number_of_loops][i].a= va_arg(valist,double);
va_end(valist);

break;
default:
;
}
/*428:*/
#line 9371 "cweb/weaver.w"

{
float nx,ny,cosine,sine,x1,y1;
nx= 2.0*((float)_interfaces[_number_of_loops][i].width);
ny= 2.0*((float)_interfaces[_number_of_loops][i].height);
cosine= cosf(_interfaces[_number_of_loops][i].rotation);
sine= sinf(_interfaces[_number_of_loops][i].rotation);
x1= (2.0*((float)_interfaces[_number_of_loops][i].x/
(float)W.width))-1.0;
y1= (2.0*((float)_interfaces[_number_of_loops][i].y/
(float)W.height))-1.0;
_interfaces[_number_of_loops][i]._transform_matrix[0]= nx*cosine/
(float)W.width;
_interfaces[_number_of_loops][i]._transform_matrix[4]= -(ny*sine)/
(float)W.width;
_interfaces[_number_of_loops][i]._transform_matrix[8]= 0.0;
_interfaces[_number_of_loops][i]._transform_matrix[12]= x1;
_interfaces[_number_of_loops][i]._transform_matrix[1]= nx*sine/
(float)W.height;
_interfaces[_number_of_loops][i]._transform_matrix[5]= ny*cosine/
(float)W.height;
_interfaces[_number_of_loops][i]._transform_matrix[9]= 0.0;
_interfaces[_number_of_loops][i]._transform_matrix[13]= y1;
_interfaces[_number_of_loops][i]._transform_matrix[2]= 0.0;
_interfaces[_number_of_loops][i]._transform_matrix[3]= 0.0;
_interfaces[_number_of_loops][i]._transform_matrix[10]= 1.0;
_interfaces[_number_of_loops][i]._transform_matrix[14]= 0.0;
_interfaces[_number_of_loops][i]._transform_matrix[3]= 0.0;
_interfaces[_number_of_loops][i]._transform_matrix[7]= 0.0;
_interfaces[_number_of_loops][i]._transform_matrix[11]= 0.0;
_interfaces[_number_of_loops][i]._transform_matrix[15]= 1.0;
}
/*:428*/
#line 8900 "cweb/weaver.w"

/*471:*/
#line 10430 "cweb/weaver.w"


_insert_interface_queue(&(_interfaces[_number_of_loops][i]));
/*:471*/
#line 8901 "cweb/weaver.w"

new_interface= &(_interfaces[_number_of_loops][i]);
}
}
#ifdef W_MULTITHREAD
pthread_mutex_unlock(&_interface_mutex);
#endif
return new_interface;
}
/*:404*//*408:*/
#line 8932 "cweb/weaver.w"

bool _destroy_interface(struct interface*inter){
int i;

for(i= 0;i<W_MAX_INTERFACES;i++)
if(&(_interfaces[_number_of_loops][i])==inter&&inter->type!=W_NONE)
break;
if(i==W_MAX_INTERFACES)
return false;
switch(_interfaces[_number_of_loops][i].type){

case W_INTERFACE_SQUARE:
case W_INTERFACE_PERIMETER:
case W_NONE:
default:
_interfaces[_number_of_loops][i].type= W_NONE;
}
/*472:*/
#line 10438 "cweb/weaver.w"


_remove_interface_queue(&(_interfaces[_number_of_loops][i]));
/*:472*/
#line 8949 "cweb/weaver.w"

#ifdef W_MULTITHREAD
if(pthread_mutex_destroy(&(_interfaces[_number_of_loops][i]._mutex))!=0){
perror("Error destroying mutex from interface:");
Wexit();
}
#endif
return true;
}
/*:408*//*412:*/
#line 8986 "cweb/weaver.w"

struct interface*_copy_interface(struct interface*inter){
int i;
struct interface*new_interface= (struct interface*)1;
#ifdef W_MULTITHREAD
pthread_mutex_lock(&_interface_mutex);
#endif

for(i= 0;i<W_MAX_INTERFACES;i++)
if(_interfaces[_number_of_loops][i].type==W_NONE)
break;
if(i==W_MAX_INTERFACES){
#if W_DEBUG_LEVEL >  0
fprintf(stderr,"WARNING (1): Not enough space for interfaces. Please, "
"increase the value of W_MAX_INTERFACES at conf/conf.h.\n");
#endif
new_interface= NULL;
}
else{

new_interface= &(_interfaces[_number_of_loops][i]);
memcpy(new_interface,inter,sizeof(struct interface));


#ifdef W_MULTITHREAD
if(pthread_mutex_init(&(_interfaces[_number_of_loops][i]._mutex),
NULL)!=0){
_interfaces[_number_of_loops][i].type= W_NONE;
perror("Initializing interface mutex:");
new_interface= NULL;
}
#endif
}
#ifdef W_MULTITHREAD
pthread_mutex_unlock(&_interface_mutex);
#endif
return new_interface;
}
/*:412*//*417:*/
#line 9110 "cweb/weaver.w"

void _move_interface(struct interface*inter,float x,float y){
#ifdef W_MULTITHREAD
pthread_mutex_lock(&(inter->_mutex));
#endif
inter->x= x;
inter->y= y;
/*429:*/
#line 9408 "cweb/weaver.w"

{
float x1,y1;
x1= (2.0*((float)inter->x/(float)W.width))-1.0;
y1= (2.0*((float)inter->y/(float)W.height))-1.0;
inter->_transform_matrix[12]= x1;
inter->_transform_matrix[13]= y1;
}
/*:429*/
#line 9117 "cweb/weaver.w"

#ifdef W_MULTITHREAD
pthread_mutex_unlock(&(inter->_mutex));
#endif
}
/*:417*//*421:*/
#line 9189 "cweb/weaver.w"

void _resize_interface(struct interface*inter,float size_x,float size_y){
#ifdef W_MULTITHREAD
pthread_mutex_lock(&(inter->_mutex));
#endif
inter->height= size_y;
inter->width= size_x;
/*430:*/
#line 9421 "cweb/weaver.w"

{
float nx,ny,cosine,sine;
nx= 2.0*((float)inter->width);
ny= 2.0*((float)inter->height);
cosine= cosf(inter->rotation);
sine= sinf(inter->rotation);
inter->_transform_matrix[0]= (nx*cosine)/(float)W.width;
inter->_transform_matrix[4]= -(ny*sine)/(float)W.width;
inter->_transform_matrix[1]= (nx*sine)/(float)W.height;
inter->_transform_matrix[5]= (ny*cosine)/(float)W.height;
}
/*:430*/
#line 9196 "cweb/weaver.w"

#ifdef W_MULTITHREAD
pthread_mutex_unlock(&(inter->_mutex));
#endif
}
/*:421*//*425:*/
#line 9270 "cweb/weaver.w"

void _rotate_interface(struct interface*inter,float rotation){
#ifdef W_MULTITHREAD
pthread_mutex_lock(&(inter->_mutex));
#endif
inter->rotation= rotation;
/*430:*/
#line 9421 "cweb/weaver.w"

{
float nx,ny,cosine,sine;
nx= 2.0*((float)inter->width);
ny= 2.0*((float)inter->height);
cosine= cosf(inter->rotation);
sine= sinf(inter->rotation);
inter->_transform_matrix[0]= (nx*cosine)/(float)W.width;
inter->_transform_matrix[4]= -(ny*sine)/(float)W.width;
inter->_transform_matrix[1]= (nx*sine)/(float)W.height;
inter->_transform_matrix[5]= (ny*cosine)/(float)W.height;
}
/*:430*/
#line 9276 "cweb/weaver.w"

#ifdef W_MULTITHREAD
pthread_mutex_unlock(&(inter->_mutex));
#endif
}
/*:425*//*432:*/
#line 9443 "cweb/weaver.w"

void _update_interface_screen_size(void){
int i,j;
float nx,ny,cosine,sine;
for(i= 0;i<_number_of_loops;i++)
for(j= 0;j<W_MAX_INTERFACES;j++){
if(_interfaces[i][j].type==W_NONE)continue;
#ifdef W_MULTITHREAD
pthread_mutex_lock(&_interfaces[i][j]._mutex);
#endif
nx= 2.0*_interfaces[i][j].width;
ny= 2.0*_interfaces[i][j].height;
cosine= cosf(_interfaces[i][j].rotation);
sine= sinf(_interfaces[i][j].rotation);
_interfaces[i][j]._transform_matrix[0]= (nx*cosine)/
(float)W.width;
_interfaces[i][j]._transform_matrix[4]= -(ny*sine)/
(float)W.width;
_interfaces[i][j]._transform_matrix[1]= (nx*sine)/
(float)W.height;
_interfaces[i][j]._transform_matrix[5]= (ny*cosine)/
(float)W.height;
#ifdef W_MULTITHREAD
pthread_mutex_unlock(&_interfaces[i][j]._mutex);
#endif
}
}
/*:432*//*464:*/
#line 10287 "cweb/weaver.w"

void _insert_interface_queue(struct interface*inter){
int begin,end,middle,tmp;
int type= inter->type;
if(_interface_queue[_number_of_loops][W_MAX_INTERFACES-1]!=NULL){
fprintf(stderr,"WARNING (0): Couldn't create new interface. You "
"should increase the value of W_MAX_INTERFACES at cont/conf.h "
"or decrease the number of inerfaces created.\n");
return;
}
begin= 0;
end= W_MAX_INTERFACES-1;
middle= (begin+end)/2;
while((_interface_queue[_number_of_loops][middle]==NULL||
_interface_queue[_number_of_loops][middle]->type!=type)&&
begin!=end){
if(_interface_queue[_number_of_loops][middle]==NULL||
_interface_queue[_number_of_loops][middle]->type<type){
tmp= (middle+end)/2;
if(tmp==end)end--;
else end= tmp;
middle= (begin+end)/2;
}
else{
tmp= (middle+begin)/2;
if(tmp==begin)begin++;
else begin= tmp;
middle= (begin+end)/2;
}
}


for(tmp= W_MAX_INTERFACES-1;tmp>=middle;tmp--)
_interface_queue[_number_of_loops][tmp]= 
_interface_queue[_number_of_loops][tmp-1];

_interface_queue[_number_of_loops][middle]= inter;
}
/*:464*//*466:*/
#line 10335 "cweb/weaver.w"

void _remove_interface_queue(struct interface*inter){
int begin,end,middle,tmp;
int type= inter->type;
begin= 0;
end= W_MAX_INTERFACES-1;
middle= (begin+end)/2;
while((_interface_queue[_number_of_loops][middle]==NULL||
_interface_queue[_number_of_loops][middle]->type!=type)
&&begin!=end){
if(_interface_queue[_number_of_loops][middle]==NULL||
_interface_queue[_number_of_loops][middle]->type<type){
tmp= (middle+end)/2;
if(tmp==end)end--;
else end= tmp;
middle= (begin+end)/2;
}
else{
tmp= (middle+begin)/2;
if(tmp==begin)begin++;
else begin= tmp;
middle= (begin+end)/2;
}
}

while(middle> 0&&_interface_queue[_number_of_loops][middle]!=NULL&&
_interface_queue[_number_of_loops][middle]->type==
_interface_queue[_number_of_loops][middle-1]->type)
middle--;
if(_interface_queue[_number_of_loops][middle]->type!=type){
#if W_DEBUG_LEVEL >= 1
fprintf(stderr,
"WARNING (1): Tried to erase a non-existent interface.\n");
#endif
return;
}


while(_interface_queue[_number_of_loops][middle]!=NULL&&
_interface_queue[_number_of_loops][middle]->type==type&&
_interface_queue[_number_of_loops][middle]!=inter)
middle++;


if(_interface_queue[_number_of_loops][middle]==inter){
while(_interface_queue[_number_of_loops][middle]!=NULL&&
middle!=W_MAX_INTERFACES-1){
_interface_queue[_number_of_loops][middle]= 
_interface_queue[_number_of_loops][middle+1];
middle++;
}
_interface_queue[_number_of_loops][W_MAX_INTERFACES-1]= NULL;
}
else{
#if W_DEBUG_LEVEL >= 1
fprintf(stderr,
"WARNING (1): Tried to erase a non-existent interface.\n");
#endif
return;
}
}
/*:466*//*468:*/
#line 10404 "cweb/weaver.w"

void _clean_interface_queue(void){
int i;
for(i= 0;i<W_MAX_INTERFACES;i++)
_interface_queue[_number_of_loops][i]= NULL;
}
/*:468*/
#line 8609 "cweb/weaver.w"

/*:389*/
