# Bridge Simulator and Generator
### by Max Schommer, David Papp, Thuc Tran, Joseph Lee

#### Goal
The goal of the project is still to create a method for bridge design and optimization. We have modeled the bridge as a series of links between pins and beams, which will take only compressive loads and tensile loads. The generation process currently take given “fixed” nodes, and builds a bridge between them using material and node minimization. We will then apply a load to the bridge, and calculate whether or not the bridge has failed. We’re currently working on these calculations. Next, we will modify the bridge iteratively using gradient descent. If the bridge fails after a number of optimization steps, a new bridge will be built using a genetic algorithm that we’ve already implemented. This process will continue until a successful bridge is built that satisfies the user's requirements. 
We’re close to achieving our MVP of a structure simulator that is able to simulate load on a truss structure, and determine whether the structure will fail or not given material properties of the beams/joints. The graphics, generation, and objects are in place, we just need to finetune the physics.
The stretch goals are then to create genetic algorithm to vary bridges based on success and failure, and implement dynamic loading.

#### Progress on project related cards

- Create a plotting function using openGL that can plot points on the screen/Create plot function that plots beams between points
![Drawing](https://github.com/thuctran289/SoftSysPowerPlants/blob/master/reports/Images/draw.png?raw=true)

- Write at least one function in C++: Everyone has contributed to some header/source file and has learned C++ data structures such as classes, maps, vectors, and sets.

- Create a function that takes in a "truss" structure and computes the loading on all of the beams: This is the physics part that we’ve made some progress on. We set some points as fixed, and have calculated the forces on others. We haven’t fine tuned the parameters, so the bridge behaviors erratically at the moment. 

- Animation: We currently have rudimentary animation, where each frame is rendered when the user presses a new key. This is very helpful for debugging already, but for the final version, we’d like to do an actual animation with a high frame rate.

- Calculating forces on the bridge: https://github.com/thuctran289/SoftSysPowerPlants/blob/master/Bridge.h (void CalculateForce())

- Implement genetic algorithm: We created a prototype for crossover and mutation, but have not combined them into an evolutionary algorithm. We also do not have a good fitness function yet. https://github.com/thuctran289/SoftSysPowerPlants/blob/master/Bridge.h

- Learn how to use Linear Algebra library: We downloaded and installed Armadillo and got it working, but have not needed to use it yet (and might only need to for gradient descent).

- Implement Bridge Pruning: We created a function that will remove all points and beams that are not the part of the largest bridge. 

- Experiment with non-terminal user interaction: We investigated the different callbacks that openGL has. 


#### Preliminary Results

![Example](https://github.com/thuctran289/SoftSysPowerPlants/blob/master/reports/Images/b1.png?raw=true)

This is an example of a generated bridge (with 50 points). The blue triangles represent fixed pins, the green triangles represent moving points, and the red lines represent beams. No load is being applied.

We have also started the physics, but this needs more work, both with the equations and the adjustment of parameters. 

![Physics](https://github.com/thuctran289/SoftSysPowerPlants/blob/master/reports/Images/phsyx.png?raw=true)

Before/After

![Before](https://github.com/thuctran289/SoftSysPowerPlants/blob/master/reports/Images/prune.png?raw=true)

We have also created a function that will help prune our bridges to get rid of all points and beams that are not associated with the largest connected bridge. 

![Callbacks](https://github.com/thuctran289/SoftSysPowerPlants/blob/master/reports/Images/callback.png?raw=true)

We were able to get mouse and keyboard callbacks (in OpenGL) so that we now has a non-terminal way of interacting with the program. 

[Database] 

#### Resources

http://bridgecon.sourceforge.net/: An example of a bridge constructor physics simulation. The website includes graphics that can aid us in creating a GUI for debugging, but no source code is available. 

https://www.scribd.com/doc/20641372/Physics-of-Bridges: Powerpoint detailing physical aspects that we will have to model in our simulation (tension, compression, arches, trusses, etc)...

https://www.mathworks.com/help/gads/how-the-genetic-algorithm-works.html: Description of how genetic algorithms work using MATLAB. Describes random initialization, fitness (which will be structural integrity for us), mutations, etc. 

https://open.gl/ A tutorial for OpenGL. This will help us get started on how to create the graphical interface to show results of our simulations and generative design. 

http://www.opengl-tutorial.org/miscellaneous/building-your-own-c-application/ A tutorial for how to use OpenGL in C in particular. 

#### Backlog
https://trello.com/b/GyAXfVON/power-plants]

#### Potential roadblocks
Roadblocks:
Slowness with Picking up C++: We are still trying to get familiar with C++, but this should be a straightforward process of spending more time. 	
Parameter adjustment: We’ve been struggling to find reasonable values for constants such as compressibility, even though we have a database of this information.
Generative/optimization algorithms: We have some concerns that the gradient descent algorithm that we have in mind might be overly slow.



