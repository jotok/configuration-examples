/* get_parm_lua.c -- read the lua-based parameter file */

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

#include <stdio.h>

int
main(void) {
    lua_State *L = luaL_newstate();
    luaL_dofile(L, "param_file_desc.lua");
    luaL_dofile(L, "params.lua");

    lua_getglobal(L, "config");
    lua_getfield(L, -1, "directory");
    const char *directory = lua_tostring(L, -1);
    printf("directory: %s\n", directory);
    lua_pop(L, 1);

    lua_getfield(L, -1, "filea");
    const char *filea = lua_tostring(L, -1);
    printf("filea: %s\n", filea);
    lua_pop(L, 1);

    lua_getfield(L, -1, "fileb");
    const char *fileb = lua_tostring(L, -1);
    printf("fileb: %s\n", fileb);
    lua_pop(L, 1);

    return 0;
}
