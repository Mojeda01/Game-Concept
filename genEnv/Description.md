# Description of main.cpp in genEnv
The `main.cpp` program is an OpenGL application that initializes a window using GLFW, sets up an OpenGL context, and renders a simple 3D scene. The scene consists of a red floor rendered as a flat plane. The program uses GLSL shaders to handle the rendering pipeline, including vertex and fragment shaders.

1. **Initialization:**
    - Initializes GLFW and creates a window.
    - Sets the OpenGL context version to 3.3 and specifies the core profile.
    - Initializes GLEW to manage OpenGL extensions.
2. **Shader Compilation:**
    - Reads the vertex and fragment shader source code from external files (vertex_shader.glsl and fragment_shader.glsl).
    - Compiles the shaders and links them into a shader program.
3. **Vertex Data Setup:**
    - Defines the vertices and indices for a flat plane (the floor).
    - Sets up Vertex Buffer Objects (VBO), Vertex Array Objects (VAO), and Element Buffer Objects (EBO) to manage the vertex data.
4. **Transformation Matrices:**
    - Creates model, view and projection matrices to transform the vertices from model space to green space.
5. **Render Loop:**
    - Continuously processes user input and renders the scene.
    - Clears the screen and applies the shader program.
    - Binds the VAO and draws the elements (the floor).
    - Swaps the buffers and polls for events.
6. **Cleanup:**
    - Deletes the allocated resources (VAO, VBO, EBO, shader program) and terminates GLFW.

## Suggestions for enhancements
1. **Add More Objects:**
    - Add additional 3D objects such as cubes, spheres, or custom models to the scene.
2. **Texture mapping:**
    - Apply textures to the floor and other objects to make the scene more realistic.
3. **Lightning:**
    - Implement different types of lightning (directional, point, spotlights) to create depth and realism.
    - Add Phong shading or other lightning models to enhance the visual quality.
4. **Camera Movement:**
    - Implement a camera system to allow moving around the scene.
    - Add controls for panning, zooming, and rotating the camera.
5. **User Input:**
    - Add more users input controls to interact with the scene, such as moving objects or changing their properties.
6. **Animations:**
    - Introduce animations to objects, such as rotating, scaling, or translating them over time.
7. **Skybox:**
    - Add a skybox to create a more immersive environment.
8. **Physics:**
    - Integrate a physics engine to add realistic physical interactions between objects.
9. **GUI:**
    - Add a graphical user interface (GUI) using libraries like ImGui to provide controls for various parameters.
10. **Post-Processing Effects:**
    - Implement post-processing effects such as bloom, motion blur, or depth of field to enhance the visual quaqlity.
    