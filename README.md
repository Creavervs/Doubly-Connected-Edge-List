# Doubly-Connected-Edge-List
#This program involves taking a list of Vertices (X,Y) from a text file and placing half edges between them. Each half edge between vertices has a twin that points in the opposite direction.

#The boundary is defined by the initial list of vertices ( No other point can exist outside the region of interest). This algorithm does not allow for holes ( Regions within the boundary where a point cannot exist).

#The Vertices are then ordered through use of a priority Queue and is ordered by the top most node and left most vertex.

#As the vertexs get popped off the queue they are assigned a state which are as follows Start,Split,Merge,End and Common. All of which need to be handled in a different way

#A Binary Search tree is then used on the Vertices to determine how to handle each of the states. There are conditions which now allow additional half edges to be made between some of the states

#These additional half edges allow for more faces to be made i.e the formation of polygons.

#The faces keep track of the half edges in each of its polygon formation. If a polygon has exactly 3 vertices then no refinement is required.

#If the polygon has greater than 3 then another sorting algorithm is used to transform a polygon into multiple triangles

#(Not Implemented) The final check once the triangles has been formed is to check to see that they are Delaunay.I.E equal areas between all triangles. The delaunay refinement allows for additional halfedge's or shifiting of vertices within the boundary to ensure that they are all equal.

#Reflection: The management of multiple triangulations and polygons has quite a large anount of book keeping involved. The refinement would only get so far before breaking on a condition in the polygon forming. It made it hard to step through the problem as there was quite alot going on and limited resources were spent on the visualisation of the algorithm. Future iterations would allow for a visualiastion and relook at the code structure.
