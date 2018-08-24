#pragma once
#ifndef IVW_RAIIUTILS_H
#define IVW_RAIIUTILS_H

namespace inviwo {

	namespace util {

		class KeepTrueWhileInScope {

		public:
			KeepTrueWhileInScope(bool* b)
				: variable_(b)
			{
				if (variable_)
					(*variable_) = true;
			}
		private:
			bool* variable_;
		};
	}

}

#endif