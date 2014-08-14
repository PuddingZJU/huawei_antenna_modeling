/**  A class representing geometrical elements
 *	 Author : 毛旭辉
 *	 Date : 2006-3-23
 *	 Description: this class contains all the objects that are in the display scene. Besides,it is obligate
 *                to manage those objects.
 *   Note : 
 */

#pragma once

#ifndef Element_h
#define Element_h

#include <string>
//using namespace std;

namespace Caca
{
	enum ShowMode{SKELETON, MODEL_WIREFRAME, MODEL_FLAT, MODEL_LIGHTED, MODEL_TEXTURE};   //Dsiplay mode: wireframe，flat，lighted，texture,etc
	enum ElmtCategory 
	{
		MOTION_DATA,
		CHARACTER,
		OTHER
		//
	};
	class Element
	{
	public:
		Element(void);
		Element(std::string name);
		virtual ~Element(void);

		//element type
		enum
		{
			TYPE_MOTIONCLIP,
			TYPE_GEOMETRY
		};

		bool IsActive()const;
		void Activate();
		void InActivate();
		bool IsVisible()const;
		void Visualize();
		void InVisualize();
		std::string GetName()const;
		void Rename(std::string newName);
		bool IsPicked()const;
		bool IsModified()const;
		void SetModified(bool isModified);
		int GetGlobalStartFrame()const;
		void SetGlobalStartFrame(int globalFrameNo);

		

		virtual void  SetPicked(bool isPicked,int jointIndex)=0; //!< For asset, just set jointIndex = -1
		virtual void  Render(int frmNo)=0;
		virtual void  RenderToSelectBuffer(int frmNo, int colorCode)=0;
		virtual int   GetFrameCount()const=0;
		virtual int   GetType()const=0;
		virtual double GetFrameTime() const=0;

		//设置或获取文件路径
		std::string GetFilePath();
		void SetFilePath(std::string strFilePath);

	protected:
		bool m_isActive;
		bool m_isVisible;
		bool m_isPicked;   //it is true as long as any of its joint is picked
		bool m_isModified;
		std::string m_name;

		//frankmao 2007.3.13
		int m_globalStartFrame;
		

		//动作数据文件的路径
		//李启雷2006.6.12
		std::string m_strFilePath;
	private:
		
	};
}

#endif
