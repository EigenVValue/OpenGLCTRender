# OpenGLCTRender

This project is used to study OpenGL and do the whole rendering.\n
Thanks to http://www.opengl-tutorial.org/.\n
And my professor, TA and friends.\n

Pipeline:
1. Initialize GLEW, GLFW and glm.
2. Create a background.
3. Load vertex shader and fragment shader.
4. Load cube.obj to get vertices.
5. Scale down vertices because it is too large to see clearly.
6. Set colors.
7. Do a flexible MVP matrix.
8. Render.

TODO:\n
[ ] add light\n
[ ] add texture\n
[ ] get normal vector\n
[ ] get UV coordinate\n
[ ] make better shadow\n