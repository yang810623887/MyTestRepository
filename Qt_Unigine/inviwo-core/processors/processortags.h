/*********************************************************************************
*
* NameSpace: inviwo-core
* ClassName: processortags
* --------------------------------------------------------------------------------
* Versions : v1.0
* Principle: YangYunhe
* Telephone: 15502285265
* email    : 810623887@qq.com
* Edition  : First Edition 2018-8-30 16:44:33
* --------------------------------------------------------------------------------
* DateTime : 2018/08/30
* Copyright (c) 2018 ShenZhouZhiHui. All rights reserved.
* Description:
*
*
 *********************************************************************************/
#ifndef IVW_PROCESSORTAGS_H
#define IVW_PROCESSORTAGS_H

#include "../inviwocoredefine.h"
#include "../inviwo.h"

namespace inviwo {

	class IVW_CORE_API Tag
	{
	public:
		Tag();
		Tag(std::string tag);
		Tag(const Tag& rhs);
		Tag& operator=(const Tag& that);
		Tag& operator=(const std::string& that);

		virtual ~Tag() = default;

		const std::string& getString() const;

		friend std::ostream& operator << (std::ostream& os, const inviwo::Tag& obj);

	private:
		std::string tag_;
	};

	inline bool operator==(const Tag& lhs, const Tag& rhs) {
		return lhs.getString() == rhs.getString();
	}
	inline bool operator< (const Tag& lhs, const Tag& rhs) {
		return lhs.getString() < rhs.getString();
	}
	inline bool operator!=(const Tag& lhs, const Tag& rhs) { return !operator==(lhs, rhs); }
	inline bool operator> (const Tag& lhs, const Tag& rhs) { return  operator< (rhs, lhs); }
	inline bool operator<=(const Tag& lhs, const Tag& rhs) { return !operator> (lhs, rhs); }
	inline bool operator>=(const Tag& lhs, const Tag& rhs) { return !operator< (lhs, rhs); }

	class IVW_CORE_API Tags {
	public:
		Tags();
		Tags(const std::string tags);
		Tags(const char* tags);
		Tags(const Tags& rhs);
		Tags& operator=(const Tags& that);
		Tags& operator=(const std::string& that);

		virtual ~Tags() = default;

		void addTag(Tag);
		void addTags(const Tags &t);

		size_t size() const;
		bool empty() const;

		std::string getString() const;

		int getMatches(const Tags&) const;

		friend std::ostream& operator << (std::ostream& os, const inviwo::Tags& obj);
		friend bool operator==(const Tags& lhs, const Tags& rhs);
		friend bool operator< (const Tags& lhs, const Tags& rhs);

		std::vector<Tag> tags_;

		// pre-defined platform tags
		static const Tags None;
		static const Tags GL;
		static const Tags CL;
		static const Tags CPU;
	};

	inline bool operator==(const Tags& lhs, const Tags& rhs) {
		return lhs.tags_ == rhs.tags_;
	}
	inline bool operator< (const Tags& lhs, const Tags& rhs) {
		return lhs.tags_ < rhs.tags_;
	}
	inline bool operator!=(const Tags& lhs, const Tags& rhs) { return !operator==(lhs, rhs); }
	inline bool operator> (const Tags& lhs, const Tags& rhs) { return  operator< (rhs, lhs); }
	inline bool operator<=(const Tags& lhs, const Tags& rhs) { return !operator> (lhs, rhs); }
	inline bool operator>=(const Tags& lhs, const Tags& rhs) { return !operator< (lhs, rhs); }

	namespace util {

		Tags IVW_CORE_API getPlatformTags(const Tags& t);

	} // namespace util
}
#endif