# Minitalk
[![42 School: Rank 2](https://img.shields.io/badge/42%20School-Rank%202-%2315bbbb)](https://www.42network.org/)

_This document contains my notes about 42 Common Core curriculum project "Minitalk"._

___


### Table of contents

[Subject instructions](#subject-instructions) · [References & further reading](#references--further-reading)

___

</br>

<details open>
  <summary><h2>Subject instructions</h2></summary>
  <h3>Mandatory</h3>
  <ul>
    <li>Name of executable files: <code>client</code> and <code>server</code>.</li>
    <li>Turn in a Makefile to compile source files. It must not relink.</li>
    <li>Use of <code>libft</code> is allowed.</li>
    <li>Errors must be handled.</li>
    <li>No memory leaks.</li>
    <li>Up to one global varible per program (one for the <code>client</code>, one for the <code>server</code>).</li>
    <li>The <code>server</code> must be started first. After its launch, it has to print its PID.</li>
    <li>The <code>client</code> takes two parameters: <code>server PID</code> + <code>string to send</code>.</li>
    <li>The <code>client</code> must send the string passed as a parameter to the <code>server</code>. Once the string has been received, the server must print it. (Original, in French: <em>Une fois la chaîne <strong>entièrement reçue</strong>, le serveur doit l’afficher.</em>)</li>
    <li>One can only use these two signals: <code>SIGUSR1</code> and <code>SIGUSR2</code>.</li>
    <li>The <code>server</code> should be able to receive strings from several clients in a row without needing to restart.</li>
    <li>Communication between client and your server has to be done <strong>only</strong> using <code>UNIX signals</code>.</li>
    <li>Use of the following functions is allowed:</br></br>
      <table>
        <tr>
          <th>Function</th>
          <th>Library</th>
          <th>Description / Notes</th>
        </tr>
        <tr>
          <td>write</td>
          <td>unistd.h</td>
          <td></td>
        </tr>
        <tr>
          <td>signal</td>
          <td>signal.h</td>
          <td><em>ANSI C signal handling.</em> </br></br> :warning: <strong>WARNING:</strong> the behavior of <code>signal()</code> varies across UNIX versions, and has also varied historically across different versions of Linux.  Avoid its use: use <code>sigaction(2)</code> instead.</td>
        </tr>
        <tr>
          <td>sigemptyset</td>
          <td>signal.h</td>
          <td><code>int  sigemptyset(sigset_t *set);</code></br><em>Returns <code>0</code> on success and <code>-1</code> on error.</em></br></br><em><code>sigemptyset()</code> initializes the signal set given by set to empty, with all signals excluded from the set.</em></br></br>💡 <strong>OBS.:</strong> Objects of type <code>sigset_t</code> must be initialized by a call to either <code>sigemptyset()</code> or <code>sigfillset()</code> before  being passed to the functions <code>sigaddset()</code>, <code>sigdelset()</code>, and <code>sigismember()</code> or the additional glibc functions described below (<code>sigisemptyset()</code>, <code>sigandset()</code>,  and  <code>sigorset()</code>). The results are undefined if this is not done.</td>
        </tr>
        <tr>
          <td>sigaddset</td>
          <td>signal.h</td>
          <td><code>int sigaddset(sigset_t *set, int signum);</code></br><em>Returns <code>0</code> on success and <code>-1</code> on error.</em></br></br><em><code>sigaddset()</code> adds signal signum from set.</em></td>
        </tr>
        <tr>
          <td>sigaction</td>
          <td>signal.h</td>
          <td><code>int sigaction(int signum, const struct sigaction *restrict act, struct sigaction *restrict oldact);</code></br></br><em><code>sigaction</code> examines and changes a signal action. The <code>sigaction()</code> system  call is used to change the action taken by a process on receipt of a specific signal.</em></br></br><code>struct sigaction {</code></br><code>void     (*sa_handler)(int);</code></br><code>void     (*sa_sigaction)(int, siginfo_t *, void *);</code></br><code>sigset_t   sa_mask;</code></br><code>int        sa_flags;</code></br><code>void     (*sa_restorer)(void);</code></br><code>};</code></br></br><hr><em>The <code>sa_flags</code> field can be used to modify the behavior of the specified signal:</em></br></br>If <code>SA_SIGINFO</code> is set and the signal is caught, the signal-catching function shall be entered as:</br><code>  void func(int signo, siginfo_t *info, void *context);</code></br>where two additional arguments are passed to the signal-catching function.</br></br><code>typedef struct {</code></br><code>  int		si_signo;</code></br><code>  int		si_code;</code></br><code>  union sigval	si_value;</code></br><code>  int          si_errno;</code></br><code>  pid_t	si_pid;</code></br><code>  uid_t        si_uid;</code></br><code>  void		*si_addr;</code></br><code>  int		si_status;</code></br><code>  int		si_band;</code></br><code>}  siginfo_t;</code></td>
        </tr>
        <tr>
          <td>kill</td>
          <td>signal.h</td>
          <td><code>int kill(pid_t pid, int sig);</code></br></br><em><code>kill</code> sends a signal to a process.</em></br></br> 💡 <strong>OBS.:</strong><ul><li>Negative PID values may be used to choose whole process groups; see the PGID (Process Group ID) column in <code>ps</code> command output.</li><li>A PID of <code>0</code> indicates all of the processes in the calling process’ group.<li>A PID of <code>-1</code> indicates  all processes except the <code>kill</code> process itself and <code>init</code>.</li></ul></td>
        </tr>
        <tr>
          <td>getpid</td>
          <td>unistd.h</td>
          <td><code>pid_t  getpid(void);</code></br><em><code>getpid()</code> returns the process ID (PID) of the calling process. (This is often used by routines that generate unique temporary filenames.)</em></td>
        </tr>
        <tr>
          <td>malloc</td>
          <td>stdlib.h</td>
          <td></td>
        </tr> 
        <tr>
          <td>free</td>
          <td>stdlib.h</td>
          <td></td>
        </tr>
        <tr>
          <td>pause</td>
          <td>unistd.h</td>
          <td><em>Wait for signal.</em></br></br><em><code>pause()</code>  causes  the calling process (or thread) to sleep until a signal is delivered that either terminates the process or causes the invocation of a signal-catching function.</em></br></br><em><code>pause()</code> returns only when a signal was caught and the signal-catching function returned. In this case, <code>pause()</code> returns <code>-1</code>, and errno is set to EINTR.</em></td>
        </tr>
        <tr>
          <td>sleep</td>
          <td></td>
          <td></td>
        </tr>
        <tr>
          <td>usleep</td>
          <td>unistd.h</td>
          <td><em><code>usleep</code> suspends execution for microsecond intervals.</em></br></br><em>The <code>usleep()</code> function suspends execution of the calling thread for (at least) usec microseconds. The sleep may be lengthened slightly by any system activity or by the time spent processing the call or by the granularity of system timers.</em></td>
        </tr>
        <tr>
          <td>exit</td>
          <td></td>
          <td></td>
        </tr>
      </table>
    </li>
  </ul>
</br>
<h3>Bonus</h3>
<ul>
  <li>The <code>server</code> acknowledges every message received by sending back a signal to the <code>client</code>.</li>
  <li>Unicode characters support.</li>
</ul>
</br><hr></br>
</details>

<details open>
<summary><h3>References & further reading</h3></summary>
  <h4>Processes</h4>
    <ul>
      <li><a href="https://sourceware.org/glibc/manual/2.40/html_mono/libc.html#Processes">The GNU C Library Reference Manual (version 2.40.): Processes</a></li>
    </ul>
  </br>
  <h4>Signals</h4>
    <ul>
      <li><a href="https://sourceware.org/glibc/manual/2.40/html_mono/libc.html#Signal-Handling">The GNU C Library Reference Manual (version 2.40.): Signal Handling</a></li>
      <li><a href="https://www.codequoi.com/en/sending-and-intercepting-a-signal-in-c/">Code(quoi); : Sending and intercepting a signal in C</a></li>
      <li><a href="https://youtu.be/L3XuR-iRysU?si=esZTueFBHtXtvLeM">Understanding signals in Linux system [video]</a></li>
      <li><a href="https://www.youtube.com/watch?v=5We_HtLlAbs">Code Vault: Short introduction to signals in C [video]</a></li>
      <li><a href="https://www.youtube.com/watch?v=jF-1eFhyz1U">Code Vault: Handling signals [video]</a></li>
      <li><a href="https://www.youtube.com/watch?v=PErrlOx3LYE">Code Vault: Communicating between processes using signals [video]</a></li>
    </ul>
  </br>
  <h4>Bitwise operators</h4>
    <ul>
      <li><a href="https://www.geeksforgeeks.org/bitwise-operators-in-c-cpp/">Bitwise operators in C</a></li>
      <li><a href="https://www.codequoi.com/en/binary-010-uses-of-bit-shifting-and-bitwise-operations/">Binary 010: The uses of bit shifting and bitwise operations</a></li>
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
