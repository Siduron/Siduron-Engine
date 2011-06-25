/*
** Lua binding: Kernel_Interface
** Generated automatically by tolua++-1.0.92 on 06/24/11 16:26:35.
*/

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"
#include "../Core/Kernel.h"

#include "tolua++.h"

/* Exported function */
int tolua_Kernel_Interface_open (lua_State* tolua_S);


/* function to release collected object via destructor */
#ifdef __cplusplus

static int tolua_collect_Kernel (lua_State* tolua_S)
{
 Kernel* self = (Kernel*) tolua_tousertype(tolua_S,1,0);
 delete self;
 return 0;
}
#endif


/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"Kernel");
}

/* method: new of class  Kernel */
#ifndef TOLUA_DISABLE_tolua_Kernel_Interface_Kernel_new00
static int tolua_Kernel_Interface_Kernel_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertable(tolua_S,1,"Kernel",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
 {
  Kernel* tolua_ret = (Kernel*)  new Kernel();
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"Kernel");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  Kernel */
#ifndef TOLUA_DISABLE_tolua_Kernel_Interface_Kernel_new00_local
static int tolua_Kernel_Interface_Kernel_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertable(tolua_S,1,"Kernel",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
 {
  Kernel* tolua_ret = (Kernel*)  new Kernel();
 tolua_pushusertype_and_takeownership(tolua_S,(void *)tolua_ret,"Kernel");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Instance of class  Kernel */
#ifndef TOLUA_DISABLE_tolua_Kernel_Interface_Kernel_Instance00
static int tolua_Kernel_Interface_Kernel_Instance00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertable(tolua_S,1,"Kernel",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
 {
  Kernel* tolua_ret = (Kernel*)  Kernel::Instance();
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"Kernel");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Instance'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  Kernel */
#ifndef TOLUA_DISABLE_tolua_Kernel_Interface_Kernel_delete00
static int tolua_Kernel_Interface_Kernel_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"Kernel",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  Kernel* self = (Kernel*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'",NULL);
#endif
 delete self;
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
int tolua_Kernel_Interface_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
 #ifdef __cplusplus
 tolua_cclass(tolua_S,"Kernel","Kernel","",tolua_collect_Kernel);
 #else
 tolua_cclass(tolua_S,"Kernel","Kernel","",NULL);
 #endif
 tolua_beginmodule(tolua_S,"Kernel");
  tolua_function(tolua_S,"new",tolua_Kernel_Interface_Kernel_new00);
  tolua_function(tolua_S,"new_local",tolua_Kernel_Interface_Kernel_new00_local);
  tolua_function(tolua_S,".call",tolua_Kernel_Interface_Kernel_new00_local);
  tolua_function(tolua_S,"Instance",tolua_Kernel_Interface_Kernel_Instance00);
  tolua_function(tolua_S,"delete",tolua_Kernel_Interface_Kernel_delete00);
 tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 int luaopen_Kernel_Interface (lua_State* tolua_S) {
 return tolua_Kernel_Interface_open(tolua_S);
};
#endif

