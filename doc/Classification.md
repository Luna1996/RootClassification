# Classification
<a id="this"></a>

[Classification]: #this

> A class in which classification algorithms are implemented.

## Properties
[ccdata]: #ccdata
[numRootDetected]: #nord
[root]: #root
[mark]: #mk
[edgeContaining]: #ec
[edgeContainingL]: #ecn
[faceContaining]: #fc
[faceContainingL]: #fcn

| Name                               | Type      | Discription                                |
| ---------------------------------- | --------- | ------------------------------------------ |
| [ccdata]<a id='ccdata'></a> | CCData*    | A CCData structure containing original information of vertices, edges and faces. |
| [numRootDetected]<a id='nord'></a> | int    | The number of roots that have been detected automatically. |
| [root]<a id='root'></a> | QList    | An List of root. |
| [mark]<a id='mk'></a> | char*    | An 1d char array storing the result of classification. |
| [edgeContaining]<a id='ec'></a> | int**    | An array in row i storing the indices of edges containing point i. |
| [edgeContainingL]<a id='ecn'></a> | int*    | An array in row i storing the number of indices of edges containing point i. |
| [faceContaining]<a id='fc'></a> | int**    | An array in row i storing the indices of edges containing point i. |
| [faceContainingL]<a id='fcn'></a> | int*    | An array in row i storing the number of indices of edges containing point i. |

## Functions

[Classification]:#classification

> <a id='classification'></a>
> **[Classification] (void)**   
> 
> Create and initialize all cells of [mark] to -1.

[updateContainings]:#updatecontaining

> <a id='updatecontaining'></a>
> **void [updateContainings] (void)**   
> 
> Update the indices of edges and faces containing point i and store them in members.

[markInSpheres]:#mark-in-spheres

><a id='mark-in-spheres'></a>
> **void [markInSpheres] (void)**  
> 
> Mark vertices in spheres to corresponding root.
> 
> * *path*  
>   The path of the location you want to save.
> * *data*  
>   Data.
> * *return value*  
>   Return the 0 pointer if succeed, non-zero otherwise.

[classify]:#clsf

><a id='clsf'></a>
> **void [classify] (void)**  
> 
> Classify all points to one of the roots, 0 or 1.

