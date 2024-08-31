/*
Author:Assem Samy
File:fdisk_funcs.h
comment:contains all functions declarartions used in memory_manage.c and app.c
*/

#ifndef MEMORY_MANAGE_H
#define MEMORY_MANAGE_H
/*-----------------includes section--------------*/
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <libgen.h> // Include for basename()
#include <dirent.h>
#include <sys/wait.h>
#include <sys/sysinfo.h>
#include <time.h>
#include <aio.h>
#include <error.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
/*----------------macros declarations-----------------*/


/*-------------------data types------------------*/
typedef struct {
    uint8_t status;
    uint8_t first_chs[3];
    uint8_t partition_type;
    uint8_t last_chs[3];
    uint32_t Lba;
    uint32_t sector_count;
} partition_entry;

/*-----------section contains functions declarations -----------*/

void print_partition(const char *dev, int index, const partition_entry *entry);
int read_extended_partition_table(const char *dev, uint32_t lba_start);
#endif
