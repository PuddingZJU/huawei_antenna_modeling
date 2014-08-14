
#ifndef VERTEXINFO_H
#define VERTEXINFO_H

#include <vector>
#include <string>

namespace Caca
{
	/**
	* Mesh vertex information
	*/
	struct VertexInfo
	{
		bool valid;
		std::string part;
		std::vector<unsigned int> neighbor; 
	};

	typedef std::vector< VertexInfo > MeshVertexInfo;
}



#endif //VERTEXINFO_H