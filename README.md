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
./build_tools/premake_[platform]/premake5 [IDE environment: xcode4, vs2019]
```

## Current Dependencies

* **OpenGL** – The graphics framework of choice for the project.
* **GLFW** The window framework. It is cross-platform, perfect for
	porting to other operating systems.
* **spdlog** A logging library because *no one* needs to reinvent this wheel.

## Feature List

**Icon Descriptions**
* ⬜️ – Scheduled task / feature.
* ℹ️ – Currently in progress or researched.
* ⏩ – Task / feature scheduled for rework.
* ✅ – Completed task / feature.
* 🆑 – Scraped task / feature.

| Feature Name | Status | Implemented |
| :--- | :--- | :----: |
| Xcode premake | Premake creates project files, compilation to be tested | ℹ️ |
| Visual Studio premake | Untested | ℹ️ |
| Logging | Included library, in-dev, no work necessary | ✅ |
| App Framework | Not started | ⬜️ |
| Sandbox Project | Not started | ⬜️ |
| GLFW Project | Included source, in-dev | ⬜️ |
| Premake Project Builder | Not started | ⬜️ |
| Essential Utilities | Not started | ⬜️ |



