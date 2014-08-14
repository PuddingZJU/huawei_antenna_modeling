
#include "MeshSerializer.h"
#include "Mesh.h"
#include "SubMesh.h"
#include "Skeleton.h"
#include "MeshVertexData.h"
#include <fstream>
#include <sstream>
#include <errno.h>
using namespace std;
using namespace Caca;

MeshSerializer::MeshSerializer(void)
{
}

MeshSerializer::~MeshSerializer(void)
{
	m_pstream = NULL;
}


/** import the mesh from file
 * 
 * @param filename the mesh file
 * 
 * @return a mesh object if it is loaded successully,otherwise return null
 */
Mesh* MeshSerializer::ImportMesh(const string filename)
{
	Mesh *pMesh;
	
	try
	{
		pMesh = LoadMeshFromOGRE(filename);   
		pMesh->ComputerMeshVertexLocalCoord();
	}
	catch(MeshSerializerError& /*e*/)
	{
		//AfxMessageBox(e.what());
		throw;
		//return NULL;
	}

	return pMesh;
}


bool MeshSerializer::ExpectToken(const string token)
{
	return checkToken(token);
}


bool  MeshSerializer::ExportMesh(const string filename, Mesh *pMesh)
{
	/*try
	{
		StoreMeshToOwn(filename,pMesh);
	}
	catch(MeshSerializerError& e)
	{
		AfxMessageBox(e.what());
		return false;
	}*/
	return true;
}


/**Load mesh from OGRE xml mesh file
 *
 * @param filename the mesh file
 * 
 * @return a mesh object if it is loaded successully,otherwise throw a exception
 */
Mesh* MeshSerializer::LoadMeshFromOGRE(const string filename)
{
	//读取mesh文件信息
	ifstream input(filename.c_str());
	
	if(input.fail())
	{	
		throw MeshSerializerError("Open Mesh File failed");
	}

	//file is open successfully
	this->m_pstream = &input;  //...
	this->fillBuf();

	Mesh* pMesh = new Mesh; //create a new mesh object
	string skeletonFilePath;//骨架文件路径，他存放在Mesh文件中

	//读取Mesh数据
	try
	{
		if(NextItem() != "<mesh>")
			throw MeshSerializerError("Not a valida OGRE mesh xml format:<mesh></mesh>");

		LoadSubMeshesFromOGRE(pMesh); //load submeshes
	
		//读取skeleton文件路径
		string item = NextItem();
		string datastr = ParserFormat2(item);
		istringstream is(datastr);
		string word1,word2;
		is>>word1>>word2;
		if(is.fail() || word1 != "skeletonlink")
			throw MeshSerializerError("Not a valida OGRE mesh xml format:<skeletonlink .../>");
		string attribute,value; 
		ParserFormat3(word2,attribute,value);
		if(attribute != "name")
			throw MeshSerializerError("Not a valida OGRE mesh xml format:<skeletonlink .../>");

		skeletonFilePath = value;

		/////
		if(NextItem() != "</mesh>")
			throw MeshSerializerError("Not a valida OGRE mesh xml format:<mesh></mesh>");
	}
	catch(MeshSerializerError& e)
	{
		delete pMesh;
		input.close();
		throw e;
	}

	input.close();

	//读取骨架数据
	try
	{
		pMesh->m_pSkeleton = LoadSkeletonFromOGRE(skeletonFilePath);
	}
	catch(MeshSerializerError& e)
	{
		delete pMesh;
		throw e;
	}

	return pMesh;
}


/** load the skeleton from the OGRE xml file
 *
 * @param skeletonFilePath the skeleton file path
 *
 * @return a skeleton object if successful,otherwise throw exception
 */
Skeleton* MeshSerializer::LoadSkeletonFromOGRE(std::string skeletonFilePath)
{
	//clear m_pstream & m_pLine
	if (m_pLine)
	{
		delete m_pLine;
	}
	m_pLine = NULL;
	m_pstream = NULL;

	ifstream input(skeletonFilePath.c_str());
	
	if(input.fail())
	{	
		throw MeshSerializerError("Open Skeleton File failed");
	}

	//file is open successfully
	this->m_pstream = &input;  //...
	this->fillBuf();

	Skeleton *pSkeleton = new Skeleton;

	try
	{
		if(NextItem() != "<skeleton>")
			throw MeshSerializerError("Not a valida OGRE mesh skeleton format:<skeleton></skeleton>");

		ReadSkeletonJointsFromOGRE(pSkeleton);  //read skeleton joints
		ReadSkeletonJointsHierarchyFromOGRE(pSkeleton); //read Joints Hierarchy
	
		if(NextItem() != "</skeleton>")
			throw MeshSerializerError("Not a valida OGRE mesh skeleton format:<skeleton></skeleton>");
	}
	catch(MeshSerializerError& e)
	{
		delete pSkeleton;
		throw e;
	}
	
	return pSkeleton;
}

/** read skeleton joints
 *
 */
void MeshSerializer::ReadSkeletonJointsFromOGRE(Skeleton *pSkeleton)
{
	if(NextItem() != "<bones>")
		throw MeshSerializerError("Not a valida OGRE mesh skeleton format:<bones></bones>");

	string item,datastr;
	string word1,word2,word3,word4;
	string attribute,value;		
	istringstream is;

	item = NextItem();
	datastr = ParserFormat1(item); 
	is.str(datastr);
	is>>word1;

	while(word1 == "bone")
	{
		is>>word2>>word3;
		if(is.fail())
			throw MeshSerializerError("Not a valida OGRE mesh skeleton format:<bone ...>");

		string name;
		int idx;
		Vector3 pos;
		double angle;  //单位为弧度
		Vector3 axis;  //旋转轴 

		//idx
		ParserFormat3(word2,attribute,value);
		idx = atoi(value.c_str());
		if(attribute != "id" || errno == EINVAL)
			throw MeshSerializerError("Not a valida OGRE mesh skeleton format:<bone ...>");
			
		//name
		ParserFormat3(word3,attribute,value);
		if(attribute != "name" || errno == EINVAL)
			throw MeshSerializerError("Not a valida OGRE mesh skeleton format:<bone ...>");
		name = value;

		//position relative to parent
		item = NextItem();
		datastr = ParserFormat2(item);
		is.str(datastr);
		is.clear();
			
		is>>word1>>word2>>word3>>word4;
		if(is.fail() || word1 != "position")
			throw MeshSerializerError("Not a valida OGRE mesh skeleton format:<bone ...><position/>");

		//x
		ParserFormat3(word2,attribute,value);
		pos.x = atof(value.c_str());
		if(attribute != "x" || errno == EINVAL)
			throw MeshSerializerError("Not a valida OGRE mesh skeleton format:<bone ...><position/>");

		//y
		ParserFormat3(word3,attribute,value);
		pos.y = atof(value.c_str());
		if(attribute != "y" || errno == EINVAL)
			throw MeshSerializerError("Not a valida OGRE mesh skeleton format:<bone ...><position/>");

		//z
		ParserFormat3(word4,attribute,value);
		pos.z = atof(value.c_str());
		if(attribute != "z" || errno == EINVAL)
			throw MeshSerializerError("Not a valida OGRE mesh skeleton format:<bone ...><position/>");

		//rotation relative to parent
		item = NextItem();
		datastr = ParserFormat1(item);
		is.str(datastr);
		is.clear();

		//angle
		is>>word1>>word2;
		if(is.fail() || word1 != "rotation")
			throw MeshSerializerError("Not a valida OGRE mesh skeleton format:<bone ...><rotation/>");

		ParserFormat3(word2,attribute,value);
		angle = atof(value.c_str());
		if(attribute != "angle" || errno == EINVAL)
			throw MeshSerializerError("Not a valida OGRE mesh skeleton format:<bone ...><rotation/>");

		//axis
		item = NextItem();
		datastr = ParserFormat2(item);
		is.str(datastr);
		is.clear();

		is>>word1>>word2>>word3>>word4;
		if(is.fail() || word1 != "axis")
			throw MeshSerializerError("Not a valida OGRE mesh skeleton format:<bone ...><rotation/>");

		ParserFormat3(word2,attribute,value);
		axis.x = atof(value.c_str());
		if(attribute != "x" || errno == EINVAL)
			throw MeshSerializerError("Not a valida OGRE mesh skeleton format:<bone ...><rotation/>");

		ParserFormat3(word3,attribute,value);
		axis.y = atof(value.c_str());
		if(attribute != "y" || errno == EINVAL)
			throw MeshSerializerError("Not a valida OGRE mesh skeleton format:<bone ...><rotation/>");

		ParserFormat3(word4,attribute,value);
		axis.z = atof(value.c_str());
		if(attribute != "z" || errno == EINVAL)
			throw MeshSerializerError("Not a valida OGRE mesh skeleton format:<bone ...><rotation/>");

		if(NextItem() != "</rotation>")
			throw MeshSerializerError("Not a valida OGRE mesh skeleton format:<rotation></rotation>");

		if(NextItem() != "</bone>")
			throw MeshSerializerError("Not a valida OGRE mesh skeleton format:<bones></bones>");

		Joint j;
		j.name = name;
		j.pos = pos;
		j.rotateAngle = angle;
		j.rotateAxis = axis;
		j.parent = -1; 

		pSkeleton->AddJoint(j);

		item = NextItem();
		datastr = ParserFormat1(item); 
		is.str(datastr);
		is.clear();
		is>>word1;
	}
			
	if(item != "</bones>")
		throw MeshSerializerError("Not a valida OGRE mesh skeleton format:<bones></bones>");
}


/** read Joints Hierarchy
 */
void MeshSerializer::ReadSkeletonJointsHierarchyFromOGRE(Skeleton *pSkeleton)
{
	if(NextItem() != "<bonehierarchy>")
		throw MeshSerializerError("Not a valida OGRE mesh skeleton format:<bonehierarchy></bonehierarchy>");

	string item,datastr;
	string word1,word2,word3;
	istringstream is;
	string attribute,value;
	string child,parent;

	for(int i = 0; i < pSkeleton->GetJointsCount()-1; ++i) //hip 没有父节点
	{
		item = NextItem();
		datastr = ParserFormat2(item);
		is.str(datastr);
		is.clear();

		is>>word1>>word2>>word3;
		if(is.fail() || word1 != "boneparent")
			throw MeshSerializerError("Not a valida OGRE mesh skeleton format:<boneparent.../>");

		ParserFormat3(word2,attribute,value);
		if(attribute != "bone")
			throw MeshSerializerError("Not a valida OGRE mesh skeleton format:<boneparent.../>");
		child = value;

		ParserFormat3(word3,attribute,value);
		if(attribute != "parent")
			throw MeshSerializerError("Not a valida OGRE mesh skeleton format:<boneparent.../>");
		parent = value;

		int childIdx, parentIdx;
		childIdx = pSkeleton->GetJointIndexByName(child);
		parentIdx = pSkeleton->GetJointIndexByName(parent);

		if(childIdx == -1 || parentIdx == -1)
			throw MeshSerializerError("Not a valida OGRE mesh skeleton format:<boneparent.../>");

		pSkeleton->SetParent(childIdx,parentIdx);
	}

	if(NextItem() != "</bonehierarchy>")
		throw MeshSerializerError("Not a valida OGRE mesh skeleton format:<bonehierarchy></bonehierarchy>");
}


/** load the submeshes from the file
 */
void MeshSerializer::LoadSubMeshesFromOGRE(Mesh *pMesh)
{
	SubMesh *pSubMesh = NULL;

	try
	{
		if(NextItem() != "<submeshes>")
			throw MeshSerializerError("Not a valid OGRE mesh xml format:<submeshes></submeshes>");

		string item;
		string datastr;

		item = NextItem();  
		datastr = ParserFormat1(item);
		istringstream is(datastr);

		string word1,word2,word3,word4,word5;
		
		is>>word1;
		if(is.fail())
			throw MeshSerializerError("Not a valid OGRE mesh xml format: ");
		
		while(word1 == "submesh") //读取一个submesh
		{
			pSubMesh = new SubMesh();

			is>>word2>>word3>>word4>>word5;
			if(is.fail())
				throw MeshSerializerError("Not a valid OGRE mesh xml format: ");


			ReadSubMeshDataFromOGRE(pSubMesh);
			pMesh->AddSubMesh(pSubMesh);

			if(NextItem() != "</submesh>")
				throw MeshSerializerError("Not a valid OGRE mesh xml format:<submesh></submesh>");
			
			//read next item
			item = NextItem(); 
			datastr = ParserFormat1(item);
			is.str(datastr);
			is.clear();

			is>>word1;
			if(is.fail())
				throw MeshSerializerError("Not a valid OGRE mesh xml format: ");
		}

		if(item != "</submeshes>")
			throw MeshSerializerError("Not a valida OGRE mesh xml format:<submeshes></submeshes>");
	}
	catch(MeshSerializerError& e)
	{
		if(pSubMesh)
		{
			pMesh->DeleteSubMesh(pSubMesh);
			delete pSubMesh;
		}
		throw e;
	}
}


/** read the  submesh's data
 */
void MeshSerializer::ReadSubMeshDataFromOGRE(SubMesh *pSubMesh)
{
	try
	{
		ReadFacesFromOGRE(pSubMesh);  //faces
		ReadGeometryFromOGRE(pSubMesh);  //geometry
		ReadBoneAssignmentFromOGRE(pSubMesh); //bone assignments
	}
	catch(MeshSerializerError& e)
	{
		throw e;
	}
}


/** 读入三角面片信息
 */
void MeshSerializer::ReadFacesFromOGRE(SubMesh *pSubMesh)
{
	string item = NextItem();
	string datastr = ParserFormat1(item);
	istringstream is(datastr);

	string word1,word2,word3,word4,word5,word6;
	
	is>>word1>>word2;
	if(is.fail() || word1 != "faces")
		throw MeshSerializerError("Not a valida OGRE mesh xml format: <faces count></faces>");

	string attribute,value;
	ParserFormat3(word2,attribute,value);

	int facecount = atoi(value.c_str()); //face count;
	if(attribute != "count" || errno == EINVAL)
		throw MeshSerializerError("Not a valida OGRE mesh xml format: <faces count></faces>");
	
	pSubMesh->AllocatePatchList(facecount);

	//读入面的点索引
	for(int i = 0; i < facecount; ++i)
	{
		item = NextItem();
		datastr = ParserFormat2(item);
		is.str(datastr);
		is.clear();	//clear the error flag
	
		is>>word1>>word2>>word3>>word4;
		if(is.fail() || word1 != "face")
			throw MeshSerializerError("Not a valida OGRE mesh xml format: <face v1 v2 v3/>");
	
		int v1,v2,v3;
		
		ParserFormat3(word2,attribute,value);
		v1 = atoi(value.c_str());
		if(attribute != "v1" || errno == EINVAL)
			throw MeshSerializerError("Not a valida OGRE mesh xml format: <face v1 v2 v3/>");

		ParserFormat3(word3,attribute,value);
		v2 = atoi(value.c_str());
		if(attribute != "v2" || errno == EINVAL)
			throw MeshSerializerError("Not a valida OGRE mesh xml format: <face v1 v2 v3/>");

		ParserFormat3(word4,attribute,value);
		v3 = atoi(value.c_str());
		if(attribute != "v3" || errno == EINVAL)
			throw MeshSerializerError("Not a valida OGRE mesh xml format: <face v1 v2 v3/>");

		Patch p;
		p.vertexIndexOne = v1;
		p.vertexIndexTwo = v2;
		p.vertexIndexThree = v3;

		//pSubMesh->SetPatch(i,p);

	}

	if(NextItem() != "</faces>")
		throw MeshSerializerError("Not a valida OGRE mesh xml format: <faces count></faces>");
	
}


//读入顶点数据
void MeshSerializer::ReadGeometryFromOGRE(SubMesh *pSubMesh)
{
	string item,datastr;
	string word1,word2,word3,word4,word5,word6;
	string attribute,value;
	istringstream is;
	
	item = NextItem();
	datastr = ParserFormat1(item);
	is.str(datastr);
	is.clear();

	is>>word1>>word2;
	if(is.fail() || word1 != "geometry")
			throw MeshSerializerError("Not a valida OGRE mesh xml format: <geometry vertexcount></geometry>");
	
	ParserFormat3(word2,attribute,value);
	int vertexcount = atoi(value.c_str());
	if(attribute != "vertexcount" || errno == EINVAL)
		throw MeshSerializerError("Not a valida OGRE mesh xml format: <geometry vertexcount></geometry>");

	pSubMesh->AllocateVertexBuffer(vertexcount);

	item = NextItem();
	datastr = ParserFormat1(item);
	is.str(datastr);
	is.clear();

	//几何顶点数据的格式
	bool has_position,has_normal,has_colordiffuse,has_colorspecular;
	int texturenum;

	is>>word1>>word2>>word3>>word4>>word5>>word6;
	if(is.fail() || word1 != "vertexbuffer")
		throw MeshSerializerError("Not a valida OGRE mesh xml format: <vertexbuffer ...></vertexbuffer>");

	//has positions?
	ParserFormat3(word2,attribute,value);
	if(attribute != "positions" || (value != "true" && value != "false"))
		throw MeshSerializerError("Not a valida OGRE mesh xml format: <vertexbuffer...>");
	if(value == "true")
		has_position = true;
	else
		has_position = false;

	//has normals?
	ParserFormat3(word3,attribute,value);
	if(attribute != "normals" || (value != "true" && value != "false"))
		throw MeshSerializerError("Not a valida OGRE mesh xml format: <vertexbuffer...>");
	if(value == "true")
		has_normal = true;
	else
		has_normal = false;

	//has color diffuse?
	ParserFormat3(word4,attribute,value);
	if(attribute != "colours_diffuse" || (value != "true" && value != "false"))
		throw MeshSerializerError("Not a valida OGRE mesh xml format: <vertexbuffer...>");
	if(value == "true")
		has_colordiffuse = true;
	else
		has_colordiffuse = false;

	//has color colorspecular
	ParserFormat3(word5,attribute,value);
	if(attribute != "colours_specular" || (value != "true" && value != "false"))
		throw MeshSerializerError("Not a valida OGRE mesh xml format: <vertexbuffer...>");
	if(value == "true")
		has_colorspecular = true;
	else
		has_colorspecular = false;

	//texture num
	ParserFormat3(word6,attribute,value);
	texturenum = atoi(value.c_str());
	if(attribute != "texture_coords" || errno == EINVAL)
		throw MeshSerializerError("Not a valida OGRE mesh xml format: <vertexbuffer...>");
	
	for(int i = 0; i < vertexcount; ++i)
	{
		if(NextItem() != "<vertex>")
			throw MeshSerializerError("Not a valida OGRE mesh xml format: <vertex></vertex>");

		if(has_position)
		{
			//position
			item = NextItem();
			datastr = ParserFormat2(item);
			is.str(datastr);
			is.clear();
	
			is>>word1>>word2>>word3>>word4;
			if(is.fail() || word1 != "position")
				throw MeshSerializerError("Not a valida OGRE mesh xml format: <position .../>");

			Vector3 pos;
			ParserFormat3(word2,attribute,value);
			pos.x = atof(value.c_str());
			if(attribute != "x" || errno == EINVAL)
				throw MeshSerializerError("Not a valida OGRE mesh xml format: <position .../>");

			ParserFormat3(word3,attribute,value);
			pos.y = atof(value.c_str());
			if(attribute != "y" || errno == EINVAL)
				throw MeshSerializerError("Not a valida OGRE mesh xml format: <position .../>");

			ParserFormat3(word4,attribute,value);
			pos.z = atof(value.c_str());
			if(attribute != "z" || errno == EINVAL)
				throw MeshSerializerError("Not a valida OGRE mesh xml format: <position .../>");
			
			pSubMesh->SetVertexPos(i,pos);
		}

		if(has_normal)
		{
			//normal
			item = NextItem();
			datastr = ParserFormat2(item);
			is.str(datastr);
			is.clear();

			is>>word1>>word2>>word3>>word4;
			if(is.fail() || word1 != "normal")
				throw MeshSerializerError("Not a valida OGRE mesh xml format: <normal .../>");

			Vector3 normal;
			ParserFormat3(word2,attribute,value);
			normal.x = atof(value.c_str());
			if(attribute != "x" || errno == EINVAL)
				throw MeshSerializerError("Not a valida OGRE mesh xml format: <position .../>");

			ParserFormat3(word3,attribute,value);
			normal.y = atof(value.c_str());
			if(attribute != "y" || errno == EINVAL)
				throw MeshSerializerError("Not a valida OGRE mesh xml format: <position .../>");

			ParserFormat3(word4,attribute,value);
			normal.z = atof(value.c_str());
			if(attribute != "z" || errno == EINVAL)
				throw MeshSerializerError("Not a valida OGRE mesh xml format: <position .../>");

			pSubMesh->SetVertexNormal(i,normal);
		}

		if(has_colordiffuse)
		{
			NextItem(); //read color diffuse item and parse,which has not been done
			//parser...
		}

		if(has_colorspecular)
		{
			NextItem(); //read color diffuse item and parse,which has not been done
			//parser...
		}

		if(texturenum > 0)
		{
			//texture
			item = NextItem();
			datastr = ParserFormat2(item);
			is.str(datastr);
			is.clear();

			is>>word1>>word2>>word3;
			if(is.fail() || word1 != "texcoord")
				throw MeshSerializerError("Not a valida OGRE mesh xml format: <texcoord .../>");
	
			Vector2 texture;
			ParserFormat3(word2,attribute,value);
			texture.x = atof(value.c_str());
			if(attribute != "u" || errno == EINVAL)
				throw MeshSerializerError("Not a valida OGRE mesh xml format: <texcoord .../>");

			ParserFormat3(word3,attribute,value);
			texture.y = atof(value.c_str());
			if(attribute != "v" || errno == EINVAL)
				throw MeshSerializerError("Not a valida OGRE mesh xml format: <texcoord .../>");

			pSubMesh->SetVertexTexture(i,texture);

			//如果多于1个texture，读进来，不过我不清楚剩下的texture有什么用？
			for(int j = 1; j <= texturenum-1; ++j)
				NextItem();
		}

		if(NextItem() != "</vertex>")
			throw MeshSerializerError("Not a valida OGRE mesh xml format: <vertex></vertex>");
	}

	
	if(NextItem() != "</vertexbuffer>")
		throw MeshSerializerError("Not a valida OGRE mesh xml format: <vertexbuffer ...></vertexbuffer>");
		
	if(NextItem() != "</geometry>")
		throw MeshSerializerError("Not a valida OGRE mesh xml format: <geometry vertexcount></geometry>");
}
	

//读入绑定数据
void MeshSerializer::ReadBoneAssignmentFromOGRE(SubMesh *pSubMesh)
{
	string item,datastr;
	string word1,word2,word3,word4;
	string attribute,value;
	istringstream is;

	if(NextItem() != "<boneassignments>")
		throw MeshSerializerError("Not a valida OGRE mesh xml format: <boneassignments></boneassignments>");
	
	try
	{
		item = NextItem();
		datastr = ParserFormat2(item);
		is.str(datastr);
		is.clear();

		is>>word1;
		if(is.fail() || word1 != "vertexboneassignment")
			throw MeshSerializerError("Not a valida OGRE mesh xml format: <vertexboneassignment .../>");

		while(1/*word1 == "vertexboneassignment"*/)
		{
			int vertexidx,boneidx;
			double weight;

			is>>word2>>word3>>word4;

			ParserFormat3(word2,attribute,value);
			vertexidx = atoi(value.c_str());
			if(attribute != "vertexindex" || errno == EINVAL)
				throw MeshSerializerError("Not a valida OGRE mesh xml format: <vertexboneassignment .../>");

			ParserFormat3(word3,attribute,value);
			boneidx = atoi(value.c_str());
			if(attribute != "boneindex" || errno == EINVAL)
				throw MeshSerializerError("Not a valida OGRE mesh xml format: <vertexboneassignment .../>");

			ParserFormat3(word4,attribute,value);
			weight = atof(value.c_str());
			if(attribute != "weight" || errno == EINVAL)
				throw MeshSerializerError("Not a valida OGRE mesh xml format: <vertexboneassignment .../>");

			//add boneassignment
			pSubMesh->AddAssignment(vertexidx,boneidx,weight);

			item = NextItem();
			datastr = ParserFormat2(item);
			is.str(datastr);
			is.clear();

			is>>word1;
			if(is.fail() || word1 != "vertexboneassignment")
			throw MeshSerializerError("Not a valida OGRE mesh xml format: <vertexboneassignment .../>");
		}
	}
	catch(MeshSerializerError& e)
	{
		if(item != "</boneassignments>")
			throw e;
	}
}



/**
 * each item with format: <Item>
 */
string MeshSerializer::NextItem()
{
	string item;
	char ch;

	SetSkipWriteSpace(true); //skip whitespace, default mode
	ch = nextChar();

	if(ch != '<')
		throw MeshSerializerError("Not a valida OGRE mesh xml format:<data>");

	item.append(1,ch);

	SetSkipWriteSpace(false);
	ch = nextChar();
	while(ch != '>')
	{
		item.append(1,ch);
		ch = nextChar();		
	}

	item.append(1,ch);

	SetSkipWriteSpace(true);
	
	return item;
}



/**
 * format: <data>
 */
string MeshSerializer::ParserFormat1(string item)
{
	string::size_type size = item.length();
	if(size < 2 ||item[0] != '<' || item[size-1] != '>')
		throw MeshSerializerError("Not a valida OGRE mesh xml format:<data>");

	return item.substr(1,size-2);

}


/**
 * format: <data/>
 */
string MeshSerializer::ParserFormat2(string item)
{
	string::size_type size = item.length();

	if(size < 3 || item[0] != '<' || item[size-1] != '>' || item[size-2] != '/')
		throw MeshSerializerError("Not a valida OGRE mesh xml format:<data/>");

	return item.substr(1,size-3);

}


/**
 * string with format attibure="value", parse it and return substring attribute and value
 */
void MeshSerializer::ParserFormat3(string source, string& attribute, string& value)
{
	string::size_type idx = source.find('=');
	if(idx == string::npos)
		throw MeshSerializerError("Not a valida OGRE mesh xml format: attribute=\"value\"");

	attribute = source.substr(0,idx);
	value = source.substr(idx+1,source.length() - idx - 1);

	if(*(value.begin()) != '\"' || *(value.end()-1) != '\"')
		throw MeshSerializerError("Not a valida OGRE mesh xml format: attribute=\"value\"");

	value.erase(value.begin());
	value.erase(value.end()-1);

	return;
}


//以上是从文件中读入mesh
//下面是从流中读入mesh
Mesh* MeshSerializer::ImportMesh(std::ifstream& input)
{
	Mesh *pMesh;
	try
	{
		m_pstream = &input;  //...
		fillBuf();
		pMesh = LoadMeshFromOGRE();   
		pMesh->m_pSkeleton = LoadSkeletonFromOGRE();
		pMesh->ComputerMeshVertexLocalCoord();
	}catch(MeshSerializerError& /*e*/)
	{
		//AfxMessageBox(e.what());
		throw;
		//return NULL;
	}
	return pMesh;
}


Mesh* MeshSerializer::LoadMeshFromOGRE()
{
	Mesh* pMesh = new Mesh; //create a new mesh object

	//读取Mesh数据
	try
	{
		if(NextItem() != "<mesh>")
		{
			throw MeshSerializerError("Not a valida OGRE mesh xml format:<mesh></mesh>");
		}
		LoadSubMeshesFromOGRE(pMesh); //load submeshes
	
		if(NextItem() != "</mesh>")
			throw MeshSerializerError("Not a valida OGRE mesh xml format:<mesh></mesh>");
	}
	catch(MeshSerializerError& e)
	{
		delete pMesh;
		throw e;
	}

	return pMesh;
}



Skeleton* MeshSerializer::LoadSkeletonFromOGRE()
{
	Skeleton *pSkeleton = new Skeleton;

	try
	{
		if(NextItem() != "<skeleton>")
			throw MeshSerializerError("Not a valida OGRE mesh skeleton format:<skeleton></skeleton>");

		ReadSkeletonJointsFromOGRE(pSkeleton);  //read skeleton joints
		ReadSkeletonJointsHierarchyFromOGRE(pSkeleton); //read Joints Hierarchy
	
		if(NextItem() != "</skeleton>")
			throw MeshSerializerError("Not a valida OGRE mesh skeleton format:<skeleton></skeleton>");
	}
	catch(MeshSerializerError& e)
	{
		delete pSkeleton;
		throw e;
	}

	return pSkeleton;
}