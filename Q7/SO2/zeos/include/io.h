/*
 * io.h - Definició de l'entrada/sortida per pantalla en mode sistema
 */

#ifndef __IO_H__
#define __IO_H__

#include <types.h>

/** Screen functions **/
/**********************/

Byte inb (unsigned short port);
void printc(char c);
void printc_xy(Byte x, Byte y, char c);
void printk(char *string);
void change_cursor(Byte x2, Byte y2);
void remove_character();
void change_foreground_color(Byte fc2);
void change_background_color(Byte bc2);

#endif  /* __IO_H__ */
