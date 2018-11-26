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

| Name                               | Type      | Discription                                |
| ---------------------------------- | --------- | ------------------------------------------ |
| [n1],[n2],[n3]<a id='n'></a> | int, int, int     | The length of vertex, edge and face lists. |
| [c1],[c2],[c3]<a id='c'></a> | float*, int*, int* | The vertex, edge and face lists.           |

## Static Functions
[LoadPLYFile]:#load-ply-file
> <a id='load-ply-file'></a>
> **public [CCData]\*  [LoadPLYFile](QString path)**  
> 
> Load the cell complex data from .ply file provide by *path*.
> 
> * *path*  
>   The path of the file.
> * *return value*  
>   Return the [CCData] pointer if succeed, NULL otherwise.

[SaveCCData]:#save-ccdata
> <a id='save-ccdata'></a>
> **public int [SaveCCData](QString path, [CCData]\* data)**  
> 
> Save the cell complex data to .ply file provide by *path*.
> 
> * *path*  
>   The path of the location you want to save.
> * *data*  
>   Data.
> * *return value*  
>   Return the 0 pointer if succeed, non-zero otherwise.