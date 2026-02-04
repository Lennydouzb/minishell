*This project has been created as part of the 42 curriculum by ldesboui, fgarnier.*
# Minishell Project Documentation

## 1. Description

Minishell is a simplified version of a Unix shell (like bash). The objective of this project is to understand processes, file descriptors, and the complexities of parsing a command line.

## 2.Instructions

To use this project :
```bash
    make
    ./minishell
```
once ./minishell is executed you'll enter its realm

## 3.Resources

RTFM, bash itself is what you need to copy.
Linked list example : https://www.geeksforgeeks.org/dsa/linked-list-data-structure/

Ai was used on this project for Debugging advanced part of it when classic debuggers were harder to follow

## 4. feature list
This shell handles redirect (> / <), heredocs (<<), append (>>), and pipes.
Moreover echo, env, pwd, export, unset, exit are builtsin, which mean we coded them ourselves.

## 5. Technical choices

Every command (separated by pipes) are handled by chained lists.
Commands except for  builtsin and cd are executed by execve;
