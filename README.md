
#Abstract

###Bridges are everywhere. Thousands of engineers are employed every year in order to design and build these bridges. Sadly, most of the design for bridges is currently manual. This means that an experienced engineer will come up with a design, model it, test it, see if it fails, and then repeat until the bridge is shown to not fail under the planned loads. 

###We believe that this process can be automated. What an experienced engineer can do in three tries, a genetic algorithm can do in 100,000. We’ve built a system to simulate a bridge as a truss structure in real time. It solves indeterminate and determinate truss systems using gradient descent. We’ve built a way to distinguish sort bridges based on how stressed their beams are. We then used this environment to produce thousands of bridges, breed them, and produce realistic bridge structures at the end of several cycles. 

###Our generative design program can improve the bridge design to be faster, more reliable, and less costly. Engineers will be able to focus on more important tasks, and further increase their productivity. 



#Background

###The real-world physics involved in actual bridges is fairly complicated, involving a massive number of factors, including environmental considerations and material property variation. In designing software to genetically generate bridges, we need a way to model bridges and determine their behavior. Fairly simple abstractions of the physical system can actually accomplish this with reasonable accuracy. The California Department of Transportation has an article that describes some of the many different ways in which bridges can be modelled: http://www.dot.ca.gov/des/techpubs/manuals/bridge-design-practice/page/bdp-4.pdf Here is another good article describing the forces involved in bridges. https://www.scribd.com/doc/20641372/Physics-of-Bridges

###Another important aspect of our project is of course the genetic algorithm. The general idea behind genetic algorithms is to take aspects from parent objects and merge them in different ways to create ‘children’. The objects are then scored based on how well they accomplish whatever goal they are designed for. The highest scoring objects are then treated as the ‘parents’ for the next generation. Mathworks has a good article describing genetic algorithms and how they work here: https://www.mathworks.com/help/gads/how-the-genetic-algorithm-works.html

###The third component of our project is the graphics. The two articles below are helpful for learning how to use OpenGL, the platform we used for our graphics.

https://open.gl/ A tutorial for OpenGL. This will help get started on how to create the graphical interface to show results of our simulations and generative design. 
http://www.opengl-tutorial.org/miscellaneous/building-your-own-c-application/ A tutorial for how to use OpenGL in C in particular. 



Implementation

We modeled a bridge as a pin-beam truss structure. This means that there are no moments on any of the points, but simply forces. This simplification made it much easier for us to solve trusses, since we didn’t have to account for bending. There are three types of truss structures: determinate, indeterminate, and unconstrained. We wanted to place a load on our truss, and calculate the forces on all of the beams. We wanted to be able to do this for all three of the truss types. That is why we chose gradient descent to approach a solution. We modeled all of the beams using Young’s modulus as the linear spring constant, and iteratively moved points in the direction that minimized force. 

We were able to develop a genetic algorithm that effectively uses random placement of points and placement of beams in between those points to generate a realistic looking bridge. The process by which we did this was by maintaining a population of 50 bridges, sorted by the squared average stress on each of the beams. This was chosen as a metric in lieu of amount of material or costs due to a team decision to focus on stronger bridges, because we were more concerned with creating robust bridges than cheap bridges.
 
Using this this genetic algorithm, we tried to merge the best features from each generation of the population of bridges to produce new bridges that are hopefully better than the population before. The ‘genes’ of the genetic algorithm that get passed down from generation to generation are the location of pins in the structure. Points were chosen as genes due to being a relatively concise way of encoding the information of the bridge. Unfortunately, the genetic algorithm approach performed worse than the random bridge generation algorithm that we were using. A possible reason for the poor performance that was discussed is that choosing points as genes might have been too great of a simplification for how to combine bridges. For example, two good bridges could randomly swap points, and each child will be worse than the parent because the good bridges became highly specialized, and randomly combining points isn’t sufficient to merge the good qualities of both bridges. Another possible reason discussed is due to performance constraints. Even though we tried to multithread our most computationally intensive functions, we were constrained to using a smaller number of generations for simulation than what would have been desirable due to time constraints. 


Results

We created a graphic display for debugging. This display illustrates the functionality of our physics implementation. Bridges are randomly generated and as points and beams are pulled by gravity, beams compress and stretch. The strain on each beam is illustrated by its color: as strain on a beam increases, its color fades, until eventually the beam turns yellow when it breaks.

Below is an example of a bridge with 15 and 10 points. The animation runs until convergence is found. Note which beams are under the most strain. 


The results of our genetic algorithm over several iterations are shown below:

Note that the bridges gradually start to resemble an actual bridge. These results are encouraging. There are still beams that break, but this is because our fitness evaluation does not explicitly penalize breaking versus simply high stress.
