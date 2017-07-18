# pong

You can play this game at: XXX

Arrow keys control the paddle. In two-players mode, W and S also control one of the paddles. And the Enter key select options in the menu.

This is a Pong game written in C using the Weaver Game Engine (https://thiagoharry.github.io/weaver/). It uses OpenGL, OpenAL and was compiled to asm.js.

To compile the game as a Linux executable, run `make` in the command line and run the `./pong` command. 
To compile the game as a web page, edit `conf/conf.h` and change the W_TARGET macro definition as `#define W_TARGET W_WEB`.

## Credits

This game was created and programmed by @thiagoharry. 
The font used in the game was created by @ArmlessJohn404 which also created a pong game.
The sound used in the game is taken from https://www.freesound.org/, created by users `noisecollector`, `projectsu012` and `n-audioman`.
I also got some sounds from https://opengameart.org. Thanks for users `DoKashiteru`
A lot of shader effects were created adapting code from http://glslsandbox.com/.
