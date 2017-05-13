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

//v1.3 copyright Comine.com 20170511R0936
#include "MStdLib.h"
#include "MCommandArg.h"
#include "MLicenseGPL.h"
#include "MEnvironTable.h"


//******************************************************
//* Module Elements
//******************************************************
static const char *GApplicationName="MEnv";			// Used in Help
static const char *GApplicationVersion="1.3";		// Used in Help


////////////////////////////////////////////////////
static void GDisplayHelp(void);
static void GDisplayTable(MEnvironTable &table);
static void GDisplayTableVariable(MEnvironTable &table,const char *variable);
static void GSetTableVariable(MEnvironTable &table,const char *var,const char *value);
static void GDisplayEnvironBlock(void);


////////////////////////////////////////////////////
int main(int argn,const char *argv[])
	{
	MCommandArg args(argn,argv);
	if(args.CheckRemoveHelp()==true)
		{
		GDisplayHelp();
		return 0;
		}

	if(args.CheckRemoveArg("-gpl")==true)
		{
		MLicenseGPL lic(true);
		lic.Print();
		return 0;
		}

	if(args.CheckRemoveArg("-l")==true)
		{
		GDisplayEnvironBlock();
		return 0;
		}

	// System Flag
	bool systemflag=false;
	if(args.CheckRemoveArg("-s")==true) {  systemflag=true; }

	// kill flag
	bool killflag=false;
	if(args.CheckRemoveArg("-r")==true) { killflag=true;  }

	// setflag
	bool setflag=false;
	if(args.CheckRemoveArg("-a")==true) { setflag=true;  }

	MEnvironTable table;
	if(table.Create(systemflag,killflag==false && setflag==false)==false)
		{
		MStdPrintf("*Unable to init system\n");
		return 1;
		}

	// Check for -kill
	if(killflag==true && args.GetArgCount()==2)
		{
		if(table.Delete(args.GetArg(1))==false)
			{	
			MStdPrintf("%-30s: *failed\n",args.GetArg(1) );
			return 1;
			}

		MStdPrintf("%-30s: deleted\n",args.GetArg(1) );	
		return 0;
		}

	// Check for add
	if(setflag==true && args.GetArgCount()==3 )
		{
		if(table.Set(args.GetArg(1),args.GetArg(2))==false)
			{
			MStdPrintf("*Unable to set env variable %s\n",args.GetArg(1));
			return 1;
			}

		MStdPrintf("Added %s\n",args.GetArg(1));

		return 0;
		}

	//=We will print out all values
	if(args.GetArgCount()==1)
		{
		GDisplayTable(table);
		return 0;
		}

	int i;
	for(i=1;i<args.GetArgCount();++i)
		{  GDisplayTableVariable(table,args.GetArg(i) );  }

	return 0;
	}


////////////////////////////////////////////////////
static void GDisplayHelp(void)
	{
	MStdPrintf(
			"\n"
			"   usage  :   %s [-s] <-r <var> |-a <var> <value> > [-?|-gpl]\n"
			"              v%s copyright Comine.com\n"
			"           use -gpl to display GPL license\n"
			"\n"
			"     Sets the user environment variable with given value\n"
			"\n"
			"   options:\n"
			"       -s               :  Will set global environmental variable\n"
			"       -r <var>         :  Deletes given variable\n"
			"       -a <var> <value> :  Adds given variable\n"
			"       -l               :  Display Local Process Environ table\n"
			"\n"
			,GApplicationName,GApplicationVersion);
	}


////////////////////////////////////////////////////
static void GDisplayTable(MEnvironTable &table)
	{
	int index;
	for(index=0;  ;index=index+1)
		{
		MString name,value;
		if(table.GetEntry(index,name,value)==false) { break; }
		MStdPrintf("%s=%s\n",name.Get(),value.Get());
		}
	}


////////////////////////////////////////////////////
static void GDisplayTableVariable(MEnvironTable &table,const char *variable)
	{
	MString value;
	if(table.Get(variable,value)==false) { return; }
	MStdPrintf("%s=%s\n",variable,value.Get() );
	}


/////////////////////////////////////////////////////
static void GSetTableVariable(MEnvironTable &table,const char *var,const char *value)
	{
	if(table.Set(var,value)==false)
		{
		MStdPrintf("*Unable to set env variable %s\n",var);
		return;
		}
	}


//////////////////////////////////////////////////////
static void GDisplayEnvironBlock(void)
	{
	extern char **environ;
	int i;
	for(i=0;environ[i]!=NULL;++i)
		{
		MStdPrintf("%s\n",environ[i]);
		}
	}

