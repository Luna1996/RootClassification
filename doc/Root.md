# Root(Sphere)

The root data that will be used both in calculation and display.

## Properties
[pos]: #pos
[rgb]: #rgb
[radius]: #radius

| Name                        | Type      | Discription                      |
| --------------------------- | --------- | -------------------------------- |
| [pos]<a id='pos'></a>       | QVector3D | The center position.             |
| [rgb]<a id='rgb'></a>       | QVector3D | The root color.                  |
| [radius]<a id='radius'></a> | float     | The radius of containing sphere. |

## Static functions
[inThisSphere]:#its

> <a id='its'></a>
> **bool [inThisSphere](Sphere s, QVector3D p)** 
>   
>   check whether given point p is in Sphere s.
> 
> * *s*  
>   given Sphere
> * *p*  
>   given point
> * *return value*  
>   a bool value.  
>   true: p is in or on the edge of s  
>   false: p is out of s
