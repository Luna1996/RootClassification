# Classification
<a id="this"></a>

[Classification]: #this

> A class in which classification algorithms are implemented.

## Properties
[ccdata]: #ccdata
[numRootDetected]: #nord
[roots]: #roots
[mark]: #mk
[edgeContaining]: #ec
[edgeContainingL]: #ecn
[faceContaining]: #fc
[faceContainingL]: #fcn
[usedByEdges]: #ube

| Name                               | Type      | Discription                                |
| ---------------------------------- | --------- | ------------------------------------------ |
| [ccdata]<a id='ccdata'></a> | CCData*    | A CCData structure containing original information of vertices, edges and faces. |
| [numRootDetected]<a id='nord'></a> | int    | The number of roots that have been detected automatically. |
| [roots]<a id='roots'></a> | QList\<Root\>    | An List of root. |
| [mark]<a id='mk'></a> | char*    | An 1d char array storing the result of classification. |
| [edgeContaining]<a id='ec'></a> | int**    | An array in row i storing the indices of edges containing point i. |
| [edgeContainingL]<a id='ecn'></a> | int*    | An array in row i storing the number of indices of edges containing point i. |
| [faceContaining]<a id='fc'></a> | int**    | An array in row i storing the indices of edges containing point i. |
| [faceContainingL]<a id='fcn'></a> | int*    | An array in row i storing the number of indices of edges containing point i. |
| [usedByEdges]<a id='ube'></a> | bool*    | An array of bool indicating whether a point is used by edges or faces. |

## Static Functions
[addOneToIntArray]:#aotia

> <a id='aotia'></a>
> **void [addOneToIntArray](int\*\* arr, int row, int length, int newValue)** 
>   
>   Add a newValue to arr[row] whose length is length
> 
> * *arr*  
>   Int array 
> * *row*  
>   Row of target array
> * *length*  
>   The length of arr[row]
> * *newValue*  
>   New element need to insert.

## Non-static Functions
[Classification]:#classification

> <a id='classification'></a>
> **[Classification](CCData\* data)** 
>   
>   Create and initialize all cells of [mark] to 2.  
>   Initialize edgeContaining, edgeContainingL, faceContaining and faceContainingL.
> 
> * *data*  
>   The root data need to process.  
> 

[~Classification]:#nclassification

> <a id='nclassification'></a>
> **[~Classification] (void)**   

[junctionAutoDetection]:#jad

> <a id='jad'></a>
> **void [junctionAutoDetection] (void)** 
>   
>   Automatically detect the number and position of junctions.



[updateContainings]:#updatecontaining

> <a id='updatecontaining'></a>
> **void [updateContainings] (void)**   
> 
> Update the indices of edges and faces containing point i and store them in members.

[markVerticesInJunctionSpheres]:#mark-in-spheres

><a id='mark-in-spheres'></a>
> **void [markVerticesInJunctionSpheres] (void)**  
> 
> Mark vertices in spheres to corresponding root.
> 

[classify]:#clsf

><a id='clsf'></a>
> **void [classify] (void)**  
> 
> Classify all points to one of the roots, 0 or 1.

[centerOfAface]:#coaf
> <a id='coaf'></a>
> **float\* [centerOfAface](uint index)** 
>   
>   Given the index of a face, output the center of its three vertices.
> 
> * *index*  
>   Index of given face 
> * *return value*  
>   a float array in form: [x, y, z]

[faceSet2JunctionPosition]:#fs2jp
> <a id='fs2jp'></a>
> **Sphere [faceSet2JunctionPosition](QSet<uint>\* set)** 
>   
>   Given a set of indices of faces, output the sphere whose center is the center of all the faces in the set
> 
> * *set*  
>   A set of face indices
> * *return value*  
>   A sphere containing this junction

[nearestSphere]:#ns
> <a id='ns'></a>
> **int [nearestSphere](QSet<uint>\* set)** 
>   
>   Given a set of points of a line segment, output the index of nearest junction.
> 
> * *set*  
>   A set of point of a line segment.
> * *return value*  
>   0: junction 0;  
>   1: junction 1.

[floodVerticesThroughEdgesFromSeed]:#fvtes
> <a id='fvtes'></a>
> **void [floodVerticesThroughEdgesFromSeed](uint seed)** 
>   
>   Mark all vertices that could be flooded from seed.
> 
> * *seed*  
>   The starting point of edges.

[setJunctionRadius]:#sjr
> <a id='sjr'></a>
> **void [setJunctionRadius](float r)** 
>   
>   If there are right two junctions, set there radius d*r, where d is the distance between two junctions.
> 
> * *r*  
>   The ratio parameter: r = radius/d