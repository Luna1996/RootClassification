# README
<a id="this"></a>

[readme]: #this

> Abstract manual of RootClassification tool.

After launching the excutable file, you can see that the window is made up with two sections, a tool bar in left side and a white visualization field in right side.

Firstly click the folder icon just below "File" at the top of the tool bar. Please select the .ply file you want to process from the explorer. After loading the file, you will see a gray skeleton at the right side of the window.

After finishing loading, click the refresh icon to enable the program automatically detect the clusters of faces. One or more items would appear below the three icons with filled circles in distinct colors at the left side of them. Each item represents a cluster detected, containing colored filled circle, four number fields and a delete button from left to right. The four number field correspondingly represent x, y, z coordinate of the center of this cluster and the radius of the sphere that used to visualize this cluster. Clicking the colored filled circle at left side could make the program show a sphere containing this cluster in the visualization field.

Next, please visually check whether at the center of each root there is exactly one cluster. You could repeatedly click the items to show the corresponding spheres. Please delete extra clusters from the root. For example, sometimes there are two clusters at the center of one root and there probably will also be some face clusters outside of both roots. The classification algorithm will not work if the number of item shown in the tool bar is not exactly two.

If at the center of any root there is no clusters, please click "+" button to manually create a sphere in the model. You can iteratively modify and show the sphere in the visualization field just like a detected one.

If you have made sure that there exactly two spheres individually at the center of two root systems. Please click check button to run the classification algorithm.

The result will be shown in the visualization field. Two roots are marked with different colors which are just the color of the filled circle corresponding to the cluster shown in the tool bar.

If you want process other file please load new file and repeat the above procedure again.