# OpenGLCTRender

This project is used to study OpenGL and do the whole rendering.  
Thanks to http://www.opengl-tutorial.org/.  
And my professor, TA and friends.  

Pipeline:
Initialization:
1.  Initialize GLEW, GLFW and glm.
2.  Create a background.
3.  Load vertex shader and fragment shader.
4.  Create MVP, view and model matrix.
5.  Load cube.obj to get vertices.
6.  Scale down vertices because it is too large to see clearly.
7.  Calculate surface normal vector.
8.  Set colors.

Rendering:
9.  Do a flexible MVP matrix.
10. Set light postion.
11. Draw triangles.

TODO:  
[x] add light  
[ ] add texture  
[x] get normal vector (surface normal)  
[ ] get UV coordinate  
[ ] make better shadow  