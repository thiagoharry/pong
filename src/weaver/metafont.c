/*812:*/
#line 17901 "cweb/weaver.w"

#include "weaver.h"
/*865:*/
#line 19105 "cweb/weaver.w"

#define HINT_ENDGROUP      1
/*:865*//*871:*/
#line 19205 "cweb/weaver.w"

#define NOT_DECLARED -1
#define BOOLEAN       0
#define PATH          1


#define PEN           4
#define PICTURE       5
#define TRANSFORM     6
#define PAIR          7
/*:871*//*906:*/
#line 20201 "cweb/weaver.w"

#define MACRO 8
/*:906*//*922:*/
#line 20834 "cweb/weaver.w"

#define INTERNAL 9
/*:922*/
#line 17903 "cweb/weaver.w"

/*914:*/
#line 20565 "cweb/weaver.w"

static struct token*eval(struct metafont**,struct token**);
static struct token*eval_string(struct metafont**,struct token**);
static struct token*eval_numeric(struct metafont**,struct token**);
/*:914*/
#line 17904 "cweb/weaver.w"

/*815:*/
#line 17919 "cweb/weaver.w"


/*:815*//*819:*/
#line 17955 "cweb/weaver.w"

static void*metafont_arena;
/*:819*//*824:*/
#line 18012 "cweb/weaver.w"

struct metafont{
char filename[256];
FILE*fp;
char buffer[4096];
int buffer_position;
int line;
bool error;
struct metafont*parent;
/*838:*/
#line 18521 "cweb/weaver.w"

struct token*pending_tokens,*past_tokens;
/*:838*//*847:*/
#line 18704 "cweb/weaver.w"

struct _trie*internal_quantities;
/*:847*//*853:*/
#line 18916 "cweb/weaver.w"

char*everyjob_token_name;
/*:853*//*862:*/
#line 19087 "cweb/weaver.w"

int hint;
/*:862*//*872:*/
#line 19223 "cweb/weaver.w"

struct _trie*variable_types;
/*:872*//*874:*/
#line 19240 "cweb/weaver.w"

struct _trie*vars[8];
/*:874*//*878:*/
#line 19317 "cweb/weaver.w"

struct _trie*delimiters;
/*:878*//*883:*/
#line 19409 "cweb/weaver.w"

struct _trie*outer_tokens;
/*:883*//*887:*/
#line 19542 "cweb/weaver.w"

struct _trie*def,*vardef,*primarydef,*secondarydef,*tertiarydef;
/*:887*//*898:*/
#line 19896 "cweb/weaver.w"

struct _trie*macros;
/*:898*/
#line 18021 "cweb/weaver.w"

};
/*:824*//*833:*/
#line 18259 "cweb/weaver.w"


#define NUMERIC 1
#define STRING  2
#define SYMBOL  3
struct token{
int type;
float value;
char*name;
/*925:*/
#line 20991 "cweb/weaver.w"

bool deterministic;
int known;
/*:925*//*947:*/
#line 21440 "cweb/weaver.w"

float value2;
/*:947*/
#line 18268 "cweb/weaver.w"

struct token*prev,*next;
};
/*:833*//*890:*/
#line 19599 "cweb/weaver.w"

static struct _trie*primitive_sparks;
/*:890*//*896:*/
#line 19871 "cweb/weaver.w"


#define PRIMARY    4
#define SECONDARY  5
#define TERTIARY   7
#define EXPR       8
#define SUFFIX     9
#define TEXT      10
/*:896*//*897:*/
#line 19886 "cweb/weaver.w"

struct macro{
struct token*parameters;
struct token*replacement_text;
};
/*:897*//*919:*/
#line 20717 "cweb/weaver.w"

struct string_variable{
char*name;
bool deterministic;
};
/*:919*//*946:*/
#line 21431 "cweb/weaver.w"



/*:946*/
#line 17905 "cweb/weaver.w"

/*816:*/
#line 17923 "cweb/weaver.w"


/*:816*//*828:*/
#line 18098 "cweb/weaver.w"

char read_char(struct metafont*mf){
char ret;
size_t size;
while(mf->parent!=NULL)
mf= mf->parent;
ret= mf->buffer[mf->buffer_position];
if(ret!='\0'){
mf->buffer_position++;
}
else if(mf->fp!=NULL){
size= fread(mf->buffer,1,4095,mf->fp);
mf->buffer[size]= '\0';
if(size!=4095){
fclose(mf->fp);
mf->fp= NULL;
}
mf->buffer_position= 0;
ret= mf->buffer[mf->buffer_position];
if(ret!='\0')
mf->buffer_position++;
}
else
return'\0';

if(ret=='\n')
mf->line++;
return ret;
}
/*:828*//*829:*/
#line 18133 "cweb/weaver.w"

char peek_char(struct metafont*mf){
char ret;
size_t size;
while(mf->parent!=NULL)
mf= mf->parent;
ret= mf->buffer[mf->buffer_position];
if(ret=='\0'){
if(mf->fp!=NULL){
size= fread(mf->buffer,1,4095,mf->fp);
mf->buffer[size]= '\0';
if(size!=4095){
fclose(mf->fp);
mf->fp= NULL;
}
mf->buffer_position= 0;
ret= mf->buffer[mf->buffer_position];
}
else
return'\0';
}
return ret;
}
/*:829*//*830:*/
#line 18163 "cweb/weaver.w"

void mf_error(struct metafont*mf,char*message){
while(mf->parent!=NULL)
mf= mf->parent;
if(!mf->error){
fprintf(stderr,"ERROR: Metafont: %s:%d: %s\n",
mf->filename,mf->line,message);
mf->error= true;

if(mf->fp!=NULL){
fclose(mf->fp);
mf->fp= NULL;
}
mf->buffer_position= 0;
mf->buffer[mf->buffer_position]= '\0';
}
}
/*:830*//*831:*/
#line 18184 "cweb/weaver.w"

void mf_end(struct metafont*mf){

while(mf->parent!=NULL)
mf= mf->parent;
if(mf->fp!=NULL){
fclose(mf->fp);
mf->fp= NULL;
}
mf->buffer_position= 0;
mf->buffer[mf->buffer_position]= '\0';
/*860:*/
#line 19050 "cweb/weaver.w"

if(mf->parent!=NULL){
mf_error(mf,"A group begun and never ended.");
}
/*:860*/
#line 18195 "cweb/weaver.w"

}
/*:831*//*834:*/
#line 18284 "cweb/weaver.w"

static struct token*new_token(int type,float value,char*name,
void*memory_arena){
struct token*token;
token= (struct token*)Walloc_arena(memory_arena,sizeof(struct token));
if(token==NULL)
goto error_no_memory;
token->type= type;
token->value= value;
if(name!=NULL){
token->name= Walloc_arena(memory_arena,strlen(name)+1);
if(token->name==NULL)
goto error_no_memory;
strcpy(token->name,name);
}
else
token->name= name;
token->prev= token->next= NULL;
/*926:*/
#line 20999 "cweb/weaver.w"

token->deterministic= true;
token->known= 0;
/*:926*//*948:*/
#line 21446 "cweb/weaver.w"

token->value2= 0.0;
/*:948*/
#line 18302 "cweb/weaver.w"

return token;
error_no_memory:
fprintf(stderr,"ERROR (0): Not enough memory to parse METAFONT "
"source. Please, increase the value of %s "
"at conf/conf.h.\n",
(memory_arena==_user_arena)?"W_MAX_MEMORY":
"W_INTERNAL_MEMORY");
return NULL;
}
#define new_token_number(a) new_token(NUMERIC, a, NULL, _internal_arena)
#define new_token_string(a) new_token(STRING, 0.0, a, _internal_arena)
#define new_token_symbol(a) new_token(SYMBOL, 0.0, a, _internal_arena)
/*:834*//*835:*/
#line 18323 "cweb/weaver.w"

static struct token*next_token(struct metafont*mf){
char buffer[512];
int buffer_position= 0,number_of_dots= 0;
char current_char,next_char;
char family[56];
bool valid_char;
start:
current_char= read_char(mf);
switch(current_char){
case'\0':return NULL;
case' ':case'\n':goto start;
case'.':
next_char= peek_char(mf);
if(next_char=='.'){
strcpy(family,".");
break;
}
else if(isdigit(next_char))
goto numeric;
else
goto start;
case'%':
while(current_char!='\n'&&current_char!='\0')
current_char= read_char(mf);
goto start;
case'0':case'1':case'2':case'3':case'4':case'5':
case'6':case'7':case'8':case'9':
{
numeric:
for(;;){
buffer[buffer_position]= current_char;
buffer_position= (buffer_position+1)%512;
if(current_char=='.')
number_of_dots++;
next_char= peek_char(mf);
if((next_char=='.'&&number_of_dots==1)||
(next_char!='.'&&!isdigit(next_char))){
buffer[buffer_position]= '\0';
return new_token_number(atof(buffer));
}
current_char= read_char(mf);
}
}
case'"':
current_char= read_char(mf);
while(current_char!='"'&&current_char!='\0'){
if(current_char=='\n'){
mf_error(mf,"Incomplete string. "
"Strings should finish on the same line"
" as they began.");
return NULL;
}
buffer[buffer_position]= current_char;
buffer_position= (buffer_position+1)%512;
current_char= read_char(mf);
}
buffer[buffer_position]= '\0';
return new_token_string(buffer);
case'(':case')':case',':case';':
buffer[buffer_position]= current_char;
buffer_position= (buffer_position+1)%512;
buffer[buffer_position]= '\0';
return new_token_symbol(buffer);
case'a':case'b':case'c':case'd':case'e':case'f':case'g':
case'h':case'i':case'j':case'k':case'l':case'm':case'n':
case'o':case'p':case'q':case'r':case's':case't':case'u':
case'v':case'w':case'x':case'y':case'z':case'_':case'A':
case'B':case'C':case'D':case'E':case'F':case'G':case'H':
case'I':case'J':case'K':case'L':case'M':case'N':case'O':
case'P':case'Q':case'R':case'S':case'T':case'U':case'V':
case'W':case'X':case'Y':case'Z':
strcpy(family,"abcdefghijklmnopqrstuvwxyz_ABCDEFGHIJKLMNOPQRSTUVWXYZ");
break;
case'<':case'=':case'>':case':':case'|':
strcpy(family,"<=>:|");
break;
case'`':case'\'':
strcpy(family,"`'");
break;
case'+':case'-':
strcpy(family,"+-");
break;
case'/':case'*':case'\\':
strcpy(family,"/*\\");
break;
case'!':case'?':
strcpy(family,"!?");
break;
case'#':case'&':case'@':case'$':
strcpy(family,"#&@$");
break;
case'[':
strcpy(family,"[");
break;
case']':
strcpy(family,"]");
break;
case'{':case'}':
strcpy(family,"{}");
break;
case'~':case'^':
strcpy(family,"~^");
break;
default:
mf_error(mf,"Text line contains an invalid character.");
return NULL;
}

do{
char*c= family;
buffer[buffer_position]= current_char;
buffer_position= (buffer_position+1)%512;
next_char= peek_char(mf);
valid_char= false;
while(*c!='\0'){
if(*c==next_char){
valid_char= true;
current_char= read_char(mf);
break;
}
c++;
}
}while(valid_char);
buffer[buffer_position]= '\0';
return new_token_symbol(buffer);
}
/*:835*//*836:*/
#line 18458 "cweb/weaver.w"


static void concat_token(struct token*before,struct token*after){
if(after==NULL)
return;
while(before->next!=NULL)
before= before->next;
before->next= after;
after->prev= before;
}
/*:836*//*840:*/
#line 18537 "cweb/weaver.w"

/*844:*/
#line 18673 "cweb/weaver.w"

bool expand_token(struct metafont*mf,struct token**first_token){

return false;
}
/*:844*/
#line 18538 "cweb/weaver.w"

static struct token*get_token(struct metafont*mf){
struct token*first_token= NULL;

if(mf->pending_tokens){
first_token= mf->pending_tokens;
first_token->next->prev= NULL;
mf->pending_tokens= first_token->next;
first_token->next= NULL;
}
else{
first_token= next_token(mf);
}
while(expand_token(mf,&first_token));
return first_token;
}
/*:840*//*841:*/
#line 18558 "cweb/weaver.w"

static struct token*get_statement(struct metafont*mf){
struct token*first_token,*current_token;
first_token= get_token(mf);
current_token= first_token;

if(current_token==NULL||
(current_token->type==SYMBOL&&
(!strcmp(current_token->name,"end")||
!strcmp(current_token->name,"dump")))){
mf_end(mf);
return NULL;
}

while(1){
if(current_token->type==SYMBOL&&
!strcmp(current_token->name,";"))
break;

if(current_token->next==NULL){
if(mf->pending_tokens==NULL)
current_token->next= next_token(mf);
else{
current_token->next= mf->pending_tokens;
mf->pending_tokens= mf->pending_tokens->next;
current_token->next->next= NULL;
}
}
if(current_token->next==NULL)
goto source_incomplete_or_with_error;
current_token->next->prev= current_token;
current_token= current_token->next;
while(expand_token(mf,&current_token));
}

if(current_token->next!=NULL){
current_token->next->prev= NULL;
if(mf->pending_tokens==NULL)
mf->pending_tokens= current_token->next;
else
concat_token(mf->pending_tokens,current_token->next);
}
current_token->next= NULL;
/*869:*/
#line 19167 "cweb/weaver.w"

{
int count= 0;
struct token*aux= current_token;
while(aux!=NULL){
if(aux->type==SYMBOL&&
!strcmp(aux->name,"endgroup")){
mf->hint= HINT_ENDGROUP;
}
else if(aux->type==SYMBOL&&
!strcmp(aux->name,"begingroup")){
mf->hint= 0;
}
aux= aux->prev;
count++;
}
}
/*:869*/
#line 18601 "cweb/weaver.w"

return first_token;
source_incomplete_or_with_error:
mf_error(mf,"Source with error or incomplete, aborting.");
return NULL;
}
/*:841*//*850:*/
#line 18844 "cweb/weaver.w"

static struct token*symbolic_token_list(struct metafont*mf,
struct token**token){
struct token*first_token= *token,*current_token;
current_token= first_token;
while(1){

if(current_token==NULL||current_token->type!=SYMBOL){
mf_error(mf,"Missing symbolic token.");
return NULL;
}


if(current_token->next==NULL||
current_token->next->type!=SYMBOL||
strcmp(current_token->next->name,",")){
*token= current_token->next;
current_token->next= NULL;
return first_token;
}


if(current_token->next->next!=NULL)
current_token->next->next->prev= current_token;
current_token->next= current_token->next->next;
current_token= current_token->next;
}
}
/*:850*//*881:*/
#line 19375 "cweb/weaver.w"

static char*delimiter(struct metafont*mf,struct token*tok){
char*result= NULL;
while(mf!=NULL){
bool ret= _search_trie(mf->delimiters,VOID_P,tok->name,
(void*)&result);
if(ret){
return result;
}
mf= mf->parent;
}
return NULL;
}
/*:881*//*889:*/
#line 19556 "cweb/weaver.w"

static bool is_tag(struct metafont*mf,struct token*token){
struct metafont*scope= mf;
void*dummy;
if(token==NULL)
return false;
while(scope!=NULL){
if(_search_trie(scope->variable_types,VOID_P,
token->name,&dummy))
return true;
if(_search_trie(scope->internal_quantities,VOID_P,
token->name,&dummy))
return true;
if(_search_trie(scope->def,VOID_P,
token->name,&dummy))
return false;
if(_search_trie(scope->vardef,VOID_P,
token->name,&dummy))
return true;
if(_search_trie(scope->primarydef,VOID_P,
token->name,&dummy))
return false;
if(_search_trie(scope->secondarydef,VOID_P,
token->name,&dummy))
return false;
if(_search_trie(scope->tertiarydef,VOID_P,
token->name,&dummy))
return false;
scope= scope->parent;
}
if(_search_trie(primitive_sparks,VOID_P,
token->name,&dummy))
return false;
else
return true;
}
/*:889*//*892:*/
#line 19644 "cweb/weaver.w"

void declared_variable(struct metafont*mf,struct token**token,
char*dst,int dst_size){
struct token*first_token= *token,*current_token;
dst[0]= '\0';

if(first_token==NULL||first_token->type!=SYMBOL){
mf_error(mf,"Missing symbolic token.");
return;
}
current_token= first_token->next;
strncpy(dst,first_token->name,dst_size-1);
strcat(dst," ");
dst_size-= (strlen(first_token->name)+1);
while(current_token!=NULL){

if(current_token->type!=SYMBOL||
(!is_tag(mf,current_token)&&
(strcmp(current_token->name,"[")&&
strcmp(current_token->name,"]")))){
current_token= current_token->prev;
break;
}

if(!strcmp(current_token->name,"[")&&
(current_token->next==NULL||
strcmp(current_token->next->name,"]"))){
mf_error(mf,"Illegal suffix at token declaration.");
current_token= current_token->prev;
break;
}

if(!strcmp(current_token->name,"]")&&
(current_token->prev==NULL||
strcmp(current_token->prev->name,"["))){
mf_error(mf,"Illegal suffix at token declaration.");
current_token= current_token->prev;
break;
}

strncpy(dst,first_token->name,dst_size-1);
strcat(dst," ");
dst_size-= (strlen(current_token->name)+1);
current_token= current_token->next;
}
dst[dst_size-1]= '\0';
if(current_token==NULL&&first_token->prev==NULL)
*token= NULL;
else if(current_token==NULL){
first_token->prev->next= NULL;
*token= NULL;
}
else if(first_token->prev==NULL){
*token= current_token->next;
current_token->prev= NULL;
}
else{
*token= current_token->next;
current_token->next->prev= first_token->prev;
first_token->prev->next= current_token->next;
}
return;
}
/*:892*//*900:*/
#line 19917 "cweb/weaver.w"

static struct token*delimited_parameters(struct metafont*mf,
struct token**token,
void*arena){
struct token*tok= *token,*parameter_list;
struct token*result= NULL,*last_result= NULL;
int type= NOT_DECLARED;

while(tok!=NULL&&tok->type==SYMBOL&&!strcmp(tok->name,"(")){
tok= tok->next;
if(tok==NULL||tok->type!=SYMBOL){
mf_error(mf,"Missing symbolic token.");
return NULL;
}
if(!strcmp(tok->name,"expr"))
type= EXPR;
else if(!strcmp(tok->name,"suffix"))
type= SUFFIX;
else if(!strcmp(tok->name,"text"))
type= TEXT;
else{
mf_error(mf,"Missing paramaeter type.");
return NULL;
}
tok= tok->next;
parameter_list= symbolic_token_list(mf,&tok);
while(parameter_list!=NULL){
char*name= (char*)
Walloc_arena(arena,
strlen(parameter_list->name)+1);
if(name==NULL)goto error_no_memory;
if(last_result!=NULL){
last_result->next= new_token(type,0.0,name,arena);
if(last_result->next==NULL)
return NULL;
last_result->next->prev= last_result;
last_result= last_result->next;
last_result->next= NULL;
}
else{
result= new_token(type,0.0,name,arena);
if(result==NULL)
return NULL;
last_result= result;
}
parameter_list= parameter_list->next;
}
if(tok==NULL||tok->type!=SYMBOL||strcmp(tok->name,")")){
mf_error(mf,"Missing ')' closing parameters.");
return NULL;
}
tok= tok->next;
}
*token= tok;
return result;
error_no_memory:
fprintf(stderr,"ERROR: Not enough memory. Please, increase"
" the value of W_%s_MEMORY at conf/conf.h\n",
(arena==_user_arena)?"MAX":"INTERNAL");
return NULL;
}
/*:900*//*901:*/
#line 19982 "cweb/weaver.w"

static struct token*undelimited_parameters(struct metafont*mf,
struct token**token,
void*arena){
struct token*tok= *token;
int type= NOT_DECLARED;
if(tok!=NULL&&tok->type==SYMBOL){
if(!strcmp(tok->name,"primary"))
type= PRIMARY;
else if(!strcmp(tok->name,"secondary"))
type= SECONDARY;
else if(!strcmp(tok->name,"tertiary"))
type= TERTIARY;
else if(!strcmp(tok->name,"tertiary"))
type= TERTIARY;
else if(!strcmp(tok->name,"expr"))
type= EXPR;
else if(!strcmp(tok->name,"suffix"))
type= SUFFIX;
else if(!strcmp(tok->name,"text"))
type= TEXT;
else return NULL;
}
tok= tok->next;
if(tok==NULL){
mf_error(mf,"Missing symbolic token.");
return NULL;
}
*token= tok->next;
return new_token(type,0.0,tok->name,arena);
}
/*:901*//*902:*/
#line 20036 "cweb/weaver.w"

static struct token*replacement_text(struct metafont*mf,struct token**token,
void*arena){
struct token*tok= *token,*result= NULL,*current_token= NULL;
int depth= 0,dummy;
for(;;){
if(tok==NULL||(depth<=0&&tok->type==SYMBOL&&
!strcmp(tok->name,"enddef")))
break;

if(tok->type==SYMBOL&&_search_trie(mf->outer_tokens,INT,
tok->name,&dummy)){
mf_error(mf,"Forbidden token at macro.");
return NULL;
}

if(tok->type==SYMBOL&&
(!strcmp(tok->name,"def")||!strcmp(tok->name,"vardef")||
!strcmp(tok->name,"primarydef")||
!strcmp(tok->name,"secondarydef")||
!strcmp(tok->name,"tertiarydef")))
depth++;
else if(tok->type==SYMBOL&&!strcmp(tok->name,"enddef"))
depth--;

if(result!=NULL){
current_token->next= new_token(tok->type,tok->value,
tok->name,arena);
if(current_token->next==NULL)
goto end_of_function;
current_token->next->prev= current_token;
current_token= current_token->next;
}
else{
result= new_token(tok->type,tok->value,tok->name,arena);
if(result==NULL)
goto end_of_function;
current_token= result;
}
if(tok->next==NULL){
tok->next= get_statement(mf);
if(tok->next!=NULL){
tok->next->prev= tok;
}
}
tok= tok->next;
}
end_of_function:
if(tok!=NULL){
if(tok->next==NULL){
tok->next= get_statement(mf);
if(tok->next!=NULL)
tok->next->prev= tok;
}
*token= tok->next;
}
else
*token= tok;

mf->hint= 0;
return result;
}
/*:902*//*920:*/
#line 20727 "cweb/weaver.w"

void new_string_variable(char*var_name,char*string,bool deterministic,
struct metafont*mf){
struct metafont*scope= mf;
int current_type= -1;
void*current_arena;
struct string_variable*new_variable;
while(scope!=NULL){
if(_search_trie(scope->variable_types,INT,var_name,&current_type))
break;
scope= scope->parent;
}

switch(current_type){
case BOOLEAN:
mf_error(mf,"Equation cannot be performed (boolean=string).");
return;
case PATH:
mf_error(mf,"Equation cannot be performed (path=string).");
return;
case STRING:

break;
case PEN:
mf_error(mf,"Equation cannot be performed (pen=string).");
return;
case PICTURE:
mf_error(mf,"Equation cannot be performed (picture=string).");
return;
case TRANSFORM:
mf_error(mf,"Equation cannot be performed (transform=string).");
return;
case PAIR:
mf_error(mf,"Equation cannot be performed (pair=string).");
return;
default:
mf_error(mf,"Equation cannot be performed (numeric=string).");
return;
}

if(scope->parent==NULL)
current_arena= _user_arena;
else
current_arena= metafont_arena;

new_variable= (struct string_variable*)
Walloc_arena(current_arena,
sizeof(struct string_variable));
if(new_variable==NULL)
goto error_no_memory;
new_variable->name= (char*)Walloc_arena(current_arena,
strlen(string)+1);
if(new_variable->name==NULL)
goto error_no_memory;
strcpy(new_variable->name,string);
new_variable->deterministic= deterministic;
_insert_trie(scope->vars[STRING],current_arena,VOID_P,string,
(void*)new_variable);
return;
error_no_memory:
fprintf(stderr,"ERROR: Not enough memory. Please, increase "
"the value of W_%s_MEMORY at conf/conf.h.\n",
(current_arena==_user_arena)?"MAX":"INTERNAL");
exit(1);
}
/*:920*//*923:*/
#line 20839 "cweb/weaver.w"

void variable(struct metafont**mf,struct token**token,
char*dst,int dst_size,int*type){
struct metafont*scope= *mf;
bool internal= false;
float dummy;
char type_name[1024];
dst[0]= '\0';
type_name[0]= '\0';
int pos= 0,type_pos= 0,original_size= dst_size;
if(*token==NULL||(*token)->type!=SYMBOL)
return;

while((*mf)->parent!=NULL){
internal= _search_trie((*mf)->internal_quantities,DOUBLE,
(*token)->name,&dummy);
if(internal)
break;
*mf= (*mf)->parent;
}
internal= _search_trie((*mf)->internal_quantities,DOUBLE,
(*token)->name,&dummy);
if(internal){
strncpy(dst,(*token)->name,dst_size);
dst[dst_size-1]= '\0';
if((*token)->prev!=NULL)
(*token)->prev->next= (*token)->next;
if((*token)->next!=NULL)
(*token)->next->prev= (*token)->prev;
*token= (*token)->next;
*type= INTERNAL;
strncpy(type_name,dst,1023);
return;
}

if(!is_tag(*mf,*token)){
*type= NOT_DECLARED;
return;
}

strncat(dst,(*token)->name,dst_size);
pos+= strlen((*token)->name);
dst_size-= pos;
strncat(dst," ",dst_size);
pos++;
dst_size-= 1;
*token= (*token)->next;
while(*token!=NULL){


if((*token)->type==SYMBOL&&
(!is_tag(*mf,*token)&&
strcmp((*token)->name,"[")&&
strcmp((*token)->name,"]"))){
break;
}


if((*token)->type==SYMBOL&&!strcmp((*token)->name,"[")){
struct token*result;
*token= (*token)->next;
result= eval_numeric(mf,token);
if(result==NULL||result->type!=NUMERIC){
mf_error(*mf,"Undefined numeric expression after '['.");
*type= NOT_DECLARED;
return;
}
if(*token==NULL||(*token)->type!=SYMBOL||
strcmp((*token)->name,"]")){
mf_error(*mf,"Missing ']' after '[' in variable name.");
*type= NOT_DECLARED;
return;
}
*token= (*token)->next;

snprintf(&(dst[pos]),dst_size,"%f ",result->value);
pos= strlen(dst);
dst_size= original_size-pos;
strncat(type_name,"[ ] ",1023-type_pos);
type_pos+= 4;
continue;
}

if((*token)->type==SYMBOL){
int size= strlen((*token)->name);
strncat(dst,(*token)->name,dst_size);
pos+= size;
dst_size-= pos;
strncat(dst," ",dst_size);
pos++;
dst_size-= 1;
strncat(type_name,(*token)->name,1024-type_pos);
type_pos+= size;
*token= (*token)->next;
continue;
}

if((*token)->type==NUMERIC){
snprintf(&(dst[pos]),dst_size,"%f ",(*token)->value);
pos= strlen(dst);
dst_size= original_size-pos;
strncat(type_name,"[ ] ",1023-type_pos);
type_pos+= 4;
continue;
}


break;
}

*type= NUMERIC;
while(scope!=NULL){
bool found= false;
found= _search_trie(scope->variable_types,INT,type_name,type);
if(found)
break;
scope= scope->parent;
}

if(dst_size> 0)
dst[pos-1]= '\0';
else
dst[original_size-1]= '\0';
return;
}
/*:923*//*924:*/
#line 20970 "cweb/weaver.w"

struct token*read_var(char*var_name,int type,struct metafont*mf){
struct metafont*scope= mf;
struct token*ret= NULL;
while(scope!=NULL){
struct string_variable*var= NULL;
_search_trie(scope->vars[type],VOID_P,var_name,(void*)&var);
if(var!=NULL){
ret= new_token_string(var->name);
ret->deterministic= var->deterministic;
return ret;
}
scope= scope->parent;
}
return NULL;
}
/*:924*//*940:*/
#line 21247 "cweb/weaver.w"

void number2utf8(uint32_t number,char*result){
int endian_probe_x= 1;
char*number_probe= (char*)&number;
char*little_endian= (char*)&endian_probe_x;
if(number<=127){
result[0]= (char)number;
result[1]= '\0';
return;
}
if(number<=2047){
if(*little_endian){
result[0]= number_probe[1];
result[1]= number_probe[0];
result[2]= '\0';
return;
}
else{
result[0]= number_probe[2];
result[1]= number_probe[3];
result[2]= '\0';
return;
}
}
if(number<=65535){
if(*little_endian){
result[0]= number_probe[2];
result[1]= number_probe[1];
result[2]= number_probe[0];
result[3]= '\0';
return;
}
else{
result[0]= number_probe[1];
result[1]= number_probe[2];
result[2]= number_probe[3];
result[3]= '\0';
return;
}
}
if(*little_endian){
result[0]= number_probe[3];
result[1]= number_probe[2];
result[2]= number_probe[1];
result[3]= number_probe[0];
result[4]= '\0';
return;
}
else{
result[0]= number_probe[0];
result[1]= number_probe[1];
result[2]= number_probe[2];
result[3]= number_probe[3];
result[4]= '\0';
return;
}
}
/*:940*//*941:*/
#line 21313 "cweb/weaver.w"

struct token*numeric_primary(struct metafont**mf,struct token**token){
struct token*result;
if(token==NULL){
mf_error(*mf,"ERROR: Missing numeric primary.");
return NULL;
}
if((*token)->type==NUMERIC){
result= new_token_number((*token)->value);
result->next= (*token)->next;
if((*token)->next!=NULL)
(*token)->next->prev= result;
result->prev= (*token)->prev;
if((*token)->prev!=NULL)
(*token)->prev->next= result;
*token= (*token)->next;
return result;
}
mf_error(*mf,"ERROR: Unknown numeric primary.");
return NULL;
}
/*:941*//*949:*/
#line 21462 "cweb/weaver.w"

struct token*pair_primary(struct metafont**mf,struct token**token){
struct token*result,*tok= *token;
bool deterministic= true;
if(tok==NULL){
mf_error(*mf,"ERROR: Missing pair primary.");
return NULL;
}
if(tok->type==SYMBOL&&!strcmp(tok->name,"(")&&
tok->next!=NULL&&(tok->next->type!=SYMBOL||
strcmp(tok->next->name,"("))){
struct token*n1,*n2;
tok= tok->next;
if(tok==NULL){
mf_error(*mf,"Missing numeric expression.");
return NULL;
}
n1= eval_numeric(mf,&tok);
if(n1==NULL)
return NULL;
deterministic= deterministic&&n1->deterministic;
if(n1->type!=NUMERIC){
mf_error(*mf,"Unknown numeric expression result.");
return NULL;
}
if(tok==NULL||tok->type!=SYMBOL||strcmp(tok->name,",")){
mf_error(*mf,"Missing ',' at pair.");
return NULL;
}
tok= tok->next;
if(tok==NULL){
mf_error(*mf,"Missing numeric expression.");
return NULL;
}
n2= eval_numeric(mf,&tok);
if(n2==NULL)
return NULL;
deterministic= deterministic&&n2->deterministic;
if(n2->type!=NUMERIC){
mf_error(*mf,"Unknown numeric expression result.");
return NULL;
}
if(tok==NULL||tok->type!=SYMBOL||strcmp(tok->name,")")){
mf_error(*mf,"Missing ')' at pair.");
return NULL;
}
result= new_token_number(n1->value);
result->type= PAIR;
result->deterministic= deterministic;
result->value2= n2->value;
if((*token)->prev!=NULL)
(*token)->prev->next= tok->next;
if(tok->next!=NULL)
tok->next->prev= (*token)->prev;
*token= tok->next;
return result;
}
mf_error(*mf,"ERROR: Unknown numeric primary.");
return NULL;
}
/*:949*/
#line 17906 "cweb/weaver.w"

/*915:*/
#line 20571 "cweb/weaver.w"

/*921:*/
#line 20816 "cweb/weaver.w"

static struct token*eval_numeric(struct metafont**mf,
struct token**expression){
struct token*ret= *expression;
if(ret->next!=NULL)
ret->next->prev= ret->prev;
if(ret->prev!=NULL)
ret->prev->next= ret->next;
*expression= ret->next;
return ret;
}
/*:921*/
#line 20572 "cweb/weaver.w"

/*916:*/
#line 20644 "cweb/weaver.w"

static struct token*eval_string(struct metafont**mf,
struct token**expression){
bool delimited= false;
struct token*current_token= *expression;
char*delim= delimiter(*mf,*expression);
if(delim!=NULL){
current_token= current_token->next;
delimited= true;
}

while(current_token!=NULL&&
((delimited&&strcmp(current_token->name,delim))||
(!delimited&&strcmp(current_token->name,";")))){
/*927:*/
#line 21007 "cweb/weaver.w"

if(current_token->type==SYMBOL){
char variable_name[1024];
int type= NOT_DECLARED;
struct token*replacement;
variable(mf,&current_token,variable_name,1024,&type);
if(type!=NOT_DECLARED){

if(type!=STRING){
mf_error(*mf,"Variable isn't a string.");
return NULL;
}
replacement= read_var(current_token->name,type,*mf);
if(replacement==NULL)
current_token->known= -1;
else{
replacement->prev= current_token->prev;
replacement->next= current_token->next;
if(current_token->prev!=NULL)
current_token->prev->next= replacement;
else
*expression= replacement;
if(current_token->next!=NULL)
current_token->next->prev= replacement;
}
if(replacement!=NULL){
current_token= replacement;
continue;
}
}
}
/*:927*//*930:*/
#line 21052 "cweb/weaver.w"

if(current_token->type==SYMBOL&&
!strcmp(current_token->name,"jobname")){
struct token*jobname= new_token_string((*mf)->filename);
if(jobname==NULL)
goto error_no_memory_internal;
jobname->prev= current_token->prev;
jobname->next= current_token->next;
current_token= jobname;
if(current_token->prev!=NULL)
current_token->prev->next= current_token;
else
*expression= current_token;
if(current_token->next!=NULL)
current_token->next->prev= NULL;
}
/*:930*//*932:*/
#line 21077 "cweb/weaver.w"

{
char*current_delim= delimiter(*mf,current_token);
if(current_delim!=NULL){
eval_string(mf,&current_token);
}
}
/*:932*//*934:*/
#line 21099 "cweb/weaver.w"

if(current_token->type==SYMBOL&&
!strcmp(current_token->name,"begingroup")){
if(current_token->prev!=NULL){
current_token->prev->next= NULL;
current_token->prev= NULL;
}
Wbreakpoint_arena(metafont_arena);
*mf= _new_metafont(*mf,(*mf)->filename);
(*mf)->past_tokens= *expression;
(*mf)->pending_tokens= current_token->next;
if(current_token->next!=NULL)
concat_token((*mf)->pending_tokens,
(*mf)->parent->pending_tokens);
else
(*mf)->pending_tokens= (*mf)->parent->pending_tokens;
(*mf)->parent->pending_tokens= NULL;

return NULL;
}
/*:934*//*936:*/
#line 21126 "cweb/weaver.w"

if(current_token->type==SYMBOL&&
!strcmp(current_token->name,"readstring")){
struct token*token;
char*buffer= NULL,*begin;
size_t size;
if(getline(&buffer,&size,stdin)==-1||buffer==NULL){
fprintf(stderr,"ERROR: Not enough memory.\n");
exit(1);
}
begin= buffer;
while(isspace(*begin))
begin++;
while(size!=0&&(buffer[size]=='\n'||isspace(buffer[size])))
size--;
buffer[size+1]= '\0';
token= new_token_string(begin);
free(buffer);
token->next= current_token->next;
token->prev= current_token->prev;
if(token->prev==NULL)
*expression= token;
else
token->prev->next= token;
if(token->next!=NULL)
token->next->prev= token;
}
/*:936*//*938:*/
#line 21162 "cweb/weaver.w"

if(current_token->type==SYMBOL&&
!strcmp(current_token->name,"str")){
char buffer[2048];
buffer[0]= '\0';
int remaining_size= 2047;
bool deterministic= true;
struct token*last_token= current_token->next,*new_result;
while(last_token!=NULL){
if(last_token->type==SYMBOL&&!strcmp(last_token->name,"[")){
char buffer_number[16];
struct token*result;
strncat(buffer,"[",remaining_size);
remaining_size--;
last_token= last_token->next;
if(last_token==NULL){
mf_error(*mf,"Missing numeric expression.");
return NULL;
}
result= eval_numeric(mf,&last_token);
if(result==NULL)
return NULL;
if(result->type!=NUMERIC){
mf_error(*mf,"Undefined numeric expression.");
return NULL;
}
deterministic= deterministic&&result->deterministic;
snprintf(buffer_number,16,"%f",result->value);
strncat(buffer,buffer_number,remaining_size);
remaining_size-= strlen(buffer_number);
if(last_token==NULL||last_token->type!=SYMBOL||
strcmp(last_token->name,"]")){
mf_error(*mf,"Missing ']'.");
return NULL;
}
strncat(buffer,"]",remaining_size);
remaining_size--;
last_token= last_token->next;
continue;
}
if(last_token->type==SYMBOL&&!is_tag(*mf,last_token))
break;
if(last_token->type==SYMBOL&&is_tag(*mf,last_token)){
if(buffer[0]!='\0'){
strncat(buffer,".",remaining_size);
remaining_size--;
}
strncat(buffer,last_token->name,remaining_size);
remaining_size-= strlen(last_token->name);
}
last_token= last_token->next;
}
new_result= new_token_string(buffer);
new_result->deterministic= deterministic;
new_result->prev= current_token->prev;
if(new_result->prev==NULL)
*expression= new_result;
else
new_result->prev->next= new_result;
new_result->next= last_token;
if(new_result->next!=NULL)
new_result->next->prev= new_result;
current_token= new_result;
}
/*:938*//*942:*/
#line 21338 "cweb/weaver.w"

if(current_token->type==SYMBOL&&
!strcmp(current_token->name,"char")){
char buffer[5]= {0x00,0x00,0x00,0x00};
unsigned long number;
bool deterministic;
struct token*result;
if(current_token->next==NULL){
mf_error(*mf,"Missing numeric primary.");
return NULL;
}
result= numeric_primary(mf,&(current_token->next));
if(result==NULL)
return NULL;
if(result->type!=NUMERIC){
mf_error(*mf,"Not recognized numeric primary.");
return NULL;
}
deterministic= result->deterministic;
number= (unsigned long)round(result->value);
number2utf8((uint32_t)number,buffer);
result= new_token_string(buffer);
result->deterministic= deterministic;
result->next= current_token->next;
result->prev= current_token->prev;
if(result->next!=NULL)
result->next->prev= result;
if(result->prev!=NULL)
result->prev->next= result;
else
*expression= result;
}
/*:942*//*944:*/
#line 21380 "cweb/weaver.w"

if(current_token->type==SYMBOL&&
!strcmp(current_token->name,"decimal")){
struct token*result;
char buffer[32];
bool deterministic;
int n;
if(current_token->next==NULL){
mf_error(*mf,"Missing numeric primary.");
return NULL;
}
result= numeric_primary(mf,&(current_token->next));
if(result==NULL)
return NULL;
if(result->type!=NUMERIC){
mf_error(*mf,"Not recognized numeric primary.");
return NULL;
}
deterministic= result->deterministic;
snprintf(buffer,32,"%f",result->value);

for(n= 0;buffer[n]!='\0';n++);
n--;
while(buffer[n]=='0'&&n>=0){
buffer[n]= '\0';
n--;
}
if(n>=0&&buffer[n]=='.')
buffer[n]= '\0';

result= new_token_string(buffer);
result->deterministic= deterministic;
result->next= current_token->next;
result->prev= current_token->prev;
if(result->next!=NULL)
result->next->prev= result;
if(result->prev!=NULL)
result->prev->next= result;
else
*expression= result;
}
/*:944*//*950:*/
#line 21533 "cweb/weaver.w"

if(current_token->type==SYMBOL&&
!strcmp(current_token->name,"substring")){
struct token*pair,*substring_token;
substring_token= current_token;
current_token= current_token->next;
pair= pair_primary(mf,&current_token);
if(pair==NULL){
return NULL;
}
pair->next= current_token;
pair->prev= substring_token;
substring_token->next= pair;
if(current_token!=NULL)
current_token->prev= pair;
}
/*:950*//*951:*/
#line 21561 "cweb/weaver.w"

while(current_token!=NULL&&current_token->prev!=NULL&&
current_token->prev->prev!=NULL&&
current_token->prev->prev->prev!=NULL&&
current_token->prev->prev->prev->type==SYMBOL&&
!strcmp(current_token->prev->prev->prev->name,"substring")){
struct token*result;
int i;
long n1,n2,max_size;
char*buffer;
bool reversed,deterministic= true;
if(current_token->type!=STRING){
mf_error(*mf,"Can't get substring from an unknown string.");
return NULL;
}
deterministic= deterministic&&current_token->deterministic;
if(current_token->prev->type!=SYMBOL||
strcmp(current_token->prev->name,"of")){
mf_error(*mf,"Missing 'of' in substring expression.");
return NULL;
}
if(current_token->prev->prev->type!=PAIR){
mf_error(*mf,"Unknown pair after substring expression.");
return NULL;
}
deterministic= deterministic&&
current_token->prev->prev->deterministic;
max_size= (long)strlen(current_token->name);
n1= (long)round(current_token->prev->prev->value);
if(n1<0)
n1= 0;
if(n1> max_size)
n1= max_size;
n2= (long)round(current_token->prev->prev->value2);
if(n2> max_size)
n2= max_size;
if(n2<0)
n2= 0;
if(n1> n2){
reversed= true;
max_size= n1-n2+1;
}
else{
reversed= false;
max_size= n2-n1+1;
}
buffer= (char*)Walloc_arena(_internal_arena,max_size);
if(buffer==NULL){
fprintf(stderr,"ERROR: Not enough memory. Please, increase the "
"value of W_INTERNAL_MEMORY at conf/conf.h.\n");
exit(1);
}
if(!reversed)
for(i= 0;i<max_size-1;i++)
buffer[i]= current_token->name[n1+i];
else
for(i= 0;i<max_size-1;i++)
buffer[i]= current_token->name[n1-i-1];
buffer[max_size-1]= '\0';
result= new_token_string(buffer);
result->deterministic= deterministic;
result->prev= current_token->prev->prev->prev->prev;
result->next= current_token->next;
if(result->prev!=NULL)
result->prev->next= result;
else
*expression= result;
if(result->next!=NULL)
result->next->prev= result;
current_token= result;
}
/*:951*/
#line 20658 "cweb/weaver.w"

current_token= current_token->next;
}

current_token= *expression;
if(delim!=NULL)
current_token= current_token->next;
while(current_token!=NULL&&
((delimited&&strcmp(current_token->name,delim))||
(!delimited&&strcmp(current_token->name,";")))){
/*954:*/
#line 21646 "cweb/weaver.w"

if(current_token->type==SYMBOL&&
!strcmp(current_token->name,"&")){
int new_string_size;
char*buffer;
struct token*result;

if(current_token->prev==NULL||current_token->prev->type!=STRING){
mf_error(*mf,"Missing known string before '&'.");
return NULL;
}

if(current_token->next==NULL||current_token->next->type!=STRING){
mf_error(*mf,"Missing known string after '&'.");
return NULL;
}
new_string_size= strlen(current_token->prev->name)+
strlen(current_token->next->name)+1;
buffer= Walloc_arena(_internal_arena,new_string_size);
if(buffer==NULL){
fprintf(stderr,"ERROR: Not enough memory. Please, increase the "
"value of W_INTERNAL_MEMORY at conf/conf.h.\n");
exit(1);
}
strcpy(buffer,current_token->prev->name);
strcat(buffer,current_token->next->name);
result= new_token_string(buffer);
result->deterministic= current_token->next->deterministic&&
current_token->prev->deterministic;
result->prev= current_token->prev->prev;
result->next= current_token->next->next;
if(result->prev!=NULL)
result->prev->next= result;
else
*expression= result;
if(result->next!=NULL)
result->next->prev= result;
current_token= result;
}
/*:954*/
#line 20668 "cweb/weaver.w"

current_token= current_token->next;
}


if(delimited){
if(*expression!=NULL&&(*expression)->next!=NULL&&
(*expression)->next->next!=NULL&&
!strcmp((*expression)->next->next->name,
delim)){
*expression= (*expression)->next;
(*expression)->prev= (*expression)->prev->prev;
if((*expression)->prev!=NULL)
(*expression)->prev->next= *expression;
(*expression)->next= (*expression)->next->next;
if((*expression)->next!=NULL)
(*expression)->next->prev= *expression;
}
}
return*expression;
error_no_memory_internal:
fprintf(stderr,"ERROR: Not enough memory. Please, increase the "
"value of W_INTERNAL_MEMORY at conf/conf.h\n");
exit(1);


}
/*:916*/
#line 20573 "cweb/weaver.w"

struct token*eval(struct metafont**mf,struct token**expression){
struct token*aux= *expression;
struct metafont*scope= *mf;
bool is_variable= false;
int type;

while(aux!=NULL&&aux->type==SYMBOL&&delimiter(*mf,aux)!=NULL)
aux= aux->next;

if(aux==NULL){
mf_error(*mf,"Missing expression.");
return NULL;
}
if(aux->type==STRING)
return eval_string(mf,expression);

else if(aux->type==SYMBOL){
if(!strcmp(aux->name,"begingroup")){


aux->prev->next= NULL;
aux->prev= NULL;
aux->next->prev= NULL;

Wbreakpoint_arena(metafont_arena);
*mf= _new_metafont(*mf,(*mf)->filename);
(*mf)->past_tokens= *expression;
(*mf)->pending_tokens= aux->next;
if(aux->next!=NULL)
concat_token((*mf)->pending_tokens,
(*mf)->parent->pending_tokens);
else
(*mf)->pending_tokens= (*mf)->parent->pending_tokens;
(*mf)->parent->pending_tokens= NULL;

return NULL;
}
while(scope!=NULL){
if(_search_trie(scope->variable_types,INT,aux->name,&type)){
is_variable= true;
break;
}
scope= scope->parent;
}
if(!is_variable){
if(!strcmp(aux->name,"jobname"))
return eval_string(mf,expression);
if(!strcmp(aux->name,"readstring"))
return eval_string(mf,expression);
if(!strcmp(aux->name,"str"))
return eval_string(mf,expression);
if(!strcmp(aux->name,"char"))
return eval_string(mf,expression);
if(!strcmp(aux->name,"decimal"))
return eval_string(mf,expression);
if(!strcmp(aux->name,"substring"))
return eval_string(mf,expression);
}
}
if(is_variable&&type==STRING)
return eval_string(mf,expression);
mf_error(*mf,"Undetermined expression.");
return NULL;
}
/*:915*/
#line 17907 "cweb/weaver.w"

/*842:*/
#line 18613 "cweb/weaver.w"

/*843:*/
#line 18649 "cweb/weaver.w"

void run_single_statement(struct metafont**mf,struct token*statement){
if(statement->type==SYMBOL&&!strcmp(statement->name,";"))
return;
/*866:*/
#line 19113 "cweb/weaver.w"

{
struct token*aux= statement;
while(aux!=NULL){
if(aux->type==SYMBOL&&!strcmp(aux->name,"endgroup")){
if(aux->prev!=NULL)
aux->prev->next= aux->next;
else
statement= aux->next;
if(aux->next!=NULL)
aux->next->prev= aux->prev;
break;
}
aux= aux->next;
}
}
/*:866*/
#line 18653 "cweb/weaver.w"

/*851:*/
#line 18878 "cweb/weaver.w"

if(statement->type==SYMBOL&&!strcmp(statement->name,"newinternal")){
struct token*current_token= statement->next;
struct token*list= symbolic_token_list(*mf,&current_token);

if(current_token==NULL||current_token->type!=SYMBOL||
strcmp(current_token->name,";")){
mf_error(*mf,"Extra token at newinternal command.");
return;
}

while(list!=NULL){
_insert_trie((*mf)->internal_quantities,_user_arena,DOUBLE,
list->name,0.0);
list= list->next;
}
return;
}
/*:851*//*855:*/
#line 18929 "cweb/weaver.w"

if(statement->type==SYMBOL&&!strcmp(statement->name,"everyjob")){

if(statement->next==NULL||statement->next->type!=SYMBOL){
mf_error(*mf,"Missing symbolic token.");
return;
}

if(!strcmp(statement->next->name,";")){
statement->next->next= get_statement(*mf);
if(statement->next->next!=NULL)
statement->next->next->prev= statement->next;
}

if(statement->next->next==NULL||
statement->next->next->type!=SYMBOL||
strcmp(statement->next->next->name,";")){
mf_error(*mf,"Extra tokens found after everyjob.");
return;
}

if((*mf)->everyjob_token_name==NULL||
strlen((*mf)->everyjob_token_name)<strlen(statement->next->name))
(*mf)->everyjob_token_name= (char*)
Walloc(strlen(statement->next->name)+1);
strcpy((*mf)->everyjob_token_name,statement->next->name);
return;
}
/*:855*//*858:*/
#line 18990 "cweb/weaver.w"

if(statement->type==SYMBOL&&
(!strcmp(statement->name,"batchmode")||
!strcmp(statement->name,"nonstopmode")||
!strcmp(statement->name,"scrollmode")||
!strcmp(statement->name,"errorstopmode"))){

if(statement->next==NULL||statement->next->type!=SYMBOL||
strcmp(statement->next->name,";")){
mf_error(*mf,"Extra tokens found after mode command.");
return;
}
return;
}
/*:858*//*861:*/
#line 19061 "cweb/weaver.w"

if(statement->type==SYMBOL&&!strcmp(statement->name,"begingroup")){
Wbreakpoint_arena(metafont_arena);
*mf= _new_metafont(*mf,(*mf)->filename);
statement= statement->next;
statement->prev= NULL;
(*mf)->pending_tokens= statement;
if(statement!=NULL)
concat_token((*mf)->pending_tokens,
(*mf)->parent->pending_tokens);
else
(*mf)->pending_tokens= (*mf)->parent->pending_tokens;
(*mf)->parent->pending_tokens= NULL;
return;
}
/*:861*//*876:*/
#line 19256 "cweb/weaver.w"

if(statement->type==SYMBOL&&!strcmp(statement->name,"save")){
struct token*current_token= statement->next;
struct token*list= symbolic_token_list(*mf,&current_token);

if(current_token==NULL||current_token->type!=SYMBOL||
strcmp(current_token->name,";")){
mf_error(*mf,"Extra token at save command.");
return;
}

while(list!=NULL){
void*current_arena= 
((*mf)->parent==NULL)?_user_arena:metafont_arena;
int current_type;
bool already_declared= _search_trie((*mf)->variable_types,INT,
list->name,&current_type);
if(already_declared&&current_type!=NOT_DECLARED)
_remove_trie((*mf)->vars[current_type],list->name);
_insert_trie((*mf)->variable_types,current_arena,INT,list->name,
NOT_DECLARED);
list= list->next;
}
return;
}
/*:876*//*880:*/
#line 19328 "cweb/weaver.w"

if(statement->type==SYMBOL&&!strcmp(statement->name,"delimiters")){
char*end_delimiter;
void*current_arena;
struct metafont*scope= (*mf);
statement= statement->next;
if(statement==NULL||statement->type!=SYMBOL){
mf_error(*mf,"Missing symbolic token.");
return;
}
while(scope->parent!=NULL){
void*result;
if(_search_trie(scope->variable_types,VOID_P,
statement->name,&result))
break;
scope= scope->parent;
}
current_arena= (scope->parent==NULL)?_user_arena:metafont_arena;
statement= statement->next;
if(statement==NULL||statement->type!=SYMBOL){
mf_error(*mf,"Missing symbolic token.");
return;
}
end_delimiter= (char*)Walloc_arena(current_arena,
strlen(statement->name)+1);
if(end_delimiter==NULL){
fprintf(stderr,"ERROR: Not enough memory to parse METAFONT. "
"Please, increase the value of %s at conf/conf.h.\n",
(current_arena==_user_arena)?"W_MAX_MEMORY":"W_INTERNAL_MEMORY");
return;
}
strcpy(end_delimiter,statement->name);
_insert_trie(scope->delimiters,current_arena,VOID_P,
statement->prev->name,(void*)end_delimiter);
statement= statement->next;
if(statement==NULL||statement->type!=SYMBOL||
strcmp(statement->name,";")){
mf_error(*mf,"Missing symbolic token.");
return;
}
return;
}
/*:880*//*885:*/
#line 19419 "cweb/weaver.w"

if(statement->type==SYMBOL&&
(!strcmp(statement->name,"inner")||
!strcmp(statement->name,"outer"))){
bool inner_command= (statement->name[0]=='i');
statement= statement->next;
struct token*list= symbolic_token_list(*mf,&statement);

if(statement==NULL||statement->type!=SYMBOL||
strcmp(statement->name,";")){
mf_error(*mf,"Extra token at save command");
return;
}

while(list!=NULL){
void*current_arena;
struct metafont*scope= (*mf);
while(scope->parent!=NULL){
int dummy_result;
if(_search_trie(scope->variable_types,INT,
list->name,&dummy_result))
break;
scope= scope->parent;
}
current_arena= (scope->parent==NULL)?_user_arena:metafont_arena;
if(inner_command)
_remove_trie((*mf)->outer_tokens,list->name);
else
_insert_trie((*mf)->outer_tokens,current_arena,INT,
list->name,0);
list= list->next;
}
return;
}
/*:885*//*893:*/
#line 19711 "cweb/weaver.w"

if(statement->type==SYMBOL&&
(!strcmp(statement->name,"boolean")||
!strcmp(statement->name,"string")||
!strcmp(statement->name,"path")||
!strcmp(statement->name,"pen")||
!strcmp(statement->name,"picture")||
!strcmp(statement->name,"transform")||
!strcmp(statement->name,"pair")||
!strcmp(statement->name,"numeric"))){
int type;
char buffer[1024];

switch(statement->name[0]){
case'b':
type= BOOLEAN;
break;
case's':
type= STRING;
break;
case't':
type= TRANSFORM;
break;
case'n':
type= NUMERIC;
break;
default:
switch(statement->name[2]){
case't':
type= PATH;
break;
case'n':
type= PEN;
break;
case'c':
type= PICTURE;
break;
default:
type= PAIR;
break;
}
}
statement= statement->next;
while(1){
bool already_declared= false;
int current_type_if_already_declared;
void*current_arena;
struct metafont*scope= *mf;

declared_variable(*mf,&statement,buffer,1024);
if(!strcmp(buffer,"")){
mf_error(*mf,"Missing symbolic token.");
return;
}

if(scope->parent==NULL)
already_declared= _search_trie(scope->variable_types,INT,
buffer,
&current_type_if_already_declared);
while(scope->parent!=NULL){
already_declared= _search_trie(scope->variable_types,INT,
buffer,
&current_type_if_already_declared);
if(already_declared)
break;
scope= scope->parent;
}

if(scope->parent==NULL)
current_arena= _user_arena;
else
current_arena= metafont_arena;

if(already_declared&&current_type_if_already_declared!=NOT_DECLARED)
_remove_trie(scope->vars[current_type_if_already_declared],
buffer);

_insert_trie(scope->variable_types,current_arena,INT,buffer,type);

if(statement!=NULL&&statement->type==SYMBOL&&
!strcmp(statement->name,";"))
break;

if(statement!=NULL&&statement->type==SYMBOL&&
!strcmp(statement->name,",")){
statement= statement->next;
continue;
}

else{
mf_error(*mf,"Illegal suffix or missing symbolic token.");
return;
}
}
return;
}
/*:893*//*903:*/
#line 20103 "cweb/weaver.w"

if(statement->type==SYMBOL&&!strcmp(statement->name,"def")){
char*name;
struct macro*new_macro;
struct token*delimited_headers,*undelimited_header;
statement= statement->next;
struct metafont*scope= *mf;
void*current_arena= _user_arena;

if(statement==NULL||statement->type!=SYMBOL){
mf_error(*mf,"Missing symbolic token.");
return;
}
name= statement->name;

while(scope->parent!=NULL){
int dummy_result;
if(_search_trie(scope->variable_types,INT,
name,&dummy_result)){
current_arena= metafont_arena;
break;
}
scope= scope->parent;
}
statement= statement->next;
delimited_headers= delimited_parameters(*mf,&statement,current_arena);
undelimited_header= undelimited_parameters(*mf,&statement,current_arena);
new_macro= (struct macro*)Walloc_arena(current_arena,sizeof(struct macro));
if(new_macro==NULL){
fprintf(stderr,"ERROR: Not enough memory. Please, increase the "
"value of W_%s_MEMORY at conf/conf.h\n",
(current_arena==_user_arena)?"MAX":"INTERNAL");
exit(1);
}
new_macro->parameters= undelimited_header;
if(new_macro->parameters==NULL)
new_macro->parameters= delimited_headers;
else
new_macro->parameters->next= delimited_headers;
if(delimited_headers!=NULL)
delimited_headers->prev= undelimited_header;

if(statement==NULL||statement->type!=SYMBOL||
(strcmp(statement->name,"=")&&strcmp(statement->name,":="))){
mf_error(*mf,"Missing '=' or ':=' at macro definition.");
return;
}
statement= statement->next;

new_macro->replacement_text= replacement_text(*mf,&statement,
current_arena);

_insert_trie(scope->macros,current_arena,VOID_P,name,
(void*)new_macro);

if(statement==NULL||statement->type!=SYMBOL||
strcmp(statement->name,";")){
mf_error(*mf,"Extra token after enddef");
return;
}
return;
}
/*:903*//*907:*/
#line 20214 "cweb/weaver.w"

if(statement->type==SYMBOL&&!strcmp(statement->name,"vardef")){
struct macro*new_macro;
struct token*tok;
char variable_name[1024];
struct token*delimited_headers= NULL,*undelimited_header= NULL,
*suffix_header= NULL;
void*current_arena= _user_arena;
struct metafont*scope= *mf;
statement= statement->next;

variable_name[0]= '\0';
declared_variable(*mf,&statement,variable_name,1024);

while(scope->parent!=NULL){
int dummy_result;
if(_search_trie(scope->variable_types,INT,
variable_name,&dummy_result)){
current_arena= metafont_arena;
break;
}
scope= scope->parent;
}

if(statement!=NULL&&statement->type==SYMBOL&&
!strcmp(statement->name,"@#")){
suffix_header= new_token(SUFFIX,0.0,"@#",current_arena);
statement= statement->next;
}

delimited_headers= delimited_parameters(*mf,&statement,current_arena);
undelimited_header= undelimited_parameters(*mf,&statement,current_arena);
new_macro= (struct macro*)Walloc_arena(current_arena,sizeof(struct macro));
if(new_macro==NULL){
fprintf(stderr,"ERROR: Not enough memory. Please, increase the "
"value of W_%s_MEMORY at conf/conf.h\n",
(current_arena==_user_arena)?"MAX":"INTERNAL");
exit(1);
}
new_macro->parameters= suffix_header;
if(new_macro->parameters==NULL)
new_macro->parameters= undelimited_header;
else if(undelimited_header!=NULL)
concat_token(new_macro->parameters,undelimited_header);
if(delimited_headers!=NULL){
if(new_macro->parameters!=NULL)
concat_token(new_macro->parameters,delimited_headers);
else
new_macro->parameters= delimited_headers;
}

if(statement==NULL||statement->type!=SYMBOL||
(strcmp(statement->name,"=")&&strcmp(statement->name,":="))){
mf_error(*mf,"Missing '=' or ':=' at macro definition.");
return;
}
statement= statement->next;

new_macro->replacement_text= new_token(SYMBOL,0.0,"begingroup",
current_arena);
if(new_macro->replacement_text==NULL){
if(current_arena==_user_arena)
goto error_no_memory_user;
else
goto error_no_memory_internal;
}
new_macro->replacement_text= replacement_text(*mf,&statement,
current_arena);
tok= new_token(SYMBOL,0.0,"endgroup",current_arena);
if(tok==NULL){
if(current_arena==_user_arena)
goto error_no_memory_user;
else
goto error_no_memory_internal;
}
concat_token(new_macro->replacement_text,tok);

_insert_trie(scope->variable_types,current_arena,INT,variable_name,
MACRO);
_insert_trie(scope->vardef,current_arena,VOID_P,variable_name,
(void*)new_macro);

if(statement==NULL||statement->type!=SYMBOL||
strcmp(statement->name,";")){
mf_error(*mf,"Extra token after enddef");
return;
}
return;
}
/*:907*//*910:*/
#line 20338 "cweb/weaver.w"

if(statement->type==SYMBOL&&
(!strcmp(statement->name,"primarydef")||
!strcmp(statement->name,"secondarydef")||
!strcmp(statement->name,"tertiarydef"))){
struct _trie*destiny[3];
int precedence;
char*name;
struct token*arg1,*arg2;
struct metafont*scope= *mf;
void*current_arena= _user_arena;
struct macro*new_macro;

switch(statement->name[0]){
case'p':
precedence= 0;
break;
case's':
precedence= 1;
break;
default:
precedence= 2;
break;
}

if(statement->next==NULL){
mf_error(*mf,"Missing symbolic token.");
return;
}
statement= statement->next->next;
if(statement==NULL||statement->type!=SYMBOL){
mf_error(*mf,"Missing symbolic token.");
return;
}
name= statement->name;

while(scope->parent!=NULL){
int dummy_result;
if(_search_trie(scope->variable_types,INT,
name,&dummy_result)){
current_arena= metafont_arena;
break;
}
scope= scope->parent;
}
destiny[0]= scope->primarydef;
destiny[1]= scope->secondarydef;
destiny[2]= scope->tertiarydef;

new_macro= (struct macro*)Walloc_arena(current_arena,
sizeof(struct macro));
if(new_macro==NULL){
fprintf(stderr,"ERROR: Not enough memory. Please, increase the "
"value of W_%s_MEMORY at conf/conf.h\n",
(current_arena==_user_arena)?"MAX":"INTERNAL");
exit(1);
}

statement= statement->prev;
if(statement->type!=SYMBOL){
mf_error(*mf,"Missing symbolic token.");
return;
}
arg1= new_token(SYMBOL,0.0,statement->name,current_arena);
if(arg1==NULL){
fprintf(stderr,"ERROR: Not enough memory. Please, increase the "
"value of W_%s_MEMORY at conf/conf.h\n",
(current_arena==_user_arena)?"MAX":"INTERNAL");
exit(1);
}

statement= statement->next->next;
if(statement->type!=SYMBOL){
mf_error(*mf,"Missing symbolic token.");
return;
}
arg2= new_token(SYMBOL,0.0,statement->name,current_arena);
if(arg1==NULL){
fprintf(stderr,"ERROR: Not enough memory. Please, increase the "
"value of W_%s_MEMORY at conf/conf.h\n",
(current_arena==_user_arena)?"MAX":"INTERNAL");
exit(1);
}
arg1->next= arg2;
arg2->prev= arg1;
new_macro->parameters= arg1;

statement= statement->next;
if(statement==NULL||statement->type!=SYMBOL||
(strcmp(statement->name,"=")&&strcmp(statement->name,":="))){
mf_error(*mf,"Missing '=' or ':=' at macro definition.");
return;
}
statement= statement->next;

new_macro->replacement_text= new_token(SYMBOL,0.0,"begingroup",
current_arena);
if(new_macro->replacement_text==NULL){
if(current_arena==_user_arena)
goto error_no_memory_user;
else
goto error_no_memory_internal;
}
new_macro->replacement_text= replacement_text(*mf,&statement,
current_arena);


_insert_trie(destiny[precedence],current_arena,VOID_P,name,
(void*)new_macro);

if(statement==NULL||statement->type!=SYMBOL||
strcmp(statement->name,";")){
mf_error(*mf,"Extra token after enddef");
return;
}
return;
}
/*:910*//*957:*/
#line 21713 "cweb/weaver.w"

if(statement->type==SYMBOL&&(!strcmp(statement->name,"message")||
!strcmp(statement->name,"errmessage")||
!strcmp(statement->name,"errhelp"))){
struct token*expr_result;

if(statement->next==NULL){
mf_error(*mf,"Missing string expression.");
return;
}
expr_result= eval_string(mf,&(statement->next));
if(expr_result==NULL){
if(!(*mf)->error){
if((*mf)->pending_tokens==NULL)
(*mf)->pending_tokens= statement;
else
concat_token((*mf)->pending_tokens,statement);
}
return;
}
if(expr_result->type!=STRING){
mf_error(*mf,"Tried to print unknown string.");
return;
}
if(statement->name[0]=='m')
printf("%s\n",expr_result->name);
else if(statement->name[3]=='m')
fprintf(stderr,"%s\n",expr_result->name);
return;
}
/*:957*/
#line 18654 "cweb/weaver.w"

/*913:*/
#line 20526 "cweb/weaver.w"

{
struct token*new_tokens= (*mf)->past_tokens;
struct token*expression_result= eval(mf,&statement);
if((*mf)->hint==HINT_ENDGROUP){
if((*mf)->parent==NULL){
mf_error(*mf,"Extra 'endgroup' while not in 'begingroup'.");
return;
}
if(expression_result!=NULL){
if(new_tokens!=NULL)
concat_token(new_tokens,expression_result);
else
new_tokens= expression_result;
(*mf)->parent->pending_tokens= new_tokens;
}
*mf= (*mf)->parent;
Wtrash_arena(metafont_arena);
}
else{


if(expression_result==NULL)
return;
if(expression_result->type!=STRING)
mf_error(*mf,"Isolated expression.");
else if(expression_result->type==STRING){
;
}
}
return;
}
/*:913*/
#line 18655 "cweb/weaver.w"

mf_error(*mf,"Isolated expression. I couldn't find a = or := after it.");
return;
error_no_memory_user:
fprintf(stderr,"ERROR: Not enough memory. Please, increase the "
"value of W_MAX_MEMORY at conf/conf.h\n");
exit(1);
error_no_memory_internal:
fprintf(stderr,"ERROR: Not enough memory. Please, increase the "
"value of W_INTERNAL_MEMORY at conf/conf.h\n");
exit(1);
}
/*:843*/
#line 18614 "cweb/weaver.w"

void run_statements(struct metafont*mf){
struct token*statement;
bool end_execution= false,first_loop= (mf->parent==NULL);
while(!end_execution){
if(mf->pending_tokens==NULL)
_iWbreakpoint();
if(first_loop){
/*856:*/
#line 18963 "cweb/weaver.w"

if(mf->everyjob_token_name!=NULL)
mf->pending_tokens= new_token_symbol(mf->everyjob_token_name);
/*:856*/
#line 18622 "cweb/weaver.w"

first_loop= false;
}
/*864:*/
#line 19098 "cweb/weaver.w"

mf->hint= 0;
/*:864*/
#line 18625 "cweb/weaver.w"

statement= get_statement(mf);
if(statement==NULL)
end_execution= true;
else{
run_single_statement(&mf,statement);
}
/*867:*/
#line 19133 "cweb/weaver.w"

if(mf->hint==HINT_ENDGROUP){


if(mf->parent==NULL)
mf_error(mf,"Extra 'endgroup' while not in 'begingroup'.");
else{
mf= mf->parent;
Wtrash_arena(metafont_arena);
}
}
/*:867*/
#line 18632 "cweb/weaver.w"

if(mf->pending_tokens==NULL)
_iWtrash();
}
/*868:*/
#line 19150 "cweb/weaver.w"

while(mf->parent!=NULL){
mf= mf->parent;
Wtrash_arena(metafont_arena);
}
/*:868*/
#line 18636 "cweb/weaver.w"

}
/*:842*/
#line 17908 "cweb/weaver.w"

/*817:*/
#line 17927 "cweb/weaver.w"


/*:817*//*821:*/
#line 17969 "cweb/weaver.w"

void _initialize_metafont(void){
struct metafont*mf;
metafont_arena= Wcreate_arena(W_INTERNAL_MEMORY/4);
if(metafont_arena==NULL){
fprintf(stderr,"ERROR: This system have no enough memory to "
"run this program.\n");
exit(1);
}
/*891:*/
#line 19606 "cweb/weaver.w"

primitive_sparks= _new_trie(_user_arena);
_insert_trie(primitive_sparks,_user_arena,INT,"end",0);
_insert_trie(primitive_sparks,_user_arena,INT,"dump",0);
_insert_trie(primitive_sparks,_user_arena,INT,";",0);
_insert_trie(primitive_sparks,_user_arena,INT,",",0);
_insert_trie(primitive_sparks,_user_arena,INT,"newinternal",0);
_insert_trie(primitive_sparks,_user_arena,INT,"everyjob",0);
_insert_trie(primitive_sparks,_user_arena,INT,"batchmode",0);
_insert_trie(primitive_sparks,_user_arena,INT,"nonstopmode",0);
_insert_trie(primitive_sparks,_user_arena,INT,"scrollmode",0);
_insert_trie(primitive_sparks,_user_arena,INT,"errorstopmode",0);
_insert_trie(primitive_sparks,_user_arena,INT,"begingroup",0);
_insert_trie(primitive_sparks,_user_arena,INT,"endgroup",0);
_insert_trie(primitive_sparks,_user_arena,INT,"save",0);
_insert_trie(primitive_sparks,_user_arena,INT,"delimiters",0);
_insert_trie(primitive_sparks,_user_arena,INT,"outer",0);
_insert_trie(primitive_sparks,_user_arena,INT,"inner",0);
_insert_trie(primitive_sparks,_user_arena,INT,"[",0);
_insert_trie(primitive_sparks,_user_arena,INT,"]",0);
_insert_trie(primitive_sparks,_user_arena,INT,"boolean",0);
_insert_trie(primitive_sparks,_user_arena,INT,"string",0);
_insert_trie(primitive_sparks,_user_arena,INT,"path",0);
_insert_trie(primitive_sparks,_user_arena,INT,"pen",0);
_insert_trie(primitive_sparks,_user_arena,INT,"picture",0);
_insert_trie(primitive_sparks,_user_arena,INT,"transform",0);
_insert_trie(primitive_sparks,_user_arena,INT,"pair",0);
_insert_trie(primitive_sparks,_user_arena,INT,"numeric",0);
/*895:*/
#line 19846 "cweb/weaver.w"

_insert_trie(primitive_sparks,_user_arena,INT,"expr",0);
_insert_trie(primitive_sparks,_user_arena,INT,"suffix",0);
_insert_trie(primitive_sparks,_user_arena,INT,"text",0);
_insert_trie(primitive_sparks,_user_arena,INT,"primary",0);
_insert_trie(primitive_sparks,_user_arena,INT,"secondary",0);
_insert_trie(primitive_sparks,_user_arena,INT,"tertiary",0);
_insert_trie(primitive_sparks,_user_arena,INT,"=",0);
_insert_trie(primitive_sparks,_user_arena,INT,":=",0);
_insert_trie(primitive_sparks,_user_arena,INT,"(",0);
_insert_trie(primitive_sparks,_user_arena,INT,")",0);
/*:895*//*905:*/
#line 20187 "cweb/weaver.w"

_insert_trie(primitive_sparks,_user_arena,INT,"@#",0);
/*:905*//*909:*/
#line 20330 "cweb/weaver.w"

_insert_trie(primitive_sparks,_user_arena,INT,"primarydef",0);
_insert_trie(primitive_sparks,_user_arena,INT,"secondarydef",0);
_insert_trie(primitive_sparks,_user_arena,INT,"tertiarydef",0);
/*:909*//*912:*/
#line 20497 "cweb/weaver.w"

_insert_trie(primitive_sparks,_user_arena,INT,"&",0);
_insert_trie(primitive_sparks,_user_arena,INT,"jobname",0);
_insert_trie(primitive_sparks,_user_arena,INT,"readstring",0);
_insert_trie(primitive_sparks,_user_arena,INT,"str",0);
_insert_trie(primitive_sparks,_user_arena,INT,"char",0);
_insert_trie(primitive_sparks,_user_arena,INT,"decimal",0);
_insert_trie(primitive_sparks,_user_arena,INT,"substring",0);
/*:912*//*953:*/
#line 21639 "cweb/weaver.w"

_insert_trie(primitive_sparks,_user_arena,INT,"&",0);
/*:953*//*956:*/
#line 21705 "cweb/weaver.w"

_insert_trie(primitive_sparks,_user_arena,INT,"message",0);
_insert_trie(primitive_sparks,_user_arena,INT,"errmessage",0);
_insert_trie(primitive_sparks,_user_arena,INT,"errhelp",0);
/*:956*/
#line 19634 "cweb/weaver.w"

/*:891*/
#line 17978 "cweb/weaver.w"

/*827:*/
#line 18086 "cweb/weaver.w"

mf= _new_metafont(NULL,"fonts/init.mf");
/*:827*/
#line 17979 "cweb/weaver.w"

}
/*:821*//*826:*/
#line 18038 "cweb/weaver.w"

struct metafont*_new_metafont(struct metafont*parent,char*filename){
void*arena;
struct metafont*structure;
size_t ret;
if(parent==NULL)
arena= _user_arena;
else
arena= metafont_arena;
structure= (struct metafont*)Walloc_arena(arena,
sizeof(struct metafont));
if(structure==NULL)
goto error_no_memory;
structure->parent= parent;
strncpy(structure->filename,filename,255);
if(parent==NULL){
structure->fp= fopen(filename,"r");
if(structure->fp==NULL)
goto error_no_file;
else{
ret= fread(structure->buffer,1,4095,structure->fp);
structure->buffer[ret]= '\0';
if(ret!=4095){
fclose(structure->fp);
structure->fp= NULL;
}
}
}
structure->buffer_position= 0;
structure->line= 1;
structure->error= false;
/*839:*/
#line 18528 "cweb/weaver.w"

structure->pending_tokens= NULL;
structure->past_tokens= NULL;
/*:839*//*848:*/
#line 18711 "cweb/weaver.w"

structure->internal_quantities= _new_trie(arena);
if(structure->internal_quantities==NULL)
goto error_no_memory;
/*:848*//*849:*/
#line 18725 "cweb/weaver.w"

if(structure->parent==NULL){
struct _trie*T= structure->internal_quantities;
time_t current_time;
unsigned int year,month,day,time_in_minutes;
struct tm*date;
time(&current_time);
date= localtime(&current_time);
year= date->tm_year+1900;
month= date->tm_mon+1;
day= date->tm_mday;
time_in_minutes= 60*date->tm_hour+date->tm_min;
_insert_trie(T,arena,DOUBLE,"tracingtitles",0.0);
_insert_trie(T,arena,DOUBLE,"tracingequations",0.0);
_insert_trie(T,arena,DOUBLE,"tracingcapsules",0.0);
_insert_trie(T,arena,DOUBLE,"tracingchoices",0.0);
_insert_trie(T,arena,DOUBLE,"tracingspecs",0.0);
_insert_trie(T,arena,DOUBLE,"tracingpens",0.0);
_insert_trie(T,arena,DOUBLE,"tracingcommands",0.0);
_insert_trie(T,arena,DOUBLE,"tracingrestores",0.0);
_insert_trie(T,arena,DOUBLE,"tracingmacros",0.0);
_insert_trie(T,arena,DOUBLE,"tracingedges",0.0);
_insert_trie(T,arena,DOUBLE,"tracingoutput",0.0);
_insert_trie(T,arena,DOUBLE,"tracingonline",0.0);
_insert_trie(T,arena,DOUBLE,"tracingstats",0.0);
_insert_trie(T,arena,DOUBLE,"pausing",0.0);
_insert_trie(T,arena,DOUBLE,"showstopping",0.0);
_insert_trie(T,arena,DOUBLE,"proofing",0.0);
_insert_trie(T,arena,DOUBLE,"turningcheck",0.0);
_insert_trie(T,arena,DOUBLE,"warningcheck",0.0);
_insert_trie(T,arena,DOUBLE,"smoothing",0.0);
_insert_trie(T,arena,DOUBLE,"autorounding",0.0);
_insert_trie(T,arena,DOUBLE,"glanularity",0.0);
_insert_trie(T,arena,DOUBLE,"glanularity",0.0);
_insert_trie(T,arena,DOUBLE,"fillin",0.0);
_insert_trie(T,arena,DOUBLE,"year",(double)year);
_insert_trie(T,arena,DOUBLE,"month",(double)month);
_insert_trie(T,arena,DOUBLE,"day",(double)day);
_insert_trie(T,arena,DOUBLE,"time",(double)time_in_minutes);
_insert_trie(T,arena,DOUBLE,"charcode",0.0);
_insert_trie(T,arena,DOUBLE,"charext",0.0);
_insert_trie(T,arena,DOUBLE,"charwd",0.0);
_insert_trie(T,arena,DOUBLE,"charht",0.0);
_insert_trie(T,arena,DOUBLE,"chardp",0.0);
_insert_trie(T,arena,DOUBLE,"charic",0.0);
_insert_trie(T,arena,DOUBLE,"chardx",0.0);
_insert_trie(T,arena,DOUBLE,"chardy",0.0);
_insert_trie(T,arena,DOUBLE,"designsize",0.0);
_insert_trie(T,arena,DOUBLE,"hppp",0.0);
_insert_trie(T,arena,DOUBLE,"vppp",0.0);
_insert_trie(T,arena,DOUBLE,"xoffset",0.0);
_insert_trie(T,arena,DOUBLE,"yoffset",0.0);
_insert_trie(T,arena,DOUBLE,"boundarychar",-1.0);
}
/*:849*//*854:*/
#line 18922 "cweb/weaver.w"

structure->everyjob_token_name= NULL;
/*:854*//*863:*/
#line 19094 "cweb/weaver.w"

structure->hint= 0;
/*:863*//*873:*/
#line 19227 "cweb/weaver.w"

structure->variable_types= _new_trie(arena);
/*:873*//*875:*/
#line 19244 "cweb/weaver.w"

{
int i;

for(i= 0;i<8;i++)
structure->vars[i]= _new_trie(arena);
}
/*:875*//*879:*/
#line 19321 "cweb/weaver.w"

structure->delimiters= _new_trie(arena);
/*:879*//*884:*/
#line 19413 "cweb/weaver.w"

structure->outer_tokens= _new_trie(arena);
/*:884*//*888:*/
#line 19546 "cweb/weaver.w"

structure->def= _new_trie(arena);
structure->vardef= _new_trie(arena);
structure->primarydef= _new_trie(arena);
structure->secondarydef= _new_trie(arena);
structure->tertiarydef= _new_trie(arena);
/*:888*//*899:*/
#line 19900 "cweb/weaver.w"

structure->macros= _new_trie(arena);
/*:899*/
#line 18069 "cweb/weaver.w"

/*845:*/
#line 18683 "cweb/weaver.w"

run_statements(structure);
/*:845*/
#line 18070 "cweb/weaver.w"

return structure;
error_no_file:
fprintf(stderr,"ERROR (0): File %s don't exist.\n",filename);
return NULL;
error_no_memory:
fprintf(stderr,"ERROR: Not enough memory to parse METAFONT "
"source. Please, increase the value of W_%s_MEMORY "
"at conf/conf.h.\n",(arena==_user_arena)?"MAX":"INTERNAL");
return NULL;
}
/*:826*/
#line 17909 "cweb/weaver.w"

/*:812*/
