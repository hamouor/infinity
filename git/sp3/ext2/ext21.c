#include <stdio.h>  /* for fopen fclose */
#include <string.h> /* for strlen */
#include <stdlib.h> /* for atoi */
#include <math.h>   /* for log */
#include <assert.h> /* for assert */

#include "ext2.h"
#include "utilsc.h"

/* -----defines for fixed sized offsets within the file system blocks----- */
#define SUPERBLOCK_ADDRESS_OFFSET 1024

#define BLOCK_SIZE_BIT_OFFSET 24
#define BLOCKS_IN_GROUP_BIT_OFFSET 32
#define INODES_IN_GROUP_BIT_OFFSET 40
#define FIRST_INODE_BIT_OFFSET 84
#define INODE_SIZE_BIT_OFFSET 88
#define TOTAL_INODES_IN_FS_BIT_OFFSET 0
#define TOTAL_BLOCKS_IN_FS_BIT_OFFSET 4
#define BLOCK_GROUP_BIT_OFFSET 90

#define BLOCK_BITMAP_BIT_OFFSET 0
#define INODE_BITMAP_BIT_OFFSET 4
#define INODE_TABLE_BIT_OFFSET 8

#define INODE_LINK_RC 26
#define FIRST_DATA_BLOCK_IN_INODE 40
#define DATA_BLOCK_IN_INODE 4
#define ROOT_DIR_INODE_IDX 2

#define MAX_NAME_LENGTH 255

typedef __uint32_t four_bytes_t;
typedef __uint16_t two_bytes_t;
typedef __uint8_t byte_t;

char file_type[13] = {0, 'f', 'c', 0, 'd', 0, 'b', 0, '-', 0, 'l', 0, 's'};

typedef struct superblock
{
    four_bytes_t total_inodes;
    four_bytes_t total_blocks;
    four_bytes_t block_group;
    four_bytes_t block_size;
    four_bytes_t blocks_in_group;
    four_bytes_t inodes_in_group;
    four_bytes_t first_inode_idx;
    two_bytes_t inode_size;
} superblock_ty;

typedef struct group_descriptor
{
    four_bytes_t block_bitmap_idx;
    four_bytes_t inode_bitmap_idx;
    four_bytes_t inode_table_idx;
} group_descriptor_ty;

typedef struct inode
{
    four_bytes_t inode_block_group;
    four_bytes_t block_0_idx;
    four_bytes_t block_1_idx;
    four_bytes_t block_2_idx;
    four_bytes_t block_3_idx;
    four_bytes_t block_4_idx;
    four_bytes_t block_5_idx;
    four_bytes_t block_6_idx;
    four_bytes_t block_7_idx;
    four_bytes_t block_8_idx;
    four_bytes_t block_9_idx;
    four_bytes_t block_10_idx;
    four_bytes_t block_11_idx;
    two_bytes_t link_rc;
    two_bytes_t permissions;
    byte_t type;
} inode_ty;

typedef struct filesys
{
    superblock_ty super_block;
    group_descriptor_ty group_descriptor;
    FILE *file_descriptor;
} filesys_ty;

/* -----global data------ */
four_bytes_t g_block_group_size;
four_bytes_t g_gd_block_idx;
four_bytes_t g_total_block_groups;
superblock_ty g_first_superblock;


/* -----static functions------ */
static void Init(FILE *filesys_ptr_);

static four_bytes_t GetData(FILE *filesys_ptr_, four_bytes_t start_offset_, four_bytes_t data_size_);

static void FindFile(FILE *filesys_ptr_, const char *file_path_);
static void FindFileImp(FILE *filesys_ptr_, filesys_ty *file_system_, inode_ty *in, const char *file_path_);

static void GetSuperBlock(FILE *filesys_ptr_, superblock_ty *super_block_, four_bytes_t block_group_);
static void PrintSuperBlock();

static void GetGroupDescriptor(FILE *filesys_ptr_, filesys_ty *file_system_);
static void PrintGroupDescriptor();

static void TraverseBlockGroup(FILE *filesys_ptr_, filesys_ty *file_system_, four_bytes_t first_inode_idx_, const char *file_path_);
static void ReadFile(FILE *filesys_ptr_, filesys_ty *file_system_, inode_ty *in);

static void GetInode(FILE *filesys_ptr_, four_bytes_t inode_idx, filesys_ty *file_system_, inode_ty *in);
static void PrintInodePermissions(inode_ty *inode);


void PrintFileContent(const char *device_path_, const char *file_path_)
{
    FILE *file_descriptor = fopen(device_path_, "rb");
    if (!file_descriptor)
    {
        printf("Failed to open file\n");
        return;
    }

    Init(file_descriptor);

    FindFile(file_descriptor, file_path_);

    fclose(file_descriptor);
}

static void Init(FILE *filesys_ptr_)
{
    four_bytes_t block_count = 0;
    four_bytes_t inode_count = 0;

    g_block_group_size = 0;
    GetSuperBlock(filesys_ptr_, &g_first_superblock, 0);
    
    g_block_group_size = g_first_superblock.blocks_in_group * g_first_superblock.block_size;
    g_gd_block_idx = g_first_superblock.block_size > 1024 ? 1 : 2;

    block_count = ceil(g_first_superblock.total_blocks / g_first_superblock.blocks_in_group);
    inode_count = ceil(g_first_superblock.total_inodes / g_first_superblock.inodes_in_group);
    g_total_block_groups = block_count > inode_count ? block_count : inode_count;
}

void FindFile(FILE *filesys_ptr_, const char *file_path_)
{
    filesys_ty file_system;
    file_system.super_block = g_first_superblock;
    
    PrintSuperBlock(&file_system.super_block);
    
    GetGroupDescriptor(filesys_ptr_, &file_system);
    PrintGroupDescriptor(&file_system.group_descriptor);
    
    TraverseBlockGroup(filesys_ptr_, &file_system, ROOT_DIR_INODE_IDX, file_path_);
}

static void GetSuperBlock(FILE *filesys_ptr_, superblock_ty *super_block_, four_bytes_t block_group_)
{
    four_bytes_t super_block_address = 0;
    
    assert(filesys_ptr_);

    super_block_address = block_group_ * g_block_group_size + SUPERBLOCK_ADDRESS_OFFSET;

    super_block_->block_size = 1024 << GetData(filesys_ptr_, super_block_address + BLOCK_SIZE_BIT_OFFSET, 4);
    super_block_->inode_size = GetData(filesys_ptr_, super_block_address + INODE_SIZE_BIT_OFFSET, 2);
    
    super_block_->blocks_in_group = GetData(filesys_ptr_, super_block_address + BLOCKS_IN_GROUP_BIT_OFFSET, 4);
    super_block_->inodes_in_group = GetData(filesys_ptr_, super_block_address + INODES_IN_GROUP_BIT_OFFSET, 4);
    
    super_block_->first_inode_idx = GetData(filesys_ptr_, super_block_address + FIRST_INODE_BIT_OFFSET, 4);
    
    super_block_->total_inodes = GetData(filesys_ptr_, super_block_address + TOTAL_INODES_IN_FS_BIT_OFFSET, 4);
    super_block_->total_blocks = GetData(filesys_ptr_, super_block_address + TOTAL_BLOCKS_IN_FS_BIT_OFFSET, 4);
    
    super_block_->block_group = GetData(filesys_ptr_, super_block_address + BLOCK_GROUP_BIT_OFFSET, 2);
}

static void PrintSuperBlock(superblock_ty *super_block_)
{
    printf("\n\n------superblock------\n");
    printf("block size = %u\n", super_block_->block_size);
    printf("inode size = %u\n", super_block_->inode_size);
    printf("block in block group = %u\n", super_block_->blocks_in_group);
    printf("inodes in block group = %u\n", super_block_->inodes_in_group);
    printf("first valid inode index = %u\n", super_block_->first_inode_idx);
}

static four_bytes_t GetData(FILE *filesys_ptr_, four_bytes_t start_offset_, four_bytes_t data_size_)
{
    four_bytes_t ret_val = 0;

    fseek(filesys_ptr_, start_offset_, SEEK_SET);
    fread(&ret_val, data_size_, 1, filesys_ptr_);
    
    return (ret_val);
}

static void GetGroupDescriptor(FILE *filesys_ptr_, filesys_ty *file_system_)
{
    four_bytes_t gd_address = 0;

    assert(filesys_ptr_);

    gd_address = file_system_->super_block.block_group * g_block_group_size + file_system_->super_block.block_size * g_gd_block_idx;

    file_system_->group_descriptor.block_bitmap_idx = GetData(filesys_ptr_, gd_address + BLOCK_BITMAP_BIT_OFFSET, 4);
    file_system_->group_descriptor.inode_bitmap_idx = GetData(filesys_ptr_, gd_address + INODE_BITMAP_BIT_OFFSET, 4);
    file_system_->group_descriptor.inode_table_idx = GetData(filesys_ptr_, gd_address + INODE_TABLE_BIT_OFFSET, 4);
}

static void PrintGroupDescriptor(group_descriptor_ty *group_descriptor_)
{
    printf("\n\n------group descriptor------\n");
    printf("block bitmap = %u\n", group_descriptor_->block_bitmap_idx);
    printf("inode bitmap = %u\n", group_descriptor_->inode_bitmap_idx);
    printf("inode table = %u\n", group_descriptor_->inode_table_idx);
}

static void TraverseBlockGroup(FILE *filesys_ptr_, filesys_ty *file_system_, four_bytes_t first_inode_idx_, const char *file_path_)
{
    inode_ty curr_in;
    GetInode(filesys_ptr_, first_inode_idx_, file_system_, &curr_in);

    FindFileImp(filesys_ptr_, file_system_, &curr_in, file_path_);
}

void FindFileImp(FILE *filesys_ptr_, filesys_ty *file_system_, inode_ty *in, const char *file_path_)
{
    inode_ty child;
    four_bytes_t inode_num = 0;
    four_bytes_t entry_length = 0;
    four_bytes_t name_length = 0;
    char *name = NULL;
    char *path = NULL;
    char *tok = NULL;
    four_bytes_t data_block_offset = 0;

    data_block_offset = file_system_->super_block.block_size * in->block_0_idx;

    entry_length = strlen(file_path_);
    path = (char *)malloc((entry_length + 1) * sizeof(char));
    EXIT_IF_BAD((!path), "alloc failed\n");

    strcpy(path, file_path_);
    tok = strtok(path, "/");
    
    while (tok)
    {
        fseek(filesys_ptr_, data_block_offset, SEEK_SET);

        /* get file inode num */
        fread(&inode_num, 4, 1, filesys_ptr_);

        /* get entry length */
        fread(&entry_length, 2, 1, filesys_ptr_);

        /* get name length */
        fread(&name_length, 1, 1, filesys_ptr_);
        if (!name_length)
        {
            printf("File not found\n");
            break;
        }

        fgetc(filesys_ptr_);

        /* get name */
        name = (char *)malloc(sizeof(char) * (name_length + 1));
        if (!name)
        {
            break;
        }
        fread(name, name_length, 1, filesys_ptr_);
        name[name_length] = '\0';

        if (!strcmp(tok, name))
        {
            GetInode(filesys_ptr_, inode_num, file_system_, &child);
            if (child.type == 8)
            {
                PrintInodePermissions(&child);
                printf("%s\n", name);
                ReadFile(filesys_ptr_, file_system_, &child);
                free(name);
                break;
            }
            else
            {
                tok = strtok(NULL, "/");
                data_block_offset = file_system_->super_block.block_size * child.block_0_idx;
            }
        }
        else
        {
            data_block_offset += entry_length;
        }
        free(name);
        name = NULL;
    }
    free(path);
}


static void ReadFile(FILE *filesys_ptr_, filesys_ty *file_system_, inode_ty *in)
{
    four_bytes_t *offset_ptr = NULL;
    char *buff = NULL;
    four_bytes_t i = 0;
    size_t read_length = 80;
    offset_ptr = &in->block_0_idx;

    buff = (char *)malloc(sizeof(char) * (read_length + 1));
    EXIT_IF_BAD((!buff), "alloc failed\n");
    
    for (i = 0; (i < 12) && *offset_ptr; ++i)
    {
        fseek(filesys_ptr_, (*((four_bytes_t *)offset_ptr + i)) * file_system_->super_block.block_size, SEEK_SET);
        while (read_length >= 80)
        {
            read_length = fread(buff, 1, read_length, filesys_ptr_);
            
            buff[read_length] = '\0';
            fputs(buff, stdout);
        }
    }
    free(buff);
}

static void GetInode(FILE *filesys_ptr_, four_bytes_t inode_idx, filesys_ty *file_system_, inode_ty *in)
{
    four_bytes_t first_data_ptr = 0;
    four_bytes_t inode_offset = (inode_idx - 1) * file_system_->super_block.inode_size + file_system_->group_descriptor.inode_table_idx * file_system_->super_block.block_size;

    in->inode_block_group = file_system_->super_block.block_group;
    in->permissions = GetData(filesys_ptr_, inode_offset, 2);
    in->type = in->permissions >> 12;

    in->permissions = (in->permissions << 4) >> 4;
    in->link_rc = GetData(filesys_ptr_, inode_offset + INODE_LINK_RC, 2);

    first_data_ptr = inode_offset + FIRST_DATA_BLOCK_IN_INODE;

    in->block_0_idx = GetData(filesys_ptr_, first_data_ptr + DATA_BLOCK_IN_INODE * 0, DATA_BLOCK_IN_INODE);
    in->block_1_idx = GetData(filesys_ptr_, first_data_ptr + DATA_BLOCK_IN_INODE * 1, DATA_BLOCK_IN_INODE);
    in->block_2_idx = GetData(filesys_ptr_, first_data_ptr + DATA_BLOCK_IN_INODE * 2, DATA_BLOCK_IN_INODE);
    in->block_3_idx = GetData(filesys_ptr_, first_data_ptr + DATA_BLOCK_IN_INODE * 3, DATA_BLOCK_IN_INODE);
    in->block_4_idx = GetData(filesys_ptr_, first_data_ptr + DATA_BLOCK_IN_INODE * 4, DATA_BLOCK_IN_INODE);
    in->block_5_idx = GetData(filesys_ptr_, first_data_ptr + DATA_BLOCK_IN_INODE * 5, DATA_BLOCK_IN_INODE);
    in->block_6_idx = GetData(filesys_ptr_, first_data_ptr + DATA_BLOCK_IN_INODE * 6, DATA_BLOCK_IN_INODE);
    in->block_7_idx = GetData(filesys_ptr_, first_data_ptr + DATA_BLOCK_IN_INODE * 7, DATA_BLOCK_IN_INODE);
    in->block_8_idx = GetData(filesys_ptr_, first_data_ptr + DATA_BLOCK_IN_INODE * 8, DATA_BLOCK_IN_INODE);
    in->block_9_idx = GetData(filesys_ptr_, first_data_ptr + DATA_BLOCK_IN_INODE * 9, DATA_BLOCK_IN_INODE);
    in->block_10_idx = GetData(filesys_ptr_, first_data_ptr + DATA_BLOCK_IN_INODE * 10, DATA_BLOCK_IN_INODE);
    in->block_11_idx = GetData(filesys_ptr_, first_data_ptr + DATA_BLOCK_IN_INODE * 11, DATA_BLOCK_IN_INODE);
}

static void PrintInodePermissions(inode_ty *in)
{
    printf("%c", file_type[in->type]);
    printf("%c", ((in->permissions >> 8) & 1) ? 'r' : '-');
    printf("%c", ((in->permissions >> 7) & 1) ? 'w' : '-');
    printf("%c", ((in->permissions >> 6) & 1) ? 'x' : '-');
    printf("%c", ((in->permissions >> 5) & 1) ? 'r' : '-');
    printf("%c", ((in->permissions >> 4) & 1) ? 'w' : '-');
    printf("%c", ((in->permissions >> 3) & 1) ? 'x' : '-');
    printf("%c", ((in->permissions >> 2) & 1) ? 'r' : '-');
    printf("%c", ((in->permissions >> 1) & 1) ? 'w' : '-');
    printf("%c  ", ((in->permissions >> 0) & 1) ? 'x' : '-');
}

/* static void ReadDir(FILE *filesys_ptr_, filesys_ty *file_system_, inode_ty *in)
{
    inode_ty child;
    four_bytes_t *struct_offset_ptr = NULL;
    four_bytes_t i = 0;
    four_bytes_t j = 0;
    four_bytes_t inode_num = 0;
    four_bytes_t entry_length = 0;
    four_bytes_t name_length = 0;
    char name[MAX_NAME_LENGTH];
    four_bytes_t inode_table_offset = 0;
    four_bytes_t data_block_offset = 0;

    struct_offset_ptr = &in->block_0_idx;

    for (i = 0; (i < 12) && *struct_offset_ptr; ++i)
    {
        data_block_offset = *(four_bytes_t *)((char *)struct_offset_ptr + (sizeof(four_bytes_t) * i)) * file_system_->super_block.block_size;

        do
        {
            name_length = 0;
            fseek(filesys_ptr_, data_block_offset, SEEK_SET);

            
            fread(&inode_num, 4, 1, filesys_ptr_);

            
            fread(&entry_length, 2, 1, filesys_ptr_);

            
            fread(&name_length, 1, 1, filesys_ptr_);
            if (!name_length)
            {
                break;
            }

            fgetc(filesys_ptr_);

            
            fread(name, 1, name_length + 1, filesys_ptr_);
            name[name_length] = '\0';

            GetInode(filesys_ptr_, inode_num, file_system_, &child);
            PrintInodePermissions(&child);
            printf("%s\n", name);

            if (!strcmp(name, ".") || !strcmp(name, "..") || strstr(name, "lost+found"))
            {
                GetInode(filesys_ptr_, inode_num, file_system_, &child);
            }
            else
            {
                if (child.permissions == 4)
                {
                    ReadDir(filesys_ptr_, file_system_, &child);
                }
                else
                {
                    ReadFile(filesys_ptr_, file_system_, &child);
                }
            }
            data_block_offset += entry_length;
            printf("\n\n\n\n");
        } while (1);
    }
} */