// ***********************************************************************
// Assembly         : trader
// Author           : Viknash
// ***********************************************************************
// <copyright file="bittrex.h" >
//     Copyright (c) FinSec Systems. All rights reserved.
// </copyright>
// <summary>
//     Communication interface with the Bittrex exchange
// </summary>
// ***********************************************************************
#pragma once

#include "api.h"
#include "app.h"
#include "interface.h"
#include "interfacehelper.h"
#include "fyb.h"

namespace trader
{

	class Fyb;

	class FybConnection : public Interface::CallConnection, public Poco::Runnable
	{
	public:
		FybConnection(const std::string &connectionid, Fyb *_exchange)
			: exchange(_exchange)
		{
			(void)connectionid;
		}

		void run() {}

	private:
		Fyb * exchange;
	};

} // namespace trader
