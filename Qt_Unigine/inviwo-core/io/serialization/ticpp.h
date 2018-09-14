#ifndef IVW_TICPP_H
#define IVW_TICPP_H

#ifndef TIXML_USE_TICPP
#  define TIXML_USE_TICPP
#endif

#include "../../../ext/ticpp/ticpp.h"

namespace inviwo {

	typedef ticpp::Document TxDocument;
	typedef ticpp::Element TxElement;
	typedef ticpp::Node TxNode;
	typedef ticpp::Exception TxException;
	typedef ticpp::Declaration TxDeclaration;
	typedef ticpp::Comment TxComment;
	typedef ticpp::Attribute TxAttribute;
	typedef ticpp::Iterator<TxElement> TxEIt;
	typedef ticpp::Iterator<TxAttribute> TxAIt;

} // namespace

#endif // IVW_TICPP_H