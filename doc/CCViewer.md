# CCViewer

Drawing the root using OpenGL.

## Properties
[raw]: #raw
[result]: #result
[roots]: #roots

| Name                        | Type                 | Discription             |
| --------------------------- | -------------------- | ----------------------- |
| [raw]<a id='raw'></a>       | [CCData](CCData.md)* | The raw data.           |
| [result]<a id='result'></a> |                      |                         |
| [roots]<a id='roots'></a>   | [Root](Root.md)**    | The user defined roots. |

##  Functions

[paint]:#paint

> <a id='paint'></a>
> **`slot` void [paint]\()**  
> 
> The function that paint all stuffs. Should be connected to relative signals.
> Will auto initiallize when first call or context changed.

[onWindowChanged]:#on-window-changed

> <a id='on-window-changed'></a>
> **`slot` void [onWindowChanged]\(QQuickWindow\*  win)**  
> 
> Handel the context changing, usually happen when start up.
