#include "Utility/BinaryFileHelper.h"

float FBinaryFileHelper::ConvertBytesToFloat(File& FilePointer)
{
    uint8 Byte1 = *FilePointer;
    uint8 Byte2 = *(++FilePointer);
    uint8 Byte3 = *(++FilePointer);
    uint8 Byte4 = *(++FilePointer);
    // Set pointer ready for the next iteration
    ++FilePointer;
    uint32 Float = Create4Bytes(Byte1, Byte2, Byte3, Byte4);
    
    return *reinterpret_cast<float*>(&Float);
}

uint32 FBinaryFileHelper::Create4Bytes(uint8& Byte1, uint8& Byte2, uint8& Byte3, uint8& Byte4, EEndianness Endianness)
{
    switch (Endianness)
    {
        case EEndianness::BigEndian:
            return CreateBigEndian4Bytes(Byte1, Byte2, Byte3, Byte4);
        case EEndianness::LittleEndian:
            return CreateBigEndian4Bytes(Byte1, Byte2, Byte3, Byte4);
    }
    return 0;
}

uint32 FBinaryFileHelper::CreateBigEndian4Bytes(uint8& Byte1, uint8& Byte2, uint8& Byte3, uint8& Byte4)
{
    return Byte4 << 24 | Byte3 << 16 | Byte2 << 8 | Byte1;
}

uint32 FBinaryFileHelper::CreateLittleEndian4Bytes(uint8& Byte1, uint8& Byte2, uint8& Byte3, uint8& Byte4)
{
    return Byte1 << 24 | Byte2 << 16 | Byte3 << 8 | Byte4;
}


