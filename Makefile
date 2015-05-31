#==========================================
#    Makefile: makefile for sl 5.1
#	Copyright 1993, 1998, 2014
#                 Toyoda Masashi
#		  (mtoyoda@acm.org)
#	Last Modified: 2015/06/01
#==========================================

CC=gcc
CFLAGS=-O

sl: sl.c sl.h
	$(CC) $(CFLAGS) -o pyonpyon sl.c -lncurses
