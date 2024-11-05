# Minitalk
[![42 School: Rank 2](https://img.shields.io/badge/42%20School-Rank%202-%2315bbbb)](https://www.42network.org/)

_Minitalk is a project about coding of a small data exchange program using UNIX signals._

___


### Table of contents
[Subject notes](#pencil2-subject-notes) · [Usage](#compass-usage) · [License](#license)

___

</br>

# :pencil2: Subject notes

Notes on the subject and further reading : [here](./minitalk-notes.md).

___

</br>

# :compass: Usage
## Setup and compilation

1. Clone repository
    ```bash
    git clone git@github.com:teresa-chow/42-minitalk.git minitalk
    ```

2. Go inside project directory and run `make`
    ```bash
    cd minitalk
    make
    ```
3. To check Makefile rules, run `make` followed by `help` as an argument
    ```bash
    make help
    ```
4. Start the `server` first
    ```bash
    ./server
    ```
5. And then execute the `client` in a different terminal window
    ```bash
    ./client <server_pid> <message>
    ```
6. To compile the project with bonus features, run `make bonus`
    ```bash
    make bonus
    ```
7. Start `server_bonus` first
    ```bash
    ./server_bonus
    ```
8.  And then `client_bonus` in a different terminal window
    ```bash
    ./client_bonus <server_pid> <message>
    ```
___

</br>

### License
This work is published under the terms of [42 Unlicense](./LICENSE).

</br>

[⬆ back to top](#minitalk)
