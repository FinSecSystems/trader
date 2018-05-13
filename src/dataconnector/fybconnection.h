///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// <copyright file="fybconnection.h" company="FinSec Systems">
// Copyright (c) 2018 finsec.systems. All rights reserved.
// </copyright>
// <author>Viknash</author>
// <date>12/5/2018</date>
// <summary>FYB Api connection Declaration</summary>
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "api.h"
#include "app.h"
#include "interface.h"
#include "interfacehelper.h"
#include "fyb.h"

namespace trader
{

	class Fyb;

	/// <summary> A fyb connection. </summary>
	class FybConnection : public Interface::CallConnection, public Poco::Runnable
	{
	public:
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary> Initializes a new instance of the FybConnection class. </summary>
		///
		/// <param name="connectionid"> The connectionid. </param>
		/// <param name="_exchange">    [in,out] If non-null, the exchange. </param>
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////
		FybConnection(const std::string &connectionid, Fyb *_exchange)
			: exchange(_exchange)
		{
			(void)connectionid;
		}

		/// <summary> Runs this object. </summary>
		void run() {}

	private:
		Fyb * exchange; ///< The exchange
	};

} // namespace trader
