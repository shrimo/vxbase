VXbase
========================
Database ver 0.01

Compile (linux)
```
gcc -o server server.c -lpthread
```

```
$ ./server

Starting server.
waiting...

```
```
$ python client.py

TCP client ( TYPE q or Q to Quit)
Enter user name: 
>root
login root

>user
root
```
```
>read
variable_01
vchar
text 01
0
variable_04
vchar
text 04
3
```
