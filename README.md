# CSuite

Cipher Suite

## Software Requirements

The following software tools were used to implement and build CSuite. Using different tools may provide different results.

- Qt Creator 18.0.1
- CMake 4.2.0
- GCC 6.3.0

## Usage

CSuite can be used in different ways.

### Downloading

First, clone CSuite to your local machine:
```
git clone https://www.github.com/ntjennings1/csuite.git
```

Then enter the cloned directory ($CSuite_HOME):
```
cd $CWD/csuite
```

NOTE: Make sure you add these to your path:
```
Qt_HOME/6.10.1/mingw_64\bin
Qt_HOME/Tools/QtCreator/bin
```

### Opening

Once inside the clonse directory, open CSuite's CMakeLists.txt file in Qt Creator:
```
qtcreator CMakeLists.txt
```

This will take a minute.

### Changing
 
After loading with Qt, users can access the following directories to change CSuite's functionalities:
```
CSuite_HOME/Forms
CSuite_HOME/Header Files
CSuite_HOME/Source Files
```

Inside are the same CPP & Header files users see through Git.

### Executing

To perform CSuite functionalities, open the packaged CMakeLists.txt in Qt Creator:

Once Qt indexes source code and dependencies, users can easily execute CSuite. This will open the UI and allow users to perform their desired tasks.

## Acknowledgements
```
Noah Jennings 
    ntjennings1@gmail.com
    Virginia Beach, VA
```
