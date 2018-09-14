#include "filesystem.h"
#include "exception.h"
#include "tinydirinterface.h"

#include <sys/types.h>
#include <sys/stat.h>

#include <stdio.h>
#include <cctype>

#ifdef WIN32
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <tchar.h>
#include <direct.h>
#include <Shlobj.h>
#elif defined(__APPLE__)
#include <CoreServices/CoreServices.h>
#include <libproc.h>  // proc_pidpath
#include <unistd.h>
#else
#include <unistd.h>
#endif

#include <array>
#include <algorithm>

namespace inviwo {
	namespace filesystem {

		std::string getWorkingDirectory()
		{
			std::array<char, FILENAME_MAX> workingDir;
#ifdef WIN32
			if (!GetCurrentDirectoryA(static_cast<DWORD>(workingDir.size()), workingDir.data()))
			{
				throw Exception("Error querying current directory");
			}
#else
			if (!getcwd(workingDir.data(), workingDir.size()))
				throw Exception("Error querying current directory");
#endif
			return cleanupPath(std::string(workingDir.data()));
		}

		std::string getExecutablePath() {
			std::string retVal;
#ifdef WIN32
			const DWORD maxBufSize = 1 << 20;
			std::vector<char> executablePath(FILENAME_MAX);

			auto size = GetModuleFileNameA(nullptr, executablePath.data(), static_cast<DWORD>(executablePath.size()));

			if (size == 0)
			{
				throw Exception("Error retrieving executable path");
			}
			while (size == executablePath.size())
			{
				auto newSize = executablePath.size() * 2;
				if (newSize > maxBufSize)
				{
					throw Exception("Insufficient buffer size");
				}
				executablePath.resize(newSize);
				size = GetModuleFileNameA(nullptr, executablePath.data(), static_cast<DWORD>(executablePath.size()));
				if (size == 0)
				{
					throw Exception("Error retrieving executable path");
				}
			}

			retVal = std::string(executablePath.data());
#elif __APPLE__
			// http://stackoverflow.com/questions/799679/programatically-retrieving-the-absolute-path-of-an-os-x-command-line-app/1024933#1024933
			std::array<char, PROC_PIDPATHINFO_MAXSIZE> executablePath;
			auto pid = getpid();
			if (proc_pidpath(pid, executablePath.data(), executablePath.size()) <= 0) {
				// Error retrieving path
				throw Exception("Error retrieving executable path");
			}
			retVal = std::string(executablePath.data());
#else  // Linux
			std::array<char, FILENAME_MAX> executablePath;
			auto size = ::readlink("/proc/self/exe", executablePath.data(), executablePath.size() - 1);
			if (size != -1) {
				// readlink does not append a NUL character to the path
				executablePath[size] = '\0';
			}
			else {
				// Error retrieving path
				throw Exception("Error retrieving executable path");
			}
			retVal = std::string(executablePath.data());

			

#endif // WIN32
			return retVal;
		}

		bool fileExists(const std::string& filePath)
		{
			// http://stackoverflow.com/questions/12774207/fastest-way-to-check-if-a-file-exist-using-standard-c-c11-c
			struct stat buffer;
			return (stat(filePath.c_str(), &buffer) == 0);
		}

		bool directoryExists(const std::string& path)
		{
			struct stat buffer;
			// If path contains the location of a directory, it cannot contain a trailing backslash.
			// If it does, -1 will be returned and errno will be set to ENOENT.
			// https://msdn.microsoft.com/en-us/library/14h5k7ff.aspx
			// We therefore check if path ends with a backslash
			if (path.size() > 1 && (path.back() == '/' || path.back() == '\\'))
			{
				std::string pathWithoutSlash = path.substr(0, path.size() - 1);
				return(stat(pathWithoutSlash.c_str(), &buffer) == 0 && (buffer.st_mode & S_IFDIR));
			} 
			else
			{
				// No need to modify path
				return (stat(path.c_str(), &buffer) == 0 && (buffer.st_mode & S_IFDIR));
			}

		}

		IVW_CORE_API std::string getParentFolderWithChildren(const std::string& path, 
															 const std::vector<std::string>& childFolders)
		{
			std::string currentDir = cleanupPath(path);
			size_t pos = currentDir.length();

			do 
			{
				currentDir = currentDir.substr(0, pos);
				bool matchChildFolders = true;
				// check current folder whether it contains all requested child folders
				for (auto it = childFolders.begin(); it != childFolders.end() && matchChildFolders; ++it)
				{
					matchChildFolders = directoryExists(currentDir + '/' + *it);
				}
				if (matchChildFolders)
				{
					return currentDir;
				}
			} while ((pos = currentDir.rfind('/')) != std::string::npos);
		}

		IVW_CORE_API std::string findBasePath()
		{
#if defined(__APPLE__)
			// We might be in a bundle
			// the executable will be in
			//    Inviwo.app/Contents/MacOS/Inviwo
			// and the our base should be
			//    Inviwo.app/Contents/Resources

			CFURLRef appUrlRef =
				CFBundleCopyResourceURL(CFBundleGetMainBundle(), CFSTR("data"), NULL, NULL);
			if (appUrlRef) {
				CFStringRef filePathRef = CFURLCopyPath(appUrlRef);
				const char* filePath = CFStringGetCStringPtr(filePathRef, kCFStringEncodingUTF8);
				std::string macPath(filePath);
				// Release references
				CFRelease(filePathRef);
				CFRelease(appUrlRef);

				if (directoryExists(macPath)) {
					// remove "data"
					auto path = splitString(macPath, '/');
					path.pop_back();
					return joinString(path, "/");
				}
			}
#endif
			// locate Inviwo base path matching the subfolders data/workspaces and modules
			std::string basePath = inviwo::filesystem::getParentFolderWithChildren(
				inviwo::filesystem::getExecutablePath(), {"data/workspaces", "modules"}
			);

			if (basePath.empty())
			{
				// could not locate base path relative to executable, try CMake source path
				if (directoryExists(IVW_TRUNK + "/data/workspaces") &&
					directoryExists(IVW_TRUNK + "/modules"))
				{
					basePath = IVW_TRUNK;
				} 
				else
				{
					throw Exception("Could not locate Inviwo base path");
				}
			} 
			return basePath;
		}

		IVW_CORE_API std::string getPath(PathType pathType, const std::string& suffix /*= ""*/, const bool createFolder /*= false*/)
		{
			std::string result = findBasePath();
			
			switch (pathType)
			{
			case inviwo::PathType::Data:
				result += "/data";
				break;
			case inviwo::PathType::Volumes:
				result += "/data/volumes";
				break;
			case inviwo::PathType::Workspaces:
				result += "/data/workspaces";
				break;
			case inviwo::PathType::Scripts:
				result += "/data/scripts";
				break;
			case inviwo::PathType::PortInspectors:
				result += "/data/workspaces/portinspectors";
				break;
			case inviwo::PathType::Images:
				result += "/data/images";
				break;
			case inviwo::PathType::Databases:
				result += "/data/databases";
				break;
			case inviwo::PathType::Resources:
				result += "/resources";
				break;
			case inviwo::PathType::TransferFunctions:
				result += "/data/transferfunctions";
				break;
			case inviwo::PathType::Settings:
				result = getInviwoUserSettingsPath();
				break;
			case inviwo::PathType::Help:
				result += "/data/help";
				break;
			case inviwo::PathType::Tests:
				result += "/tests";
				break;
			default:
				break;
			}

			if (createFolder)
			{
				createDirectoryRecursively(result);
			}
			return result + suffix;
		}

		IVW_CORE_API void createDirectoryRecursively(std::string path)
		{
			path = cleanupPath(path);
			std::vector<std::string> v = splitString(path, '/');
			std::string pathPart;
#ifdef _WIN32
			pathPart += v.front();
			v.erase(v.begin());
#endif
			while (!v.empty()) {
				pathPart += "/" + v.front();
				v.erase(v.begin());
#ifdef _WIN32
				_mkdir(pathPart.c_str());
#elif defined(__unix__)
				mkdir(pathPart.c_str(), 0755);
#elif defined(__APPLE__)
				mkdir(pathPart.c_str(), 0755);
#else
				LogWarnCustom("", "createDirectoryRecursively is not implemented for current system");
#endif
			}
		}
		// ---------- Helper function to retrieve inviwo settings folder -----------//
#ifdef _WIN32
		static std::string helperSHGetKnownFolderPath(const KNOWNFOLDERID& id) {
			PWSTR path;
			HRESULT hr = SHGetKnownFolderPath(id, 0, nullptr, &path);
			std::string s = "";
			if (SUCCEEDED(hr))
			{
				char ch[1024];
				static const char DefChar = ' ';
				WideCharToMultiByte(CP_ACP, 0, path, -1, ch, 1024, &DefChar, nullptr);
				s = std::string(ch);
			} 
			else
			{
			/*	LogErrorCustom("filesystem::getUserSettingsPath",
					"SHGetKnownFolderPath failed to get settings folder");*/
			}

			CoTaskMemFree(path);
			return s;
		}
#endif

		IVW_CORE_API std::string getInviwoUserSettingsPath()
		{
			std::stringstream ss;
#ifdef _WIN32
			ss << helperSHGetKnownFolderPath(FOLDERID_RoamingAppData);
			ss << "/Inviwo";
#elif defined(__unix__)
			ss << std::getenv("HOME");
			ss << "/.inviwo";
#elif defined(__APPLE__)
			// Taken from:
			// http://stackoverflow.com/questions/5123361/finding-library-application-support-from-c?rq=1
			// A depricated solution, but a solution...

			FSRef ref;
			OSType folderType = kApplicationSupportFolderType;
			int MAX_PATH = 512;
			char path[PATH_MAX];

#include <warn/push>
#include <warn/ignore/deprecated-declarations>
			FSFindFolder(kUserDomain, folderType, kCreateFolder, &ref);
			FSRefMakePath(&ref, (UInt8*)&path, MAX_PATH);
#include <warn/pop>
			ss << path << "/org.inviwo.network-editor";

#else
			LogWarnCustom("", "Get User Setting Path is not implemented for current system");
#endif
			return ss.str();
		}

		IVW_CORE_API std::string cleanupPath(const std::string& path)
		{
			if (path.empty())
			{
				return path;
			}

			std::string result(path);

			// replace backslashes '\' with forward slashes '/'
			std::replace(result.begin(), result.end(), '\\', '/');

			if ((result.size() > 1) && (result.front() == '\"') && (result.back() == '\"'))
			{
				result = result.substr(1, result.size() - 2);
			}
			return result;
		}

	}

}