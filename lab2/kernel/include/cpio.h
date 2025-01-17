#ifndef _CPIO_H_
#define _CPIO_H_

/*
    cpio format : https://manpages.ubuntu.com/manpages/bionic/en/man5/cpio.5.html
    We are using "newc" format
    header, file path, file data, header  ......
    header + file path (padding 4 bytes)
    file data (padding 4 bytes)  (max size 4gb)
*/

#define CPIO_NEWC_HEADER_MAGIC "070701"    // big endian constant, to check whether it is big endian or little endian

// Using newc archive format
struct cpio_newc_header
{
    char c_magic[6];            // 包含常數八進位 070707 (或 0x71c7)。 fixed, "070701".
    char c_ino[8];
    char c_mode[8];
    char c_uid[8];
    char c_gid[8];
    char c_nlink[8];
    char c_mtime[8];
    char c_filesize[8];         // 檔案長度 (以byte為單位)。 這是遵循標頭結構的資料區段長度。
    char c_devmajor[8];
    char c_devminor[8];
    char c_rdevmajor[8];
    char c_rdevminor[8];
    char c_namesize[8];         // 路徑名稱的長度，包括結尾的空字元。
    char c_check[8];
};

/* write pathname, data, next header into corresponding parameter*/
int cpio_newc_parse_header(struct cpio_newc_header *this_header_pointer,
        char **pathname, unsigned int *filesize, char **data,
        struct cpio_newc_header **next_header_pointer);

#endif /* _CPIO_H_ */
