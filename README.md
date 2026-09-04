# ATL Resource String Helper

A small helper for convenient loading of Windows resource strings
in ATL/Win32 applications.

## The problem

The Win32 `LoadString` API requires the caller to provide a buffer:

```cpp
TCHAR buffer[256];

::LoadString(
    nullptr,
    IDS_HELLO,
    buffer,
    _countof(buffer)
);
```

For simple UI code, this can be unnecessarily verbose.
## Proposed usage

```cpp
AddString(_L1(IDS_NAME));
SetWindowText(_L1(IDS_TITLE));
MessageBox(nullptr, _L1(IDS_MESSAGE), _L2(IDS_TITLE), MB_OK);
```

## Why _L1 and _L2?
A single static buffer creates a problem when multiple strings are loaded in the same expression.
For example:
```cpp
MessageBox(nullptr, _L1(IDS_MESSAGE), _L2(IDS_TITLE), MB_OK);
```
If both calls use the same buffer, the second call overwrites the first string.
This project uses independent thread-local buffers for different temporary string slots.

## Example
```cpp
#define _L1(id) LoadStringStatic<0>(id)
#define _L2(id) LoadStringStatic<1>(id)
#define _L3(id) LoadStringStatic<2>(id)
#define _L4(id) LoadStringStatic<3>(id)
```
Usage:
```cpp
MessageBox(nullptr, _L1(IDS_MESSAGE), _L2(IDS_TITLE), MB_OK);
```
## Motivation
The goal is to make localized Win32/ATL code shorter and easier to read while avoiding manual temporary buffers.

## Status
This is a small experimental/helper project and a proposal for a more convenient resource-string API for ATL/Win32.
