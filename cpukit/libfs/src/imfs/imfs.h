/*
 *  Header file for the In-Memory File System
 *
 *  COPYRIGHT (c) 1989-2010.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: imfs.h,v 1.41 2010/05/31 13:56:36 ccj Exp $
 */

#ifndef _RTEMS_IMFS_H
#define _RTEMS_IMFS_H

#include <rtems.h>
#include <rtems/chain.h>

#include <sys/types.h>
#include <limits.h>
#include <rtems/libio.h>

#include <rtems/pipe.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 *  File name macros
 */

#define IMFS_is_valid_name_char( _ch ) ( 1 )

#define IMFS_is_separator( _ch ) \
   rtems_filesystem_is_separator( _ch )

/*
 *  Data types
 */

struct IMFS_jnode_tt;
typedef struct IMFS_jnode_tt IMFS_jnode_t;

typedef struct {
  rtems_chain_control                    Entries;
  rtems_filesystem_mount_table_entry_t  *mt_fs;
}  IMFS_directory_t;

typedef struct {
  rtems_device_major_number  major;
  rtems_device_minor_number  minor;
}  IMFS_device_t;

typedef struct {
  IMFS_jnode_t  *link_node;
} IMFS_link_t;

typedef struct {
  char *name;
} IMFS_sym_link_t;

typedef struct {
  pipe_control_t  *pipe;
} IMFS_fifo_t;

/*
 *  IMFS "memfile" information
 *
 *  The data structure for the in-memory "memfiles" is based on classic UNIX.
 *
 *  block_ptr is a pointer to a block of IMFS_MEMFILE_BYTES_PER_BLOCK in
 *  length which could be data or a table of pointers to blocks.
 *
 *  Setting IMFS_MEMFILE_BYTES_PER_BLOCK to different values has a significant
 *  impact on the maximum file size supported as well as the amount of
 *  memory wasted due to internal file fragmentation.  The following
 *  is a list of maximum file sizes based on various settings
 *
 *    max_filesize with blocks of   16 is         1,328
 *    max_filesize with blocks of   32 is        18,656
 *    max_filesize with blocks of   64 is       279,488
 *    max_filesize with blocks of  128 is     4,329,344
 *    max_filesize with blocks of  256 is    68,173,568
 *    max_filesize with blocks of  512 is 1,082,195,456
 */

#define IMFS_MEMFILE_DEFAULT_BYTES_PER_BLOCK     128
  extern int imfs_rq_memfile_bytes_per_block;
  extern int imfs_memfile_bytes_per_block;

#define IMFS_MEMFILE_BYTES_PER_BLOCK imfs_memfile_bytes_per_block
#define IMFS_MEMFILE_BLOCK_SLOTS \
  (IMFS_MEMFILE_BYTES_PER_BLOCK / sizeof(void *))

typedef uint8_t *block_p;
typedef block_p *block_ptr;

typedef struct {
  rtems_off64_t size;             /* size of file in bytes */
  block_ptr     indirect;         /* array of 128 data blocks pointers */
  block_ptr     doubly_indirect;  /* 128 indirect blocks */
  block_ptr     triply_indirect;  /* 128 doubly indirect blocks */
} IMFS_memfile_t;

typedef struct {
  rtems_off64_t size;             /* size of file in bytes */
  block_p       direct;           /* pointer to file image */
} IMFS_linearfile_t;

/*
 *  Important block numbers for "memfiles"
 */

#define FIRST_INDIRECT           (0)
#define LAST_INDIRECT            (IMFS_MEMFILE_BLOCK_SLOTS - 1)

#define FIRST_DOUBLY_INDIRECT    (LAST_INDIRECT + 1)
#define LAST_DOUBLY_INDIRECT     \
   (LAST_INDIRECT + \
     (IMFS_MEMFILE_BLOCK_SLOTS * IMFS_MEMFILE_BLOCK_SLOTS))

#define FIRST_TRIPLY_INDIRECT    (LAST_DOUBLY_INDIRECT + 1)
#define LAST_TRIPLY_INDIRECT \
   (LAST_DOUBLY_INDIRECT +\
     (IMFS_MEMFILE_BLOCK_SLOTS * \
        IMFS_MEMFILE_BLOCK_SLOTS * IMFS_MEMFILE_BLOCK_SLOTS))

#define IMFS_MEMFILE_MAXIMUM_SIZE \
  (LAST_TRIPLY_INDIRECT * IMFS_MEMFILE_BYTES_PER_BLOCK)

/*
 *  What types of IMFS file systems entities there can be.
 */

#define IMFS_jnode_types_t rtems_filesystem_node_types_t
#define IMFS_DIRECTORY     RTEMS_FILESYSTEM_DIRECTORY
#define IMFS_DEVICE        RTEMS_FILESYSTEM_DEVICE
#define IMFS_HARD_LINK     RTEMS_FILESYSTEM_HARD_LINK
#define IMFS_SYM_LINK      RTEMS_FILESYSTEM_SYM_LINK
#define IMFS_MEMORY_FILE   RTEMS_FILESYSTEM_MEMORY_FILE
#define IMFS_LINEAR_FILE   (IMFS_MEMORY_FILE + 1)
#define IMFS_FIFO          (IMFS_LINEAR_FILE + 1)

#define IMFS_NUMBER_OF_TYPES  (IMFS_FIFO + 1)

typedef union {
  IMFS_directory_t   directory;
  IMFS_device_t      device;
  IMFS_link_t        hard_link;
  IMFS_sym_link_t    sym_link;
  IMFS_memfile_t     file;
  IMFS_linearfile_t  linearfile;
  IMFS_fifo_t        fifo;
} IMFS_types_union;

/*
 * Major device number for the IMFS. This is not a real device number because
 * the IMFS is just a file system and does not have a driver.
 */
#define IMFS_DEVICE_MAJOR_NUMBER (0xfffe)

/*
 *  Maximum length of a "basename" of an IMFS file/node.
 */

#define IMFS_NAME_MAX  32

/*
 *  The control structure for an IMFS jnode.
 */

struct IMFS_jnode_tt {
  rtems_chain_node    Node;                  /* for chaining them together */
  IMFS_jnode_t       *Parent;                /* Parent node */
  char                name[IMFS_NAME_MAX+1]; /* "basename" */
  mode_t              st_mode;               /* File mode */
  nlink_t             st_nlink;              /* Link count */
  ino_t               st_ino;                /* inode */

  uid_t               st_uid;                /* User ID of owner */
  gid_t               st_gid;                /* Group ID of owner */

  time_t              stat_atime;            /* Time of last access */
  time_t              stat_mtime;            /* Time of last modification */
  time_t              stat_ctime;            /* Time of last status change */
  IMFS_jnode_types_t  type;                  /* Type of this entry */
  IMFS_types_union    info;
};

#define IMFS_update_atime( _jnode )         \
  do {                                      \
    struct timeval tv;                      \
    gettimeofday( &tv, 0 );                 \
    _jnode->stat_atime  = (time_t) tv.tv_sec; \
  } while (0)

#define IMFS_update_mtime( _jnode )         \
  do {                                      \
    struct timeval tv;                      \
    gettimeofday( &tv, 0 );                 \
    _jnode->stat_mtime  = (time_t) tv.tv_sec; \
  } while (0)

#define IMFS_update_ctime( _jnode )         \
  do {                                      \
    struct timeval tv;                      \
    gettimeofday( &tv, 0 );                 \
    _jnode->stat_ctime  = (time_t) tv.tv_sec; \
  } while (0)

#define IMFS_mtime_ctime_update( _jnode )   \
  do {                                      \
    struct timeval tv;                      \
    gettimeofday( &tv, 0 );                 \
    _jnode->stat_mtime  = (time_t) tv.tv_sec; \
    _jnode->stat_ctime  = (time_t) tv.tv_sec; \
  } while (0)

typedef struct {
  int                                     instance;
  ino_t                                   ino_count;
  const rtems_filesystem_file_handlers_r *memfile_handlers;
  const rtems_filesystem_file_handlers_r *directory_handlers;
} IMFS_fs_info_t;

/*
 *  Type defination for tokens returned from IMFS_get_token
 */

typedef enum {
  IMFS_NO_MORE_PATH,
  IMFS_CURRENT_DIR,
  IMFS_UP_DIR,
  IMFS_NAME,
  IMFS_INVALID_TOKEN
} IMFS_token_types;

/*
 *  Shared Data
 */

extern const rtems_filesystem_file_handlers_r       IMFS_directory_handlers;
extern const rtems_filesystem_file_handlers_r       IMFS_device_handlers;
extern const rtems_filesystem_file_handlers_r       IMFS_link_handlers;
extern const rtems_filesystem_file_handlers_r       IMFS_memfile_handlers;
extern const rtems_filesystem_file_handlers_r       IMFS_fifo_handlers;
extern const rtems_filesystem_operations_table      IMFS_ops;
extern const rtems_filesystem_operations_table      miniIMFS_ops;
extern const rtems_filesystem_limits_and_options_t  IMFS_LIMITS_AND_OPTIONS;

/*
 *  Routines
 */

extern int IMFS_initialize(
   rtems_filesystem_mount_table_entry_t *mt_entry,
   const void                           *data
);

extern int miniIMFS_initialize(
   rtems_filesystem_mount_table_entry_t *mt_entry,
   const void                           *data
);

extern int IMFS_initialize_support(
   rtems_filesystem_mount_table_entry_t       *mt_entry,
   const rtems_filesystem_operations_table    *op_table,
   const rtems_filesystem_file_handlers_r     *memfile_handlers,
   const rtems_filesystem_file_handlers_r     *directory_handlers
);

extern int IMFS_fsunmount(
   rtems_filesystem_mount_table_entry_t *mt_entry
);

extern int rtems_tarfs_load(
   char         *mountpoint,
   uint8_t      *tar_image,
   size_t        tar_size
);

/*
 * Returns the number of characters copied from path to token.
 */
extern IMFS_token_types IMFS_get_token(
  const char       *path,
  int               pathlen,
  char             *token,
  int              *token_len
);

extern void IMFS_dump( void );

extern void IMFS_initialize_jnode(
  IMFS_jnode_t        *the_jnode,
  IMFS_jnode_types_t   type,
  IMFS_jnode_t        *the_parent,
  char                *name,
  mode_t               mode
);

extern IMFS_jnode_t *IMFS_find_match_in_dir(
  IMFS_jnode_t *directory,                         /* IN */
  char         *name                               /* IN */
);

extern rtems_filesystem_node_types_t IMFS_node_type(
  rtems_filesystem_location_info_t    *pathloc     /* IN */
);

extern int IMFS_stat(
  rtems_filesystem_location_info_t *loc,           /* IN  */
  struct stat                      *buf            /* OUT */
);

extern int IMFS_Set_handlers(
  rtems_filesystem_location_info_t   *loc
);

extern int IMFS_evaluate_link(
  rtems_filesystem_location_info_t *node,        /* IN/OUT */
  int                               flags        /* IN     */
);

extern int IMFS_eval_path(
  const char                        *pathname,     /* IN     */
  size_t                            pathnamelen,   /* IN     */
  int                               flags,         /* IN     */
  rtems_filesystem_location_info_t  *pathloc       /* IN/OUT */
);

extern int IMFS_link(
  rtems_filesystem_location_info_t  *to_loc,      /* IN */
  rtems_filesystem_location_info_t  *parent_loc,  /* IN */
  const char                        *token        /* IN */
);

extern int IMFS_unlink(
  rtems_filesystem_location_info_t  *parent_pathloc, /* IN */
  rtems_filesystem_location_info_t  *pathloc         /* IN */
);

extern int IMFS_chown(
  rtems_filesystem_location_info_t  *pathloc,      /* IN */
  uid_t                              owner,        /* IN */
  gid_t                              group         /* IN */
);

extern int IMFS_freenodinfo(
  rtems_filesystem_location_info_t  *pathloc       /* IN */
);

extern int IMFS_mknod(
  const char                        *path,         /* IN */
  mode_t                             mode,         /* IN */
  dev_t                              dev,          /* IN */
  rtems_filesystem_location_info_t  *pathloc       /* IN/OUT */
);

extern IMFS_jnode_t *IMFS_allocate_node(
  IMFS_jnode_types_t                type,         /* IN  */
  const char                       *name,         /* IN  */
  mode_t                            mode          /* IN  */
);

extern IMFS_jnode_t *IMFS_create_root_node(void);

extern IMFS_jnode_t *IMFS_create_node(
  rtems_filesystem_location_info_t *parent_loc,   /* IN  */
  IMFS_jnode_types_t                type,         /* IN  */
  const char                       *name,         /* IN  */
  mode_t                            mode,         /* IN  */
  const IMFS_types_union           *info          /* IN  */
);

extern int IMFS_evaluate_for_make(
  const char                         *path,       /* IN     */
  rtems_filesystem_location_info_t   *pathloc,    /* IN/OUT */
  const char                        **name        /* OUT    */
);

extern int IMFS_mount(
  rtems_filesystem_mount_table_entry_t *mt_entry  /* IN */
);

extern int IMFS_unmount(
  rtems_filesystem_mount_table_entry_t *mt_entry  /* IN */
);

extern int IMFS_freenod(
  rtems_filesystem_location_info_t  *node         /* IN/OUT */
);

extern int IMFS_memfile_remove(
 IMFS_jnode_t  *the_jnode         /* IN/OUT */
);

extern int memfile_ftruncate(
  rtems_libio_t *iop,               /* IN  */
  rtems_off64_t  length             /* IN  */
);

extern int imfs_dir_open(
  rtems_libio_t *iop,             /* IN  */
  const char    *pathname,        /* IN  */
  uint32_t       flag,            /* IN  */
  uint32_t       mode             /* IN  */
);

extern int imfs_dir_close(
  rtems_libio_t *iop             /* IN  */
);

extern ssize_t imfs_dir_read(
  rtems_libio_t *iop,              /* IN  */
  void          *buffer,           /* IN  */
  size_t         count             /* IN  */
);

extern rtems_off64_t imfs_dir_lseek(
  rtems_libio_t        *iop,              /* IN  */
  rtems_off64_t         offset,           /* IN  */
  int                   whence            /* IN  */
);

extern int imfs_dir_fstat(
  rtems_filesystem_location_info_t *loc,         /* IN  */
  struct stat                      *buf          /* OUT */
);

extern int imfs_dir_rmnod(
  rtems_filesystem_location_info_t *parent_pathloc, /* IN */
  rtems_filesystem_location_info_t *pathloc         /* IN */
);

extern int memfile_open(
  rtems_libio_t *iop,             /* IN  */
  const char    *pathname,        /* IN  */
  uint32_t       flag,            /* IN  */
  uint32_t       mode             /* IN  */
);

extern int memfile_close(
  rtems_libio_t *iop             /* IN  */
);

extern ssize_t memfile_read(
  rtems_libio_t *iop,             /* IN  */
  void          *buffer,          /* IN  */
  size_t         count            /* IN  */
);

extern ssize_t memfile_write(
  rtems_libio_t *iop,             /* IN  */
  const void    *buffer,          /* IN  */
  size_t         count            /* IN  */
);

extern int memfile_ioctl(
  rtems_libio_t *iop,             /* IN  */
  uint32_t       command,         /* IN  */
  void          *buffer           /* IN  */
);

extern rtems_off64_t memfile_lseek(
  rtems_libio_t        *iop,        /* IN  */
  rtems_off64_t         offset,     /* IN  */
  int                   whence      /* IN  */
);

extern int memfile_rmnod(
  rtems_filesystem_location_info_t  *parent_pathloc, /* IN */
  rtems_filesystem_location_info_t  *pathloc         /* IN */
);

extern int device_open(
  rtems_libio_t *iop,            /* IN  */
  const char    *pathname,       /* IN  */
  uint32_t       flag,           /* IN  */
  uint32_t       mode            /* IN  */
);

extern int device_close(
  rtems_libio_t *iop             /* IN  */
);

extern ssize_t device_read(
  rtems_libio_t *iop,            /* IN  */
  void          *buffer,         /* IN  */
  size_t         count           /* IN  */
);

extern ssize_t device_write(
  rtems_libio_t *iop,               /* IN  */
  const void    *buffer,            /* IN  */
  size_t         count              /* IN  */
);

extern int device_ioctl(
  rtems_libio_t *iop,               /* IN  */
  uint32_t       command,           /* IN  */
  void          *buffer             /* IN  */
);

extern rtems_off64_t device_lseek(
  rtems_libio_t *iop,               /* IN  */
  rtems_off64_t  offset,            /* IN  */
  int            whence             /* IN  */
);

extern int device_ftruncate(
  rtems_libio_t *iop,               /* IN  */
  rtems_off64_t  length             /* IN  */
);

extern int IMFS_utime(
  rtems_filesystem_location_info_t  *pathloc,       /* IN */
  time_t                             actime,        /* IN */
  time_t                             modtime        /* IN */
);

extern int IMFS_fchmod(
  rtems_filesystem_location_info_t *loc,
  mode_t                            mode
);

extern int IMFS_symlink(
  rtems_filesystem_location_info_t  *parent_loc,  /* IN */
  const char                        *link_name,
  const char                        *node_name
);

extern int IMFS_readlink(
 rtems_filesystem_location_info_t   *loc,         /* IN */
 char                               *buf,         /* OUT */
 size_t                             bufsize
);

extern int IMFS_rename(
  rtems_filesystem_location_info_t  *old_loc,         /* IN */
  rtems_filesystem_location_info_t  *old_parent_loc,  /* IN */
  rtems_filesystem_location_info_t  *new_parent_loc,  /* IN */
  const char                        *new_name         /* IN */
);

extern int IMFS_fdatasync(
  rtems_libio_t *iop
);

extern int IMFS_fcntl(
  int            cmd,
  rtems_libio_t *iop
);

extern int IMFS_rmnod(
  rtems_filesystem_location_info_t  *parent_pathloc, /* IN */
  rtems_filesystem_location_info_t  *pathloc         /* IN */
);

#ifdef __cplusplus
}
#endif

#endif
/* end of include file */
