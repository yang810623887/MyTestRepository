/*********************************************************************************
*
* NameSpace: inviwo-core
* ClassName: fileobserver
* --------------------------------------------------------------------------------
* Versions : v1.0
* Principle: YangYunhe
* Telephone: 15502285265
* email    : 810623887@qq.com
* Edition  : First Edition 2018-8-29 17:29:02
* --------------------------------------------------------------------------------
* DateTime : 2018/08/29
* Copyright (c) 2018 ShenZhouZhiHui. All rights reserved.
* Description:
*
*
 *********************************************************************************/
#ifndef IVW_FILEOBSERVER_H
#define IVW_FILEOBSERVER_H

#include "../inviwocoredefine.h"
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

namespace inviwo {

	class IVW_CORE_API FileObserver
	{
	public:
		FileObserver() = default;
		virtual ~FileObserver() = default;

		void startFileObservation(const std::string& fileName);
		void stopFileObservation(const std::string& fileName);
		std::vector<std::string> getFiles() const;
		bool isObserved(const std::string& fileName) const;

		virtual void fileChanged(const std::string& fileName) = 0;
	private:
		std::unordered_map<std::string, int> observedFiles_; ///< stores the files to be observed

	};
}
#endif