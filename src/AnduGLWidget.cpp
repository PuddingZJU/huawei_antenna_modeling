#include "AnduGLWidget.h"
#include "Mathematics.h"
#include "Mesh.h"
#include "MeshVertexData.h"
#include "submesh.h"
#include <GL\glut.h>
#include "..\src\gui\kernel\qevent.h"

using namespace Andu;
using namespace Caca;

int Andu::AnduGLWidget::m_texImgHeight = 100;
int Andu::AnduGLWidget::m_texImgWidth = 100;

Andu::AnduGLWidget::AnduGLWidget()
	: m_pRender(0)
	, m_pMesh(0)
{	
	printf("init AnduGLWidget class\n");
}

Andu::AnduGLWidget::~AnduGLWidget()
{

}

void Andu::AnduGLWidget::paintGL()
{
 	SandboxGLWidget::paintGL();
 	return;	
}

void Andu::AnduGLWidget::resizeGL(int width, int height)
{
	makeCurrent();

	SandboxGLWidget::resizeGL(width, height);
// 	static int preWidth = width;
// 	static int preHeight = height;
// 	winWidth *= (double)width/preWidth;
// 	winHeight *= (double)height/preHeight;
// 	preWidth = width;
// 	preHeight = height;
// 	glViewport(0, 0, (GLint)width, (GLint)height);

}

bool Andu::AnduGLWidget::addGLList( int listIdx, Caca::Mesh* pMesh, GLenum renderType /*= GL_TRIANGLES*/ )
{
	makeCurrent();

	list<int>::iterator li = std::find(m_glListIdxList.begin(), m_glListIdxList.end(),
		listIdx);
	if(li != m_glListIdxList.end()) {
		return false;
	}
	m_glListIdxList.push_back(listIdx);

	newGLList(listIdx, pMesh, renderType);
	
	return true;
}

bool Andu::AnduGLWidget::setGLList( int listIdx, Caca::Mesh* pMesh, GLenum renderType /*= GL_TRIANGLES*/ )
{
	makeCurrent();

	list<int>::iterator li = std::find(m_glListIdxList.begin(), m_glListIdxList.end(),
		listIdx);
	if(li == m_glListIdxList.end()) {
		return false;
	}

	glDeleteLists(listIdx, 1);

	newGLList(listIdx, pMesh, renderType);

	return true;
}

void Andu::AnduGLWidget::newGLList( int listIdx, Caca::Mesh* pMesh,
	GLenum renderType /*= GL_TRIANGLES*/,
	map<int, vector<QColor> > *pVertexColorMap /*= 0*/,
	map<int, vector<QColor> > *pPatchColorMap /*= 0*/)
{
	makeCurrent();

// 	glNewList(2, GL_COMPILE);
// 	glutWireCube (1.0);
// 	glEndList();

	printf("new gl list %d\n", listIdx);

	glPushAttrib(GL_LIGHTING);
	glPushAttrib(GL_LIGHT0);


	glNewList(listIdx, GL_COMPILE);	

	glPolygonMode (GL_FRONT_AND_BACK, GL_FILL);	

	//  	glEnable (GL_BLEND);	

	Patch p;
	MeshVertex v1,v2,v3;

	//glColor4f(0,0.5,0.5,0.0);

	GLfloat mat[] = { 0.5, 0.5, 0.5, 1.0 };

	//glMaterialfv(GL_FRONT, GL_AMBIENT, mat);
	
	for(int j = 0; j < pMesh->GetSubMeshCount(); j++) {
		SubMesh* pSubMesh = pMesh->GetSubMesh(j);
		const std::list<Patch>& patchList = pSubMesh->GetPatchList();

		vector<QColor> *pPatchColorVec = 0;
		if(pPatchColorMap) {
			auto iter = pPatchColorMap->find(j);
			if(iter != pPatchColorMap->end()) {
				pPatchColorVec = &(iter->second);
			}
		}

		vector<QColor> *pVertexColorVec = 0;
		if(pVertexColorMap) {
			auto iter = pVertexColorMap->find(j);
			if(iter != pVertexColorMap->end()) {
				pVertexColorVec = &(iter->second);
			}
		}

		int patchIdx = 0;

		for(std::list<Patch>::const_iterator i = patchList.begin();
			i != patchList.end() ; i++)
		{
			MeshVertex v1 = pSubMesh->GetVertex(i->vertexIndexOne);
			MeshVertex v2 = pSubMesh->GetVertex(i->vertexIndexTwo);
			MeshVertex v3 = pSubMesh->GetVertex(i->vertexIndexThree);

			glPushAttrib(GL_CURRENT_BIT);
			glBegin(renderType);

			QColor patchColor;
			if(pPatchColorVec) {
				patchColor = pPatchColorVec->at(patchIdx);
				qglColor(patchColor);
			}
			
			if(!patchColor.isValid() && pVertexColorVec) {
				qglColor(pVertexColorVec->at(i->vertexIndexOne));
			}
			glNormal3f(v1.normal.x,v1.normal.y,v1.normal.z);
			glVertex3f(v1.pos.x,v1.pos.y,v1.pos.z);
			
			if(!patchColor.isValid() && pVertexColorVec) {
				qglColor(pVertexColorVec->at(i->vertexIndexThree));
			}
			glNormal3f(v3.normal.x,v3.normal.y,v3.normal.z);
			glVertex3f(v3.pos.x,v3.pos.y,v3.pos.z);

			if(!patchColor.isValid() && pVertexColorVec) {
				qglColor(pVertexColorVec->at(i->vertexIndexTwo));
			}
			glNormal3f(v2.normal.x,v2.normal.y,v2.normal.z);
			glVertex3f(v2.pos.x,v2.pos.y,v2.pos.z);

			glEnd();
			glPopAttrib();

			patchIdx++;
		}
	}
	
	
	glEndList();

	glPopAttrib();
	glPopAttrib();
}

void Andu::AnduGLWidget::initializeGL()
{
	SandboxGLWidget::initializeGL();	
}

void Andu::AnduGLWidget::resizeEvent( QResizeEvent* event )
{
	resizeGL(event->size().width(), event->size().height());
}

void delOneGlList(int i)
{	
	glDeleteLists(i, 1);
	printf("glDeleteLists %d, is %d\n", i, glIsList(i));
}

void Andu::AnduGLWidget::delAllGLList()
{
	makeCurrent();

	std::for_each(m_glListIdxList.begin(), m_glListIdxList.end(), delOneGlList);
	m_glListIdxList.clear();
}

bool checkTexFlag(Vector2 t)
{
	double step = 0.01;
	return (int(t.x/step) + int(t.y/step))%2 == 0;
}
