# cpp-geometry-templates

A menu-driven CLI application in C++ that represents and computes properties of 2D and 3D geometric objects using templates and object-oriented programming.

## Features

- Models **2D and 3D points** (`Point2D`, `Point3D`) and **lines** (`Line2D`, `Line3D`)
- Computes **scalar values** (e.g. distance/magnitude) for each geometric type
- Uses **function templates** to compare and find scalar differences across any geometric type
- Supports sorting and filtering geometric objects via menu options

## Concepts Demonstrated

- C++ **function templates** (`scalar_difference<T>`, `equals<T>`)
- Inheritance and class hierarchies across 2D/3D types
- Operator overloading for equality comparison
- Modular design with header/source file separation

## Build & Run

```bash
g++ -std=c++11 Assn3.cpp Functions.cpp Point2D.cpp Point3D.cpp Line2D.cpp Line3D.cpp -o geometry_app
./geometry_app
```

## File Structure

```
├── Assn3.cpp         # Entry point and menu loop
├── Functions.h/cpp   # Menu and option logic
├── MyTemplates.h     # Function templates (scalar_difference, equals)
├── Point2D.h/cpp     # 2D point class
├── Point3D.h/cpp     # 3D point class
├── Line2D.h/cpp      # 2D line class
└── Line3D.h/cpp      # 3D line class
```
