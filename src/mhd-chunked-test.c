/*
  This file is part of libmicrohttpd
  (C) 2007 Christian Grothoff

  libmicrohttpd is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published
  by the Free Software Foundation; either version 2, or (at your
  option) any later version.

  libmicrohttpd is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with libmicrohttpd; see the file COPYING.  If not, write to the
  Free Software Foundation, Inc., 59 Temple Place - Suite 330,
  Boston, MA 02111-1307, USA.
*/

/**
 * @file daemontest_get_chunked.c
 * @brief  Testcase for libmicrohttpd GET operations with chunked content encoding
 *         TODO:
 *         - how to test that chunking was actually used?
 *         - use CURLOPT_HEADERFUNCTION to validate
 *           footer was sent
 * @author Christian Grothoff
 */

#include <microhttpd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#ifndef WINDOWS
#include <unistd.h>
#endif

#if defined(CPU_COUNT) && (CPU_COUNT+0) < 2
#undef CPU_COUNT
#endif
#if !defined(CPU_COUNT)
#define CPU_COUNT 2
#endif

#define PORTNUM 1081

struct CBC
{
    char *buf;
    size_t pos;
    size_t size;
};

static size_t
copyBuffer (void *ptr, size_t size, size_t nmemb, void *ctx)
{
    struct CBC *cbc = ctx;

    if (cbc->pos + size * nmemb > cbc->size)
        return 0;                   /* overflow */
    memcpy (&cbc->buf[cbc->pos], ptr, size * nmemb);
    cbc->pos += size * nmemb;
    return size * nmemb;
}

/**
 * MHD content reader callback that returns
 * data in chunks.
 */
static ssize_t
crc (void *cls, uint64_t pos, char *buf, size_t max)
{
    struct MHD_Response **responseptr = cls;

    if (pos == 128 * 10)
    {
        //MHD_add_response_header (*responseptr, "Footer", "working");
        return MHD_CONTENT_READER_END_OF_STREAM;
    }
    if (max < 128)
        abort ();                   /* should not happen in this testcase... */
    memset (buf, 'A' + (pos / 128), 128);
    /* Wait some time so that we actually see that chunking is happening */
    sleep(1);
    return 128;
}

/**
 * Dummy function that does nothing.
 */
static void
crcf (void *ptr)
{
    free (ptr);
}

static int
ahc_echo (void *cls,
          struct MHD_Connection *connection,
          const char *url,
          const char *method,
          const char *version,
          const char *upload_data, size_t *upload_data_size, void **ptr)
{
    static int aptr;
    const char *me = cls;
    struct MHD_Response *response;
    struct MHD_Response **responseptr;
    int ret;

    if (0 != strcmp (me, method))
        return MHD_NO;              /* unexpected method */
    if (&aptr != *ptr)
    {
        /* do never respond on first call */
        *ptr = &aptr;
        return MHD_YES;
    }
    responseptr = malloc (sizeof (struct MHD_Response *));
    if (responseptr == NULL)
        return MHD_NO;
    response = MHD_create_response_from_callback (MHD_SIZE_UNKNOWN,
                                                  128,
                                                  &crc, responseptr, &crcf);
    *responseptr = response;
    ret = MHD_queue_response (connection, MHD_HTTP_OK, response);
    MHD_destroy_response (response);
    return ret;
}

int main(int argc, char *const *argv)
{
    struct MHD_Daemon *d;
    char buf[2048];
    struct CBC cbc;

    cbc.buf = buf;
    cbc.size = 2048;
    cbc.pos = 0;
    d = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY | MHD_USE_DEBUG,
                         PORTNUM, NULL, NULL, &ahc_echo, "GET",
                         MHD_OPTION_THREAD_POOL_SIZE, CPU_COUNT, MHD_OPTION_END);
    if (!d)
        return 16;

    printf("HTTP server running on port %d. Press ENTER to stop the server.\n",
           PORTNUM);
    getchar();

    MHD_stop_daemon (d);

    return EXIT_SUCCESS;
}
