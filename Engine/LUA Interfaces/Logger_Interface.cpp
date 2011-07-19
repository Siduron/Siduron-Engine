/*
** Lua binding: Logger_Interface
** Generated automatically by tolua++-1.0.92 on 07/11/11 00:37:55.
*/

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"
#include "../Util/Logger.h"
#include "../Development/ExposeTest.h"

/* Exported function */
int tolua_Logger_Interface_open (lua_State* tolua_S);


/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"Logger");
 tolua_usertype(tolua_S,"Messagetype");
}

/* method: Instance of class  Logger */
#ifndef TOLUA_DISABLE_tolua_Logger_Interface_Logger_Instance00
static int tolua_Logger_Interface_Logger_Instance00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertable(tolua_S,1,"Logger",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
 {
  Logger* tolua_ret = (Logger*)  Logger::Instance();
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"Logger");
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

/* method: Log of class  Logger */
#ifndef TOLUA_DISABLE_tolua_Logger_Interface_Logger_Log00
static int tolua_Logger_Interface_Logger_Log00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertable(tolua_S,1,"Logger",0,&tolua_err) ||
 !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
 !tolua_isusertype(tolua_S,3,"Messagetype",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  std::string message = ((std::string)  tolua_tocppstring(tolua_S,2,0));
  Messagetype type = *((Messagetype*)  tolua_tousertype(tolua_S,3,0));
 {
  Logger::Log(message,type);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Log'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Progress of class  Logger */
#ifndef TOLUA_DISABLE_tolua_Logger_Interface_Logger_Progress00
static int tolua_Logger_Interface_Logger_Progress00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertable(tolua_S,1,"Logger",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
 {
  Logger::Progress();
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Progress'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
int tolua_Logger_Interface_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
 tolua_cclass(tolua_S,"Logger","Logger","",NULL);
 tolua_beginmodule(tolua_S,"Logger");
  tolua_function(tolua_S,"Instance",tolua_Logger_Interface_Logger_Instance00);
  tolua_function(tolua_S,"Log",tolua_Logger_Interface_Logger_Log00);
  tolua_function(tolua_S,"Progress",tolua_Logger_Interface_Logger_Progress00);
 tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 int luaopen_Logger_Interface (lua_State* tolua_S) {
 return tolua_Logger_Interface_open(tolua_S);
};
#endif

