#include "stdafx.h"
#include "fyb.h"
#include "app.h"
#include "fybapi.h"
#include "fybconnection.h"
#include "connectionmanager.h"

namespace trader
{

    using namespace FybApi;

	AutoPtr< Interface::Connection > Fyb::getConnection(const std::string &connectionId)
	{
		return new FybConnection(connectionId, new Fyb());
	}

} // namespace trader
