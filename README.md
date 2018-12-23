# CactuJam Game
A little game written at the weekend for the CactuJam

### Technology
C++17, SFML 2.5.0, Lua, Sol2

### CMAKE
Create file **/cmake-modules/Config.cmake** and set your SFML ROOT directory inside, eg.
```
set(SFML_ROOT ../SFML-2.5.0/)
set(LUA_ROOT ../Lua-5.1/)
set(SOL2_ROOT ../Sol2/)
```
After this click File -> Reload CMake Project in CLion