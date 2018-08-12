/*214:*/
#line 5072 "cweb/weaver.w"

#include "trie.h"
#include <stdarg.h>  

/*222:*/
#line 5222 "cweb/weaver.w"

struct _trie*_new_node(void*arena,char*string,struct _trie*parent){
int i,size= strlen(string);
struct _trie*ret;
ret= (struct _trie*)Walloc_arena(arena,sizeof(struct _trie));
if(ret==NULL)
goto no_memory_error;
ret->string= (char*)Walloc_arena(arena,size+1);
if(ret->string==NULL)
goto no_memory_error;
strncpy(ret->string,string,size);
ret->string[size]= '\0';
ret->leaf= false;
for(i= 0;i<256;i++)
ret->child[i]= NULL;
ret->parent= parent;
return ret;
no_memory_error:
fprintf(stderr,"ERROR (0): No memory enough. Please increase the value of "
"%s at conf/conf.h.\n",(arena==_user_arena)?"W_MAX_MEMORY":
"W_INTERNAL_MEMORY");
return NULL;
}
/*:222*//*223:*/
#line 5253 "cweb/weaver.w"

void _split_trie(void*arena,struct _trie**origin,char*divergence,
char*remaining_match){
struct _trie*old_way,*new_way;
int i;
old_way= _new_node(arena,divergence,*origin);
new_way= _new_node(arena,remaining_match,*origin);
for(i= 0;i<256;i++){
old_way->child[i]= (*origin)->child[i];
(*origin)->child[i]= NULL;
}
old_way->leaf= (*origin)->leaf;
(*origin)->leaf= false;
(*origin)->child[(int)*divergence]= old_way;
(*origin)->child[(int)*remaining_match]= new_way;
*divergence= '\0';
*origin= new_way;
}
/*:223*/
#line 5076 "cweb/weaver.w"

/*219:*/
#line 5136 "cweb/weaver.w"

struct _trie*_new_trie(void*arena){
int i;
struct _trie*ret;
ret= (struct _trie*)Walloc_arena(arena,sizeof(struct _trie));
if(ret==NULL)
goto no_memory_error;
ret->string= (char*)Walloc(1);
if(ret->string==NULL)
goto no_memory_error;
ret->string[0]= '\0';
ret->leaf= false;
for(i= 0;i<256;i++)
ret->child[i]= NULL;
ret->parent= NULL;
return ret;
no_memory_error:
fprintf(stderr,"ERROR: No memory enough. Please increase the value of "
"%s at conf/conf.h.\n",(arena==_user_arena)?"W_MAX_MEMORY":
"W_INTERNAL_MEMORY");
return NULL;
}
/*:219*//*221:*/
#line 5170 "cweb/weaver.w"

void _insert_trie(struct _trie*tree,void*arena,int type,char*name,...){
va_list arguments;
va_start(arguments,name);
struct _trie*current_prefix= tree;
char*match= name,*p= current_prefix->string;
while(*match!='\0'){
if(*p=='\0'){

if(current_prefix->child[(int)*match]!=NULL){
current_prefix= current_prefix->child[(int)*match];
p= current_prefix->string;
}
else{

current_prefix->child[(int)*match]= 
_new_node(arena,match,current_prefix);
current_prefix= current_prefix->child[(int)*match];
break;
}
}
else if(*p!=*match){

_split_trie(arena,&current_prefix,p,match);
break;
}
else{

p++;
match++;
}
}

current_prefix->leaf= true;
switch(type){
case INT:
current_prefix->value.integer= va_arg(arguments,int);
break;
case DOUBLE:
current_prefix->value.real= va_arg(arguments,double);
break;
default:
current_prefix->value.generic= va_arg(arguments,void*);
break;
}
}
/*:221*//*225:*/
#line 5284 "cweb/weaver.w"

bool _search_trie(struct _trie*tree,int type,char*name,...){
va_list arguments;
va_start(arguments,name);
struct _trie*current_prefix= tree;
char*match= name,*p= current_prefix->string;
while(*match!='\0'){
if(*p=='\0'){

if(current_prefix->child[(int)*match]!=NULL){
current_prefix= current_prefix->child[(int)*match];
p= current_prefix->string;
}
else
return false;
}
else if(*p==*match){
p++;
match++;
}
else
return false;
}
if(*p!='\0'||!(current_prefix->leaf))
return false;
switch(type){
int*ret;
double*ret2;
void**ret3;
case INT:
ret= va_arg(arguments,int*);
*ret= current_prefix->value.integer;
return true;
case DOUBLE:
ret2= va_arg(arguments,double*);
*ret2= current_prefix->value.real;
return true;
default:
ret3= va_arg(arguments,void**);
*ret3= current_prefix->value.generic;
return true;
}
}
/*:225*//*227:*/
#line 5337 "cweb/weaver.w"

void _remove_trie(struct _trie*tree,char*name){
struct _trie*current_prefix= tree;
char*match= name,*p= current_prefix->string;
while(*match!='\0'){
if(*p=='\0'){

if(current_prefix->child[(int)*match]!=NULL){
current_prefix= current_prefix->child[(int)*match];
p= current_prefix->string;
}
else
return;
}
else if(*p==*match){
p++;
match++;
}
else
return;
}
current_prefix->leaf= false;
}
/*:227*/
#line 5077 "cweb/weaver.w"

/*:214*/
