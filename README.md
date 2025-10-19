Code from Competitive Programming Essentials, Master Algorithms

## 1 How to run c++ code in VSC
Install compiler. (MinGW)
https://winlibs.com/ -> https://www.mingw-w64.org/ -> https://winlibs.com/#download-release
Download GCC 15.2.0 (with POSIX threads) + MinGW-w64 13.0.0 (UCRT) - release 2 Win64 (without LLVM/Clang/LLD/LLDB): 7-Zip archive* (012.winlibs-x86_64-posix-seh-gcc-15.2.0-mingw-w64ucrt-13.0.0-r2.7z)
Extract using 7zip. Put the mingw64 folder somewhere.
Add mingw64\bin to your environment variable PATH.
Check g++ --version

Manual type g++ command
View>Terminal>Command Prompt
g++ -std=c++17 -O2 -Wall main.cpp -o main.exe

or add a VSC build task
Terminal → Configure Tasks → Create tasks.json from template → Others
See .vscode\task.json

Make cmd (instead of powershell) default terminal. as current task.json set to compile and run cannot work with powershell.
1. Press Ctrl + Shift + P
2. Type Terminal: Select Default Profile
3. Choose Command Prompt
4. Then open a new terminal — it will use cmd.exe

## 2 Make VSC work with freopen in.txt, out.txt (files in same directory as cpp)
when you run the compiled program in VS Code, the current working directory is usually not the folder containing your .cpp file. freopen("in.txt", "r", stdin) looks for the file in the current working directory. By default, tasks (from tasks.json) use the folder you opened in VS Code as the CWD. "D:\\WJ_git\\CompetitiveProgramming"

In tasks.json, add "options": { "cwd": "${fileDirname}" }. "D:\\WJ_git\\CompetitiveProgramming\\CompetitiveProgramming_Exercises"