#ifndef SERIALIZABLE_H
#define SERIALIZABLE_H
#pragma once

#include <string>
#include <iostream>

namespace MESSAGES
{

	class Serializable
	{
	public:
		virtual bool SerializeToOstream(std::ostream* output) const = 0;
		virtual bool ParseFromIstream(std::istream* input) = 0;		
	};

}
#endif