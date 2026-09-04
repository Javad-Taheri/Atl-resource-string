#pragma once

template<int Slot>
LPCTSTR LoadStringStatic(UINT id)
{
    thread_local TCHAR buffer[256];
    ::LoadString(nullptr, id, buffer, _countof(buffer));
    return buffer;
}

#define _L1(id) LoadStringStatic<0>(id)
#define _L2(id) LoadStringStatic<1>(id)
#define _L3(id) LoadStringStatic<2>(id)
#define _L4(id) LoadStringStatic<3>(id)
