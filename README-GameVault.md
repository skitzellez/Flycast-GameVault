# Flycast for Game Vault

**Flycast for Game Vault** is a build of [Flycast](https://github.com/flyinghead/flycast) (by Flyinghead and
contributors) for the Xbox Series X|S in Dev Mode, made to work with
[Game Vault](https://github.com/skitzellez/xbox-game-vault). Game Vault uses it for **Sega NAOMI, NAOMI 2 and
Atomiswave** arcade games.

## What is different from Flycast

- **NAOMI 2 games run at full speed on Xbox.**
- **The arcade BIOS is found where players keep it:** next to the game, or in the games drive's `Game Vault\bios`
  folder (as well as Flycast's own places).
- **Arcade buttons that work on an Xbox controller:** View inserts a coin, L3 is the cabinet's Test button, R3 opens
  Flycast's menu.
- Its own app identity (`GamerDad.FlycastForGameVault`, link `gamevault-flycast:`), so it installs next to the
  original Flycast.

## Building

Windows, Visual Studio 2022, CMake and the Windows 10 SDK 10.0.26100:

```
build_gv.bat 0.1.0.7
package_gv.bat 0.1.0.7
```

The package is signed with Game Vault's own certificate, which is not part of this repository.

## Licence

Flycast is free software under the **GNU General Public License, version 2 or later** (see `LICENSE`). This build
and its changes are under the same licence. Flycast is © Flyinghead and the Flycast contributors; the Game Vault
changes are by Skitzelles.
