#include "FileWatcher.h"
#include "../../Framework/Includes/FrameworkGlobals.h"

namespace anarchy::utils
{
    size_t FileWatcher::AddFileForWatch(framework::AC_String filePath)
    {
        framework::AC_Assert(std::filesystem::exists(filePath), "Cannot Open File for FileWatcher.");
        
        auto lastModifiedTime = std::filesystem::last_write_time(filePath);
        
        m_filePathsToWatch.emplace_back(filePath);
        m_watchFilesLastWriteTime.emplace_back(lastModifiedTime);
        
        return (m_filePathsToWatch.size() - 1); // Return the index of the element added
    }

    bool FileWatcher::IsFileModified(size_t fileIndex)
    {
        framework::AC_Assert(fileIndex < m_filePathsToWatch.size(), "File index out of range requested from FileWatcher");

        auto time = std::filesystem::last_write_time(m_filePathsToWatch[fileIndex]);
        
        if (time > m_watchFilesLastWriteTime[fileIndex])
        {
            m_watchFilesLastWriteTime[fileIndex] = time;
            return true;
        }
        
        return false;
    }
}