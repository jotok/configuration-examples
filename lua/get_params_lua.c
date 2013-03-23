/* get_parm_lua.c -- read the lua-based parameter file */

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

#include <stdio.h>

int
main(void) {
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);
    luaL_dofile(L, "param_file_desc.lua");
    luaL_dofile(L, "params.lua");

    // print the data directory
    lua_getglobal(L, "config");
    lua_getfield(L, -1, "directory");
    const char *directory = lua_tostring(L, -1);
    printf("directory: %s\n", directory);
    lua_pop(L, 1);

    // print the value of the summary flag
    lua_getfield(L, -1, "summary");
    printf("summary: %d\n", lua_toboolean(L, -1));
    lua_pop(L, 1);


    // print the name, length, and column parameters for the "first" field
    lua_getfield(L, -1, "fields");
    lua_getfield(L, -1, "first");
    lua_pushinteger(L, 1);
    lua_gettable(L, -2);
    int length = lua_tointeger(L, -1);
    lua_pop(L, 1);
    lua_pushinteger(L, 2);
    lua_gettable(L, -2);
    int starta = lua_tointeger(L, -1);
    lua_pop(L, 1);
    lua_pushinteger(L, 3);
    lua_gettable(L, -2);
    int startb = lua_tointeger(L, -1);
    lua_pop(L, 3); // config now the top of the stack
    printf("first %d %d %d\n", length, starta, startb);

    // print the number of blocking fields in the first strategy
    lua_getfield(L, -1, "strategies");
    lua_pushinteger(L, 1);
    lua_gettable(L, -2);
    lua_getfield(L, -1, "block");
    lua_len(L, -1);
    printf("number of blocking fields: %d\n", (int)lua_tointeger(L, -1));

    return 0;
}
