#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include </usr/include/ext2fs/ext2_fs.h>

#define BASE_OFFSET 1024                   /* locates beginning of the super block (first group) */
#define FD_DEVICE "/dev/ram0"               /* the floppy disk device */
#define BLOCK_OFFSET(block) ((block)*block_size)
#define DIR_SEPRT           (-47)

static unsigned int block_size = 0;        /* block size (to be calculated) */

static void read_dir(int fd, const struct ext2_inode *inode, const struct ext2_group_desc *group, char* file);
static void read_inode(int, int, const struct ext2_group_desc*, struct ext2_inode*);
/*static int PrintFile(int fd, const inode_t *inode);*/

int main(int argc, char *argv[])
{
	struct ext2_super_block super;
	struct ext2_group_desc group;
	struct ext2_inode inode;
    char *file_name = NULL;
	int fd;

	/* open ram device */

	if ((fd = open(FD_DEVICE, O_RDONLY)) < 0) {
		perror(FD_DEVICE);
		exit(1);  /* error while opening the floppy device */
	}

    file_name = argv[1];

	/* read super-block */

	lseek(fd, BASE_OFFSET, SEEK_SET); 
	read(fd, &super, sizeof(super));

	if (super.s_magic != EXT2_SUPER_MAGIC) {
		fprintf(stderr, "Not a Ext2 filesystem\n");
		exit(1);
	}
		
	block_size = 1024 << super.s_log_block_size;

	/* read group descriptor */

	lseek(fd, block_size, SEEK_SET);
	read(fd, &group, sizeof(group));

	/* show entries in the root directory */

	read_inode(fd, super.s_first_ino, &group, &inode);   /* read inode 2 (root directory) */
	read_dir(fd, &inode, &group, strchr(file_name, '/') + 1);

	close(fd);
	exit(0);
} /* main() */

static void read_inode(int fd, int inode_no, const struct ext2_group_desc *group, struct ext2_inode *inode)
{
    lseek(fd, BLOCK_OFFSET(group->bg_inode_table)+(inode_no - 1) * 128, SEEK_SET);
	read(fd, inode, sizeof(struct ext2_inode));
} /* read_inode() */


static void read_dir(int fd, const struct ext2_inode *inode, const struct ext2_group_desc *group, char* file)
{
	void *block;
	struct ext2_dir_entry_2 *entry, *entry2;
	unsigned int size = 0, size2 = 0;

    int comp_ret = 0;

	if (S_ISDIR(inode->i_mode)) {

		if ((block = malloc(block_size)) == NULL) { /* allocate memory for the data block */
			fprintf(stderr, "Memory error\n");
			close(fd);
			exit(1);
		}

		lseek(fd, BLOCK_OFFSET(inode->i_block[0] - 1), SEEK_SET);
		read(fd, block, block_size);                /* read block from disk*/

		entry = (struct ext2_dir_entry_2 *) block;  /* first entry in the directory */
        entry2 = entry;
                /* Notice that the list may be terminated with a NULL
                   entry (entry->inode == NULL)*/
		while((size < inode->i_size) && entry->inode) {
			char file_name[EXT2_NAME_LEN+1];
			memcpy(file_name, entry->name, entry->name_len);
			file_name[entry->name_len] = 0;     /* append null character to the file name */
			printf("%10u %s\n", entry->inode, file_name);
            entry = (void*) entry + entry->rec_len;
			size += entry->rec_len;
		}
		
        while((size2 < inode->i_size) && entry2->inode)
        {
			comp_ret = strcmp(entry2->name, file);
            if(!comp_ret)  /* this is the file name */
            {
                read_inode(fd, entry->inode, group, inode);
                
                if (PrintFile(fd, inode))
                {
                    free(block);
                    return 1;
                }

                break;
            }
            else if(DIR_SEPRT == comp_ret) /* this is a path directory name */
            {
                ReadInode(fd, entry2->inode, group, inode);
                printf("inode no: %u\n", entry2->inode);
                if (FindPrintFile(fd, inode, group, strchr(file, '/') + 1))
                {
                    free(block);
                    return 1;
                }

                break;
            }

			entry2 = (entry_t*)((char*)entry2 + entry2->rec_len);
			size += entry2->rec_len;
		}
		free(block);
	}
} /* read_dir() */

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