# minishell
42 project minishell

A simple Unix shell implemented in C, designed as a project to understand and practice basic shell functionalities such as parsing commands, managing environment variables, handling redirections, and implementing built-in commands.

---

## Overview

**minishell** is a minimalistic command-line shell that replicates a subset of common shell features. This project is an educational exercise to deepen knowledge of process control, parsing, and system calls in Unix-based systems.

---

## Features

* Execute external commands with arguments
* Built-in commands: `cd`, `echo`, `env`, `exit`, `pwd`, `export`, `unset`
* Environment variable management
* Input/output redirection (`>`, `<`, `>>`)
* Command pipelines (`|`)
* Signal handling (e.g., Ctrl-C to interrupt)
* Proper error handling and exit statuses

---

## Getting Started

### Prerequisites

* Unix-like operating system (Linux, macOS)
* GCC compiler (or compatible C compiler)
* Make utility

### Installation

1. Clone the repository:

   ```bash
   git clone https://github.com/JohannaGcd/minishell.git
   cd minishell
   ```

2. Compile the project using `make`:

   ```bash
   make
   ```

3. Run the shell:

   ```bash
   ./minishell
   ```

---

## Usage

Once running, you can enter commands just like in a regular shell.

Examples:

```bash
$ echo Hello, minishell!
Hello, minishell!
$ cd ..
$ pwd
/home/user
$ ls -l | grep minishell
-rwxr-xr-x  1 user user  12345 Jun 10 2025 minishell
```

To exit the shell, use the `exit` command or press `Ctrl-D`.

---

## Project Structure

* `src/` - Source code files implementing the shell
* `includes/` - Header files
* `Makefile` - Build configuration
* `.gitignore` - Ignored files for Git

---

## Contributing

This project is primarily for educational purposes. Feel free to fork and experiment with improvements or additional features.

---

## License

This project is licensed under the [MIT License](LICENSE).

---

## Acknowledgments

Inspired by basic shell design principles and implemented as part of 42 coding curriculum.
