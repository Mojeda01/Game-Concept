This program is an OpenGL application that sets up a basic 3D environment with a simple orange floor and
allows for camera movement using the WASD keys and mouse input. The program begins by including 
necessary libraries such as GLEW, GLFW, and GLM for OpenGL functionality, window management, and 
mathematical operations.

The camera settings are initialized wiht a starting position, direction, and up vector. Variables 
for handling time, mouse input, and camera orientation are also defined. An error callback function 
for GLFW is set up to handle and display any errors that occur during execution.

The `processInput` function is responsible for handling keyboard input. It checks if the Escape key 
is pressed to close the window and updates the camera position based on the WASD keys. The camera
speed is adjusted according to the time elapsed between frames to ensure smooth movement. Debugging
statements are included to print the camera position when the keys are pressed.

The `mouse_callback`function handles mouse movement input. It calculates the offset of the mouse
movement and updates the camera's yaw and pitch angles accordingly. The camera's front vector is
then recalculated based on these angles to update the direction the camera is facing.

The `checkShaderCompileErrors` function is used to check for and display any errors that occur during 
the compilation and linking of shaders. The `checkGLError` function is used to check for any display 
any OpenGL errors that occur during execution.

In the `main` function, GLFW is initialized and configured to use OpenGL version 3.3 with the core 
profile. A window is created with a resolution of 1920x1080, and the context is made current. The 
mouse callback function is set, and the cursor is disabled to allow for unrestricted mouse movement.p

GLEW is initialized to set up the OpenGL function pointers, and depth testing is enabled to ensure 
correct rendering of 3D objects. Vertex data for a simple floor is defined, including positions and
colors. Vertex Buffer Objects (VBO), Vertex Array Objects (VAO), and Element Buffer Objects (EBO) are
generated and bound to store and manage this data.

Simple vertex and fragment shaders are defined and compiled. The vertex shader transforms the vertex
positions and passes the color data to the fragment shader, which outputs the final color. The shaders 
are linked into a shader program, which is then used for rendering.

The main loop of the program runs until the window is closed. Within this loop, the time elapsed between frames is calculated, and the `processInput` function is called to handle any input. The screen is cleared, and the shader program is used for rendering. The model, view, and projection matrices are defined and passed to the shader program to transform the vertices correctly. The floor is rendered using the vertex and element buffer data, and the buffers are swapped to display the rendered frame.

Finally, the VAO, VBO, and EBO are deleted, and GLFW is terminated to clean up resources before the program exits. This program provides a basic framework for rendering a 3D scene with camera controls,
which can be expanded and modified for more complex applications.