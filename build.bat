@echo off
gcc -g -c framework/matrix.c -o framework/matrix.o -lm
gcc -g -c main.c -o main.o -lm
gcc -g framework/matrix.o main.o -o main -lm
.\main
del main.o & del framework\matrix.o