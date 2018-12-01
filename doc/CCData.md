# CCData
<a id="this"></a>

[CCData]: #this

> The data stucture of cells complex and provide the method to load and save it.

## Properties
[n1]: #n
[n2]: #n
[n3]: #n
[c1]: #c1
[c2]: #c2
[c3]: #c3
[flat]: #flat
[sphere]: #sphr

| Name                         | Type               | Discription                                |
| ---------------------------- | ------------------ | ------------------------------------------ |
| [n1],[n2],[n3]<a id='n'></a> | int, int, int      | The length of vertex, edge and face lists. |
| [c1],[c2],[c3]<a id='c'></a> | float*, int*, int* | The vertex, edge and face lists.           |
| [flat]<a id='flat'></a>      | void**             | Flattened data for rendering purpose.      |
| [sphere]<a id='sphr'></a>    | Sphere             | A sphere containning all the points in the system.

## Static Functions

[LoadPLYFile]:#load-ply-file

> <a id='load-ply-file'></a>
> **[CCData]\*  [LoadPLYFile](QString path)**  
> 
> Load the cell complex data from .ply file provide by *path*. After loaded, [LoadPLYFile] will auto flatten the data and calculate the containing sphere of all points.
> 
> * *path*  
>   The path of the file.
> * *return value*  
>   Return the [CCData] pointer if succeed, NULL otherwise.

[SaveCCData]:#save-ccdata

><a id='save-ccdata'></a>
> **int [SaveCCData](QString path, [CCData]\* data)**  
> 
> Save the cell complex data to .ply file provide by *path*.
> 
> * *path*  
>   The path of the location you want to save.
> * *data*  
>   Data.
> * *return value*  
>   Return the 0 pointer if succeed, non-zero otherwise.

## Non-static Functions
[flatten]:#flt

><a id='flt'></a>
> **void [flatten] (void)**  
> 
> Reshape vertices, edges and faces into 1d arrays.  
> Calculate center and radius of this->sphere