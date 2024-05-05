# ICP-24 
#### Authors: Pomsar Jakub (xpomsa00) , Cagala Simon (xcagal00)  
## Robot collision detection simulator
### 1. Introduction
This program simulates the movement and behavior of robots that avoid obstacles in their path based on user-defined parameters. Users can define parameters for the robot, such as _rotation_ upon detection, _detection distance_, movement _speed_, detection range for obstacles or other robots, and the _orientation_ of the robot on the grid. Parameters for obstacles include _width_ and _height_.

## 2. Detecting collision
The detection area, which is rectangular in shape, extends from the center of the robot to the distance specified for the detection area. When a collision occurs, meaning another object is within the detection area, the robot stops moving and rotates either to the left or right (user-defined, defaulting to right) by a specified angle (also user-defined).

## 3. Control
Every function that manipulates the simulation can be found in the contextual menu as a button or triggered by a key combination. More detailed descriptions of functions such as spawning robots/obstacles, deleting, editing parameters, etc., are conveniently provided directly within the main view.

### 3.1 Setting up
Setting up a scene can be achieved through various methods. It can be left to random generation, loaded from a `JSON` configuration file, or manually set up by generating objects and then dragging and dropping them within the scene.

### 3.2 Manual control 
To control a robot, it must first be selected with a left click. Once selected, it can be controlled using the `arrow keys` or the `WAD keys`. The robot can rotate left or right, or move forward. However, the robot cannot collide with another object because its detection area will prevent it from moving in that direction.

## 4. Saving/loading from/to files
To save the current state of the simulation (`Ctrl+S`), as well as the current state of all objects within the simulation, JSON files are utilized. These files can also be loaded (`Ctrl+O`) to restore the simulation from the saved configurations.

## 5. Unimplemented features and known bugs:

 - Obstacles *cannot* be rotated. This unimplemented feature is addressed by spawning rectangles instead of simple squares.
 - When spawning objects into the scene, their parameters, position, and size are randomly generated. To prevent obstacles or robots from being hidden behind other objects, they are placed in positions where they don't collide with existing objects. However, this implementation feature can lead to an _infinite loop_ where no other objects can be spawned. In the future, this could be reimplemented by calculating the available area against the entire scene's area or by simply spawning them regardless of their placement.

