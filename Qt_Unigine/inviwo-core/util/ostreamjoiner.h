#ifndef IVW_OSTREAMJOINER_H
#define IVW_OSTREAMJOINER_H

#include "../inviwocoredefine.h"

#include <ostream>
#include <iterator>
#include <string>

namespace inviwo {

	namespace util {
		template <class DelimT, class charT = char, class traits = std::char_traits<charT> >

		class ostream_joiner : public std::iterator<std::output_iterator_tag, void, void, void, void>
		{
			std::basic_ostream<charT, traits> *os;
			std::basic_string<charT> delimiter;
			bool need_delimiter = false;

		public:
			using char_type = charT;
			using traits_type = traits;
			using ostream_type = std::basic_ostream<charT, traits>;

			ostream_joiner(ostream_type &s, const DelimT &d)
				: os(&s)
				, delimiter(d)
			{}
			ostream_joiner(ostream_type &s, DelimT &&d)
				:os(&s)
				,delimiter(std::move(d))
			{}

			template <typename T>
			ostream_joiner<DelimT, charT, traits> &operator = (const T &item)
			{
				if (need_delimiter)
				{
					*os << delimiter;
				}
				auto pos = os->tellp();
				*os << item;
				need_delimiter = (os->tellp() != pos);
				return *this;
			}

			ostream_joiner<DelimT, charT, traits> &operator*() { return *this; }
			ostream_joiner<DelimT, charT, traits> &operator++() { return *this; }
			ostream_joiner<DelimT, charT, traits> &operator++(int) { return *this; }
		};

		template <class charT, class traits, class DelimT>
		ostream_joiner<std::decay_t<DelimT>, charT, traits> make_ostream_joiner(std::basic_ostream<charT, traits> &os, DelimT &&delimiter)
		{
			return ostream_joiner<std::decay_t<DelimT>, charT, traits>(os, delimiter);
		}
		
	}
}

#endif
