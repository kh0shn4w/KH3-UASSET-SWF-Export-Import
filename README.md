# UASSET SWF Export/Import Tool for Kingdom Hearts 3

This is a C++ console application designed to export and import `.gfx` or `.swf` files from and to `.uexp` files for modding *Kingdom Hearts 3*. The tool is based on a 010 Editor template and allows modders to extract `.gfx` or `.swf` assets (e.g., UI elements) from `.uexp` files, edit them, and import them back into a new `.uexp` file for use in the game.

## Features
- **Export**: Extract `.gfx` or `.swf` files from `.uexp` files starting at offset 285.
- **Import**: Replace the `.gfx` or `.swf` data in a `.uexp` file with an edited version while preserving the original file structure.
- **Console Interface**: Simple menu-driven interface for selecting export or import operations.
- **Error Handling**: Basic checks for file operations to ensure reliable extraction and importation.
- **Cross-Platform Compatibility**: Written in standard C++ for compatibility with Windows, Linux, or macOS (with appropriate compilers).

## Prerequisites
- **Visual Studio 2022** with the *Desktop development with C++* workload installed (for Windows users).
- **g++** or another C++11-compatible compiler (for Linux/macOS or manual compilation).
- A basic understanding of *Kingdom Hearts 3* modding and file structures.

## Compilation
The project is written in standard C++11 and can be compiled using Visual Studio 2022 or other C++ compilers.

### Option 1: Compile with Visual Studio 2022 (Windows)
1. Clone the repository:
   ```bash
   git clone https://github.com/kh0shn4w/KH3-UASSET-SWF-Export-Import.git
   cd KH3-UASSET-SWF-Export-Import
