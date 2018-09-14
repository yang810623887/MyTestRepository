/*********************************************************************************
*
* NameSpace: inviwo-core
* ClassName: tinydirinterface
* --------------------------------------------------------------------------------
* Versions : v1.0
* Principle: YangYunhe
* Telephone: 15502285265
* email    : 810623887@qq.com
* Edition  : First Edition 2018-8-29 10:10:08
* --------------------------------------------------------------------------------
* DateTime : 2018/08/29
* Copyright (c) 2018 ShenZhouZhiHui. All rights reserved.
* Description:
*
*
 *********************************************************************************/

#ifndef IVW_TINYDIR_INTERFACE_H
#define IVW_TINYDIR_INTERFACE_H

#include "../inviwocoredefine.h"
#include <functional>
#include <string>
#include <vector>
#include <memory>

struct tinydir_dir_hack;

namespace inviwo {

	class IVW_CORE_API TinyDirInterface {
	public:
		enum class ListMode {
			FilesOnly,
			DirectoriesOnly,
			FilesAndDirectories,
		};

		TinyDirInterface();
		TinyDirInterface(TinyDirInterface const&) = delete;
		TinyDirInterface& operator=(TinyDirInterface const&) = delete;

		virtual ~TinyDirInterface();

		/**
		* \brief Opens the given path as directory resource.
		*
		* \see close isOpen
		*
		* @param path Path of the directory whose contents will be queried.
		* @return True if opening the directory resource is successful.
		*/
		bool open(const std::string &path);

		/**
		* \brief Closes any open directory resource. Directory contents can
		* no longer be listed. The resource will automatically be closed on
		* deconstruction of this object.
		*
		* \see open
		*/
		void close();

		/**
		* \brief Returns whether a directory resource is open, i.e. available,
		* for querying.
		*
		* @return True if resource is open. False otherwise.
		*/
		bool isOpen() const;

		/**
		* \brief Set the current mode used for listing the directory.
		*
		* @param mode new listing mode
		*/
		void setListMode(ListMode mode);

		/**
		* \brief Returns the current mode used for listing the directory.
		*
		* @return current listing mode
		*/
		ListMode getListMode() const;

		/**
		* \brief Returns whether the directory resource can be queried for
		* another entry.
		*
		* @return True if directory listing contains at least one entry.
		*/
		bool isNextEntryAvailable() const;

		/**
		* \brief Queries the directory for the next entry. The current ListMode
		*  determines what contents will be returned. An empty string is
		*  returned in case the resource is closed or no further file is available.
		*  Querying the last file automatically closes the directory resource.
		*
		* \see close getNextEntryWithBasePath
		*
		* @return next entry in directory. If none is available or the directory
		*         was not open before, an empty string is returned.
		* @throws FileException
		*/
		std::string getNextEntry();

		/**
		* \brief Convenience function for getNextEntry including the base path.
		*
		* \see close getNextEntry
		*
		* @return next entry in directory. If none is available or the directory
		*         was not open before, an empty string is returned.
		* @throws FileException
		*/
		std::string getNextEntryWithBasePath();

		/**
		* \brief Queries the directory for all entries. The current ListMode
		*  determines what contents will be returned. An empty vector is
		*  returned in case the resource is closed. This function will close
		*  the directory resource.
		*
		* \see close getNextEntry getFileNamesWithBasePath
		*
		* @return directory listing based on ListMode setting.
		* @throws FileException
		*/
		std::vector<std::string> getContents();

		/**
		* \brief Convenience function for getContents including the base path.
		*
		* \see close getNextEntry getContents
		*
		* @return directory listing based on ListMode setting.
		* @throws FileException
		*/
		std::vector<std::string> getContentsWithBasePath();

		protected:
			std::string getNextEntry(bool includeBasePath);

			private:
				bool isOpen_;
				ListMode mode_;
				std::string path_;
				std::unique_ptr<tinydir_dir_hack> resource_;
	};
}

#endif
