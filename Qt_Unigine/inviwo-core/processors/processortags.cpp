#include "processortags.h"
#include "../util/stringconversion.h"
#include "../util/stdextensions.h"

namespace inviwo {

	Tag::Tag() : tag_(""){}

	Tag::Tag(std::string tag) : tag_(tag){}

	Tag::Tag(const Tag& rhs) : tag_(rhs.tag_){}

	Tag& Tag::operator=(const Tag& that)
	{
		if (this != &that)
		{
			tag_ = that.tag_;
		}
		return *this;
	}

	Tag& Tag::operator=(const std::string& that)
	{
		tag_ = that;
		return *this;
	}

	const std::string& Tag::getString() const
	{
		return tag_;
	}

	std::ostream& operator << (std::ostream& os, const inviwo::Tag& obj) {
		os << obj.tag_;
		return os;
	}
	///////////Tags
	Tags::Tags() {}


	Tags::Tags(const std::string tags)
	{
		std::vector<std::string> strings = splitString(tags, ',');
		for (auto& strings_it : strings)
		{
			addTag(Tag(trim(strings_it)));
		}
	}

	Tags::Tags(const char* chartags)
	{
		const std::string tags(chartags);
		std::vector<std::string> strings = splitString(tags, ',');
		for (auto& strings_it : strings)
		{
			addTag(Tag(trim(strings_it)));
		}
	}

	Tags::Tags(const Tags& rhs)
	{
		tags_ = rhs.tags_;
	}

	void Tags::addTag(Tag t)
	{
		if ( !util::contains(tags_, t))
		{
			tags_.push_back(t);
		}
	}

	void Tags::addTags(const Tags &t)
	{
		for (auto& tag : t.tags_)
		{
			addTag(tag);
		}
	}

	size_t Tags::size() const
	{
		return tags_.size();
	}

	bool Tags::empty() const
	{
		return tags_.empty();
	}

	std::string Tags::getString() const
	{
		std::stringstream ss;
		ss << *this;
		return ss.str();
	}

	int Tags::getMatches(const Tags& input) const
	{
		int matches = 0;
		for (auto& elem : input.tags_) {
			for (auto& t : tags_)
			{
				if (elem == t)
				{
					matches++;
				}
			}
		}

		return matches;
	}

	std::ostream& operator<<(std::ostream& os, const Tags& obj) {
		for (std::vector<Tag>::const_iterator it = obj.tags_.begin(); it != obj.tags_.end(); ++it)
		{
			os << *it;
			if (std::distance(it, obj.tags_.end()) > 1)
			{
				os << ", ";
			}
		}
		return os;
	}

	Tags& Tags::operator=(const std::string& that)
	{
		tags_.clear();
		std::vector<std::string> strings = splitString(that, ',');
		for ( auto& strings_it : strings)
		{
			addTag(Tag(trim(strings_it)));
		}
		return *this;
	}

	Tags& Tags::operator=(const Tags& that)
	{
		if (this != &that)
		{
			tags_ = that.tags_;
		}
		return *this;
	}

	const Tags Tags::None("");
	const Tags Tags::GL("GL");
	const Tags Tags::CL("CL");
	const Tags Tags::CPU("CPU");

	namespace util {

		Tags getPlatformTags(const Tags& t)
		{
			Tags result;
			for (auto& tag : t.tags_)
			{
				if (util::contains(Tags::GL.tags_, tag)) {
					result.addTag(tag);
				}
				if (util::contains(Tags::CL.tags_, tag)) {
					result.addTag(tag);
				}
				if (util::contains(Tags::CPU.tags_, tag)) {
					result.addTag(tag);
				}
			}
			return result;
		}

	}

}