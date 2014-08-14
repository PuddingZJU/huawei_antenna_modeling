//#include "StdAfx.h"
#include "Element.h"

using namespace Caca;
Element::Element(void)
{
	m_name = "";
	m_isActive = true;
	m_isVisible = true;
	m_isPicked = false;
	m_globalStartFrame = 0;
	

	m_strFilePath = "";
}


Element::Element(std::string name)
{
	m_name = name;
	m_isActive = true;
	m_isVisible = true;
	m_isPicked = false;
	m_isModified =false;
	m_globalStartFrame = 0;

	m_strFilePath = "";
}

Element::~Element(void)
{
}

	

/** Query whether the Element is active
 * 
 * @return bool,true if it is active and false otherwise
 */
bool Element::IsActive()const
{
	return m_isActive;
}


/** Activete the Element object
 * 
 * @return void
 */
void Element::Activate()
{
	m_isActive = true;
}


/** InActivate the Element object
 *
 * @return void
 */
void Element::InActivate()
{
	m_isActive = false;
}


/** Query whether the Element is visible
 *
 * @return bool,true if visible,otherwise fasle
 */
bool Element::IsVisible()const
{
	return m_isVisible;
}



/** Visualize the Element object
 * 
 * @return void
 */
void Element::Visualize()
{
	m_isVisible = true;
}



/** InVisualize the Element object
 *
 * @return void
 */
void Element::InVisualize()
{
	m_isVisible = false;
}



/** Get the name of the Element
 *
 * @return string The name of the Element
 */
std::string Element::GetName()const
{
	return m_name;
}


void Element::Rename(std::string newName)
{
	//先判断是否跟场景中其他名字冲突, 不过不需要在这里做
	m_name = newName;
}


/** Quary whether the something of the Element is picked 
 * 
 * @return bool. 
 */
bool Element::IsPicked()const
{
	return m_isPicked;
}


bool Element::IsModified()const
{
	return m_isModified;
}


void Element::SetModified(bool isModified)
{
	m_isModified = isModified;
}

std::string Element::GetFilePath()
{
	return m_strFilePath;
}
void Element::SetFilePath(std::string strFilePath)
{
	m_strFilePath = strFilePath;
}

int Element::GetGlobalStartFrame()const
{
	return m_globalStartFrame;
}

void Element::SetGlobalStartFrame(int globalFrameNo)
{
	if(m_globalStartFrame < 0)
	{
		//AfxMessageBox(_T("invalidate parameter,can't be less than 0"));
		return;
	}
	m_globalStartFrame = globalFrameNo;
}