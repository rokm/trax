
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#include "trax.h"
#include "message.h"
#include "region.h"

#if defined(__OS2__) || defined(__WINDOWS__) || defined(WIN32) || defined(_MSC_VER) 


#else

#define strcmpi strcasecmp

#endif

int main( int argc, char** argv) {

    if (argc < 2) return 0;

    if (strcmpi(argv[1], "parsing") == 0) {

        string_list arguments;
        trax_properties* properties;
        int input;
        int output = fileno(stdout);

        if (argc != 3) return 0;

        input = open(argv[2], O_RDONLY);

        LIST_CREATE(arguments, 8);
        properties = trax_properties_create();

        message_stream* stream = create_message_stream_file(input, output);

        while (1) {

            int type;

            LIST_RESET(arguments);
            trax_properties_clear(properties);

            type = read_message(stream, NULL, &arguments, properties);

            if (type == TRAX_ERROR) break;

            write_message(stream, NULL, type, arguments, properties); 

        }

        close(input);

        LIST_DESTROY(arguments);
        trax_properties_release(&properties);

        destroy_message_stream(&stream);

    } else if (strcmpi(argv[1], "overlap") == 0) {

        region_container* a, *b;

        if (argc != 4) return 0;

        region_parse(argv[2], &a);
        region_parse(argv[3], &b);

        fprintf(stdout, "Region A:");
        region_print(stdout, a);
        fprintf(stdout, "\n");
        fprintf(stdout, "Region B:");
        region_print(stdout, b);
        fprintf(stdout, "\n");

        float overlap = region_compute_overlap(a, b).overlap;

        fprintf(stdout, "Overlap of A and B: %f\n", overlap);

        region_release(&a);
        region_release(&b);
    }
}



