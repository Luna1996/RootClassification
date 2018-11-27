# MainWindow

## Properties
[A]: #a

| Name                               | Type      | Discription                                |
| ---------------------------------- | --------- | ------------------------------------------ |
| [A]<a id='a'></a> | [RootClassification](RootClassification.md)*     | The algorithm object. |

##  Functions

[LoadData]:#load-data

> <a id='load-data'></a>
> **int [LoadData](QString path)**  
> 
> Load the cell complex data from .ply file provide by *path*.
> 
> * *path*  
>   The path of the file.
> * *return value*  
>   Return 0 if succeed, none-zero otherwise.

[DrawData]:#draw-data

> <a id='draw-data'></a>
> **void [DrawData]\()**  
> 
> Draw data using OpenGL.

[GetSelection]:#get-selection

> <a id='get-selection'></a>
> **int [GetSelection](int x, int y)**  
> 
> Return the edge user clicked.
> 
> * *x, y*  
>   Cursor coordinate.
> * *return value*  
>   Return index of edge, -1 if none.