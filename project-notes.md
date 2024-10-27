# Minitalk
[![42 School: Rank 2](https://img.shields.io/badge/42%20School-Rank%202-%2315bbbb)](https://www.42network.org/)

_This document contains my notes about 42 Common Core curriculum project "Minitalk"._

___


### Table of contents
[Mandatory instructions](#mandatory) · [Bonus instructions](#bonus-part) · [References & further reading](#references--further-reading)

___

</br>

# 📖 Subject – instructions

## Mandatory

- Name of executable files: `client` and `server`.
- Turn in a Makefile to compile source files. It must not relink.
- Use of `libft` is allowed.
- Errors must be handled.
- No memory leaks.
- Up to one global varible per program (one for the `client`, one for the `server`).
- The `server` must be started first. After its launch, it has to print its PID.
- The `client` takes two parameters: `server PID` + `string to send`.
- The `client` must send the string passed as a parameter to the `server`. Once the string has been received, the server must print it. (Original, in French: _Une fois la chaîne **entièrement reçue**, le serveur doit l’afficher._)
- One can only use these two signals: `SIGUSR1` and `SIGUSR2`.
- The `server` should be able to receive strings from several clients in a row without needing to restart.
- Communication between client and your server has to be done **only** using `UNIX signals`.

- Use of the following functions is allowed:

Function | Library | Description
--|--|--
write | unistd.h |
signal | signal.h | _ANSI C signal handling._ </br></br> :warning: **WARNING:** the behavior of `signal()` varies across UNIX versions, and has also varied historically across different versions of Linux.  Avoid its use: use `sigaction(2)` instead.
sigemptyset | signal.h | `int  sigemptyset(sigset_t *set);` </br> _Returns `0` on success and `-1` on error._ </br></br> _`sigemptyset()` initializes the signal set given by set to empty, with all signals excluded from the set._ </br></br> 💡 **OBS.:** Objects of type `sigset_t` must be initialized by a call to either `sigemptyset()` or `sigfillset()` before  being passed to the functions `sigaddset()`, `sigdelset()`, and `sigismember()` or the additional glibc functions described below (`sigisemptyset()`, `sigandset()`,  and  `sigorset()`). The results are undefined if this is not done.
sigaddset | signal.h | `int sigaddset(sigset_t *set, int signum);` </br> _Returns `0` on success and `-1` on error._ </br></br> _`sigaddset()` adds signal signum from set._
sigaction | signal.h | `struct sigaction {`</br>`void     (*sa_handler)(int);`</br>`void     (*sa_sigaction)(int, siginfo_t *, void *);`</br>`sigset_t   sa_mask;`</br>`int        sa_flags;`</br>`void     (*sa_restorer)(void);`</br>`};` </br></br>_`sigaction` examines and changes a signal action._</br></br>_The `sigaction()` system  call is used to change the action taken by a process on receipt of a specific signal._
kill | | `kill [options] <pid>`</br></br>_`kill` sends a signal to a process._</br></br> 💡 **OBS.:** (…) Negative PID values may be used to choose whole process groups; see the PGID column in ps command output.  A PID of -1 is special;  it  indicates  all processes except the kill process itself and init.
getpid | unistd.h | _`getpid()` returns the process ID (PID) of the calling process. (This is often used by routines that generate unique temporary filenames.)_
malloc | stdlib.h |
free | stdlib.h |
pause | unistd.h | _Wait for signal._</br></br>_`pause()`  causes  the calling process (or thread) to sleep until a signal is delivered that either terminates the process or causes the invocation of a signal-catching function._</br></br>_`pause()` returns only when a signal was caught and the signal-catching function returned. In this case, `pause()` returns `-1`, and errno is set to EINTR._
sleep | |
usleep | unistd.h | _`usleep` suspends execution for microsecond intervals._</br></br>_The `usleep()` function suspends execution of the calling thread for (at least) usec microseconds. The sleep may be lengthened slightly by any system activity or by the time spent processing the call or by the granularity of system timers._
exit | |

</br>

## Bonus

- The `server` acknowledges every message received by sending back a signal to the `client`.
- Unicode characters support.

___

</br>

<details>
<summary><h3>References & further reading</h3></summary>

  <h4>Signals</h4>
    <ul>
      <li><a href="https://youtu.be/L3XuR-iRysU?si=esZTueFBHtXtvLeM">Understanding signals in Linux system [video]</a></li>
      <li><a href="https://www.youtube.com/watch?v=5We_HtLlAbs">Code Vault: Short introduction to signals in C [video]</a></li>
      <li><a href="https://www.youtube.com/watch?v=jF-1eFhyz1U">Code Vault: Handling signals [video]</a></li>
      <li><a href="https://www.youtube.com/watch?v=PErrlOx3LYE">Code Vault: Communicating between processes using signals [video]</a></li>
      <li><a href="https://www.codequoi.com/en/sending-and-intercepting-a-signal-in-c/">Code(quoi); : Sending and intercepting a signal in C</a></li>
    </ul>
  </br>
  <h4>Bitwise operators</h4>
    <ul>
      <li><a href="https://www.geeksforgeeks.org/bitwise-operators-in-c-cpp/">Bitwise operators in C</a></li>
    </ul>
  </br>
  <h4>Makefile</h4>
    <ul>
      <li><a href="https://www.gnu.org/software/make/manual/">GNU Make (manual)</a></li>
      <li><a href="https://github.com/amjadmajid/Makefile/tree/master/04_Same_Directory">Makefile special variables</a></li>
      <li><a href="https://stackoverflow.com/questions/4879592/whats-the-difference-between-and-in-makefile">Makefile assignments</a></li>
      <li><a href="https://www.padok.fr/en/blog/beautiful-makefile-awk">Beautiful Makefile</a></li>
    </ul>
</details>
