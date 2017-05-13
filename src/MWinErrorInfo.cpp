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

//v2.1 copyright Comine.com 20160328M1345
#include <windows.h>
#include "MStdLib.h"
#include "MBuffer.h"
#include "MWinErrorInfo.h"


//********************************************************
//** Module Elements 
//********************************************************
static const int GMaxErrorSize=2048;

//********************************************************
//** MWinErrorInfo 
//********************************************************
void MWinErrorInfo::ClearObject(void)
	{
	mError=0;
	}

///////////////////////////////////////////////////////////
MWinErrorInfo::MWinErrorInfo(bool initialize)
	{
	ClearObject();
	if(initialize==true && Create()==false)
		{
		return;
		}
	}


/////////////////////////////////////////////////////////
MWinErrorInfo::~MWinErrorInfo(void)
	{  Destroy();  }


/////////////////////////////////////////////////////////
bool MWinErrorInfo::Create(void)
	{
	Destroy();
	if(mInfo.Create(GMaxErrorSize)==false)
		{
		return false;
		}

	mInfo.SetString("");
	return true;
	}


/////////////////////////////////////////////////////////
bool MWinErrorInfo::Destroy(void)
	{
	mInfo.Destroy();
	ClearObject();
	return true;
	}


/////////////////////////////////////////////////////////
bool MWinErrorInfo::SetError(void)
	{
	return SetError(GetLastError() );
	}


/////////////////////////////////////////////////////////
bool MWinErrorInfo::SetError(unsigned int errorno)
	{
	mError=errorno;
	if(FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM,NULL,(DWORD)mError
		,MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),mInfo.GetBuffer()
		,mInfo.GetSize(),0)==0)
		{
		mInfo.SetString("");
		return false;
		}

	return true;
	}


//////////////////////////////////////////////////////////
bool MWinErrorInfo::TrimRight(void)
	{
	MStdStrTrimRight(mInfo.GetBuffer());
	return true;
	}


/////////////////////////////////////////////////////////
const char *MWinErrorInfo::GetErrorString(void)
	{
	return mInfo.GetBuffer();
	}


/////////////////////////////////////////////////////////
unsigned int MWinErrorInfo::GetErrorNo(void)
	{
	return mError;
	}

