# GameEngineDev

**GameEngineDev** is a foundational project aimed at developing a simple game engine using C and C++.  
The project utilizes the SDL (Simple DirectMedia Layer) library to manage graphics rendering, audio playback, and user input, providing a comprehensive framework for game development.

## Features

- **Graphics Rendering**: Leverages SDL to render 2D graphics efficiently.
- **Audio Playback**: Incorporates SDL's audio subsystem for sound effects and music.
- **Input Handling**: Captures and processes user input from various devices.

## Getting Started

To set up the project on your local machine:

### 1. Clone the Repository

```bash
git clone https://github.com/ShamsulArifin/GameEngineDev.git
```

### 2. Install Dependencies

- **SDL Library**:  
  Make sure SDL3 is installed on your system. You can download it from this [link](https://github.com/libsdl-org/SDL/releases).

### 3. Build the Project

Navigate to the project directory:

```bash
cd GameEngineDev
```

Compile the source code using your preferred build system or compiler. For example, with `g++`:

```bash
g++ main.cpp -I src/include -L src/lib -lSDL3 -o main.exe
```
or, to run with SDL3_ttf:

```bash
g++ -I src/include -L src/lib -o main main.cpp -lSDL3 -lSDL3_ttf
```

### 4. Run the Application

```bash
./main
```

## Project Structure

The repository currently contains the following directory:

- **SDLTemplate/**: A template project set up with SDL to kickstart development.

## About the Author

This project is maintained by [Shamsul Arifin](https://portfolio-eta-seven-57.vercel.app/)  
Website: [shamsularifin.pro](https://portfolio-eta-seven-57.vercel.app/)

## Contributing

Contributions are welcome!  
If you'd like to contribute to this project, please fork the repository and submit a pull request with your enhancements.

## License

This project is licensed under the [MIT License](LICENSE).
