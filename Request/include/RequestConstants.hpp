#pragma once

#define KILOBYTE 1024
#define MEGABYTE 1024*1024
#define MAX_BUFFER_SIZE MEGABYTE

namespace request {
    
    namespace RequestType {
        enum Type {
            UNKNOWN,
            HEADER,
            CREATE,
            GET,
            READ,
            WRITE
        };

    }
}
