
#pragma once

#include "Containers/ArrayView.h"

typedef TCheckedPointerIterator<uint8, int> File;

struct NSM_API FBinaryFileHelper
{
    enum class EEndianness
    {
        BigEndian,
        LittleEndian
    };
    
    static float ConvertBytesToFloat(File& FilePointer);

    static uint32 Create4Bytes(uint8& Byte1, uint8& Byte2, uint8& Byte3, uint8& Byte4, EEndianness Endianness = EEndianness::BigEndian);
    
    static uint32 CreateBigEndian4Bytes(uint8& Byte1, uint8& Byte2, uint8& Byte3, uint8& Byte4);
    
    static uint32 CreateLittleEndian4Bytes(uint8& Byte1, uint8& Byte2, uint8& Byte3, uint8& Byte4);
};
