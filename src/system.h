#ifndef SYSTEM_H
#define SYSTEM_H

#include <sys/termios.h>
#include <stdio.h>

struct termios original_tio;

void disable_input_buffering();
void restore_input_buffering();
void handle_interrupt(int signal);
void disable_input_buffering();
void restore_input_buffering();
void handle_interrupt(int signal);
void read_image_file(FILE *file);
int read_image(const char *image_path);

#endif