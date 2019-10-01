# Setup and Compile Instructions
**Developed with Qt Creator**
Qt Creator can be downloaded from their website if the target machine does not already have it installed.
[https://www.qt.io/](https://www.qt.io/)

Debug compilation through Qt is possible, but Qt hard-codes the build paths by default.  Code was locally developed in the following directory:
C:\code\dss\qt\NCP-CodeExample

If pulled from GitHub the repository should be cloned in to C:\code\dss (the qt/DCP-CodeExample directories are in the repository).

If Qt Creator is unavailable, there is a NCP-CodeExample_win.zip file in the qt/ folder that includes a build that is compatible with Windows 10.  Extract the files, navigate to the 'deployment' directory within the extracted directory and run the NCP-CodeExample.exe executable.

**Caveats**
After a build from Qt Creater - if the images fail to load there may be some TLS issues.  On a windows machine this can be fixed by moving the content of the qt/crypto folder into appropriate the build directory.
