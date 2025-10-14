# vizionsdk_c Samples

This repository contains sample project demonstrating how to use the vizionsdk_c:

### Prerequisites

Before building, ensure you have:

1.  **CMake (Version 3.0 or newer):**
    * CMake is required to configure the build.
    * If you don't have it, download and install it from the [official CMake website](https://cmake.org/download/).
    * Make sure the `cmake` executable is in your system's PATH. You can verify by running `cmake --version` in your terminal.

2.  **C Compiler:**
    ### C Compiler
    - **Windows:** Install Visual Studio (with the "Desktop development with C++" workload) or use MinGW to obtain the gcc compiler.
    - **Linux (Ubuntu/Debian):**  
    Install the GNU C compiler and essential build tools:
    ```bash
    sudo apt install build-essential
    ```

---

## Building

For sample (Windows/Linux):

1. Open the terminal/command prompt:
   - Windows: Command Prompt or PowerShell
   - Linux: Your preferred terminal

2. Navigate to the sample directory:  
   e.g., `cd samples`

3. Create a build directory:
   ```bash
   mkdir build && cd build
   ```

4. Generate build files using CMake:
   ```bash
   cmake ..
   ```

5. Build the project:
   ```bash
   cmake --build .
   ```

---

## Configuring CMakeLists.txt

Link vizionsdk_c library from the extracted folder, update the paths manually:

```cmake
# Set include and lib paths
# NOTE: Adjust the path to match your actual SDK location
set(VIZIONSDK_C_PREFIX <your_vizionsdk_c_path>)

list(APPEND CMAKE_PREFIX_PATH ${VIZIONSDK_C_PREFIX})
find_package(vizionsdk_c REQUIRED)

target_include_directories(${PROJECT_NAME}
  PRIVATE
  ${VIZIONSDK_C_INCLUDE_DIR}
)

# Link libraries
target_link_libraries(${PROJECT_NAME}
  PRIVATE
  vizionsdk_c::vizionsdk_c
)
```

> 📌 **Note:**  
> Replace `<YOUR_SDK_PATH>` with the actual path to your extracted SDK directory.  
>
> You can also customize the location of the `VxConfig.conf` and `VxExposure.yaml` files by setting the `VIZIONSDK_CONFIG_PATH` environment variable.

---

## Running

After building, you'll find the executable in the `build` directory.  
Run it from the command line or terminal:

- **Windows**:  
  ```bash
  .\sample.exe
  ```

- **Linux**:  
  ```bash
  ./sample
  ```

---