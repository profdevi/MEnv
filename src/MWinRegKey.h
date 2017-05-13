/*    
    MEnv.exe : Changes environment variable persistantly
    Copyright (C) 2017  Comine.com

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

//v2.1 copyright Comine.com 20150911F0941
#ifndef MWinRegKey_h
#define MWinRegKey_h

////////////////////////////////////////////////////
#include <windows.h>
#include "MString.h"
#include "MBuffer.h"

// Data types are REG_BINARY, REG_DWORD, REG_DWORD_LITTLE_ENDIAN
// REG_DWORD_BIG_ENDIAN  REG_EXPAND_SZ  REG_LINK  REG_MULTI_SZ REG_NONE
// REG_RESOURCE_LIST  REG_SZ

////////////////////////////////////////////////////
class MWinRegKey
	{
	static DWORD mTmpType;
	static DWORD mTmpSize;
	HKEY mKeyHandle;

	//////////////////////////////////////////////
	void ClearObject(void);
	bool CreateNewKey(const char *keyname,HKEY root
			,bool setvolatile,REGSAM access);
	bool OpenExistingKey(const char *keyname,HKEY root
			,REGSAM access);

	////////////////////////////////////////////////
	public:
	MWinRegKey(void);
	~MWinRegKey(void);
	bool Create(bool create			// =true if create a fresh key
			,const char *keyname,HKEY root=HKEY_CURRENT_USER
			,bool setvolatile=true  // =true if key will be gone by shutdown
			,REGSAM access=KEY_READ|KEY_WRITE); // Create/Open Key
	bool Destroy(void);
	HKEY GetKey(void);
	bool SetValueData(const char *name,const char *data);
	bool SetValueDataExpand(const char *name,const char *data);
	bool SetValueData(const char *name,DWORD value);
	bool GetValueData(const char *name,MString &outvalue); // outvalue is a return value
	bool GetValueData(const char *name,DWORD &value);
	bool GetValueData(const char *name,MBuffer &buffer);
	bool DeleteValue(const char *name);
	bool GetValueTypeSize(const char *name,DWORD &type,DWORD &size=mTmpSize);
	bool GetSubKeyName(int index,MString &name);// Keep increasing index until false
	bool GetValueName(int index,MString &name,DWORD &type=mTmpType,DWORD &size=mTmpSize);
	bool DoesNameExist(const char *name);

	/////// Class Methods //////////////////
	static bool Delete(const char *keyname,HKEY root=HKEY_CURRENT_USER);	// fails if child keys exist
	static bool DeleteTree(const char *keyname,HKEY root);					// Recursively delete key
	static bool DoesKeyExist(const char *keyname,HKEY root=HKEY_CURRENT_USER);
	};


#endif // MWinRegKey_h

