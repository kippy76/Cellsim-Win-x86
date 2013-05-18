//=======================================================================
// Name        : CellSim.cpp
// Author      : Christopher Walker
// Version     : 1.0
// Copyright   : Christopher Walker
// Description : Cellular automata model of the Dundee iGem 2012 project.
//               http://dundeeigem.blogspot.co.uk
//               http://2012.igem.org/Team:Dundee
// License     : GNU GPL 3.0
//=======================================================================

#include <string>

using namespace std;

class CAException : public exception
{
		string message;

		CAException()
		{
			message = "";
		}

	public:
		CAException(string errorText)
		{
			message = errorText;
		}

		~CAException() throw ()
		{
		}

		virtual const char* what() const throw ()
		{
			if (message.length() == 0)
			{
				return "Error: An unknown error occurred.";
			}
			return &message[0];
		}
};
