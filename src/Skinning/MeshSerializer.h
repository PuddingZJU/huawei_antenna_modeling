#pragma once

#ifndef MeshSerializer_h
#define MeshSerializer_h 
#include <string>
#include <vector>
#include <exception>
#include "SerialTextDataReader.h"

namespace Caca
{
	class Mesh;
	class SubMesh;
	class MeshVertexData;
	class Skeleton;
	
	class MeshSerializer : public SerialTextDataReader 
	{
	public:
		MeshSerializer(void);
		~MeshSerializer(void);

		Mesh* ImportMesh(const std::string filename);
		Mesh* ImportMesh(std::ifstream& input);
		bool ExportMesh(const std::string filename, Mesh *pMesh);
	
		

	protected:

		bool ExpectToken(const std::string token);


		//以下函数都是用于读取OGRE（xml）格式的mesh
		Mesh* LoadMeshFromOGRE(const std::string filename);//throw(MeshSerializerError&)
		void LoadSubMeshesFromOGRE(Mesh *pMesh);//throw(MeshSerializerError&)
		Skeleton* LoadSkeletonFromOGRE(std::string skeletonFilePath);
		void ReadSubMeshDataFromOGRE(SubMesh *pSubMesh);//throw(MeshSerializerError&)
		void ReadFacesFromOGRE(SubMesh *pSubMesh);
		void ReadGeometryFromOGRE(SubMesh *pSubMesh);
		void ReadBoneAssignmentFromOGRE(SubMesh *pSubMesh);
		void ReadSkeletonJointsFromOGRE(Skeleton *pSkeleton);
		void ReadSkeletonJointsHierarchyFromOGRE(Skeleton *pSkeleton);
		std::string NextItem(); 
		std::string ParserFormat1(std::string item);
		std::string ParserFormat2(std::string item);
		void ParserFormat3(std::string source, std::string& attribute, std::string& value);

		//从流中读入mesh
		Mesh* LoadMeshFromOGRE(/*std::ifstream& input*/);
		Skeleton* LoadSkeletonFromOGRE(/*std::ifstream& input*/);

		
	};


	//exception 
	class MeshSerializerError : public std::exception
	{
	public:
		MeshSerializerError(const std::string& msg) : std::exception(msg.c_str()){}
		~MeshSerializerError(){}
	};
}
#endif
