#ifndef AnduGLWidget_h__
#define AnduGLWidget_h__
#include "SandboxGLWidget.h"
#include <QGLWidget>
#include <map>
#include <vector>

using std::vector;
using std::map;

namespace Caca
{
	class SceneWindow;
	class Camera;
	class Mesh;
}

namespace Andu
{
	using namespace Caca;

	class AnduGLRender;

	class AnduGLWidget : public SandboxGLWidget
	{
	public:
		AnduGLWidget();
		~AnduGLWidget();
		Caca::Mesh * mesh() const { return m_pMesh; }
		void mesh(Caca::Mesh * val) { m_pMesh = val; }
		bool addGLList(int listIdx, Caca::Mesh* pMesh, GLenum renderType = GL_TRIANGLES);
		bool setGLList(int listIdx, Caca::Mesh* pMesh, GLenum renderType = GL_TRIANGLES);
		void delAllGLList();

		static int getTextureImgWdith();
		static int getTextureImgHeight();

	protected:
		void paintGL();
		void resizeGL(int width, int height);
		void drawTexCoor(Mesh* pMesh);

		void newGLList(int listIdx, Caca::Mesh* pMesh,
			GLenum renderType = GL_TRIANGLES,
			map<int, vector<QColor> > *pVertexColorMap = 0,
			map<int, vector<QColor> > *pPatchColorMap = 0);
		void initializeGL();
		void resizeEvent(QResizeEvent* event);

	protected:
		Caca::Mesh *m_pMesh;
		
		AnduGLRender* m_pRender;

		static int m_texImgWidth;
		static int m_texImgHeight;
	};
}

#endif // AnduGLWidget_h__
