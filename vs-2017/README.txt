Michael Bosik
mbosik@wpi.edu

Files Included in Submission:

Header Files
- Box.h
- Clock.h
- DisplayManager.h
- Event.h
- EventCollision.h
- EventKeyboard.h
- EventMouse.h
- EventOut.h
- EventStep.h
- EventView.h
- Frame.h
- GameManager.h
- InputManager.h
- LogManager.h
- Manager.h
- Music.h
- Object.h
- ObjectList.h
- ObjectListIterator.h
- ResourceManager.h
- Sound.h
- Sprite.h
- utility.h
- Vector.h
- ViewObject.h
- WorldManager.h
- TestInputDetectorObject.h

Source Files
- Box.cpp
- Clock.cpp
- DisplayManager.cpp
- Event.cpp.
- EventCollision.cpp
- EventKeyboard.cpp
- EventMouse.cpp
- EventOut.cpp
- EventStep.cpp
- EventView.cpp
- Frame.cpp
- GameManager.cpp
- InputManager.cpp
- LogManager.cpp
- Manager.cpp
- Music.cpp
- Object.cpp
- ObjectList.cpp
- ObjectListIterator.cpp
- ResourceManager.cpp
- Sound.cpp
- Sprite.cpp
- Test.cpp
- TIDO.cpp
- utility.cpp
- Vector.cpp
- ViewObject.cpp
- WorldManager.cpp

Other Files
- dragonfly.log
- dragonfly.sln
- README.txt
- saucer-shoot.vcxproj
- saucer-shoot.vcxproj.filters
- saucer-shoot.vcxproj.user
- ../df-font.ttf
- ../Makefile
- ../sprites/explosion-spr.txt
- ../sprites/saucer-spr.txt
- ../sounds/Africa8Bit.wav
- ../sounds/Pew.wav

The provided source files allow for the user to log messages to a log file, create objects to
put in object lists and iterate through them, create vectors for objects to follow, create step
events in the game engine, detect keyboard and mouse input, render objects to the screen as well
as draw objects with colors, detect object collisions and draw strings to the screen, load sounds,
msuic and sprites to the engine, associate sprites to objects, set a viewfollowing camera to an
objects.

To compile this code, load the project solution into a compiler such as Visual Studio. Build the 
solution by clicking on the Build drop down and then Build Solution. Click on the Local Windows Debugger
button to run the code.

The tests for this assignment were written in the source file "Test.cpp". This file contains
fluent tests for every single method in the Clock, Event, EventStep, GameManager, LogManager,
Manager, Object, ObjectList, ObjectListIterator, Vector, DisplayManager, InputManager, and 
WorldManager classes. All of the tests results will be logged to the logfile "dragonfly.log" 
in the project location on your harddrive. To run these tests, compile the project as explained above.