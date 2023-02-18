# Libraries installation guide

Two external C++ library are used in the development of this project:
a) [mlpack](https://www.mlpack.org/), which provides various implementations of machine learning algorithms.
b) [nlohmann-json](https://github.com/nlohmann/json), which provides implementation to process JSON files.

In order to install all the packages required to successfully build the EC3 project's application in Visual Studio, the following steps are suggested for Windows users.

## 1- Install _vcpkg_ dependency manager

1. Download the source files of _vcpkg_ dependency manager directly from its official GitHub [repository](https://github.com/Microsoft/vcpkg#quick-start-windows). For this task, open a terminal instance in a directory of your preference  and type the following command:

        git clone https://github.com/microsoft/vcpkg

    > PS.: It is recommended to download the vcpkg source files in a general directory of your machine (somewhere like _C:\src\vcpkg_ or _C:\dev\vcpkg_), so that the libraries installed by _vcpkg_ can stay globally available for other possible projects in the future.
2. Bootstrap vcpkg by running the following the terminal command in the chosen directory:

        .\vcpkg\bootstrap-vcpkg.bat

3. Install the _vcpkg_ integration for Visual Studio by running the terminal command:

        .\vcpkg\vcpkg integrate install

    > With this command, we can make  all the libraries installed using vcpkg automatically available in any C++ file created inside Visual Studio environment.Even, these libraries will show up in Visual Code IntelliSense System automatically.

## 2 - Set _vcpkg_'s path as an environment variable in Windowns

1. In Windows, press _Windows Key_ + _R_ to open the Windows 'Run' box
2. Type "_systempropertiesadvanced_" in the input box and press "_ok_"
3. Choose "_Environment Variables_" from the _System Properties_ window
4. Click on "_Path_" in User's Variables section 
5. Click on "_New_"
6. Write the directory path that you have chosen for vcpkg source files (_C:\dev\vcpkg_ for example)

If the previous steps were followed correctly, the vcpkg terminal command should now be available in all directories of your machine.

To ensure that this process was concluded successfully, open your terminal in any directory and type the following command:

    vcpkg --help

If no error was returned, then the global installation of _vcpkg_ was successful.

## 3 - Install the mlpack library and its dependencies with _vcpkg_

Once the installation of vcpkg dependency manager was installed successfully, mlpack can be installed with all the packages required for this project by typing the following command in the terminal:

    vcpkg install mlpack:x64-windows

With this command, the x64 version of the mlpack library, along with its dependencies, such as _armadillo_, are going to be installed and linked properly inside the _packages_ folder in the _vcpkg_'s chosen directory.

## 4 - Install the nlohmann-json library and its dependencies with _vcpkg_

Once the installation of vcpkg dependency manager was installed successfully, nlohmann-json can be installed with all the packages required for this project by typing the following command in the terminal:

    vcpkg install nlohmann-json:x64-windows

With this command, the x64 version of the nlohmann-json library, along with its dependencies, are going to be installed and linked properly inside the _packages_ folder in the _vcpkg_'s chosen directory.
