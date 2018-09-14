#include "fileobserver.h"
#include "filesystem.h"
#include "stdextensions.h"
#include "../inviwoapplication.h"

namespace inviwo {

	void FileObserver::startFileObservation(const std::string& fileName)
	{
		auto it = observedFiles_.find(fileName);
		if (it == observedFiles_.end())
		{
			if (filesystem::fileExists(fileName))
			{
				observedFiles_[fileName] = 1;
				//******
			}
		} 
		else
		{
			++(it->second);
		}
	}

}