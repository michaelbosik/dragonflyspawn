Brian Earl
Bearl

Platform: Windows

Files:
Box.cpp
Box.h
Clock.cpp
Clock.h
Color.h
DevelopmentCheck.cpp
df-font
DisplayManager.h
DisplayManager.cpp
dragonfly.txt
Event.cpp
Event.h
EventCollision.cpp
EventCollision.h
EventKeyboard.cpp
EventKeyboard.h
EventMouse.cpp
EventMouse.h
EventOut.cpp
EventOut.h
EventStep.cpp
EventStep.h
EventView.cpp
EventView.h
Frame.cpp
Frame.h
GameManager.cpp
GameManager.h
InputManager.cpp
InputManager.h
LogManager.cpp
LogManager.h
Main.cpp
Manager.cpp
Manager.h
Music.cpp
Music.h
Object.cpp
Object.h
ObjectList.cpp
ObjectList.h
ObjectListIterator.cpp
ObjectListIterator.h
README.txt
ResourceManager.cpp
ResourceManager.h
Sound.cpp
Sound.h
Sprite.cpp
Sprite.h
utility.cpp
utility.h
Vector.cpp
Vector.h
ViewObject.cpp
ViewObject.h
WorldManager.cpp
WorldManager.h

vs-2017/sourcer-shoot.sln
vs-2017/sourcer-shoot.vcxproj
vs-2017/sourcer-shoot.vcxproj.filters
vs-2017/sourcer-shoot.vcxproj.user

Resources/sounds/explode.wav
Resources/sounds/fire.wav
Resources/sounds/game-over.wav
Resources/sounds/nuke.wav
Resources/sounds/start-music.wav

Resources/sprites/bullet-spr.txt
Resources/sprites/bullet-spr-2.txt
Resources/sprites/explosion-spr.txt
Resources/sprites/gameover-spr.txt
Resources/sprites/startover-spr.txt
Resources/sprites/saucer-spr.txt
Resources/sprites/ship-spr.txt


How To Compile:
To compile, open project using the saucer-shoot.sln file found in the vs-2017 folder. 
When it is open, build the program using the Build Solution option under the Build menu on the toolbar. 
After it is built, you can launch the program using the Local Windows Debugger button.

Other Information:
After the code is compiled, open up the dragonfly.txt file and you will see a print out of all of the tests for the code.
Alternatively, you can also open the DevelopmentCheck.cpp file to see all of the tests for the code.
When you run the code, a window will open up with a ship on the left and a ViewObject on the right
You can use the WASD keys to move the ship in all four direction
If you move the ship off the right side of the screen, it will be teleported back to its starting position
If you press the F key, a sound effect will play when the key is released
If you press the left mouse button, the number of the viewObject will increase
If you press the Q key, Music will start to play and then control will be taken away
Text and a character will be displayed on the screen and after a little, the screen will change and the character and text will move
Soon, the music will pause, and a sound will play and stop part way through
After a little, the same sound will play again, pause part way through and resume after a little, the music will then resume.