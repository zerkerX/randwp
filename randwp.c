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
    (void) jpeg_start_decompress(&cinfo);

    /* Configure destination object */
    dest_mgr = jinit_write_bmp(&cinfo, FALSE);
    dest_mgr->output_file = outfile;
    (*dest_mgr->start_output) (&cinfo, dest_mgr);

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
}



int main()
{
    const char * inname = "/home/zerker/Pictures/Backgrounds/4-3 Small/800x600/art_keeper_orland.jpg";
    const char * outname = "/home/zerker/result.bmp";
    printf("%s to %s\n", inname, outname);
    convert_jpeg(inname, outname);
}
