# README

## Overview

This project is a simple tool for displaying partition information from a disk image. It reads the Master Boot Record (MBR) of a specified device, parses the partition table, and displays information about each partition. It also handles extended partitions by recursively reading their tables.

## File Structure

- **`main.c`**: Contains the main program logic for reading the partition table from a specified device and displaying partition information.
- **`fdisk_funcs.c`**: Implements functions for printing partition details and reading extended partition tables.
- **`fdisk_funcs.h`**: Header file containing function declarations and data type definitions.

## Compilation

To compile the project, use the following command:

```bash
gcc myfdisk.c fdisk_funcs.c fdisk_funcs.h -o fdisk.out
sudo ./fdisk.out <your device> 
```

## Usage

Run the compiled executable with the path to the device or disk image as an argument:

```bash
./partition_tool <device>
```

Replace `<device>` with the path to the device or disk image file (e.g., `/dev/sda` or `disk.img`).

## Functions

### `void print_partition(const char *dev, int index, const partition_entry *entry)`

Prints details of a single partition. The details include:
- Device path
- Partition index
- Boot status (indicates if the partition is bootable)
- Start LBA (Logical Block Addressing)
- End LBA
- Sector count
- Size in GB
- Partition type

### `int read_extended_partition_table(const char *dev, uint32_t lba_start)`

Reads and prints the extended partition table from the specified LBA start address. This function recursively handles additional extended partitions found within the extended partition table.

## Data Types

### `partition_entry`

Defines the structure of a partition entry in the partition table. It contains:
- `status`: Boot status of the partition
- `first_chs`: Cylinder-Head-Sector (CHS) address of the start
- `partition_type`: Type of the partition
- `last_chs`: CHS address of the end
- `Lba`: Start LBA of the partition
- `sector_count`: Number of sectors in the partition

## Error Handling

- **File Open Errors**: Errors encountered when opening the device or disk image file are reported using `perror`.
- **Read Errors**: Errors during reading the file are reported using `perror`.
- **Seek Errors**: Errors encountered while seeking to a specific LBA are reported using `perror`.

## Author

Assem Samy

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

## Example

Here’s an example of how the tool might display partition information:

```text
Device    Boot   Start        End         Sectors     Size       Type      
/dev/sda  *      2048        1023999     1021952     500M       83
/dev/sda          1024000     2047999     1024000     500M       83
/dev/sda          2048000     4095999     2048000     1G         05
Extended Partition Found
Device    Boot   Start        End         Sectors     Size       Type      
/dev/sda          4096000     8191999     4096000     2G         83
```

In this example, the tool lists partitions, indicating bootable partitions, and recursively handles extended partitions.
