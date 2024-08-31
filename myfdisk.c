
#include "fdisk_funcs.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <device>\n", argv[0]);
        return -1;
    }

    char buf[512];
    int fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        perror("error: can't open file");
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
    	if (partition_table_entry[i].partition_type == 0x05 || partition_table_entry[i].partition_type == 0x0F) {
            // Handle extended partition
            print_partition(argv[1], i, &partition_table_entry[i]);
            printf("Extended Partition Found\n");
            read_extended_partition_table(argv[1], partition_table_entry[i].Lba);
        } else if (partition_table_entry[i].partition_type >= 0x81) {
            // Handle primary and logical partitions
            
            print_partition(argv[1], i, &partition_table_entry[i]);
        }else{
        }
    
    }

    return 0;
}

