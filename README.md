# pong

You can play this game at: https://thiagoharry.github.com/pong

## Game Controls

* UP: Move left paddle up in 1-player mode. Move right paddle up in
  2-players-mode. Move the cursor up in the title screen.

* DOWN: Move left paddle down in 1-player-mode. Move right paddle down
  in 2-players-mode. Move the cursor down in the title screen.

* W: Move left paddle up in 2-players mode.

* S: Move left paddle down in 2-players mode.

* ENTER: Select option in the title screen.

## Compiling the game

This is a Pong game written in C using the [Weaver Game
Engine](https://thiagoharry.github.io/weaver/). The game can be
compiled in a Linux environment with a C compiler and GNU Make.

### Compiling the game as a Linux executable

First install the dependencies. In Ubuntu, Linux Mint and related
distros, the following command should work:

```
sudo apt-get install build-essentials libx11-dev mesa-common-dev libxrandr-dev libglew-dev libopenal1 libopenal-dev vim-common
```
In other distros, research how to install the equivalent packages.

Check file `conf/conf.h` and change the line which starts with
`#define W_TARGET` to:

```C
#define W_TARGET W_ELF
```

Then run the command `make`. And finally you can run the game with
`./pong`.

### Compiling the game as a web page

First install the dependencies. In Ubuntu, Linux Mint and related
distros, the following command should work:

```
sudo apt-get install emscripten vim-common
```

But you must ensure that Emscripten is in version 1.34.0 or
greater. In other distros, research how to install the equivalent
packages.

Check file `conf/conf.h` and change the line which starts with
`#define W_TARGET` to:

```C
#define W_TARGET W_WEB
```

Then run the command `make`. It should produce a directory called
`web` where you can open the file `pong.html` in a web browser to play
the game.

## Credits

###### Created and programmed by

* [thiagoharry](https://github.com/thiagoharry/)

###### Fonts used in title screen, sound effect ideas

* [ArmlessJohn404](https://github.com/ArmlessJohn/)

###### Sound Effects

* [NoiseCollector](http://freesound.org/people/NoiseCollector/)
* [ProjectsU012](http://freesound.org/people/ProjectsU012/)
* [DoKashiteru](https://opengameart.org/users/dokashiteru)
* [qubodup](https://opengameart.org/users/qubodup)
* [Retimer](https://opengameart.org/users/retimer)

###### Shaders

* Anonymous authors who posted interesting shaders at http://www.glslsandbox.com/
