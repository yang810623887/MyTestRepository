#include "tinydirinterface.h"
#include "exception.h"

#ifdef WIN32
#define NOMINMAX // tinydir.h includes windows.h... 
#define WIN32_LEAN_AND_MEAN
#endif // WIN32

#include "..\..\ext\tinydir\tinydir.h"
#include <algorithm>
#include <cerrno>


struct tinydir_dir_hack : tinydir_dir {};

namespace inviwo {

	TinyDirInterface::TinyDirInterface()
		: isOpen_(false)
		, mode_(ListMode::FilesOnly)
		, path_()
	{
		resource_ = std::make_unique<tinydir_dir_hack>();
		memset(resource_.get(), 0, sizeof(tinydir_dir_hack));
	}

	TinyDirInterface::~TinyDirInterface()
	{
		//close();
	}

// 	bool TinyDirInterface::open(const std::string &path)
// 	{
// 		close();
// 
// 		if (path.empty())
// 		{
// 			return false;
// 		}
// 
// 		path_ = path;
// 
// 		int errCode = tinydir_open(resource_.get(), path_.c_str());
// 	}

}
