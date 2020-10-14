#ifndef AARCH64_CPU_H
#define AARCH64_CPU_H

int get_thread_id();

int get_el();
   
void switch_to_usermode();

#endif AARCH64_CPU_H