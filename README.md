
<!-- GETTING STARTED -->
## Getting Started
This repository containin a ready to use project template for compiling a User Filer for Aurora Vision Studio.
To get a local copy up and running follow these simple example steps.


### Prerequisites
Compiling the filter requires Ubuntu operating system with GNU gcc compiler installed. 
Having Aurora AVExecutor installed is also mandatory for header files.

### Usage
1. Clone the repo
   ```sh
   git clone https://github.com/ErykDevZebra/ExampleUserFilterLinux.git
   ```
2. Go to CMakeLists.txt file
    ```sh
   gedit /build/CMakeLists.txt
   ```
4. Edit AVExecutor path
   ```sh
   # Specify the source directory
   set(AVEXECUTOR_DIR "/home/mk6554/Downloads/Installers/5.5/avexecutor/")
   ```
6. Open console at /build dir, and run
  ```sh
  cmake ./
  make
  ```

Read More about linux filters [setup](https://docs.adaptive-vision.com/5.5/avl/getting_started/UserFilterOnLinux.html)
