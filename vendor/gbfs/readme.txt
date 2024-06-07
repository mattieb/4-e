GBFS
a read-only filesystem for game media in game boy advance roms
by Damian Yerrick


Ever wanted to include media (images, palettes, sound samples, etc.)
in GBA games?  Tired of repeatedly converting your binary media
files to source code and having to give your artists copies of
your compiler toolchain to test their work in an emulator?
Here's another solution.

GBFS is an archive format.  It is similar in principle to GNU 'tar'
but is much simpler in structure, has an order of magnitude less
overhead per stored object (32 bytes vs. 500 bytes), and can be
searched in O(log n) time rather than O(n) time.

GBFS comes with four utility programs for the host system and a small
library for the target system for accessing GBFS files.


=== Programs ===

The GBFS utilities create and manage GBFS files.  They are written in
98% portable ANSI C code.  This package also includes binaries for
Windows 4.x and later (9x, ME, NT, 2000, XP).

The programs gbfs, insgbfs, lsgbfs, ungbfs, and padbin are licensed
under the GNU General Public License, version 2 or later, and come
with ABSOLUTELY NO WARRANTY. See the COPYING file for details.

gbfs OUTFILE [INFILE]...
  Creates (or replaces) OUTFILE as a GBFS file with the contents of
  each INFILE as an object, naming the objects after the basenames
  (that is, file name without path information) of their respective
  files.  The user must have read permissions for each FILE and write
  permissions for OUTFILE.  This is analogous to genromfs or mkisofs.
  The current version of gbfs requires that "gbfs.$$$" in the current
  directory be writable and on the same partition as OUTFILE.  

insgbfs INFILE ROMFILE SYMNAME
  Inserts INFILE into the allocated space in ROMFILE named SYMNAME.
  The user must have read permissions for INFILE and read and write
  permissions for ROMFILE.

lsgbfs FILE
  Lists the names and lengths of objects in FILE to stdout.
  The user must have read permissions for FILE.

ungbfs FILE
  Dumps the objects in FILE as files to the current directory.
  The user must have read permissions for FILE and write permissions
  in the current directory.

padbin NUM FILE
  Pads FILE to the smallest multiple of NUM bytes greater than or
  equal to the length of FILE.  The user must have read and write
  permissions for FILE.

bin2s INFILE... > OUTFILE
  Converts binary files to ARM assembly source code and writes
  them to stdout, using symbol names similar to each file's name.
  Punctuation becomes underscores, and symbols with an initial digit
  are prepended with an underscore.  Use this to help compile GBFS
  files directly into your program if you debug with .elf.  It
  does the Right Thing with respect to alignment and segmenting in
  popular GBA link scripts, and its output (.s) can be compiled much
  more quickly than the C code that some conversion tools generate.

To compile the GBFS tools using MinGW, use mktools.bat.
  C:\...\GBFS>mktools

To compile the GBFS tools on a UNIX system or similar system
(BSD, Linux, Cygwin), use mktools.sh.
  [pin0cchio@lameboy gbfs]$ sh mktools.sh

The primary difference between these two scripts is that the
.bat version adds .exe to the names of the binaries and includes
a modified djbasename.c from the DJGPP libc distribution.  To find
DJGPP software, go to
  http://www.delorie.com/djgpp/

To add a GBFS file to a program binary, you'll need to use cat (or
its MS-DOS equivalent).

cat ROM INFILE > OUTROM    (UNIX)
copy /b ROM+INFILE OUTROM  (DOS/Windows)
  Adds the named GBFS file to the end of the ROM file and places
  the result in OUTROM.  (This program does not come with the GBFS
  package.  To obtain cat, go to any site offering GNU software and
  download the Fileutils package.)


=== Library function calls ===

The file libgbfs.c, licensed under a simple permissive license,
implements the following functions.  Use gbfs.h to get their
prototypes.

const GBFS_FILE *find_first_gbfs_file(const void *start);
  Finds the first GBFS file after start.  Note that this does a
  slow linear search at 256-byte strides, so make sure that your
  files are aligned to 256-byte boundaries and that you pass a start
  location close to (but not past) the beginning of the GBFS file.
  If you concatenate the GBFS file immediately after the binary, and
  libgbfs.c appears near the end of the link order, you can do this
  cute trick to find a file:

    find_first_gbfs_file(find_first_gbfs_file);

const void *skip_gbfs_file(const GBFS_FILE *file);
  Returns the address of the end of the given GBFS file.  This is
  useful if you want to have more than one GBFS file in a single
  binary, such as if you have multiple musicians and artists
  working on their own parts of a project.

const void *gbfs_get_obj(const GBFS_FILE *file,
                         const char *name,
                         u32 *len);
  Performs a binary search inside the given file for an object with
  the given name and returns a pointer to the object.  If len is not
  NULL, gbfs_get_obj() stores the length of the object (in bytes)
  into the referenced location.  If the object was not found,
  gbfs_get_obj() returns NULL and does not modify *len.
  A search on a file that contains two objects of the same name will
  return an undefined result.  The current implementation of
  gbfs_get_obj() uses bsearch() from the C library as its backend.

size_t gbfs_count_objs(const GBFS_FILE *file)
  If file is NULL, returns 0.  Otherwise, returns the number of
  objects in the given file.

const void *gbfs_get_nth_obj(const GBFS_FILE *file,
                             size_t n,
                             char name[],
                             u32 *len)
  Returns a pointer to the (n + 1)th object in the given file.  If
  name is not NULL, gbfs_get_nth_obj() copies the name of the object
  into the buffer, which must be at least 25 bytes long.  If len is
  not NULL, gbfs_get_nth_obj() stores the length of the object (in
  bytes) into the referenced location.  If n is greater than or equal
  to the number of objects in the file, gbfs_get_nth_obj() returns
  NULL and does not modify *len or name[].

void *gbfs_copy_obj(void *dst,
                    const GBFS_FILE *file,
                    const char *name);
  Calls gbfs_get_obj() to find an object with the given name, copies
  it to memory starting at dst[0] using memcpy(), and returns dst.
  If the object was not found, gbfs_copy_obj() returns NULL and does
  not modify memory.  Hint: for speed, override memcpy() with a DMA
  copy on platforms that support it.

gbfs_get_nth_obj() and gbfs_copy_obj() have not been tested as
rigorously as the rest of the library.


=== GBFS file format ===

Integers are stored in little-endian byte order because that's what
the local scene's favorite machines (SNES, GBA, PC) tend to use.

typedef struct GBFS_FILE
{
  char magic[16];    /* "PinEightGBFS\r\n\032\n" */
  u32  total_len;    /* total length of archive */
  u16  dir_off;      /* offset in bytes to directory */
  u16  dir_nmemb;    /* number of files */
  char reserved[8];  /* for future use */
} GBFS_FILE;

typedef struct GBFS_ENTRY
{
  char name[24];     /* filename, nul-padded */
  u32  len;          /* length of object in bytes */
  u32  data_offset;  /* in bytes from beginning of file */
} GBFS_ENTRY;

Note that GBFS_ENTRY records must be sorted in memcmp() order
by name so that the binary search can do its job correctly.

=== Change log ===

20040208
  * sped up find_first_gbfs_file() for multiboot programs that read
    GBFS files in ROM; now the search skips 0x02040000 to 0x08000000,
    speeding up DKA R5b3 multiboot programs' searches
  * changed to fix a compilation problem on a Mac compiler
    (reported by Jason Kim <jmkim@uci.edu>)
  * added gbfs_copy_obj() to make it easier to dump graphics to VRAM
  * added gbfs_count_objs() and gbfs_get_nth_obj()
  * included bin2s so that GBFS archives can be compiled to .elf
    for debugging support
  * replaced DOS executables with Windows ones because so many of us
    have moved on to Windows 2000 and XP

20030121
  * added exception to the tools' licenses to allow them to be
    used in Photoshop plug-ins
  * clarified license of manual
  * fixed warnings about missing strcmp() prototype
  * worked around MinGW's fclose(NULL) behavior, which crashes
    instead of doing nothing
  * recompiled the included binaries with a more recent version
    of MinGW
  * changed padbin.exe to pad with 0xff instead of 0x00 for faster
    flash writing
  * added a compile time option to libgbfs.c to make
    find_first_gbfs_file() use an alignment of any power of 2.
    I normally use a 256-byte alignment, which provides a
    reasonably fast search of the 32 MB cart address space.

20020404
  * changed upper bound on find_first_gbfs_file() in libgbfs.c
    to the end of ROM rather than the end of EWRAM to make libgbfs
    compatible with ROM-based programs
  * Added skip_gbfs_file() to find the end of a GBFS file
  * Clarified license of gbfs.h

20020402
  * initial release


=== Legal ===

Copyright 2002-2003 Damian Yerrick.
This manual (but not the accompanying programs) is subject to the
QING PUBLIC LICENCE

Copying, distribution, public performance, public display, digital
audio transmission, and use of this work is permitted without
restriction.  Circumvention of any technological measure or measures
which effectively control access to this work is permitted without
restriction.  Preparation of derivative works is permitted provided
that you cause any such work to be licensed as a whole at no charge
to all third parties under the terms of this License.

The programs in this package are released under their own licenses;
check the source code files for details.
