# CCViewer

Drawing the root using OpenGL.

## Properties
[roots]: #roots
[raw]: #raw
[mark]: #mark
[prog]: #prog
[vao]: #vao
[vbo]: #vao

| Name                        | Type                 | Discription                        |
| --------------------------- | -------------------- | ---------------------------------- |
| [roots]<a id='roots'></a>   | [Root](Root.md)**    | The user defined roots.            |
| [raw]<a id='raw'></a>       | [CCData](CCData.md)* | The raw data.                      |
| [mark]<a id='mark'></a>     | char*                | The classification result          |
| [prog]<a id='prog'></a>     | QOpenGLShaderProgram |                                    |
| [P]<a id='prog'></a>        | QMatrix4x4           | The perspective matrix.            |
| [vao],[vbo]<a id='vao'></a> | GLuint               | The vetext array and buffer object |

##  Functions

[setRaw]:#setraw
[setMark]:#setMark

> <a id='setraw'></a>
> **void [setRaw]\([CCData](CCData.md)\* raw)**  
> **void [setMark]\(char\* mark)**  
> 
> These function should only be called inside OpenGL render thread. They set up corrosponding buffer data.

[onWindowChanged]:#on-window-changed

> <a id='on-window-changed'></a>
> **`slot` void [onWindowChanged]\(QQuickWindow\*  win)**  
> 
> Handel the context changing, usually happen when start up.

[paint]:#paint

> <a id='paint'></a>
> **`slot` void [paint]\()**  
> 
> The function that paint all stuffs. Should be connected to relative signals.
> Will auto initiallize when first call or context changed.