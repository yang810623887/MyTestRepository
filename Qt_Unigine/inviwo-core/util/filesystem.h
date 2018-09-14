/*********************************************************************************
*
* NameSpace: inviwo-core
* ClassName: filesystem
* --------------------------------------------------------------------------------
* Versions : v1.0
* Principle: YangYunhe
* Telephone: 15502285265
* email    : 810623887@qq.com
* Edition  : First Edition 2018-8-28 17:30:12
* --------------------------------------------------------------------------------
* DateTime : 2018/08/28
* Copyright (c) 2018 ShenZhouZhiHui. All rights reserved.
* Description:
*
*
 *********************************************************************************/

#ifndef IVW_FILE_SYSTEM_H
#define IVW_FILE_SYSTEM_H

#include "../inviwocoredefine.h"
#include "../inviwo.h"
#include "pathtype.h"
#include <vector>

namespace inviwo {
	namespace filesystem {

		/**
		* Get the working directory of the application.
		*
		* @note getBasePath should be used in the framework in general.
		* @see getBasePath
		* @return Full path to working directory.
		*/
		IVW_CORE_API std::string getWorkingDirectory();

		/**
		* Get full/path/to/executable running the application.
		* @return Full path to the executable if successfull, empty string otherwise.
		*/
		IVW_CORE_API std::string getExecutablePath();

		/**
		* \brief Check if a file exists.
		* @see directoryExists for directories
		* @param std::string fileName The path to the file
		* @return bool True if file exists, false otherwise
		*/
		IVW_CORE_API bool fileExists(const std::string& filePath);

		/**
		* Check if the directory exists
		*
		* @see fileExists for files
		* @param path Directory path
		* @return bool True if directory exists, false otherwise
		*/
		IVW_CORE_API bool directoryExists(const std::string& path);

		enum class ListMode {
			Files,
			Directories,
			FilesAndDirectories,
		};

		/**
		* Returns the file listing of a directory
		*
		* @param path Files are listed for this directory
		* @return List of files residing in the given path
		*/
		IVW_CORE_API std::vector<std::string> getDirectoryContents(const std::string& path,
			ListMode mode = ListMode::Files);

		/**
		* Checks whether a given string matches a pattern. The pattern
		* might contain '*' matching any string including the empty string
		* and '?' matching a single character.
		*
		* @param std::string pattern  The pattern used for matching, might contain '*' and '?'
		* @param std::string str      String which needs to be checked
		* @return True if the given string matches the pattern, false otherwise.
		*/
		IVW_CORE_API bool wildcardStringMatch(const std::string& pattern, const std::string& str);

		/**
		* Checks whether a given string matches a pattern including digits.
		* The pattern might contain a single sequence of '#' for indicating a number
		* besides '*' matching any string including the empty string and '?' matching a
		* single character.
		*
		* The digit sequence indicated by '#' is extracted and returned. Depending on the
		* flags, the number have to exactly match sequence or might be shorter (matchLess)
		* or longer (matchMore). For example, the sequence '###' matches only a three-digit
		* number. Enabling 'matchLess' also matches one-digit and two-digit numbers whereas
		* 'matchMore' allows for numbers with more digits.
		*
		* Examples:
		*  * '###*.jpg' will match all jpeg files starting with a 3-digit sequence. Setting
		*       'matchMore = true' matches the same files, but might extract longer numbers.
		*  * 'myfile#.png' matches all files containing exactly one digit with 'matchMore = false'.
		*
		* @param std::string pattern  The pattern used for matching, might contain a single
		*             sequence of '#' besides '*', and '?'
		* @param std::string str      String which needs to be checked
		* @param int index  if the match is successful, this index contains the extracted
		*             digit sequence indicated by '#'
		* @param bool matchLess   allows to match digit sequences shorter than defined by the number of '#'
		* (default false)
		* @param bool matchMore   allows to match longer digit sequences (default true)
		* @return True if the given string matches the pattern, false otherwise.
		*/
		IVW_CORE_API bool wildcardStringMatchDigits(const std::string& pattern, const std::string& str,
			int& index, bool matchLess = false,
			bool matchMore = true);

		/**
		* Traverses all parent folders of path and returns the first directory matching the list of child
		* folders.
		*
		* @param path   directory where the search is started
		* @param childFolders   list of subfolders
		* @return path of parent directory holding all childFolders, otherwise empty string
		*/
		IVW_CORE_API std::string getParentFolderWithChildren(const std::string& path,
			const std::vector<std::string>& childFolders);

		/**
		* Find Inviwo base path which contains subfolders "data/workspaces" and "modules"
		*
		* @return Inviwo base path
		* @throws exception in case base path could not be located
		*/
		IVW_CORE_API std::string findBasePath();

		/**
		* Get basePath +  pathType + suffix.
		* @see PathType
		* @param pathType Enum for type of path
		* @param suffix Path extension
		* @return basePath +  pathType + suffix
		*/
		IVW_CORE_API std::string getPath(PathType pathType, const std::string& suffix = "",
			const bool createFolder = false);

		IVW_CORE_API void createDirectoryRecursively(std::string path);

		/**
		* Get inviwo settings folder for current user
		* Will for instance be AppData/Inviwo/ on windows.
		*
		* @return std::string Inviwo user settings folder
		*/
		IVW_CORE_API std::string getInviwoUserSettingsPath();

		/**
		* \brief Adds the InviwoApplication base path before the url
		*
		* @see InviwoApplication::getBasePath
		* @param const std::string url Relative path
		* @return std::string InviwoApplication base path + url
		*/
		IVW_CORE_API std::string addBasePath(const std::string& url);

		IVW_CORE_API std::string getFileDirectory(const std::string& url);
		IVW_CORE_API std::string getFileNameWithExtension(const std::string& url);
		IVW_CORE_API std::string getFileNameWithoutExtension(const std::string& url);
		IVW_CORE_API std::string getFileExtension(const std::string& url);

		/**
		* Replace the last file extension to newFileExtension, if no extension exists append
		* newFileExtension. newFileExtension should not contain any leading "."
		*/
		IVW_CORE_API std::string replaceFileExtension(const std::string& url,
			const std::string& newFileExtension);

		/**
		*	\brief Make a path relative to basePath.
		* Requirement: basePath and absulutePath has to be absolute paths.
		* basePath should point at directory.
		*
		* Example:
		* basePath = "C:/foo/bar"
		* absolutePath = "C:/foo/test/file.txt"
		* returns "../test/file.txt"
		*/
		IVW_CORE_API std::string getRelativePath(const std::string& basePath,
			const std::string& absolutePath);
		IVW_CORE_API std::string getCanonicalPath(const std::string& url);

		IVW_CORE_API bool isAbsolutePath(const std::string& path);

		/**
		* \brief Checks whether the second path is on the same drive as the first path
		*
		* If both paths are relative, this function returns true. If only refPath is relative
		* InviwoApplication::getBasePath is used instead as reference.
		*
		* @param const std::string& refPath reference path, if relative then InviwoApplication::getBasePath
		* is used instead
		* @param const std::string& queryPath path to be checked
		* @return true if queryPath and refPath are located on the same drive (on Windows), always true on
		* all other systems
		*/
		IVW_CORE_API bool sameDrive(const std::string& refPath, const std::string& queryPath);

		/**
		* \brief clean up path by replacing backslashes with forward slash and removing surrounding quotes
		*
		* @param const std::string& path given path to be cleaned up
		* @return non-quoted path containing no backslashes as directory separators
		*/
		IVW_CORE_API std::string cleanupPath(const std::string& path);
	}

}

#endif
