# ascii-3D-cylinder

Realtime 3D ASCII cylinder renderer in C++ with Z-Buffering and Shading. (No Raytracing)

# DEMO

![cylinder](https://github.com/user-attachments/assets/b0e36b4c-8034-4659-9325-c90f1d309bba)


# Yappinng AHEAD!!!

UHmmm....
Yeah this project was **INSPIRED** by the famous ASCII 3D donut renderer by Andy Sloane, which uses clever math and perspective to animate a rotating torus in a text terminal:  
https://www.a1k0n.net/2011/07/20/donut-math.html

While the original renders a torus, I thought it would be cool to try rendering a **CYLINDER** with shading and depth buffering.
Also cylinder was chosen because cylinderical coordinates are much easier to understand.


## Why this project?

Given I use Blender most of time so I have always wanted to understand how 3D graphics work at a low level — without using OpenGL or any graphics libraries. 
Using the concepts from the classic ASCII donut demo, I decided to build my own renderer and apply the math to a different shape.


## Features

- Perspective projection
- Rotation around X, Y, Z axes
- Z-buffer for depth handling
- ASCII shading using surface normals
- Runs entirely in the terminal
