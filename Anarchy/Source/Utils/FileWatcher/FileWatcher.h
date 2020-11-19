#ifndef _FILE_WATCHER_H_
#define _FILE_WATCHER_H_

#include <filesystem>
#include <string>
#include <vector>

#include "Framework/FrameworkAliases.h"

namespace anarchy
{
    class FileWatcher
    {
    public:
        FileWatcher() = default;
        ~FileWatcher() = default;

        [[nodiscard]] size_t AddFileForWatch(string filePath);
        bool IsFileModified(size_t fileIndex);

    private:
        std::vector<string> m_filePathsToWatch = {};
        std::vector<std::filesystem::file_time_type> m_watchFilesLastWriteTime = {};
    };
}

#endif // _FILE_WATCHER_H_
