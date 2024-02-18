# TMIAchievementActivator
A simple and lazy way to get all Steam achievements from Touhou Mystia's Izakaya.
Works with any game version.
## How to use
- Copy [MinHook](bin) [x86](bin/MinHook.x86.dll) or [x64](MinHook.x64.dll) to the game folder, acording to game's bitness.
- Install and open [ProcessHacker](https://processhacker.sourceforge.io/).
- Start [Touhou Mystia's Izakaya](https://store.steampowered.com/app/1584090/__Touhou_Mystias_Izakaya/) from Steam.
- While the game is loading, use ProcessHacker to inject `TMIAchievementActivator.x86.dll` / `TMIAchievementActivator.x64.dll` into the game.
- A console window will appear and all Steam achievements should be activated.
## Build
Use Visual Studio with C++ Desktop Development workload to build this project.
