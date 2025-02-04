# Bare-Bones OpenGL Game Engine

A game engine I've been writing off-and-on as a personal project. Currently it supports rendering predefined 3D objects through exposed OpenGL functionality such as the creation of Vertex Array Objects & Shaders, texture mapping, and user input through a custom Camera implementation. Usability is very limited and it will likely never be usable for a substantial game project. This project is being done for fun and for learning, and you should expect that level of code quality here.

### Features
* Exposed OpenGL functionality through the `Vertex` and `Shader` classes
* Texture loading using stb_image
* A free-cam using a custom Camera class
* A simple system for managing allocated graphics resources through the `BufCounter` class

### Features Wishlist
 - [ ] System for loading and playing audio
 - [ ] Loading and rendering 3D models in a way that doesn't require direct interaction with OpenGL functionality
 - [ ] A form of scene-based object hierachy so that we might actually be able to call this a game engine with a straight face
 - [ ] Configurable input system as currently all inputs are hard-coded