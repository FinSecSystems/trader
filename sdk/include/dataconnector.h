#pragma once

#if defined(EXPORT_DATACONNECTOR)
#define DATACONNECTOR_DLL __declspec(dllexport)
#elif defined(IMPORT_DATACONNECTOR)
#define DATACONNECTOR_DLL __declspec(dllimport)
#else
#define DATACONNECTOR_DLL
#endif

enum DataConnectorOperation
{
    DC_START = 0
};
