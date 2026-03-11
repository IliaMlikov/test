#ifndef FILE_HEADER_HPP
#define FILE_HEADER_HPP

#pragma pack(push, 1)
struct FileHeader {
    char signature[8];
    int version;
    int studentCount;
};
#pragma pack(pop)

#endif