# Transducer Visualizer
## Installation
The application is written using [Qt Creator IDE](https://info.qt.io/download-qt-for-application-development) - the simplest way to compile it, is to download Qt IDE. Qt will inform you during compilation abut any missing libraries.
If you don't want to download whole IDE, you can download qmake. [Here](https://stackoverflow.com/questions/3632038/can-i-use-qt-without-qmake-or-qt-creator) is more information about compiling without Qt IDE. Here are step by step instructions installing Qt for [Ubuntu](https://wiki.qt.io/Install_Qt_5_on_Ubuntu).
## Running application
Given application has two executable files - one for unit test and one for whole gui app. Before running, please check choosen version - it should be 'TransducerGUI2' (you can check it in bottom-left corner in QT Creator, after clicking on big button display icon). 
## Dependencies
Only QT dependencies: [For Linux](http://doc.qt.io/qt-5/linux-requirements.html)
[For Windows](http://doc.qt.io/qt-5/windows-requirements.html)
## Why QT
- QT is multiplatform
- Built-in GUI and UT frameworks
- Well maintained framework
## Application shortcuts
- T - Add new transducer to pipe
- N - Edit input
- F5 - Run Transducers
- F10 - Run One Step of transducer
- R - Reset Transducers and Inputs
- '\+' \- Zoom in
- '\-' \- Zoom out
- W, S, A, D - navigate over transducer FSM

