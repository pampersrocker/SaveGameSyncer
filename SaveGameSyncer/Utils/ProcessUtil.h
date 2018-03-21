#pragma once

#ifdef Q_OS_WIN
#include "Win32ProcessList.h"

typedef WindowsProcessUtil ProcessUtil;
#else
#error "Not implemented"
#endif