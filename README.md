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

This is a Pong game written in C using the Weaver Game Engine (https://thiagoharry.github.io/weaver/). It uses OpenGL, OpenAL and was compiled to asm.js.

To compile the game as a Linux executable, run `make` in the command line and run the `./pong` command. 
To compile the game as a web page, edit `conf/conf.h` and change the W_TARGET macro definition as `#define W_TARGET W_WEB`.

## Credits

This game was created and programmed by @thiagoharry. 
The font used in the game was created by @ArmlessJohn404 which also created a pong game.
The sound used in the game is taken from https://www.freesound.org/, created by users `noisecollector`, `projectsu012` and `n-audioman`.
I also got some sounds from https://opengameart.org. Thanks for users `DoKashiteru`
A lot of shader effects were created adapting code from http://glslsandbox.com/.
