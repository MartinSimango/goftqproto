#pragma once

namespace ResponseType {
    enum Type {
        UNKNOWN = 100, //starts at 100 to not conflict with request types
        CREATE,
        GET,
        READ,
        WRITE
    };

}

namespace ResponseStatus {
    enum Type {
        OK,
        FILE_NOT_FOUND,
        NO_READ_PERMISSIONS,
        NO_WRITE_PERMISIONS,
    };

}
