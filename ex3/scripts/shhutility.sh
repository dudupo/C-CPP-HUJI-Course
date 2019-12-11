#!/bin/sh
tar -cvf ex3.tar infi.h infi.c NumericalAnalyzer.c
scp -P 1115 ex3.tar davidponar@localhost:ex3.tar
