#ifndef _FILE_H_
#define _FILE_H_

#include <string>
#include <windows.h>
#include <concepts>

namespace anarchy
{
    template <typename T>
    concept Pointer = std::is_pointer<T>::value;

    template <typename T>
    concept Non_Pointer = !std::is_pointer<T>::value;

    enum class SeekPosition : uint16_t
    {
        Begin,
        Current,
        End
    };

    enum class FileIOMode : uint16_t
    {
        Read,
        Write,
        ReadWrite,
        Append,
        ReadAppend
    };

    class File
    {
    public:
        File() = delete;
        File(const File&) = default;
        File(File&&) = default;

        File(std::string filename, FileIOMode fileIOMode = FileIOMode::Write)
        {
            uint32_t access = 0x00000000L;

            switch (fileIOMode)
            {
            case FileIOMode::Read: access = GENERIC_READ;
                break;
            case FileIOMode::Write: access = GENERIC_WRITE;
                break;
            case FileIOMode::ReadWrite: access = GENERIC_READ | GENERIC_WRITE;
                break;
            case FileIOMode::Append: access = FILE_APPEND_DATA;
                break;
            case FileIOMode::ReadAppend: access = GENERIC_READ | FILE_APPEND_DATA;
                break;
            default: __debugbreak();
                break;
            }

            hFile = ::CreateFileA(
                filename.c_str(),
                access,
                FILE_SHARE_READ,
                NULL,
                OPEN_ALWAYS,
                NULL,
                NULL);

            if (hFile == INVALID_HANDLE_VALUE)
                __debugbreak();
        }

        ~File()
        {
            ::CloseHandle(hFile);
        }

        template <typename T>
        void Read(T& data, size_t size = sizeof(T))
        {
            ::DWORD bytesRead(0);
            ::ReadFile(hFile, &data, size, &bytesRead, nullptr);
        }

        template <typename T>
        void Read(T* data, size_t size)
        {
            ::DWORD bytesRead(0);
            ::ReadFile(hFile, data, size, &bytesRead, nullptr);
        }

        template <Non_Pointer T>
        void Write(const T& data, size_t size = sizeof(T))
        {
            uint32_t bytesWritten(0);
            ::WriteFile(hFile, &data, static_cast<uint32_t>(size), &bytesWritten, nullptr);
        }

        template <Pointer T>
        void Write(const T& data, size_t size = sizeof(T))
        {
            uint32_t bytesWritten(0); LPDWORD
                ::WriteFile(hFile, data, static_cast<uint32_t>(size), &bytesWritten, nullptr);
        }

        void Seek(int64_t bytesToMove, SeekPosition seekPosition)
        {
            LARGE_INTEGER largeInt;
            largeInt.QuadPart = bytesToMove;

            uint64_t moveMethod = -1; // max uint
            switch (seekPosition)
            {
            case SeekPosition::Begin: moveMethod = FILE_BEGIN;
                break;
            case SeekPosition::Current: moveMethod = FILE_CURRENT;
                break;
            case SeekPosition::End: moveMethod = FILE_END;
                break;
            }

            uint64_t filePosition = ::SetFilePointer(hFile, largeInt.LowPart, &largeInt.HighPart, moveMethod);

            if (filePosition == INVALID_SET_FILE_POINTER)
                __debugbreak();
        }

        uint64_t Tell()
        {
            LARGE_INTEGER largeInt;
            largeInt.QuadPart = 0; // set offset to null since we dont want to move the pointer

            uint64_t filePosition = ::SetFilePointer(hFile, largeInt.LowPart, &largeInt.HighPart, FILE_CURRENT);
            if (filePosition == INVALID_SET_FILE_POINTER)
                __debugbreak();

            return filePosition;
        }

    private:
        HANDLE hFile;
    };
}

#endif // !_FILE_H_
