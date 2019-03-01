/*714:*/
#line 16033 "./cweb/weaver.w"

#ifndef _database_h_
#define _database_h_
#ifdef __cplusplus
extern"C"{
#endif
#include "weaver.h"
/*66:*/
#line 1950 "./cweb/weaver.w"

#include "conf_begin.h"
#include "../../conf/conf.h"
#include "conf_end.h"
/*:66*/
#line 16040 "./cweb/weaver.w"

/*719:*/
#line 16090 "./cweb/weaver.w"

#if W_TARGET == W_ELF
void _initialize_database(void);
#endif
/*:719*//*722:*/
#line 16209 "./cweb/weaver.w"

#if W_TARGET == W_ELF
void _finalize_database(void);
#endif
/*:722*//*726:*/
#line 16244 "./cweb/weaver.w"

void _write_integer(char*name,int value);
/*:726*//*731:*/
#line 16316 "./cweb/weaver.w"

void _write_float(char*name,float value);
/*:731*//*736:*/
#line 16384 "./cweb/weaver.w"

void _write_string(char*name,char*value);
/*:736*//*742:*/
#line 16454 "./cweb/weaver.w"

bool _read_integer(char*name,int*value);
bool _read_float(char*name,float*value);
bool _read_string(char*name,char*value,int n);
/*:742*//*752:*/
#line 16702 "./cweb/weaver.w"

void _delete_integer(char*name);
void _delete_float(char*name);
void _delete_string(char*name);
void _delete_all(void);
/*:752*/
#line 16041 "./cweb/weaver.w"

#ifdef __cplusplus
}
#endif
#endif
/*:714*/
