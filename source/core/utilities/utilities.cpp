#include "utilities.h"
#include "Core/hash/Murmur3.h"
#include <Windows.h>
namespace Core
{
    std::wstring ToWString( const std::string& str )
    {
        return std::wstring( str.begin(), str.end() );
    }

    std::string ToString( const std::wstring& str )
    {
        return std::string( str.begin(), str.end() );
    }

    uint64 Hash( const std::string& str )
    {
        uint64 result;
        MurmurHash3_x86_32( str.c_str(), (int32)str.length(), 0, &result );
        return result;
    }

    uint64 Hash( const std::string& str, uint32 seed )
    {
        uint64 result;
        MurmurHash3_x86_32( str.c_str(), (int32)str.length(), seed, &result );
        return result;
    }

    void DebugPrintLastError()
    {
        DWORD error = GetLastError();
        LPWSTR lpMsgBuf = nullptr;
        size_t size = FormatMessage(
            FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
            NULL,
            error,
            MAKELANGID( LANG_NEUTRAL, SUBLANG_DEFAULT ),
            (LPWSTR)&lpMsgBuf,
            0, NULL );

        std::wstring message( lpMsgBuf, size );
        OutputDebugStringA( ToString( message ).c_str() );
    }

}; //namespace Core