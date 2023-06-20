/*
 * ext2.c
 *
 * Reads the super-block from a Ext2 ram disk.
 *
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ext2fs/ext2_fs.h>

#define BASE_OFFSET         1024       /* locates beginning of the super block (first group) */
#define BLOCK_OFFSET(block) ((block)*g_block_size)
#define DIR_SEPRT           (-47)

typedef struct ext2_super_block super_block_t;
typedef struct ext2_group_desc group_t;
typedef struct ext2_inode inode_t;
typedef struct ext2_dir_entry_2 entry_t;

static unsigned int g_block_size = 0;    /* block size (to be calculated) */
static super_block_t g_super;

    /* fd - the ram disk file descriptor */
    /* inode_no - the inode number to read  */
    /* group - the block group to which the inode belongs */
    /* inode - where to put the inode from disk  */
static void ReadGroup(int fd, group_t *group);
static void ReadInode(int fd, int inode_no, const group_t *group, inode_t *inode);

static int FindPrintFile(int fd, inode_t *inode, const group_t *group, char *file);

static int PrintFile(int fd, const inode_t *inode);
static void PrintSuper(const inode_t *inode);
static void PrintGroup(const group_t *group);


int main(int argc, char *argv[])
{
    group_t group;
    inode_t inode;
	int fd = 0;
    int i = 0;
    char *dev = NULL; /* the ram disk device */
    char *file_name = NULL;

    if (1 < argc)
    {
        dev = argv[1];
    }
    else
    {
        printf("device was not entered\n");
        return 1;
    }

    if (2 < argc)
    {
        file_name = argv[2];
    }
    else
    {
        printf("file was not entered\n");
        return 1;
    }
    
	/* open ram device */

	if ((fd = open(dev, O_RDONLY)) < 0) {
		perror(dev);
		return 1;  /* error while opening the ram device */
	}

	/* read super-block */
	lseek(fd, BASE_OFFSET, SEEK_SET); 
	read(fd, &g_super, sizeof(g_super));

	if (g_super.s_magic != EXT2_SUPER_MAGIC) {
		fprintf(stderr, "Not a Ext2 filesystem\n");
        close(fd);
		return 1;
	}
		
	g_block_size = 1024 << g_super.s_log_block_size;

	ReadGroup(fd, &group);

    ReadInode(fd, g_super.s_first_ino, &group, &inode);

    if (FindPrintFile(fd, &inode, &group, strchr(file_name, '/') + 1))
    {
        close(fd);
        return 1;
    }

	close(fd);
	
    return 0;
} /* main() */

static void ReadGroup(int fd, group_t *group)
{
	lseek(fd, g_block_size, SEEK_SET);
	read(fd, group, sizeof(*group));
} /* ReadGroup() */

static void ReadInode(int fd, int inode_no, const group_t *group, inode_t *inode)
{
	lseek(fd, BLOCK_OFFSET(group->bg_inode_table) + (inode_no - 1) * g_super.s_inode_size, SEEK_SET);
	read(fd, inode, sizeof(inode_t));
} /* ReadInode() */

static int FindPrintFile(int fd, inode_t *inode, const group_t *group, char *file)
{
	void *block = NULL;
    int comp_ret = 0;
    entry_t *entry;
    unsigned int size = 0;
printf("%s\n", file);
	if (S_ISDIR(inode->i_mode))
    {
		if (!(block = malloc(g_block_size))) /* allocate memory for the data block */
		{
            fprintf(stderr, "Memory error\n");
			return 1;
		}

		lseek(fd, BLOCK_OFFSET(inode->i_block[0] - 1), SEEK_SET);
		read(fd, block, g_block_size);                /* read block from disk*/

		entry = (entry_t*)block;  /* first entry in the directory */

            entry_t *entry2 = (entry_t*)block;
            unsigned int size2 = 0;
        while((size2 < inode->i_size) && entry2->inode) {
			char file_name[EXT2_NAME_LEN+1];

			memcpy(file_name, entry2->name, entry2->name_len);
			file_name[entry2->name_len] = 0;     /* append null character to the file name */
			printf("%10u %s\n", entry2->inode, file_name);
			entry2 = (entry_t*)((char*) entry2 + entry2->rec_len);
			size2 += entry2->rec_len;
		}
        
		while((size < inode->i_size) && entry->inode)
        {
			comp_ret = strcmp(entry->name, file);
            if(!comp_ret)  /* this is the file name */
            {
                ReadInode(fd, entry->inode, group, inode);
                
                if (PrintFile(fd, inode))
                {
                    free(block);
                    return 1;
                }

                break;
            }
            else if(DIR_SEPRT == comp_ret) /* this is a path directory name */
            {
                ReadInode(fd, entry->inode, group, inode);
                printf("inode no: %u\n", entry->inode);
                if (FindPrintFile(fd, inode, group, strchr(file, '/') + 1))
                {
                    free(block);
                    return 1;
                }

                break;
            }

			entry = (entry_t*)((char*)entry + entry->rec_len);
			size += entry->rec_len;
		}

        if ((size == inode->i_size) || !entry->inode)
        {
            printf("Invalid file name or path\n");
            free(block);
            return 1;
        }

		free(block);
	}
    else
    {
        printf("not a directory: %s\n", file);
        return 1;
    }
    
    return 0;
} /* FindPrintFile() */

static int PrintFile(int fd, const inode_t *inode)
{
    group_t group;
    char *buff = (char*)malloc(inode->i_size);
    if(!buff)
    {
        return 1;
    }

    PrintSuper(inode);

    ReadGroup(fd, &group);

    PrintGroup(&group);

    lseek(fd, BLOCK_OFFSET(inode->i_block[0]), SEEK_SET);
    read(fd, buff, inode->i_size);

    printf("File offset in RAM is: %d\n", BLOCK_OFFSET(inode->i_block[0]));
    printf("File content:\n%s\n", buff);

    free(buff);

    return 0;
}

static void PrintSuper(const inode_t *inode)
{
    printf("Super-block info of block no. %u:\n"
	       "Inodes count            : %u\n"
	       "Blocks count            : %u\n"
	       "Reserved blocks count   : %u\n"
	       "Free blocks count       : %u\n"
	       "Free inodes count       : %u\n"
	       "First data block        : %u\n"
	       "Block size              : %u\n"
	       "Blocks per group        : %u\n"
	       "Inodes per group        : %u\n"
	       "Creator OS              : %u\n"
	       "First non-reserved inode: %u\n"
	       "Size of inode structure : %hu\n\n"
	       ,
           inode->i_block[0],
	       g_super.s_inodes_count,  
	       g_super.s_blocks_count,
	       g_super.s_r_blocks_count,     /* reserved blocks count */
	       g_super.s_free_blocks_count,
	       g_super.s_free_inodes_count,
	       g_super.s_first_data_block,
	       g_block_size,
	       g_super.s_blocks_per_group,
	       g_super.s_inodes_per_group,
	       g_super.s_creator_os,
	       g_super.s_first_ino,          /* first non-reserved inode */
	       g_super.s_inode_size);
}

static void PrintGroup(const group_t *group)
{
    printf("Group-descriptor info:\n"
	       "Blocks bitmap block: %u\n"
	       "Inodes bitmap block: %u\n"
	       "Inodes table block : %u\n"
	       "Free blocks count  : %u\n"
	       "Free inodes count  : %u\n"
	       "Directories count  : %u\n\n"
	       ,
	       group->bg_block_bitmap,
	       group->bg_inode_bitmap,
	       group->bg_inode_table,
	       group->bg_free_blocks_count,
	       group->bg_free_inodes_count,
	       group->bg_used_dirs_count);    /* directories count */
}
