# RootClassification

## Properties
[cc]: #cc

| Name                               | Type      | Discription                                |
| ---------------------------------- | --------- | ------------------------------------------ |
| [cc]<a id='cc'></a> | [CCData](CCData.md)*     | Cell complex data. |

# Functions

[LoadPLYFile]:#load-ply-file

> <a id='load-ply-file'></a>
> **[CCData]\*  [LoadPLYFile](QString path)**  
> 
> Load the cell complex data from .ply file provide by *path*.
> 
> * *path*  
>   The path of the file.
> * *return value*  
>   Return the [CCData] pointer if succeed, NULL otherwise.