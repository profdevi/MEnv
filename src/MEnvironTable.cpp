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
#include <windows.h>
#include "MStdLib.h"
#include "MWinRegKey.h"
#include "MString.h"
#include "MBuffer.h"
#include "MEnvironTable.h"


//******************************************************
//**  Module Elements
//******************************************************
static const char *GSystemEnvTable="SYSTEM\\CurrentControlSet\\Control\\Session Manager\\Environment";
static const char *GCurrentUserEnvTable="Environment";
static const char *GCurrentUserVolatileEnvTable="Volatile Environment";


//******************************************************
//**  MEnvironTable class
//******************************************************
void MEnvironTable::ClearObject(void)
	{
	}


////////////////////////////////////////////////
MEnvironTable::MEnvironTable(void)
	{  ClearObject();  }


////////////////////////////////////////////////
MEnvironTable::~MEnvironTable(void)
	{  Destroy();  }


////////////////////////////////////////////////
bool MEnvironTable::Create(bool systemtable,bool readonly,bool volatiletable)
	{
	Destroy();

	HKEY hive=NULL;
	const char *key=NULL;
	if(systemtable==true && volatiletable==false)
		{
		hive=HKEY_LOCAL_MACHINE;
		key=GSystemEnvTable;
		}
	else if(systemtable==false && volatiletable==false)
		{
		hive=HKEY_CURRENT_USER;
		key=GCurrentUserEnvTable;
		}
	else if(systemtable==false && volatiletable==true)
		{
		hive=HKEY_CURRENT_USER;
		key=GCurrentUserVolatileEnvTable;
		}
	else
		{
		Destroy();
		return false;
		}

	// Read Access to tegistry
	REGSAM access;
	if(readonly==true)
		{  access=KEY_READ;  }
	else
		{  access=KEY_READ|KEY_WRITE;  }

	// Check for opening regkey
	if(mRegistry.Create(false,key,hive,false,access)==false)
		{
		Destroy();
		return false;
		}

	//=We have full access to the regestry key

	return true;
	}


////////////////////////////////////////////////
bool MEnvironTable::Destroy(void)
	{
	mRegistry.Destroy();
	ClearObject();
	return true;
	}


////////////////////////////////////////////////
bool MEnvironTable::Delete(const char *variable)		// Delete an env var.
	{
	// It it does not exist, return success
	if(mRegistry.DoesNameExist(variable)==false)
		{ return true; }

	// Delete the variable value
	if(mRegistry.DeleteValue(variable)==false)
		{
		return false;
		}

	return true;
	}


////////////////////////////////////////////////
bool MEnvironTable::Set(const char *variable,const char *value)		// Add/or update envtable
	{
	if(Delete(variable)==false)
		{
		return false;
		}

	if(value==NULL || *value==0) { return true; }

	if(mRegistry.SetValueDataExpand(variable,value)==false)
		{
		return false;
		}

	return true;
	}


////////////////////////////////////////////////
bool MEnvironTable::Get(const char *variable,MString &value)	// Get an existing envvalue
	{
	if(mRegistry.GetValueData(variable,value)==false)
		{
		return false;
		}

	return true;
	}


///////////////////////////////////////////////
bool MEnvironTable::Exists(const char *variable,bool casesensitive)
	{
	MString name;
	for(int i=0;;++i)
		{
		if(mRegistry.GetValueName(i,name)==false) {  return false;  }
		if(casesensitive==true)
			{
			if(MStdStrCmp(name.Get(),variable)==0) { return true; }
			}
		else
			{
			if(MStdStrICmp(name.Get(),variable)==0) { return true; }
			}
		}
	}


/////////////////////////////////////////////////
bool MEnvironTable::GetEntry(int index,MString &name,MString &value)	// Get name/value using index
	{
	if(mRegistry.GetValueName(index,name)==false)
		{  return false; }
	
	// We have a name,
	if(mRegistry.GetValueData(name.Get(),value)==false)
		{
		return false;
		}

	return true;
	}


///////////////////////////////////////////////////////
bool MEnvironTable::Expand(const char *input,MString &output)
	{
	MBuffer tmpbuffer;
	if(tmpbuffer.Create(1024*4)==false)
		{
		return false;
		}

	DWORD ret;
	ret=ExpandEnvironmentStringsA(input,tmpbuffer.GetBuffer()
			,tmpbuffer.GetSize()-1);
	if(ret==0)
		{
		return false;
		}
	
	if(output.Create(tmpbuffer.GetBuffer() )==false)
		{
		return false;
		}

	return true;
	}

