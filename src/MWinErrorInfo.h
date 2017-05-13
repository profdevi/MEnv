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
#ifndef MWinErrorInfo_h
#define MWinErrorInfo_h

///////////////////////////////////////////////////
#include "MBuffer.h"

///////////////////////////////////////////////////
class MWinErrorInfo
	{
	MBuffer mInfo;
	unsigned int mError;
	
	///////////////////////////////////////////////////
	void ClearObject(void);

	///////////////////////////////////////////////////
	public:
	MWinErrorInfo(bool initialize=false);
	~MWinErrorInfo(void);
	bool Create(void);
	bool Destroy(void);
	bool SetError(void);								// Get the last win32 error 
	bool SetError(unsigned int errorno);				// Set win32 error number
	bool TrimRight(void);								// Remove spaces(tabs newlines) from right of error string
	const char *GetErrorString(void);					// Get the Error String
	unsigned int GetErrorNo(void);
	};

#endif // MWinErrorInfo_h