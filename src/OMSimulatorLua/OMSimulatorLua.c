#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
#include <stdlib.h>

#include <OMSimulator.h>

#ifdef WITH_OMSYSIDENT
#include <OMSysIdent.h>
#endif /* WITH_OMSYSIDENT */

#define REGISTER_LUA_CALL(name) lua_register(L, #name, OMSimulatorLua_##name)
#define REGISTER_LUA_ENUM(name) lua_pushnumber(L, name); lua_setglobal(L, #name)

#ifdef _WIN32
  #define DLLEXPORT __declspec(dllexport)
#else
  #define DLLEXPORT
#endif

void push_pointer(lua_State *L, void *p)
{
  void **bp = (void**)lua_newuserdata(L, sizeof(p));
  *bp = p;
}

void* topointer(lua_State *L, int index)
{
  void **bp = (void**)lua_touserdata(L, index);
  return *bp;
}

/* ************************************ */
/* oms3                                 */
/*                                      */
/* ************************************ */

//const char* oms3_getVersion();
static int OMSimulatorLua_oms3_getVersion(lua_State *L)
{
  if (lua_gettop(L) != 0)
    return luaL_error(L, "expecting no arguments");

  const char* version = oms3_getVersion();

  lua_pushstring(L, version);
  return 1;
}

//oms_status_enu_t oms3_setLogFile(const char* filename);
static int OMSimulatorLua_oms3_setLogFile(lua_State *L)
{
  if (lua_gettop(L) != 1)
    return luaL_error(L, "expecting exactly 1 argument");
  luaL_checktype(L, 1, LUA_TSTRING);

  const char* filename = lua_tostring(L, 1);
  oms_status_enu_t status = oms3_setLogFile(filename);
  lua_pushinteger(L, status);
  return 1;
}

//oms_status_enu_t oms3_setLoggingInterval(const char* cref, double loggingInterval);
static int OMSimulatorLua_oms3_setLoggingInterval(lua_State *L)
{
  if (lua_gettop(L) != 2)
    return luaL_error(L, "expecting exactly 2 arguments");
  luaL_checktype(L, 1, LUA_TSTRING);
  luaL_checktype(L, 2, LUA_TNUMBER);

  const char* cref = lua_tostring(L, 1);
  double loggingInterval = lua_tonumber(L, 2);
  oms_status_enu_t status = oms3_setLoggingInterval(cref, loggingInterval);
  lua_pushinteger(L, status);
  return 1;
}

//oms_status_enu_t oms3_setLoggingLevel(int logLevel);
static int OMSimulatorLua_oms3_setLoggingLevel(lua_State *L)
{
  if (lua_gettop(L) != 1)
    return luaL_error(L, "expecting exactly 1 argument");
  luaL_checktype(L, 1, LUA_TNUMBER);

  int logLevel = lua_tointeger(L, 1);
  oms_status_enu_t status = oms3_setLoggingLevel(logLevel);
  lua_pushinteger(L, status);
  return 1;
}

//void oms3_setMaxLogFileSize(const unsigned long size);
static int OMSimulatorLua_oms3_setMaxLogFileSize(lua_State *L)
{
  if (lua_gettop(L) != 1)
    return luaL_error(L, "expecting exactly 1 argument");
  luaL_checktype(L, 1, LUA_TNUMBER);

  unsigned long size = lua_tointeger(L, 1);
  oms3_setMaxLogFileSize(size);
  return 0;
}

//oms_status_enu_t oms3_setTempDirectory(const char* newTempDir);
static int OMSimulatorLua_oms3_setTempDirectory(lua_State *L)
{
  if (lua_gettop(L) != 1)
    return luaL_error(L, "expecting exactly 1 argument");
  luaL_checktype(L, 1, LUA_TSTRING);

  const char* newTempDir = lua_tostring(L, 1);
  oms_status_enu_t status = oms3_setTempDirectory(newTempDir);

  lua_pushinteger(L, status);
  return 1;
}

//oms_status_enu_t oms3_setTolerance(const char* cref, double tolerance);
static int OMSimulatorLua_oms3_setTolerance(lua_State *L)
{
  if (lua_gettop(L) != 2)
    return luaL_error(L, "expecting exactly 2 arguments");
  luaL_checktype(L, 1, LUA_TSTRING);
  luaL_checktype(L, 2, LUA_TNUMBER);

  const char* cref = lua_tostring(L, 1);
  double tolerance = lua_tonumber(L, 2);

  oms_status_enu_t status = oms3_setTolerance(cref, tolerance);
  lua_pushinteger(L, status);
  return 1;
}

//oms_status_enu_t oms3_setWorkingDirectory(const char* newWorkingDir);
static int OMSimulatorLua_oms3_setWorkingDirectory(lua_State *L)
{
  if (lua_gettop(L) != 1)
    return luaL_error(L, "expecting exactly 1 argument");
  luaL_checktype(L, 1, LUA_TSTRING);

  const char* newWorkingDir = lua_tostring(L, 1);
  oms_status_enu_t status = oms3_setWorkingDirectory(newWorkingDir);

  lua_pushinteger(L, status);
  return 1;
}

//oms_status_enu_t oms3_newModel(const char* cref);
static int OMSimulatorLua_oms3_newModel(lua_State *L)
{
  if (lua_gettop(L) != 1)
    return luaL_error(L, "expecting exactly 1 argument");
  luaL_checktype(L, 1, LUA_TSTRING);

  const char* cref = lua_tostring(L, 1);
  oms_status_enu_t status = oms3_newModel(cref);

  lua_pushinteger(L, status);
  return 1;
}

//oms_status_enu_t oms3_rename(const char* cref, const char* newCref);
static int OMSimulatorLua_oms3_rename(lua_State *L)
{
  if (lua_gettop(L) != 2)
    return luaL_error(L, "expecting exactly 2 arguments");
  luaL_checktype(L, 1, LUA_TSTRING);

  const char* cref = lua_tostring(L, 1);
  const char* newCref = lua_tostring(L, 2);
  oms_status_enu_t status = oms3_rename(cref, newCref);

  lua_pushinteger(L, status);
  return 1;
}

//oms_status_enu_t oms3_delete(const char* cref);
static int OMSimulatorLua_oms3_delete(lua_State *L)
{
  if (lua_gettop(L) != 1)
    return luaL_error(L, "expecting exactly 1 argument");
  luaL_checktype(L, 1, LUA_TSTRING);

  const char* cref = lua_tostring(L, 1);
  oms_status_enu_t status = oms3_delete(cref);

  lua_pushinteger(L, status);
  return 1;
}

//oms_status_enu_t oms3_export(const char* cref, const char* filename);
static int OMSimulatorLua_oms3_export(lua_State *L)
{
  if (lua_gettop(L) != 2)
    return luaL_error(L, "expecting exactly 2 arguments");
  luaL_checktype(L, 1, LUA_TSTRING);
  luaL_checktype(L, 2, LUA_TSTRING);

  const char* cref = lua_tostring(L, 1);
  const char* filename = lua_tostring(L, 2);
  oms_status_enu_t status = oms3_export(cref, filename);

  lua_pushinteger(L, status);
  return 1;
}

//oms_status_enu_t oms3_import(const char* filename, const char** cref);
static int OMSimulatorLua_oms3_import(lua_State *L)
{
  if (lua_gettop(L) != 1)
    return luaL_error(L, "expecting exactly 1 argument");
  luaL_checktype(L, 1, LUA_TSTRING);

  const char* filename = lua_tostring(L, 1);
  char* cref = NULL;
  oms_status_enu_t status = oms3_import(filename, &cref);

  lua_pushstring(L, cref ? cref : "");
  lua_pushinteger(L, status);
  return 2;
}

//oms_status_enu_t oms3_list(const char* cref, char** contents);
static int OMSimulatorLua_oms3_list(lua_State *L)
{
  if (lua_gettop(L) != 1)
    return luaL_error(L, "expecting exactly 1 argument");
  luaL_checktype(L, 1, LUA_TSTRING);

  const char* cref = lua_tostring(L, 1);
  char* contents = NULL;
  oms_status_enu_t status = oms3_list(cref, &contents);

  lua_pushstring(L, contents ? contents : "");
  lua_pushinteger(L, status);

  if (contents)
    oms3_freeMemory(contents);

  return 2;
}

//oms_status_enu_t oms3_listUnconnectedConnectors(const char* cref, char** contents);
static int OMSimulatorLua_oms3_listUnconnectedConnectors(lua_State *L)
{
  if (lua_gettop(L) != 1)
    return luaL_error(L, "expecting exactly 1 argument");
  luaL_checktype(L, 1, LUA_TSTRING);

  const char* cref = lua_tostring(L, 1);
  char* contents = NULL;
  oms_status_enu_t status = oms3_listUnconnectedConnectors(cref, &contents);

  lua_pushstring(L, contents ? contents : "");
  lua_pushinteger(L, status);

  if (contents)
    oms3_freeMemory(contents);

  return 2;
}

//oms_status_enu_t oms3_exportDependencyGraphs(const char* cref, const char* initialization, const char* simulation);
static int OMSimulatorLua_oms3_exportDependencyGraphs(lua_State *L)
{
  if (lua_gettop(L) != 3)
    return luaL_error(L, "expecting exactly 3 arguments");

  luaL_checktype(L, 1, LUA_TSTRING);
  luaL_checktype(L, 2, LUA_TSTRING);
  luaL_checktype(L, 3, LUA_TSTRING);

  const char* cref = lua_tostring(L, 1);
  const char* initialization = lua_tostring(L, 2);
  const char* simulation = lua_tostring(L, 3);

  oms_status_enu_t status = oms3_exportDependencyGraphs(cref, initialization, simulation);
  lua_pushinteger(L, status);
  return 1;
}

//oms_status_enu_t oms3_parseModelName(const char* contents, char** cref);
static int OMSimulatorLua_oms3_parseModelName(lua_State *L)
{
  if (lua_gettop(L) != 1)
    return luaL_error(L, "expecting exactly 1 argument");
  luaL_checktype(L, 1, LUA_TSTRING);

  const char* contents = lua_tostring(L, 1);
  char* cref = NULL;
  oms_status_enu_t status = oms3_parseModelName(contents, &cref);

  lua_pushstring(L, cref ? cref : "");
  lua_pushinteger(L, status);

  if (cref)
    oms3_freeMemory(cref);

  return 2;
}

//int oms3_compareSimulationResults(const char* filenameA, const char* filenameB, const char* var, double relTol, double absTol);
static int OMSimulatorLua_oms3_compareSimulationResults(lua_State *L)
{
  if (lua_gettop(L) != 5)
    return luaL_error(L, "expecting exactly 5 arguments");
  luaL_checktype(L, 1, LUA_TSTRING);
  luaL_checktype(L, 2, LUA_TSTRING);
  luaL_checktype(L, 3, LUA_TSTRING);
  luaL_checktype(L, 4, LUA_TNUMBER);
  luaL_checktype(L, 5, LUA_TNUMBER);

  const char *filenameA = lua_tostring(L, 1);
  const char *filenameB = lua_tostring(L, 2);
  const char *var = lua_tostring(L, 3);
  double relTol = lua_tonumber(L, 4);
  double absTol = lua_tonumber(L, 5);
  int rc = oms3_compareSimulationResults(filenameA, filenameB, var, relTol, absTol);
  lua_pushinteger(L, rc);
  return 1;
}

//oms_status_enu_t oms3_importString(const char* contents, char** cref);
static int OMSimulatorLua_oms3_importString(lua_State *L)
{
  if (lua_gettop(L) != 1)
    return luaL_error(L, "expecting exactly 1 argument");
  luaL_checktype(L, 1, LUA_TSTRING);

  const char* contents = lua_tostring(L, 1);
  char* cref = NULL;
  oms_status_enu_t status = oms3_importString(contents, &cref);

  lua_pushstring(L, cref ? cref : "");
  lua_pushinteger(L, status);

  return 2;
}

//oms_status_enu_t oms3_addSystem(const char* cref, oms_system_enu_t type);
static int OMSimulatorLua_oms3_addSystem(lua_State *L)
{
  if (lua_gettop(L) != 2)
    return luaL_error(L, "expecting exactly 2 arguments");
  luaL_checktype(L, 1, LUA_TSTRING);
  luaL_checktype(L, 2, LUA_TNUMBER);

  const char* cref = lua_tostring(L, 1);
  int type = lua_tointeger(L, 2);
  oms_status_enu_t status = oms3_addSystem(cref, (oms_system_enu_t)type);

  lua_pushinteger(L, status);

  return 1;
}

//oms_status_enu_t oms3_copySystem(const char* source, const char* target);
static int OMSimulatorLua_oms3_copySystem(lua_State *L)
{
  if (lua_gettop(L) != 2)
    return luaL_error(L, "expecting exactly 2 arguments");
  luaL_checktype(L, 1, LUA_TSTRING);
  luaL_checktype(L, 2, LUA_TSTRING);

  const char* source = lua_tostring(L, 1);
  const char* target = lua_tostring(L, 2);
  oms_status_enu_t status = oms3_copySystem(source, target);

  lua_pushinteger(L, status);

  return 1;
}

//oms_status_enu_t oms3_setCommandLineOption(const char* cmd);
static int OMSimulatorLua_oms3_setCommandLineOption(lua_State *L)
{
  if (lua_gettop(L) != 1)
    return luaL_error(L, "expecting exactly 1 argument");
  luaL_checktype(L, 1, LUA_TSTRING);

  const char* cmd = lua_tostring(L, 1);
  oms_status_enu_t status = oms3_setCommandLineOption(cmd);

  lua_pushinteger(L, status);

  return 1;
}

//oms_status_enu_t oms3_getSystemType(const char* cref, oms_system_enu_t* type);
static int OMSimulatorLua_oms3_getSystemType(lua_State *L)
{
  if (lua_gettop(L) != 1)
    return luaL_error(L, "expecting exactly 1 argument");
  luaL_checktype(L, 1, LUA_TSTRING);

  const char* cref = lua_tostring(L, 1);
  oms_system_enu_t type;
  oms_status_enu_t status = oms3_getSystemType(cref, &type);

  lua_pushinteger(L, type);
  lua_pushinteger(L, status);

  return 2;
}

//oms_status_enu_t oms3_getBoolean(const char* cref, bool* value);
static int OMSimulatorLua_oms3_getBoolean(lua_State *L)
{
  if (lua_gettop(L) != 1)
    return luaL_error(L, "expecting exactly 1 argument");
  luaL_checktype(L, 1, LUA_TSTRING);

  const char* cref = lua_tostring(L, 1);
  bool value = 0.0;

  oms_status_enu_t status = oms3_getBoolean(cref, &value);
  lua_pushinteger(L, value);
  lua_pushinteger(L, status);
  return 2;
}

//oms_status_enu_t oms3_getInteger(const char* cref, bool* value);
static int OMSimulatorLua_oms3_getInteger(lua_State *L)
{
  if (lua_gettop(L) != 1)
    return luaL_error(L, "expecting exactly 1 argument");
  luaL_checktype(L, 1, LUA_TSTRING);

  const char* cref = lua_tostring(L, 1);
  int value = 0.0;

  oms_status_enu_t status = oms3_getInteger(cref, &value);
  lua_pushinteger(L, value);
  lua_pushinteger(L, status);
  return 2;
}

//oms_status_enu_t oms3_getReal(const char* cref, double* value);
static int OMSimulatorLua_oms3_getReal(lua_State *L)
{
  if (lua_gettop(L) != 1)
    return luaL_error(L, "expecting exactly 1 argument");
  luaL_checktype(L, 1, LUA_TSTRING);

  const char* cref = lua_tostring(L, 1);
  double value = 0.0;

  oms_status_enu_t status = oms3_getReal(cref, &value);
  lua_pushnumber(L, value);
  lua_pushinteger(L, status);
  return 2;
}

//oms_status_enu_t oms3_setBoolean(const char* cref, double* value);
static int OMSimulatorLua_oms3_setBoolean(lua_State *L)
{
  if (lua_gettop(L) != 2)
    return luaL_error(L, "expecting exactly 2 arguments");
  luaL_checktype(L, 1, LUA_TSTRING);
  luaL_checktype(L, 2, LUA_TNUMBER);

  const char* cref = lua_tostring(L, 1);
  bool value = lua_tointeger(L, 2);

  oms_status_enu_t status = oms3_setBoolean(cref, value);
  lua_pushinteger(L, status);
  return 1;
}

//oms_status_enu_t oms3_setInteger(const char* cref, double* value);
static int OMSimulatorLua_oms3_setInteger(lua_State *L)
{
  if (lua_gettop(L) != 2)
    return luaL_error(L, "expecting exactly 2 arguments");
  luaL_checktype(L, 1, LUA_TSTRING);
  luaL_checktype(L, 2, LUA_TNUMBER);

  const char* cref = lua_tostring(L, 1);
  int value = lua_tointeger(L, 2);

  oms_status_enu_t status = oms3_setInteger(cref, value);
  lua_pushinteger(L, status);
  return 1;
}

//oms_status_enu_t oms3_setReal(const char* cref, double* value);
static int OMSimulatorLua_oms3_setReal(lua_State *L)
{
  if (lua_gettop(L) != 2)
    return luaL_error(L, "expecting exactly 2 arguments");
  luaL_checktype(L, 1, LUA_TSTRING);
  luaL_checktype(L, 2, LUA_TNUMBER);

  const char* cref = lua_tostring(L, 1);
  double value = lua_tonumber(L, 2);

  oms_status_enu_t status = oms3_setReal(cref, value);
  lua_pushinteger(L, status);
  return 1;
}

//oms_status_enu_t oms3_addConnector(const char *cref, oms_causality_enu_t causality, oms_signal_type_enu_t type);
static int OMSimulatorLua_oms3_addConnector(lua_State *L)
{
  if (lua_gettop(L) != 3)
    return luaL_error(L, "expecting exactly 3 arguments");
  luaL_checktype(L, 1, LUA_TSTRING);
  luaL_checktype(L, 2, LUA_TNUMBER);
  luaL_checktype(L, 3, LUA_TNUMBER);

  const char* cref = lua_tostring(L, 1);
  int causality = lua_tointeger(L, 2);
  int type = lua_tointeger(L, 3);
  oms_status_enu_t status = oms3_addConnector(cref, (oms_causality_enu_t)causality, (oms_signal_type_enu_t)type);

  lua_pushinteger(L, status);

  return 1;
}

//oms_status_enu_t oms3_addConnection(const char *crefA, const char *crefB);
static int OMSimulatorLua_oms3_addConnection(lua_State *L)
{
  if (lua_gettop(L) != 2)
    return luaL_error(L, "expecting exactly 2 arguments");
  luaL_checktype(L, 1, LUA_TSTRING);
  luaL_checktype(L, 2, LUA_TSTRING);

  const char* crefA = lua_tostring(L, 1);
  const char* crefB = lua_tostring(L, 2);
  oms_status_enu_t status = oms3_addConnection(crefA, crefB);

  lua_pushinteger(L, status);

  return 1;
}

//oms_status_enu_t oms3_deleteConnection(const char *crefA, const char *crefB)
static int OMSimulatorLua_oms3_deleteConnection(lua_State *L)
{
  if (lua_gettop(L) != 2)
    return luaL_error(L, "expecting exactly 2 arguments");
  luaL_checktype(L, 1, LUA_TSTRING);
  luaL_checktype(L, 2, LUA_TSTRING);

  const char* crefA = lua_tostring(L, 1);
  const char* crefB = lua_tostring(L, 2);
  oms_status_enu_t status = oms3_deleteConnection(crefA, crefB);

  lua_pushinteger(L, status);

  return 1;
}

//oms_status_enu_t oms3_addBus(const char *cref);
static int OMSimulatorLua_oms3_addBus(lua_State *L)
{
  if (lua_gettop(L) != 1)
    return luaL_error(L, "expecting exactly 1 arguments");
  luaL_checktype(L, 1, LUA_TSTRING);

  const char* cref = lua_tostring(L, 1);
  oms_status_enu_t status = oms3_addBus(cref);

  lua_pushinteger(L, status);

  return 1;
}

//oms_status_enu_t oms3_addTLMBus(const char *cref, oms_tlm_domain_t domain, const char *dimension, const char *interpolation)
static int OMSimulatorLua_oms3_addTLMBus(lua_State *L)
{
  if (lua_gettop(L) != 3 && lua_gettop(L) != 4)
    return luaL_error(L, "expecting exactly 3 or 4 arguments");
  luaL_checktype(L, 1, LUA_TSTRING);
  luaL_checktype(L, 2, LUA_TNUMBER);
  luaL_checktype(L, 3, LUA_TNUMBER);
  if(lua_gettop(L) > 3)
    luaL_checktype(L, 4, LUA_TNUMBER);

  const char* cref = lua_tostring(L, 1);
  int domain = lua_tointeger(L, 2);
  int dimensions = lua_tointeger(L, 3);
  int interpolation = (int)oms_tlm_no_interpolation;
  if(lua_gettop(L) > 3)
    interpolation = lua_tointeger(L, 4);

  oms_status_enu_t status = oms3_addTLMBus(cref, (oms_tlm_domain_t)domain, dimensions, (oms_tlm_interpolation_t)interpolation);

  lua_pushinteger(L, status);

  return 1;
}

//oms_status_enu_t oms3_addConnectorToBus(const char *busCref, const char *connectorCref)
static int OMSimulatorLua_oms3_addConnectorToBus(lua_State *L)
{
  if (lua_gettop(L) != 2)
    return luaL_error(L, "expecting exactly 2 arguments");
  luaL_checktype(L, 1, LUA_TSTRING);
  luaL_checktype(L, 2, LUA_TSTRING);

  const char* busCref = lua_tostring(L, 1);
  const char* connectorCref = lua_tostring(L, 2);
  oms_status_enu_t status = oms3_addConnectorToBus(busCref,connectorCref);

  lua_pushinteger(L, status);

  return 1;
}

//oms_status_enu_t oms3_deleteConnectorFromBus(const char *busCref, const char *connectorCref)
static int OMSimulatorLua_oms3_deleteConnectorFromBus(lua_State *L)
{
  if (lua_gettop(L) != 2)
    return luaL_error(L, "expecting exactly 2 arguments");
  luaL_checktype(L, 1, LUA_TSTRING);
  luaL_checktype(L, 2, LUA_TSTRING);

  const char* busCref = lua_tostring(L, 1);
  const char* connectorCref = lua_tostring(L, 2);
  oms_status_enu_t status = oms3_deleteConnectorFromBus(busCref,connectorCref);

  lua_pushinteger(L, status);

  return 1;
}

//oms_status_enu_t oms3_addConnectorToTLMBus(const char* busCref, const char* connectorCref, const char* type);
static int OMSimulatorLua_oms3_addConnectorToTLMBus(lua_State *L)
{
  if (lua_gettop(L) != 3)
    return luaL_error(L, "expecting exactly 3 arguments");
  luaL_checktype(L, 1, LUA_TSTRING);
  luaL_checktype(L, 2, LUA_TSTRING);
  luaL_checktype(L, 3, LUA_TSTRING);

  const char* busCref = lua_tostring(L, 1);
  const char* connectorCref = lua_tostring(L, 2);
  const char* type = lua_tostring(L, 3);
  oms_status_enu_t status = oms3_addConnectorToTLMBus(busCref,connectorCref,type);

  lua_pushinteger(L, status);

  return 1;
}

//oms_status_enu_t oms3_deleteConnectorFromTLMBus(const char *busCref, const char *connectorCref)
static int OMSimulatorLua_oms3_deleteConnectorFromTLMBus(lua_State *L)
{
  if (lua_gettop(L) != 2)
    return luaL_error(L, "expecting exactly 2 arguments");
  luaL_checktype(L, 1, LUA_TSTRING);
  luaL_checktype(L, 2, LUA_TSTRING);

  const char* busCref = lua_tostring(L, 1);
  const char* connectorCref = lua_tostring(L, 2);
  oms_status_enu_t status = oms3_deleteConnectorFromTLMBus(busCref,connectorCref);

  lua_pushinteger(L, status);

  return 1;
}

//oms_status_enu_t oms3_addTLMConnection(const char *crefA, const char *crefB, double delay, double alpha, double Zf, double Zfr)
static int OMSimulatorLua_oms3_addTLMConnection(lua_State *L)
{
  if (lua_gettop(L) != 6)
    return luaL_error(L, "expecting exactly 6 arguments");
  luaL_checktype(L, 1, LUA_TSTRING);
  luaL_checktype(L, 2, LUA_TSTRING);
  luaL_checktype(L, 3, LUA_TNUMBER);
  luaL_checktype(L, 4, LUA_TNUMBER);
  luaL_checktype(L, 5, LUA_TNUMBER);
  luaL_checktype(L, 6, LUA_TNUMBER);

  const char* crefA = lua_tostring(L, 1);
  const char* crefB = lua_tostring(L, 2);
  double delay = lua_tonumber(L, 3);
  double alpha = lua_tonumber(L, 4);
  double linearimpedance = lua_tonumber(L, 5);
  double angularimpedance = lua_tonumber(L, 6);
  oms_status_enu_t status = oms3_addTLMConnection(crefA, crefB, delay, alpha, linearimpedance, angularimpedance);

  lua_pushinteger(L, status);

  return 1;
}

//oms_status_enu_t oms3_addExternalModel(const char *cref, const char *path, const char *startscript)
static int OMSimulatorLua_oms3_addExternalModel(lua_State *L)
{
  if (lua_gettop(L) != 3)
    return luaL_error(L, "expecting exactly 3 arguments");
  luaL_checktype(L, 1, LUA_TSTRING);
  luaL_checktype(L, 2, LUA_TSTRING);
  luaL_checktype(L, 3, LUA_TSTRING);

  const char* cref = lua_tostring(L, 1);
  const char* path = lua_tostring(L, 2);
  const char* startscript = lua_tostring(L, 3);
  oms_status_enu_t status = oms3_addExternalModel(cref, path, startscript);

  lua_pushinteger(L, status);

  return 1;
}

//oms_status_enu_t oms3_addSubModel(const char* cref, const char* fmuPath);
static int OMSimulatorLua_oms3_addSubModel(lua_State *L)
{
  if (lua_gettop(L) != 2)
    return luaL_error(L, "expecting exactly 2 arguments");
  luaL_checktype(L, 1, LUA_TSTRING);
  luaL_checktype(L, 2, LUA_TSTRING);

  const char* cref = lua_tostring(L, 1);
  const char* fmuPath = lua_tostring(L, 2);
  oms_status_enu_t status = oms3_addSubModel(cref, fmuPath);

  lua_pushinteger(L, status);

  return 1;
}

//oms_status_enu_t oms3_instantiate(const char* ident);
static int OMSimulatorLua_oms3_instantiate(lua_State *L)
{
  if (lua_gettop(L) != 1)
    return luaL_error(L, "expecting exactly 1 argument");
  luaL_checktype(L, 1, LUA_TSTRING);

  const char* ident = lua_tostring(L, 1);
  oms_status_enu_t status = oms3_instantiate(ident);
  lua_pushinteger(L, status);
  return 1;
}

//oms_status_enu_t oms3_initialize(const char* ident);
static int OMSimulatorLua_oms3_initialize(lua_State *L)
{
  if (lua_gettop(L) != 1)
    return luaL_error(L, "expecting exactly 1 argument");
  luaL_checktype(L, 1, LUA_TSTRING);

  const char* ident = lua_tostring(L, 1);
  oms_status_enu_t status = oms3_initialize(ident);
  lua_pushinteger(L, status);
  return 1;
}

//oms_status_enu_t oms3_terminate(const char* ident);
static int OMSimulatorLua_oms3_terminate(lua_State *L)
{
  if (lua_gettop(L) != 1)
    return luaL_error(L, "expecting exactly 1 argument");
  luaL_checktype(L, 1, LUA_TSTRING);

  const char* ident = lua_tostring(L, 1);
  oms_status_enu_t status = oms3_terminate(ident);
  lua_pushinteger(L, status);
  return 1;
}

//oms_status_enu_t oms3_reset(const char* ident);
static int OMSimulatorLua_oms3_reset(lua_State *L)
{
  if (lua_gettop(L) != 1)
    return luaL_error(L, "expecting exactly 1 argument");
  luaL_checktype(L, 1, LUA_TSTRING);

  const char* ident = lua_tostring(L, 1);
  oms_status_enu_t status = oms3_reset(ident);
  lua_pushinteger(L, status);
  return 1;
}

//oms_status_enu_t oms3_simulate(const char* cref);
static int OMSimulatorLua_oms3_simulate(lua_State *L)
{
  if (lua_gettop(L) != 1)
    return luaL_error(L, "expecting exactly 1 argument");
  luaL_checktype(L, 1, LUA_TSTRING);

  const char* cref = lua_tostring(L, 1);
  oms_status_enu_t status = oms3_simulate(cref);
  lua_pushinteger(L, status);
  return 1;
}

//oms_status_enu_t oms3_stepUntil(const char* cref, double stopTime);
static int OMSimulatorLua_oms3_stepUntil(lua_State *L)
{
  if (lua_gettop(L) != 2)
    return luaL_error(L, "expecting exactly 2 arguments");
  luaL_checktype(L, 1, LUA_TSTRING);
  luaL_checktype(L, 2, LUA_TNUMBER);

  const char* cref = lua_tostring(L, 1);
  double stopTime = lua_tonumber(L, 2);
  oms_status_enu_t status = oms3_stepUntil(cref, stopTime);
  lua_pushinteger(L, status);
  return 1;
}

//oms_status_enu_t oms3_getModelState(const char* cref, oms_modelState_enu_t* modelState);
static int OMSimulatorLua_oms3_getModelState(lua_State *L)
{
  if (lua_gettop(L) != 1)
    return luaL_error(L, "expecting exactly 1 argument");
  luaL_checktype(L, 1, LUA_TSTRING);

  const char* cref = lua_tostring(L, 1);
  oms_modelState_enu_t modelState = oms_modelState_terminated;

  oms_status_enu_t status = oms3_getModelState(cref, &modelState);
  lua_pushinteger(L, modelState);
  lua_pushinteger(L, status);
  return 2;
}

//oms_status_enu_t oms3_setTLMSocketData(const char* cref, const char* address, int managerPort, int monitorPort)
static int OMSimulatorLua_oms3_setTLMSocketData(lua_State *L)
{
  if (lua_gettop(L) != 4)
    return luaL_error(L, "expecting exactly 4 arguments");
  luaL_checktype(L, 1, LUA_TSTRING);
  luaL_checktype(L, 2, LUA_TSTRING);
  luaL_checktype(L, 3, LUA_TNUMBER);
  luaL_checktype(L, 4, LUA_TNUMBER);

  const char *cref =    lua_tostring(L, 1);
  const char *address = lua_tostring(L, 2);
  int managerPort =     lua_tonumber(L, 3);
  int monitorPort =     lua_tonumber(L, 4);

  oms_status_enu_t status = oms3_setTLMSocketData(cref, address, managerPort, monitorPort);
  lua_pushinteger(L, status);
  return 1;
}

//oms_status_enu_t oms3_setTLMPositionAndOrientation(const char *cref, double x1, double x2, double x3, double A11, double A12, double A13, double A21, double A22, double A23, double A31, double A32, double A33)
static int OMSimulatorLua_oms3_setTLMPositionAndOrientation(lua_State *L)
{
  if (lua_gettop(L) != 13)
    return luaL_error(L, "expecting exactly 13 arguments");

  luaL_checktype(L, 1, LUA_TSTRING);
  const char *cref =  lua_tostring(L, 1);
  int i;

  //Position
  double x[3];
  for(i=0; i<3; ++i) {
    luaL_checktype(L, i+2, LUA_TNUMBER);
    x[i] = lua_tonumber(L, i+2);
  }

  //Orientation (3x3 matrix, stored as 1x9 vector)
  double A[9];
  for(i=0; i<9; ++i) {
    luaL_checktype(L, i+5, LUA_TNUMBER);
    A[i] = lua_tonumber(L, i+5);
  }

  oms_status_enu_t status = oms3_setTLMPositionAndOrientation(cref,
                                                              x[0], x[1], x[2],
                                                              A[0], A[1], A[2],
                                                              A[3], A[4], A[5],
                                                              A[6], A[7], A[8]);

  lua_pushinteger(L, status);
  return 1;
}

//oms_status_enu_t oms3_setResultFile(const char* cref, const char* filename, unsigned int bufferSize);
static int OMSimulatorLua_oms3_setResultFile(lua_State *L)
{
  if (lua_gettop(L) != 2 && lua_gettop(L) != 3)
    return luaL_error(L, "expecting 2 or 3 arguments");
  luaL_checktype(L, 1, LUA_TSTRING);
  luaL_checktype(L, 2, LUA_TSTRING);

  const char* cref = lua_tostring(L, 1);
  const char* filename = lua_tostring(L, 2);

  unsigned int bufferSize = 1;
  if (lua_gettop(L) == 3)
  {
    luaL_checktype(L, 3, LUA_TNUMBER);
    bufferSize = lua_tonumber(L, 3);
  }
  oms_status_enu_t status = oms3_setResultFile(cref, filename, bufferSize);
  lua_pushinteger(L, status);
  return 1;
}

//oms_status_enu_t oms3_setSignalFilter(const char* cref, const char* regex)
static int OMSimulatorLua_oms3_setSignalFilter(lua_State *L)
{
  if (lua_gettop(L) != 2)
    return luaL_error(L, "expecting exactly 2 argument");
  luaL_checktype(L, 1, LUA_TSTRING);

  const char* cref = lua_tostring(L, 1);
  const char* regex = lua_tostring(L, 2);
  oms_status_enu_t status = oms3_setSignalFilter(cref, regex);
  lua_pushinteger(L, status);
  return 1;
}

//oms_status_enu_t oms3_addSignalsToResults(const char* cref, const char* regex);
static int OMSimulatorLua_oms3_addSignalsToResults(lua_State *L)
{
  if (lua_gettop(L) != 2)
    return luaL_error(L, "expecting exactly 2 argument");
  luaL_checktype(L, 1, LUA_TSTRING);

  const char* cref = lua_tostring(L, 1);
  const char* regex = lua_tostring(L, 2);
  oms_status_enu_t status = oms3_addSignalsToResults(cref, regex);
  lua_pushinteger(L, status);
  return 1;
}

//oms_status_enu_t oms3_removeSignalsFromResults(const char* cref, const char* regex);
static int OMSimulatorLua_oms3_removeSignalsFromResults(lua_State *L)
{
  if (lua_gettop(L) != 2)
    return luaL_error(L, "expecting exactly 2 argument");
  luaL_checktype(L, 1, LUA_TSTRING);

  const char* cref = lua_tostring(L, 1);
  const char* regex = lua_tostring(L, 2);
  oms_status_enu_t status = oms3_removeSignalsFromResults(cref, regex);
  lua_pushinteger(L, status);
  return 1;
}

//oms_status_enu_t oms3_getStartTime(const char* cref, double* startTime);
static int OMSimulatorLua_oms3_getStartTime(lua_State *L)
{
  if (lua_gettop(L) != 1)
    return luaL_error(L, "expecting exactly 1 argument");
  luaL_checktype(L, 1, LUA_TSTRING);

  const char* cref = lua_tostring(L, 1);
  double startTime = 0.0;
  oms_status_enu_t status = oms3_getStartTime(cref, &startTime);
  lua_pushnumber(L, startTime);
  lua_pushinteger(L, status);
  return 2;
}

//oms_status_enu_t oms3_setStartTime(const char* cref, double startTime);
static int OMSimulatorLua_oms3_setStartTime(lua_State *L)
{
  if (lua_gettop(L) != 2)
    return luaL_error(L, "expecting exactly 2 arguments");
  luaL_checktype(L, 1, LUA_TSTRING);
  luaL_checktype(L, 2, LUA_TNUMBER);

  const char* cref = lua_tostring(L, 1);
  double startTime = lua_tonumber(L, 2);
  oms_status_enu_t status = oms3_setStartTime(cref, startTime);
  lua_pushinteger(L, status);
  return 1;
}

//oms_status_enu_t oms3_getStopTime(const char* cref, double* stopTime);
static int OMSimulatorLua_oms3_getStopTime(lua_State *L)
{
  if (lua_gettop(L) != 1)
    return luaL_error(L, "expecting exactly 1 argument");
  luaL_checktype(L, 1, LUA_TSTRING);

  const char* cref = lua_tostring(L, 1);
  double stopTime = 1.0;
  oms_status_enu_t status = oms3_getStopTime(cref, &stopTime);
  lua_pushnumber(L, stopTime);
  lua_pushinteger(L, status);
  return 2;
}

//oms_status_enu_t oms3_setStopTime(const char* cref, double stopTime);
static int OMSimulatorLua_oms3_setStopTime(lua_State *L)
{
  if (lua_gettop(L) != 2)
    return luaL_error(L, "expecting exactly 2 arguments");
  luaL_checktype(L, 1, LUA_TSTRING);
  luaL_checktype(L, 2, LUA_TNUMBER);

  const char* cref = lua_tostring(L, 1);
  double startTime = lua_tonumber(L, 2);
  oms_status_enu_t status = oms3_setStopTime(cref, startTime);
  lua_pushinteger(L, status);
  return 1;
}

//oms_status_enu_t oms3_setFixedStepSize(const char* cref, double stepSize);
static int OMSimulatorLua_oms3_setFixedStepSize(lua_State *L)
{
  if (lua_gettop(L) != 2)
    return luaL_error(L, "expecting exactly 2 arguments");
  luaL_checktype(L, 1, LUA_TSTRING);
  luaL_checktype(L, 2, LUA_TNUMBER);

  const char* cref = lua_tostring(L, 1);
  double stepSize = lua_tonumber(L, 2);
  oms_status_enu_t status = oms3_setFixedStepSize(cref, stepSize);
  lua_pushinteger(L, status);
  return 1;
}

/* **************************************************** */
/* OMSysIdent API                                       */
/* **************************************************** */

#ifdef WITH_OMSYSIDENT
//void* omsi_newSysIdentModel(const char* ident);
static int OMSimulatorLua_omsi_newSysIdentModel(lua_State *L)
{
  if (lua_gettop(L) != 1)
    return luaL_error(L, "expecting exactly 1 argument");
  luaL_checktype(L, 1, LUA_TSTRING);

  const char* ident = lua_tostring(L, 1);

  void *pModel = omsi_newSysIdentModel(ident);
  push_pointer(L, pModel);
  return 1;
}

//void omsi_freeSysIdentModel(void* simodel);
static int OMSimulatorLua_omsi_freeSysIdentModel(lua_State *L)
{
  if (lua_gettop(L) != 1)
    return luaL_error(L, "expecting exactly 1 argument");
  luaL_checktype(L, 1, LUA_TUSERDATA);

  void *model = topointer(L, 1);
  omsi_freeSysIdentModel(model);
  return 0;
}

//void oms_setReal(void* model, const char* var, double value);
// oms_status_enu_t omsi_initialize(void* simodel, size_t nSeries, const double* time, size_t nTime, char const* const* inputvars, size_t nInputvars, char const* const* measurementvars, size_t nMeasurementvars);
static int OMSimulatorLua_omsi_initialize(lua_State *L)
{
  if (lua_gettop(L) != 5)
    return luaL_error(L, "expecting exactly 5 arguments");
  luaL_checktype(L, 1, LUA_TUSERDATA); // simodel
  luaL_checktype(L, 2, LUA_TNUMBER);   // nSeries
  luaL_checktype(L, 3, LUA_TTABLE);    // time
  luaL_checktype(L, 4, LUA_TTABLE);    // inputvars
  luaL_checktype(L, 5, LUA_TTABLE);    // measurementvars
  // luaL_checktype(L, 2, LUA_TSTRING);

  void *model = topointer(L, 1);
  size_t nSeries = lua_tonumber(L, 2);

  // get size of tables
  size_t nTime = luaL_len(L, 3);
  size_t nInputvars = luaL_len(L, 4);
  size_t nMeasurementvars = luaL_len(L, 5);
  // create buffers
  double* time = (double*) malloc(nTime*sizeof(double));
  char const* * inputvars = (char const**) malloc(nInputvars*sizeof(char const *));
  char const* * measurementvars = (char const**) malloc(nMeasurementvars*sizeof(char const *));

  //printf("nTime: %d, nInputvars: %d, nMeasurementvars %d\n", (int)nTime, (int)nInputvars, (int)nMeasurementvars);

  int i;
  for (i=0; i < nTime; ++i) {
    lua_rawgeti(L, 3, i+1); // push value on stack
    time[i] = lua_tonumber(L, -1);
    lua_pop(L, 1); // pop value from stack
  }

  for (i=0; i < nInputvars; ++i) {
    lua_rawgeti(L, 4, i+1);
    inputvars[i] = lua_tostring(L, -1);
    lua_pop(L, 1);
  }

  for (i=0; i < nMeasurementvars; ++i) {
    lua_rawgeti(L, 5, i+1);
    measurementvars[i] = lua_tostring(L, -1);
    lua_pop(L, 1);
  }

  oms_status_enu_t returnValue =
    omsi_initialize(model, nSeries, time, nTime, inputvars, nInputvars, measurementvars, nMeasurementvars);
  lua_pushinteger(L, returnValue);

  free(time); free(inputvars); free(measurementvars);
  return 1;
}

//oms_status_enu_t omsi_describe(void* simodel);
static int OMSimulatorLua_omsi_describe(lua_State *L)
{
  if (lua_gettop(L) != 1)
    return luaL_error(L, "expecting exactly 1 argument");
  luaL_checktype(L, 1, LUA_TUSERDATA);

  void *model = topointer(L, 1);
  oms_status_enu_t returnValue = omsi_describe(model);
  lua_pushinteger(L, returnValue);
  return 1;
}

// oms_status_enu_t omsi_addMeasurement(void* simodel, size_t iSeries, const char* var, const double* values, size_t nValues);
static int OMSimulatorLua_omsi_addMeasurement(lua_State *L)
{
  if (lua_gettop(L) != 4)
    return luaL_error(L, "expecting exactly 4 arguments");
  luaL_checktype(L, 1, LUA_TUSERDATA); // simodel
  luaL_checktype(L, 2, LUA_TNUMBER);   // iSeries
  luaL_checktype(L, 3, LUA_TSTRING);   // var
  luaL_checktype(L, 4, LUA_TTABLE);    // values

  void *model = topointer(L, 1);
  size_t iSeries = lua_tonumber(L, 2);
  const char* var = lua_tostring(L, 3);
  size_t nValues = luaL_len(L, 4);

  double* values = (double*) malloc(nValues*sizeof(double));
  int i;
  for (i=0; i < nValues; ++i) {
    lua_rawgeti(L, 4, i+1); // push value on stack
    values[i] = lua_tonumber(L, -1);
    lua_pop(L, 1); // pop value from stack
  }

  oms_status_enu_t returnValue =
    omsi_addMeasurement(model, iSeries, var, values, nValues);
  lua_pushinteger(L, returnValue);

  free(values);
  return 1;
}

// oms_status_enu_t omsi_addInput(void* simodel, const char* var, const double* values, size_t nValues);
static int OMSimulatorLua_omsi_addInput(lua_State *L)
{
  if (lua_gettop(L) != 3)
    return luaL_error(L, "expecting exactly 3 arguments");
  luaL_checktype(L, 1, LUA_TUSERDATA); // simodel
  luaL_checktype(L, 2, LUA_TSTRING);   // var
  luaL_checktype(L, 3, LUA_TTABLE);    // values

  void *model = topointer(L, 1);
  const char* var = lua_tostring(L, 2);
  size_t nValues = luaL_len(L, 3);

  double* values = (double*) malloc(nValues*sizeof(double));
  int i;
  for (i=0; i < nValues; ++i) {
    lua_rawgeti(L, 3, i+1); // push value on stack
    values[i] = lua_tonumber(L, -1);
    lua_pop(L, 1); // pop value from stack
  }

  oms_status_enu_t returnValue =
    omsi_addInput(model, var, values, nValues);
  lua_pushinteger(L, returnValue);

  free(values);
  return 1;
}

// oms_status_enu_t omsi_addParameter(void* simodel, const char* var, double startvalue);
static int OMSimulatorLua_omsi_addParameter(lua_State *L)
{
  if (lua_gettop(L) != 3)
    return luaL_error(L, "expecting exactly 3 arguments");
  luaL_checktype(L, 1, LUA_TUSERDATA); // simodel
  luaL_checktype(L, 2, LUA_TSTRING);   // var
  luaL_checktype(L, 3, LUA_TNUMBER);   // startvalue

  void *model = topointer(L, 1);
  const char* var = lua_tostring(L, 2);
  double startvalue = lua_tonumber(L, 3);

  oms_status_enu_t returnValue =
    omsi_addParameter(model, var, startvalue);
  lua_pushinteger(L, returnValue);
  return 1;
}

// oms_status_enu_t omsi_getParameter(void* simodel, const char* var, double* startvalue, double* estimatedvalue);
static int OMSimulatorLua_omsi_getParameter(lua_State *L)
{
  if (lua_gettop(L) != 2)
    return luaL_error(L, "expecting exactly 2 arguments");
  luaL_checktype(L, 1, LUA_TUSERDATA); // simodel
  luaL_checktype(L, 2, LUA_TSTRING);   // var

  void *model = topointer(L, 1);
  const char* var = lua_tostring(L, 2);

  double startvalue, estimatedvalue;
  oms_status_enu_t returnValue =
    omsi_getParameter(model, var, &startvalue, &estimatedvalue);
  lua_pushinteger(L, returnValue);
  lua_pushnumber(L, startvalue);
  lua_pushnumber(L, estimatedvalue);
  return 3;
}

// oms_status_enu_t omsi_solve(void* simodel, const char* reporttype);
static int OMSimulatorLua_omsi_solve(lua_State *L)
{
  if (lua_gettop(L) != 2)
    return luaL_error(L, "expecting exactly 2 arguments");
  luaL_checktype(L, 1, LUA_TUSERDATA); // simodel
  luaL_checktype(L, 2, LUA_TSTRING);   // reporttype

  void *model = topointer(L, 1);
  const char* reporttype = lua_tostring(L, 2);

  oms_status_enu_t returnValue =
    omsi_solve(model, reporttype);
  lua_pushinteger(L, returnValue);
  return 1;
}

// oms_status_enu_t omsi_setOptions_max_num_iterations(void* simodel, size_t max_num_iterations);
static int OMSimulatorLua_omsi_setOptions_max_num_iterations(lua_State *L)
{
  if (lua_gettop(L) != 2)
    return luaL_error(L, "expecting exactly 2 arguments");
  luaL_checktype(L, 1, LUA_TUSERDATA); // simodel
  luaL_checktype(L, 2, LUA_TNUMBER);   // max_num_iterations

  void *model = topointer(L, 1);
  int max_num_iterations = lua_tointeger(L, 2);

  oms_status_enu_t returnValue =
    omsi_setOptions_max_num_iterations(model, max_num_iterations);
  lua_pushinteger(L, returnValue);
  return 1;
}

// oms_status_enu_t omsi_getState(void* simodel, omsi_simodelstate_t* state);
static int OMSimulatorLua_omsi_getState(lua_State *L)
{
  if (lua_gettop(L) != 1)
    return luaL_error(L, "expecting exactly 1 argument");
  luaL_checktype(L, 1, LUA_TUSERDATA); // simodel

  void *model = topointer(L, 1);

  omsi_simodelstate_t state;
  oms_status_enu_t returnValue =
    omsi_getState(model, &state);
  lua_pushinteger(L, returnValue);
  switch (state) {
    case omsi_simodelstate_constructed: lua_pushstring(L, "constructed"); break;
    case omsi_simodelstate_initialized: lua_pushstring(L, "initialized"); break;
    case omsi_simodelstate_convergence: lua_pushstring(L, "convergence"); break;
    case omsi_simodelstate_no_convergence: lua_pushstring(L, "no_convergence"); break;
    case omsi_simodelstate_failure: lua_pushstring(L, "failure"); break;
  }
  return 2;
}
#endif /* WITH_OMSYSIDENT */

DLLEXPORT int luaopen_OMSimulatorLua(lua_State *L)
{
  /* ************************************ */
  /* oms3                                 */
  /*                                      */
  /* ************************************ */
  REGISTER_LUA_CALL(oms3_addBus);
  REGISTER_LUA_CALL(oms3_addConnection);
  REGISTER_LUA_CALL(oms3_addConnector);
  REGISTER_LUA_CALL(oms3_addConnectorToBus);
  REGISTER_LUA_CALL(oms3_addConnectorToTLMBus);
  REGISTER_LUA_CALL(oms3_addExternalModel);
  REGISTER_LUA_CALL(oms3_addSignalsToResults);
  REGISTER_LUA_CALL(oms3_addSubModel);
  REGISTER_LUA_CALL(oms3_addSystem);
  REGISTER_LUA_CALL(oms3_addTLMBus);
  REGISTER_LUA_CALL(oms3_addTLMConnection);
  REGISTER_LUA_CALL(oms3_compareSimulationResults);
  REGISTER_LUA_CALL(oms3_copySystem);
  REGISTER_LUA_CALL(oms3_delete);
  REGISTER_LUA_CALL(oms3_deleteConnection);
  REGISTER_LUA_CALL(oms3_deleteConnectorFromBus);
  REGISTER_LUA_CALL(oms3_deleteConnectorFromTLMBus);
  REGISTER_LUA_CALL(oms3_export);
  REGISTER_LUA_CALL(oms3_exportDependencyGraphs);
  REGISTER_LUA_CALL(oms3_getBoolean);
  REGISTER_LUA_CALL(oms3_getInteger);
  REGISTER_LUA_CALL(oms3_getReal);
  REGISTER_LUA_CALL(oms3_getStartTime);
  REGISTER_LUA_CALL(oms3_getStopTime);
  REGISTER_LUA_CALL(oms3_getSystemType);
  REGISTER_LUA_CALL(oms3_getVersion);
  REGISTER_LUA_CALL(oms3_import);
  REGISTER_LUA_CALL(oms3_importString);
  REGISTER_LUA_CALL(oms3_initialize);
  REGISTER_LUA_CALL(oms3_instantiate);
  REGISTER_LUA_CALL(oms3_list);
  REGISTER_LUA_CALL(oms3_listUnconnectedConnectors);
  REGISTER_LUA_CALL(oms3_newModel);
  REGISTER_LUA_CALL(oms3_parseModelName);
  REGISTER_LUA_CALL(oms3_removeSignalsFromResults);
  REGISTER_LUA_CALL(oms3_rename);
  REGISTER_LUA_CALL(oms3_reset);
  REGISTER_LUA_CALL(oms3_setBoolean);
  REGISTER_LUA_CALL(oms3_setCommandLineOption);
  REGISTER_LUA_CALL(oms3_setFixedStepSize);
  REGISTER_LUA_CALL(oms3_setInteger);
  REGISTER_LUA_CALL(oms3_setLogFile);
  REGISTER_LUA_CALL(oms3_setLoggingInterval);
  REGISTER_LUA_CALL(oms3_setLoggingLevel);
  REGISTER_LUA_CALL(oms3_setMaxLogFileSize);
  REGISTER_LUA_CALL(oms3_setReal);
  REGISTER_LUA_CALL(oms3_setResultFile);
  REGISTER_LUA_CALL(oms3_setSignalFilter);
  REGISTER_LUA_CALL(oms3_setStartTime);
  REGISTER_LUA_CALL(oms3_setStopTime);
  REGISTER_LUA_CALL(oms3_setTempDirectory);
  REGISTER_LUA_CALL(oms3_setTLMPositionAndOrientation);
  REGISTER_LUA_CALL(oms3_setTLMSocketData);
  REGISTER_LUA_CALL(oms3_setTolerance);
  REGISTER_LUA_CALL(oms3_setWorkingDirectory);
  REGISTER_LUA_CALL(oms3_simulate);
  REGISTER_LUA_CALL(oms3_stepUntil);
  REGISTER_LUA_CALL(oms3_terminate);

  /* ************************************ */
  /* OMSysIdent API                       */
  /* ************************************ */
#ifdef WITH_OMSYSIDENT
  REGISTER_LUA_CALL(omsi_addMeasurement);
  REGISTER_LUA_CALL(omsi_addInput);
  REGISTER_LUA_CALL(omsi_addParameter);
  REGISTER_LUA_CALL(omsi_describe);
  REGISTER_LUA_CALL(omsi_freeSysIdentModel);
  REGISTER_LUA_CALL(omsi_getParameter);
  REGISTER_LUA_CALL(omsi_getState);
  REGISTER_LUA_CALL(omsi_initialize);
  REGISTER_LUA_CALL(omsi_newSysIdentModel);
  REGISTER_LUA_CALL(omsi_setOptions_max_num_iterations);
  REGISTER_LUA_CALL(omsi_solve);
#endif /* WITH_OMSYSIDENT */

  // Add enumerable constants
  lua_pushnumber(L, 0);
  lua_setglobal(L, "input");
  lua_pushnumber(L, 1);
  lua_setglobal(L, "output");
  lua_pushnumber(L, 3);
  lua_setglobal(L, "bidirectional");

  lua_pushnumber(L, 0);
  lua_setglobal(L, "default");
  lua_pushnumber(L, 1);
  lua_setglobal(L, "coarsegrained");
  lua_pushnumber(L, 2);
  lua_setglobal(L, "finegrained");

  // oms_system_enu_t
  REGISTER_LUA_ENUM(oms_system_none);
  REGISTER_LUA_ENUM(oms_system_tlm);
  REGISTER_LUA_ENUM(oms_system_wc);
  REGISTER_LUA_ENUM(oms_system_sc);

  // oms_status_enu_t
  REGISTER_LUA_ENUM(oms_status_ok);
  REGISTER_LUA_ENUM(oms_status_warning);
  REGISTER_LUA_ENUM(oms_status_discard);
  REGISTER_LUA_ENUM(oms_status_error);
  REGISTER_LUA_ENUM(oms_status_fatal);
  REGISTER_LUA_ENUM(oms_status_pending);

  // oms_signal_type_enu_t
  REGISTER_LUA_ENUM(oms_signal_type_real);
  REGISTER_LUA_ENUM(oms_signal_type_integer);
  REGISTER_LUA_ENUM(oms_signal_type_boolean);
  REGISTER_LUA_ENUM(oms_signal_type_string);

  // oms_tlm_domain_t
  REGISTER_LUA_ENUM(oms_tlm_domain_input);
  REGISTER_LUA_ENUM(oms_tlm_domain_output);
  REGISTER_LUA_ENUM(oms_tlm_domain_mechanical);
  REGISTER_LUA_ENUM(oms_tlm_domain_rotational);
  REGISTER_LUA_ENUM(oms_tlm_domain_hydraulic);
  REGISTER_LUA_ENUM(oms_tlm_domain_electric);

  return 0;
}
