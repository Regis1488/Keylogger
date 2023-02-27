# Keylogger

[![GPLv3 License](https://img.shields.io/badge/License-GPL%20v3-yellow.svg)](https://opensource.org/licenses/)

### A keylogger in C++

My keylogger allows to record the typing of the user. It then allows when the windows receive the signal `SM_SHUTTINGDOWN` send it to discord webhook.

For now it record via `GetAsyncKeyState` but I will try to hook Windows directly.

### Dependencies
* Curlpp
* DPP
### Installation

* Git clone the project.
* Create a new Visual Studio C++ Project.
* Drag and drop the files into your project
* Use MBS characters (not Unicode)
* Put the C++17.
* Compile.

## ⚠️ Disclamer ⚠️

I am in no way responsible for the use of my project for malicious purposes. This project is for Educational Purpose.

## Authors

- [@Regis1488](https://www.github.com/Regis1488)
- [@atom1488](https://www.github.com/atom1488)
