# OpenGL Experiment Program

This program is a simple OpenGL application that demonstrates basic 3D rendering and camera movement. The application renders a single 3D triangle with lighting effects and allows the user to move around the scene using keyboard and mouse inputs. The program is built using modern OpenGL (version 3.3) and leverages the GLEW, GLFW, and GLM libraries for OpenGL extension loading, window management, and mathematics, respectively.

## Key Features

1. **3D Triangle Rendering**:
   - The program renders a single 3D triangle with vertex normals for lighting calculations.
   - The triangle is transformed using model, view, and projection matrices to position it in the 3D space.

2. **Lighting**:
   - Basic Phong lighting model is implemented in the fragment shader.
   - The lighting model includes ambient, diffuse, and specular components.
   - The light source is positioned at a fixed location in the scene.

3. **Camera Movement**:
   - A `Camera` class is implemented to handle camera positioning and orientation.
   - The camera can be moved using the WASD keys for forward, backward, left, and right movements.
   - The mouse is used to look around, changing the camera's yaw and pitch angles.

4. **Mouse Control Toggle**:
   - The mouse cursor is captured by default for camera control.
   - Pressing the `ESC` key toggles the mouse capture state, allowing the user to regain control of the mouse cursor to interact with the desktop or close the application.

## File Breakdown

1. **main.cpp**:
   - The main application file that sets up the OpenGL context, compiles shaders, initializes the camera, and handles the render loop.
   - Includes functions for handling window resizing, mouse movement, and keyboard input.

2. **Camera.h**:
   - Defines the `Camera` class, which encapsulates the camera's position, orientation, and movement logic.
   - Provides methods for updating the view matrix and processing keyboard and mouse inputs.

3. **CMakeLists.txt**:
   - The CMake configuration file that specifies the project settings, includes directories for GLEW, GLFW, and GLM, and links the necessary libraries.

## Dependencies

- **GLEW**: OpenGL Extension Wrangler Library, used for managing OpenGL extensions.
- **GLFW**: Library for creating windows, contexts, and handling input.
- **GLM**: OpenGL Mathematics library, used for matrix and vector operations.

## How to Build and Run

1. **Install Dependencies**:
   Ensure that GLEW, GLFW, and GLM are installed on your system. On macOS, you can use Homebrew:
   ```sh
   brew install glew glfw glm
   ```

2. **Build the Project**:
   Navigate to the project directory and run the following commands:
   ```sh
   mkdir build
   cd build
   cmake ..
   make
   ```

3. **Run the Executable**:
   After building the project, run the executable:
   ```sh
   ./OpenGLExample
   ```

## Usage

- **WASD Keys**: Move the camera forward, backward, left, and right.
- **Mouse**: Look around by moving the mouse.
- **ESC Key**: Toggle mouse capture to regain control of the mouse cursor.

This simple OpenGL program serves as a foundation for learning and experimenting with 3D graphics, camera movement, and basic lighting techniques.
