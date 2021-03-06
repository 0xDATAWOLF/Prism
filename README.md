# Prism
Prism is a 2D game engine that utilizes OpenGL and developed in C++. The goal of the project is to create an extensible
game engine from scratch.

## Getting Started 
To get started, simply clone the project with:

```
git clone https://github.com/0xDATAWOLF/Prism --resursive
```

The project uses premake to build the necessary project files for the platform (Visual Studio, Xcode, etc.).
This automatically creates the necessary links to the dependencies and establishes post-build steps for linking
the engine shared library to the *Sandbox* environment. Premake is already included in the `./build_tools` directory.

```
./build_tools/premake_[platform]/premake5 [IDE environment: vs2019]
```

For example: `./build_tools/premake_windows/premake5 vs2019`

You can find the appropriate documentation in the wiki tab. This is for end-users and not reflective of the engine code
which contains far more detail than what is provided in the wiki.

## Current Dependencies

* **OpenGL** – The graphics framework of choice for the project.
* **GLFW** The window framework. It is cross-platform, perfect for
	porting to other operating systems.
* **spdlog** A logging library because *no one* needs to reinvent this wheel.
* **Dear imgui** An immediate mode GUI for... GUI stuff.
* **glm** Maths library. I eventually want to make my own because this wheel is fun to reinvent.

## License
Please review the [license](LICENSE.md) before cloning the project.