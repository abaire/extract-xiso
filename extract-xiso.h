#ifndef EXTRACT_XISO_H_
#define EXTRACT_XISO_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#if defined( __DARWIN__ )
#define exiso_target				"macos-x"

#define PATH_CHAR					'/'
#define PATH_CHAR_STR				"/"

#define FORCE_ASCII					1
#define READFLAGS					O_RDONLY
#define WRITEFLAGS					O_WRONLY | O_CREAT | O_TRUNC
#define READWRITEFLAGS				O_RDWR

typedef	off_t						xoff_t;
#elif defined( __FREEBSD__ )
#define exiso_target				"freebsd"

#define PATH_CHAR					'/'
#define PATH_CHAR_STR				"/"

#define FORCE_ASCII					1
#define READFLAGS					O_RDONLY
#define WRITEFLAGS					O_WRONLY | O_CREAT | O_TRUNC
#define READWRITEFLAGS				O_RDWR

typedef	off_t						xoff_t;
#elif defined( __LINUX__ )
#define exiso_target				"linux"

#define PATH_CHAR					'/'
#define PATH_CHAR_STR				"/"

#define FORCE_ASCII					0
#define READFLAGS					O_RDONLY | O_LARGEFILE
#define WRITEFLAGS					O_WRONLY | O_CREAT | O_TRUNC | O_LARGEFILE
#define READWRITEFLAGS				O_RDWR | O_LARGEFILE

#define lseek						lseek64
#define stat						stat64

typedef off64_t 					xoff_t;
#elif defined( __OPENBSD__ )
#define exiso_target				"openbsd"
#elif defined( _WIN32 )
#define exiso_target				"win32"

#define PATH_CHAR					'\\'
#define PATH_CHAR_STR				"\\"

#define FORCE_ASCII					0
#define READFLAGS					O_RDONLY | O_BINARY
#define WRITEFLAGS					O_WRONLY | O_CREAT | O_TRUNC | O_BINARY
#define READWRITEFLAGS				O_RDWR   | O_BINARY

#define S_ISDIR( x )				( ( x ) & _S_IFDIR )
#define S_ISREG( x )				( ( x ) & _S_IFREG )

#include "win32/getopt.c"
#ifdef _MSC_VER
#include "win32/asprintf.c"
#endif
#define lseek						_lseeki64
#define mkdir( a, b )				mkdir( a )

typedef __int32						int32_t;
typedef __int64                     xoff_t;
#else
#error unknown target, cannot compile!
#endif

typedef enum modes { k_generate_avl, k_extract, k_list, k_rewrite } modes;
typedef enum errors { err_end_of_sector = -5001, err_iso_rewritten = -5002, err_iso_no_files = -5003 } errors;

typedef void (*progress_callback)( xoff_t in_current_value, xoff_t in_final_value );
typedef int (*traversal_callback)( void *in_node, void *in_context, long in_depth );

typedef struct dir_node dir_node;
typedef struct create_list create_list;
typedef struct dir_node_avl dir_node_avl;

int decode_xiso( char *in_xiso, char *in_path, modes in_mode, char **out_iso_path, bool in_ll_compat );
int verify_xiso( int in_xiso, int32_t *out_root_dir_sector, int32_t *out_root_dir_size, char *in_iso_name );
int traverse_xiso( int in_xiso, dir_node *in_dir_node, xoff_t in_dir_start, char *in_path, modes in_mode, dir_node_avl **in_root, bool in_ll_compat );
int create_xiso( char *in_root_directory, char *in_output_directory, dir_node_avl *in_root, int in_xiso, char **out_iso_path, char *in_name, progress_callback in_progress_callback );

void set_suppress_timestamps(bool val);

#ifdef __cplusplus
};
#endif

#endif  // EXTRACT_XISO_H_
