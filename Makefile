#==========================================
#    Makefile: makefile for sl 5.0
#	Copyright 1993, 1998, 2013
#                 Toyoda Masashi 
#		  (mtoyoda@acm.org)
#	Last Modified: 2013/ 5/ 5
#==========================================

#(2014/03/26 modified Taichi-Sugiyama)

CC=gcc
CFLAGS=-O

erutaso: sl.c sl.h
	$(CC) $(CFLAGS) -o erutaso sl.c -lncurses

