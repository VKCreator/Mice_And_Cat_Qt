# Mice_And_Cat_Qt
Working with classes QGraphicsScene and QGraphicsItem in Qt
Draw up a working model of a cat hunting for mice.

Data input:

1) side of the square

2) range of the cat

3) number of mice

If the distance from the center of the cat to the center of the mouse is <= the hunting radius of the cat, then the cat eats the mouse and returns. If more, then the cat sits, the mouse runs away.

Graphic illustration, developed and multilingual interface.
English
1) Launching the application, interface, entering data and getting the result:
In order to work with the application, download the catAndMice_Release folder from Google Disk, unzip the archive to a convenient location, open the bin folder and run catAndMouse.exe.
The default language is Russian. In order to change the language, select another language from the drop-down list located on the toolbar. Each item in the dropdown list has a flag icon and a language name. The language can be changed at any time while the application is running.
The soundtrack plays while the application is running.
When clicking on the button "Start the game!" (the inscription depends on the selected language), located at the bottom of the widget, spinboxes appear, that is, widgets that allow you to select from a fixed set of values.
The first thing to enter is the length of the side of the square. The square is an area where mice spawn in various places. The side of the square can be from 300-500 units. The user can only enter numbers in the SpinBox, if the value is less than 300 units, then automatically the length of the side of the square is 300 units, that is, the minimum value. A number greater than the maximum value cannot be entered by the user.
The number in the SpinBox can be changed using the mouse wheel (focus on the Spinbox), keyboard, arrows. Next, click on the "OK" button.
The second thing to enter is the cat's hunting radius. The radius can be zero, this is the minimum value, and the maximum value is the radius of the circumscribed circle around the square, in case the cat hunts throughout the area where mice live. Next, click on the "OK" button.
The third thing to specify is the number of mice. The scrollbar limits the number of mice from 1 to 50. Next, click on the "OK" button.
At the bottom of the widget are the current parameter values.
When all fields are filled, a progress bar appears, data processing and scene installation begin.
On the stage, a square with a black outline shows the area where mice live, and a circle with a green outline shows the radius of the cat's hunting. The cat does not go beyond the circle. If the mouse appeared outside the circle, they immediately run away, the cat sits still. If the mouse appears inside the circle, the cat attacks it and returns to its place. As soon as all the mice have been on the stage, the result is calculated. The main melody turns off, the "rewarding" sound starts.
If eaten mice > escaped mice, then the cat gets 3 stars.
If eaten mice == escaped mice, then the cat gets 2 stars.
If eaten mice < escaped mice, then the cat gets 1 star.
Under the stars shows the number of mice in each category.
At the bottom of the widget is the "Restart" button, by clicking on which you can start the game again. When you click on the cross located in the upper right corner, the application will exit.
2) Functions:
The "catAndMouse" folder contains *.h and *.cpp files, which contain descriptions of classes and implementations of functions, methods, along with comments.
