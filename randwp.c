#include <stdio.h>
#include "jpeglib.h"
#include "cdjpeg.h"

#include <sys/types.h>
#ifdef _DOS
    #include <direct.h>
#else
    #include <dirent.h>
#endif
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

/* Pull in bmp write routines that aren't normally in headers */
EXTERN(djpeg_dest_ptr) jinit_write_bmp(j_decompress_ptr cinfo, boolean is_os2);

int is_supported(const char * filename)
{
    size_t len = strlen(filename);
    
    return ( len > 4
        && ((
               tolower(filename[len-4]) == 'j'
            && tolower(filename[len-3]) == 'p'
            && tolower(filename[len-2]) == 'e'
            && tolower(filename[len-1]) == 'g'
        ) || (
               tolower(filename[len-3]) == 'j'
            && tolower(filename[len-2]) == 'p'
            && tolower(filename[len-1]) == 'g'
        ))
    );
}

/* Return 0 on success, 1 on failure */
int pick_file(const char * searchpath, char * selected_file)
{
    struct dirent * dir_item;
    size_t num_files = 0, choice;
    DIR * searchdir = opendir(searchpath);
    int result = 1;
    
    if (searchdir == NULL)
    {
        fprintf(stderr, "Cannot open search directory %d\n.", searchpath);
        return 1;
    }
    
    /* First pass: figure out number of supported choices */
    for(dir_item = readdir(searchdir); dir_item != NULL; dir_item = readdir(searchdir))
    {
        if (is_supported(dir_item->d_name))
            num_files++;
    }
    
    /* Pick a random choice number within range.
       Seed our random number with current time to whatever precision rand uses */
    srand(time(NULL) % RAND_MAX);
    choice = rand() % num_files;

    /* Second pass: find the choice we decided on. */
    rewinddir(searchdir);
    num_files = 0;
    for(dir_item = readdir(searchdir); dir_item != NULL; dir_item = readdir(searchdir))
    {
        if (is_supported(dir_item->d_name))
        {
            if (num_files == choice)
            {
                /* Return full path and filename to the caller */
                strcpy(selected_file, searchpath);
            #ifdef _DOS
                strcat(selected_file, "\\");
            #else
                strcat(selected_file, "/");
            #endif
                strcat(selected_file, dir_item->d_name);
                result = 0;
                break;
            }
            
            num_files++;
        }
    }
    closedir(searchdir);
    
    return result;
}

void convert_jpeg(const char * inname, const char * outname)
{
    struct jpeg_decompress_struct cinfo;
    struct jpeg_error_mgr jerr;
    JDIMENSION num_scanlines;
    djpeg_dest_ptr dest_mgr = NULL;
    FILE * infile;
    FILE * outfile;

    /* Open input and output files */
    infile = fopen(inname, "rb");
    if (infile == NULL)
    {
        fprintf(stderr, "Can't open input %s\n", inname);
        return;
    }

    outfile = fopen(outname, "wb");
    if (outfile == NULL)
    {
        fclose(infile);
        fprintf(stderr, "Can't open output %s\n", outname);
        return;
    }

    /* Step 1: allocate and initialize JPEG decompression object */
    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_decompress(&cinfo);

    jpeg_stdio_src(&cinfo, infile);
    (void) jpeg_read_header(&cinfo, TRUE);

    /* Configure destination object */
    dest_mgr = jinit_write_bmp(&cinfo, FALSE);
    dest_mgr->output_file = outfile;
    (*dest_mgr->start_output) (&cinfo, dest_mgr);
    (void) jpeg_start_decompress(&cinfo);

    /* Write data to the destination */
    while (cinfo.output_scanline < cinfo.output_height)
    {
        num_scanlines = jpeg_read_scanlines(&cinfo, dest_mgr->buffer,
                        dest_mgr->buffer_height);
        (*dest_mgr->put_pixel_rows) (&cinfo, dest_mgr, num_scanlines);
    }

    /* Cleanup */
    (*dest_mgr->finish_output) (&cinfo, dest_mgr);
    (void) jpeg_finish_decompress(&cinfo);
    jpeg_destroy_decompress(&cinfo);
    fclose(infile);
    
    printf("Converted %s to %s.\n", inname, outname);
}



int main(int argc, char * argv[])
{
    if (argc == 3)
    {
        char selected_file[PATH_MAX];
        char * searchpath = argv[1];
        char * outname = argv[2];
        if (!pick_file(searchpath, selected_file))
        {      
            convert_jpeg(selected_file, outname);
        }
    }
    else
    {
        printf("Usage: randwp searchpath outname\n");
    }
    
    return 0;
}
