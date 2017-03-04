//------------------------------------------------------------------------------
//--- MugenEngine
//------------------------------------------------------------------------------

#ifndef FILEDATA_H
#define FILEDATA_H

#include <json.hpp> // Library JSON Manipulation !
#include <fstream>

using json = nlohmann::json;

extern "C" // Standard LUA Library
{
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}
#include <selene.h> // Wrapper C++ LUA !

#include "Misc.h"

class FileData
{
    public:
        FileData();
        virtual ~FileData();

        // --- JSON File Manager !
        json loadJsonFile(std::string const filename);
        void saveJsonFile(std::string const filename, nlohmann::json data);

        // --- LUA method !
        void PrintTable(lua_State *L);

    protected:

    private:
};

#endif // FILEDATA_H
