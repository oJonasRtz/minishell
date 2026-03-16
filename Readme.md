# Minishell

`Minishell` is a minimal Unix shell implemented in `C`.
The goal of the project is to understand how shells work internally by implementing parsing, process creation, and command execution.

This project is part of the curriculum of the `Ecole 42`.

## Architecture

General
```mermaid
flowchart TD

    A[Create] --> B[Execute]
    B --> C[Destroy]

    %% CREATE
    subgraph CREATE_STAGE["Create Stage"]
        direction LR
        A1["init_data()"] --> A2["allocate prompt struct"]
        A2 --> A3["initialize variables"]
        A3 --> A4["export_init(envp)"]
        A4 --> A5["setup environment"]
    end

    %% EXECUTE
    subgraph EXECUTE_STAGE["Execute Stage"]
        direction LR
        B1["display_prompt loop"] --> B2["readline()"]
        B2 --> B3["handle_space()"]
        B3 --> B4["add_history()"]
        B4 --> B5["analysis()"]

        B5 --> B6["updateenvp()"]
        B6 --> B7["lexer()"]
        B7 --> B8["check_syntax()"]
        B8 --> B9["make_ast()"]
        B9 --> B10["minishell executor"]
    end

    %% DESTROY
    subgraph DESTROY_STAGE["Destroy Stage"]
        direction LR
        C1["export_clean()"] --> C2["clean_locals()"]
        C2 --> C3["free prompt/input"]
        C3 --> C4["reset pointers"]
        C4 --> C5["exit()"]
    end

    A --> A1
    B --> B1
    C --> C1
```

The shell processes commands through mutiples stages before execution
```mermaid
flowchart TD
    A[User Input] --> B[Lexer]
    B --> C[Syntax Analyzer]
    C --> D[AST Builder]
    D --> E[Executor]
```

## Program  Lifecycle

```mermaid
flowchart TD
    A["main()"] --> B["create()"]
    B --> C["execute()"]
    C --> D["destroy()"]
```

### Main

Initializes the shell instance and installs signal handlers.

### Create
Responsible for initializing the shell state.
```
init_data -> setup evironment
```
After initialization it transfers control to the execution loop.

### Execute
Handles the main shell loop.
```mermaid
flowchart TD
    A["display_prompt()"] --> B["analysis()"]
    B --> C[Command Execution]
```
Each user command goes through the full parsing and execution pipeline.

### Execution Engine

Commands are executed using a `AST-Based` execution model.  
Exemple:
`ls -l | grep minishell > out.txt`  
AST representation:
```mermaid
graph TD
    PIPE --> CMD1[CMD: ls -l]
    PIPE --> REDIR[REDIR > out.txt]
    REDIR --> CMD2[CMD: grep minishell]
```

### Redirection Handling
Redirections are detected and applied before command execution.    

Suported operators:
```
Redirect_out: >
Append: >>
Redirect_in: <
Heredoc: <<
```
Redirections are processed by `manage_redir()` which:
- scans tokens related to the command
- opens the required file descriptors
- applies them using `dup2`
- restores original descriptors after execution

```mermaid
flowchart TD
    A[save_origin<br/>save STDIN STDOUT] --> B[manage_redir]
    B --> C[apply_redirect]
    C --> D[execute command]
    D --> E[restore_redirect<br/>restore STDIN STDOUT]
```