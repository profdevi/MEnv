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

//v1.6 copyright Comine.com 20170511R0939
#ifndef MEnvironTable_h
#define MEnvironTable_h

///////////////////////////////////////////////////
#include <windows.h>
#include "MWinRegKey.h"
#include "MString.h"

//******************************************************
//**  MEnvironTable class
//******************************************************
class MEnvironTable
	{
	////////////////////////////////////////////////
	MWinRegKey mRegistry;
	
	////////////////////////////////////////////////
	void ClearObject(void);
	
	////////////////////////////////////////////////
	public:
	MEnvironTable(void);
	~MEnvironTable(void);
	bool Create(bool systemtable=false,bool readonly=false,bool volatiletable=false);
	bool Destroy(void);
	bool Delete(const char *variable);						// Delete an env var.
	bool Set(const char *variable,const char *value);		// Add/or update envtable
	bool Get(const char *variable,MString &value);			// Get an existing envvalue
	bool Exists(const char *variable,bool casesensitive=true);	// Check if variable exists
	bool GetEntry(int index,MString &name,MString &value);	// Get name/value using index
	bool Expand(const char *input,MString &output);	// Expand the %VAR%
	};

#endif // MEnvironTable_h

