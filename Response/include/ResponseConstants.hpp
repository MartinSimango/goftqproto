#pragma once

namespace ResponseType {
    enum Type {
        HEADER = 100, //starts at 100 to not conflict with request types
        CREATE,
        GET,
        READ,
        WRITE,
        UNKNOWN
    };

}

namespace ResponseStatus {
    enum Type {
        UNKNOWN,
        OK,
        FILE_NOT_FOUND,
        NO_READ_PERMISSIONS,
        NO_WRITE_PERMISIONS,
    };

}
