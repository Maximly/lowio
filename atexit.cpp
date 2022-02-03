/////////////////////////////////////////////////////////////////
// File: atexit.cpp
// Description:
//   Helper for static class members destructors and global
//   class instances destructors
// Author:  Lyadvinsky M.V.
// Date:    03.12.2000
/////////////////////////////////////////////////////////////////

int
atexit(void(__cdecl *func)(void))
{
 return 0;
}

