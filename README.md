# myShell
Developed a working POSIX compatible shell with a subset of
feature support of default shell. Apart from basic working,
required features implemented are listed below.

Syntax
1. IO redirection with ‘>>’ and ‘>’ will be done for one source and
one destination only.
2. For ‘|’, a minimum 3 programs must be in pipe. E.g. 
cat file1.txt | sort | uniq > save.txt
3. Prompt must change for distinguishing users($)@hostname and
root(#)@hostname and also while searching in extended features.Implementation Requirements

Shell Internals
1. Program is a input driven independent executable, no
menu options are provided. It can take n number of strings
in the format of a command following with its parameters itself.
2. For interactive processes it is a waiting process.

3.It maintain a configuration file which your program reads
on startup and sets the environment accordingly. Like our own
“.bashrc”.
5. Support for these initialization variable are provided -
PATH, HOME, USER, HOSTNAME, PS1​
6. Association of ~ with HOME variable.
7. Look of prompt via PS1​ is to be handled.
8. Alias support for commands. E.g.alias ll='ls -l'.
9. Handle support for - $
​ $, $?​ Similar to shell.

Extended Features :-
1. Recording as script command, where a user can initiate recording
of all input and output to a file, this happens in the
background. It will be invoked as record start  and record stop.
2. History as buffer - 
searchable via TRIE
. This is a list of all
commands executed ever. This can have a cap limit which can be
configured via “.myrc” file in ​
HISTSIZE variable​ . It will be
invoked as history.
3. TRIE data structure for tab completion support is needed. List of
directories to be traversed on startup which are mentioned in
PATH variable for populating all command names into the
structure.
4. Set default applications via .myrc file. This requires extension
matching/mapping to your preferred application. Handle its I/O
and parameter passing on executing.
a. E.g. MEDIA=[‘vlc’, ‘vlc path’,’.mp4’] in config file.
So on running - open same.mp4 , it must invoke vlc.
# !! Mac users be careful for collision of open
keyword in your shell.
