/*
Author:Assem Samy
File:fdisk_funcs.c
comment:contains all functions declarartions used in memory_manage.c and app.c
*/
/*-----------------includes section--------------*/
#include "fdisk_funcs.h"
/*-----------section contains functions definitions -----------*/
void print_partition(const char *dev, int index, const partition_entry *partition_table_entry){
	uint32_t start_lba = partition_table_entry[index].Lba;
        uint32_t end_lba = start_lba + partition_table_entry[index].sector_count - 1;
        uint32_t sector_count = partition_table_entry[index].sector_count;
        uint32_t size_in_gb = (uint32_t)((uint64_t)(sector_count * 512) / (1024 * 1024 * 1024));
	
        printf("%s%-5d %-6c %-10u %-10u %-10u %uG %10X\n", 
               dev,
               index + 1,
               partition_table_entry->status == 0x80 ? '*' : ' ',
               start_lba,
               end_lba,
               sector_count,
               size_in_gb,
               partition_table_entry->partition_type);

}
int read_extended_partition_table(const char *dev, uint32_t lba_start) {
    char buf[512];
    int fd = open(dev, O_RDONLY);
    if (fd == -1) {
        perror("error: can't open file");
        return -1;
    }

    if (lseek(fd, lba_start * 512, SEEK_SET) == -1) {
        perror("error: lseek failed");
        close(fd);
        return -1;
    }
    ssize_t check = read(fd, buf, 512);
    if (check == -1) {
        perror("error: read failed");
        close(fd);
        return -1;
    }
    close(fd);
    
    partition_entry *partition_table_entry = (partition_entry *) &buf[446];

    printf("%-10s %-6s %-10s %-10s %-10s %-10s %-10s\n", 
           "Device", " Boot", "  Start", "    End", "   Sectors", "  Size", "  Type");

    for (int i = 0; i < 4; i++) {
        uint32_t start_lba = partition_table_entry[i].Lba;
        uint32_t sector_count = partition_table_entry[i].sector_count;
        uint32_t end_lba = start_lba + sector_count - 1;

        if (partition_table_entry[i].partition_type == 0x05 || partition_table_entry[i].partition_type == 0x0F) {
            // Handle another extended partition
            print_partition(dev, i, &partition_table_entry[i]);
            printf("Extended Partition Found\n");
            read_extended_partition_table(dev, start_lba);
        } else if (partition_table_entry[i].partition_type >= 0x81 || partition_table_entry[i].partition_type == 0x83) {
            // Handle logical partitions
            print_partition(dev, i, &partition_table_entry[i]);
        }
    }

    return 0;
}

