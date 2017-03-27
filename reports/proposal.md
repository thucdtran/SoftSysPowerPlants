# Bridge Simulator and Generator
### by Max Schommer, David Papp, Thuc Tran, Joseph Lee

#### State the goal of your project, ideally including a lower bound you are confident you can achieve and a stretch goal that is more ambitious.

The goal of the project is to create a method for bridge design and optimization. We will model the bridge as a series of links between pins and beams, which will only take compressive loads and tensile loads. The generation process will take given “fixed” nodes, and build a bridge between them using material and node minimization. We will then apply a load to the bridge, and calculate whether or not the bridge has failed. After this calculation has occurred, we will modify the bridge iteratively using gradient descent. If the bridge fails after a number of optimization steps, a new bridge will be built using a genetic algorithm. This process will continue until a successful bridge is built that satisfies the user's requirements. 
An MVP would be a structure simulator that is able to simulate load on a truss structure, and determine whether the structure will fail or not given material properties of the beams/joints. 
The stretch goals include the ability to generate a bridge, genetic algorithm to vary bridges based on success and failure, and dynamic loading.

#### Demonstrate that you have acquired the knowledge you need to get started.  We will know that you have this knowledge if the text of the proposal uses domain language effectively to convey ideas clearly and concisely.

We’ve explored the physics of several bridge designs including truss and suspension bridges. Some of us will need to do more research to understand the fundamental forces (tension, compression, torque, etc...). The project will be math heavy and as our stretch goal, we will randomly generate bridges and use gradient descent to optimize. 
For now, we think the bridge will be a combination of pins and beams. This is a great simplification of the real world that involves more complex physics such as cables.
For the graphics aspect, we will be using OpenGL. Our 2D operations in OpenGL are expected to be especially basic.

#### Demonstrate that you have assembled the resources you need to get started.  One good way to do that is to include an annotated bibliography with a pointer to each resource and a few sentences that describe the content.

http://bridgecon.sourceforge.net/: An example of a bridge constructor physics simulation. The website includes graphics that can aid us in creating a GUI for debugging, but no source code is available. 

https://www.scribd.com/doc/20641372/Physics-of-Bridges: Powerpoint detailing physical aspects that we will have to model in our simulation (tension, compression, arches, trusses, etc)...

https://www.mathworks.com/help/gads/how-the-genetic-algorithm-works.html: Description of how genetic algorithms work using MATLAB. Describes random initialization, fitness (which will be structural integrity for us), mutations, etc. 

https://open.gl/ A tutorial for OpenGL. This will help us get started on how to create the graphical interface to show results of our simulations and generative design. 

http://www.opengl-tutorial.org/miscellaneous/building-your-own-c-application/ A tutorial for how to use OpenGL in C in particular. 

#### Present a product backlog for the next two sprints that represents a concrete plan that will keep the entire team productively engaged (this can be a link to your Trello board).  Each item in the product backlog should represent a good sized unit of work, and have an appropriate definition of done. NB: You will also complete ~4 chapters of core class activities each sprint in addition to your project-specific work.

https://trello.com/b/GyAXfVON/power-plants

#### Enumerate potential roadblocks and ways instructors can help.  Do you need materials?  Do you have show-stopping questions you have not been able to answer?

Roadblocks:
Understanding of physics: While we feel like we have a good general understanding of the underlying physics, we do not fully understand every aspect of what this will look like moving forward.
Numerical Analysis/FEA: We do not have a strong sense for what difficulties may lie with the actual simulation as a result of trying to calculate it numerically. 
Generative/optimization algorithms: Some members have concern over the math aspects.
Graphics/Visualizations: some members on the team have little/no experience doing graphics

