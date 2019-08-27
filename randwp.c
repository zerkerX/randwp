#include <stdio.h>
#include "jpeglib.h"
#include "cdjpeg.h"

/* Pull in bmp write routines that aren't normally in headers */
EXTERN(djpeg_dest_ptr) jinit_write_bmp(j_decompress_ptr cinfo, boolean is_os2);

int convert_jpeg(const char * inname, const char * outname)
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
        fprintf(stderr, "Can't open %s\n", inname);
        return 0;
    }

    outfile = fopen(outname, "wb");
    if (outfile == NULL)
    {
        fclose(infile);
        fprintf(stderr, "Can't open %s\n", outname);
        return 0;
    }

    /* Step 1: allocate and initialize JPEG decompression object */
    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_decompress(&cinfo);

    jpeg_stdio_src(&cinfo, infile);
    (void) jpeg_read_header(&cinfo, TRUE);

    /* Configure destination object */
    dest_mgr = jinit_write_bmp(&cinfo, FALSE);
    printf("Initted BMP\n");
    dest_mgr->output_file = outfile;
    (*dest_mgr->start_output) (&cinfo, dest_mgr);
    printf("Configured Output\n");
    (void) jpeg_start_decompress(&cinfo);
    printf("Started decompress\n");

    /* Write data to the destination */
    while (cinfo.output_scanline < cinfo.output_height)
    {
        num_scanlines = jpeg_read_scanlines(&cinfo, dest_mgr->buffer,
                        dest_mgr->buffer_height);
        (*dest_mgr->put_pixel_rows) (&cinfo, dest_mgr, num_scanlines);
    }
    printf("Wrote output\n");

    /* Cleanup */
    (*dest_mgr->finish_output) (&cinfo, dest_mgr);
    printf("Finished...\n");
    (void) jpeg_finish_decompress(&cinfo);
    printf("Finished Decomp\n");
    jpeg_destroy_decompress(&cinfo);
    printf("Destroyed\n");
    fclose(infile);
}



int main(int argc, char * argv[])
{
    if (argc == 3)
    {
        char * inname = argv[1];
        char * outname = argv[2];
        printf("%d, %s to %s\n", argc, inname, outname);
        convert_jpeg(inname, outname);
    }
    else
    {
        printf("Usage: randwp inname outname\n");
    }
}
