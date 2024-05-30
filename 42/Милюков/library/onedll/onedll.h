// 2019 ReVoL Primer Template
// onedll.h
#include <windows.h>
#pragma once

#ifdef ONEEXPORTS
#define ONEDLLAPI __declspec(dllexport)
#else
#define ONEDLLAPI __declspec(dllimport)
#endif
