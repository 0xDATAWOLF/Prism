# Prism
Prism is a 2D game engine that utilizes OpenGL and developed in C++.
The goal of the project is to create a functioning engine and to create
a game using it. To get started, simply clone the project with:

```
git clone https://github.com/0xDATAWOLF/Prism --resursive
```

And this will automatically import the required dependencies as well as the source files required to get started.
The project uses premake to build the necessary project files for the platform (Visual Studio, xcode, etc.). This
will automatically create the links to the dependencies. To do this, simply run the premake binary for your platform:

```
./build_tools/premake_[platform]/premake5 [IDE environment]
```

Once completed, you can open up the project and begin work developing in the engine, or if you're creating a game or
performing tests, in sandbox.

## Current Dependencies

* **OpenGL** – The graphics framework of choice for the project.
* **GLFW** The window framework. It is cross-platform, perfect for
	porting to other operating systems.
* **spdlog** A logging library because no one needs to reinvent this wheel.

## Feature List

| Feature Name | Status | Implemented |
| :--- | :--- | :----: |
| xcode premake | In progress | ℹ️ |
| Logging | Included library, in-dev, no work necessary | ✅ |
| App Framework | Not started | ⬜️ |
| Sandbox Project | Not started | ⬜️ |
| GLFW Project | Included source, in-dev | ⬜️ |
| Premake Project Builder | Not started | ⬜️ |
| Essential Utilities | Not started | ⬜️ |



