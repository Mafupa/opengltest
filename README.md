# Test with opengl

### environment configuration
- go to [msys2.org](https://www.msys2.org/)
- download the installer and run it
- follow the instructions and launch msys2 when the installation is done
- in the msys2 terminal run: `pacman -Syu` and follow the instructions
- reopen the terminal when it closes and run: `pacman -Su`
- run: `pacman -S --needed base-devel mingw-w64-x86_64-toolchain`
- add `C:\msys64\mingw64\bin` and `C:\msys64\usr\bin` to the path

### compilation
`g++ -std=c++11 -Wall -Iinclude -Llib *.cpp -lglfw3 -lopengl32 -lgdi32 -o a`
