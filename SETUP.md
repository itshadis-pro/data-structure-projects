# Setting up for CS 313 programming

Every programming assignment in CS 313 assumes the same environment: a Linux terminal with **gcc**, **make**, and **valgrind**. The Gradescope autograder runs on Linux, so this setup matches what grades your code.

Pick **one** of the three options below. Then run the check at the bottom. If the check passes, every assignment's instructions will work as written.

## Option A: the Debian virtual machine from CS 212

If you still have the VirtualBox VM from CS 212, use it. Open a terminal in the VM and install the tools (it is fine if some are already installed):

```
sudo apt update
sudo apt install build-essential valgrind
```

`build-essential` includes gcc and make.

## Option B: the department server ix-dev

UO CS runs a Linux server with everything already installed. From any terminal (on a Mac: Applications → Utilities → Terminal; on Windows: PowerShell), connect with your Duck ID:

```
ssh yourduckid@ix-dev.cs.uoregon.edu
```

To copy files between your laptop and ix-dev, use `scp`, or use VS Code with the **Remote - SSH** extension, which lets you edit files on ix-dev as if they were local. ix-dev is being retired after this year, but it works this term.

## Option C: GitHub Codespaces (runs in your browser)

Codespaces gives you a Linux machine with VS Code in a web browser. Nothing to install on your laptop. You need a free GitHub account; students get extra free hours through the GitHub Student Developer Pack.

1. Create a new GitHub repository (private is fine) and upload the assignment's files, including the `.devcontainer` folder.
2. On the repository page, click **Code → Codespaces → Create codespace**.
3. Wait a minute or two. The `.devcontainer` folder tells Codespaces to install gcc, make, and valgrind for you.

When you are done, download your files and submit them to Gradescope.

## What about my Mac or Windows laptop directly?

- **Mac:** gcc (really clang) and make work after you install the Command Line Tools (`xcode-select --install`). valgrind does not run on recent Macs. You can still build and test; the autograder runs valgrind for you.
- **Windows:** use Option B or C. (WSL also works if you already know it.)

## Check your setup

In your terminal, run:

```
gcc --version
make --version
valgrind --version
```

Each command should print a version number. (On a Mac, `valgrind --version` fails; that is expected.)

Then, in the folder of an assignment's starter files, run:

```
make
```

It should compile the starter code without errors. The starter code fails the tests on purpose, until you fill it in.

## What `make` does

A `Makefile` lists the compile commands for an assignment, so you do not have to type them. `make` builds everything; `make check` builds and runs the tests; each assignment's README lists its other commands. If you are curious what `make` is running, it prints each command before running it.

## Getting help

If none of the options work for you, come to office hours or post in the Canvas discussion for the assignment with the exact error message.
