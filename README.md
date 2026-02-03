*This project has been created as part of the 42 curriculum by ldesboui, fgarnier.*
# Minishell Project Documentation

## 1. Introduction

Minishell is a simplified version of a Unix shell (like bash). The objective of this project is to understand processes, file descriptors, and the complexities of parsing a command line. This document outlines the architectural choices, the logic behind the parsing, and the execution pipeline implemented by the team.

## 2. Architecture Overview

Our shell follows a modular architecture divided into three main phases:

1.  **Lexing & Parsing:** Converting raw user input into structured data.
2.  **Expansion:** Handling environment variables and wildcards.
3.  **Execution:** Managing processes, pipes, and redirections.

### 2.1 The Data Structure
We use a linked list structure to hold tokens and command groups:
* `t_token`: Holds individual words, operators (`|`, `>`, `<`), and their types.
* `t_cmd`: Holds the arguments for `execve`, input/output file descriptors, and pointers to the next command in the pipeline.

## 3. Parsing Logic

The parsing phase is critical for correctly interpreting quotes and special characters.

### 3.1 Tokenization
The raw string is iterated over to identify separators. We handle:
* **Single Quotes (`'`):** Literal interpretation (no expansion).
* **Double Quotes (`"`):** Allows `$` expansion but preserves spaces.
* **Metacharacters:** `|`, `<`, `>`, `<<`, `>>`.

### 3.2 Syntax Checking
Before execution, the parser verifies syntax errors, such as:
* Unclosed quotes.
* Double pipes (`||`) or misplaced redirection operators (`> |`).

## 4. Execution Pipeline

The execution engine determines whether a command is a built-in or an external binary.

### 4.1 Pipes and Redirections
* **Pipes:** We use `pipe()` and `fork()`. The Output FD of the left command is dup2'd to the Input FD of the right command.
* **Redirections:** Files are opened with specific flags (`O_TRUNC`, `O_APPEND`) and `dup2` replaces STDIN/STDOUT accordingly. `Here_doc` is handled via a temporary file (or pipe buffer).

### 4.2 Signal Handling
* `SIGINT` (Ctrl+C): Displays a new prompt on a new line.
* `SIGQUIT` (Ctrl+\): Ignored in the prompt, but kills blocking child processes (creating a core dump if required).
* `SIGEOF` (Ctrl+D): Exits the shell cleanly.

## 5. Built-ins Implementation

We implemented the following built-ins without `execve`:

| Built-in | Description | Notes |
| :--- | :--- | :--- |
| `echo` | Prints arguments to STDOUT. | Handles `-n` flag. |
| `cd` | Changes directory. | Updates `PWD` and `OLDPWD`. |
| `pwd` | Prints current working directory. | Uses `getcwd`. |
| `export` | Adds/Updates env variables. | Sorts output if no args given. |
| `unset` | Removes env variables. | Does nothing if var doesn't exist. |
| `env` | Prints environment. | Only prints exported vars with values. |
| `exit` | Exits the shell. | Handles numeric arguments (0-255). |
