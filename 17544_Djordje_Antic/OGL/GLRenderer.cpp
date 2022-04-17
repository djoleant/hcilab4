#include "StdAfx.h"
#include "GLRenderer.h"
#include "GL\gl.h"
#include "GL\glu.h"
#include "GL\glaux.h"
#include "GL\glut.h"
#include <string>
#include <iostream>

using namespace std;

CGLRenderer::CGLRenderer(void)
{
	
	
}

CGLRenderer::~CGLRenderer(void)
{
}

bool CGLRenderer::CreateGLContext(CDC* pDC)
{
	PIXELFORMATDESCRIPTOR pfd ;
   	memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));
   	pfd.nSize  = sizeof(PIXELFORMATDESCRIPTOR);
   	pfd.nVersion   = 1; 
   	pfd.dwFlags    = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;   
   	pfd.iPixelType = PFD_TYPE_RGBA; 
   	pfd.cColorBits = 32;
   	pfd.cDepthBits = 24; 
   	pfd.iLayerType = PFD_MAIN_PLANE;
	
	int nPixelFormat = ChoosePixelFormat(pDC->m_hDC, &pfd);
	
	if (nPixelFormat == 0) return false; 

	BOOL bResult = SetPixelFormat (pDC->m_hDC, nPixelFormat, &pfd);
  	
	if (!bResult) return false; 

   	m_hrc = wglCreateContext(pDC->m_hDC); 

	if (!m_hrc) return false; 

	return true;	
}

void CGLRenderer::PrepareScene(CDC *pDC)
{
	wglMakeCurrent(pDC->m_hDC, m_hrc);
	//---------------------------------
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glEnable(GL_DEPTH_TEST);
	//glCullFace(GL_BACK);
	//glEnable(GL_CULL_FACE);
	//---------------------------------
	wglMakeCurrent(NULL, NULL);
}

void CGLRenderer::DrawScene(CDC *pDC)
{
	
  	wglMakeCurrent(pDC->m_hDC, m_hrc);
	//---------------------------------
	DrawScene();
	//---------------------------------
	SwapBuffers(pDC->m_hDC);
	wglMakeCurrent(NULL, NULL);
	
}

void CGLRenderer::DrawScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glInitNames(); 
	glPushName(0);
	glTranslatef(m_x, m_y, -3.0+ m_z );
	glRotatef(m_Rx, 1.0, 0.0, 0.0);
	glRotatef(m_Ry, 0.0, 1.0, 0.0);


	glPushMatrix();
	//-------------------------------------
	glLoadName(1);
	glColor3f(1.0, 0, 0);
	glutSolidCube(1.0);

	glLoadName(2);
	glTranslatef(1.0, 0.0, -1.0);
	glColor3f(0, 1.0, 0);
	glutSolidCube(1.0);

	glLoadName(3);
	glTranslatef(-2.0, 0.0, 0.0);
	glColor3f(0, 0, 1.0);
	glutSolidCube(1.0);


	//-------------------------------------

	glPopMatrix();

	glFlush();
	
}
void CGLRenderer::Reshape(CDC *pDC, int w, int h)
{
	wglMakeCurrent(pDC->m_hDC, m_hrc);
	//---------------------------------
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	m_aspect = (float)w / (float)h;
	gluPerspective(40, m_aspect, 0.1, 100);
	glMatrixMode(GL_MODELVIEW);

	//---------------------------------
	wglMakeCurrent(NULL, NULL);
}

void CGLRenderer::DestroyScene(CDC *pDC)
{
	//wglMakeCurrent(pDC->m_hDC, m_hrc);
	wglMakeCurrent(NULL,NULL); 
	if(m_hrc) 
	{
		wglDeleteContext(m_hrc);
		m_hrc = NULL;
	}
}

unsigned int CGLRenderer::PickObject(CDC *pDC, int x, int y)
{
	wglMakeCurrent(pDC->m_hDC, m_hrc);
	//---------------------------------
	GLint viewport[4];
	GLuint selectBuf[512];

	glSelectBuffer(512, selectBuf);
	glRenderMode(GL_SELECT);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();

	glGetIntegerv(GL_VIEWPORT, viewport);
	gluPickMatrix(x, viewport[3] - y, 3, 3, viewport);
	//-----------------------------
	gluPerspective(40.0, m_aspect, 0.1, 100.0);
	//-----------------------------
	glMatrixMode(GL_MODELVIEW);
	glInitNames();
	glPushName(0);
	DrawScene();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glFlush();

	int hits = glRenderMode(GL_RENDER);
	unsigned int retVal = 0;
	if (hits != 0)
		retVal = ProcessHits(hits, selectBuf);
	//---------------------------------------
	wglMakeCurrent(NULL, NULL);
	return retVal;
}

unsigned int CGLRenderer::ProcessHits(int hits, unsigned int buffer[])
{
	int i, j;
	unsigned int names, *pointer, z_min, *pointer_names, n;
	pointer = (unsigned int *)buffer;
	z_min = ULONG_MAX;
	for (i = 0; i < hits; i++)
	{
		names = *pointer;
		pointer++;
		if (*pointer < z_min)
		{
			n = names;
			z_min = *pointer;
			pointer_names = pointer + 2;
		}
		pointer += names + 2;
	}
	pointer = pointer_names;
	
	const char* pom = to_string(n).c_str();

	if (*pointer == 1)
	{
		AfxMessageBox(_T("Crvena kocka"));

	}
	else if (*pointer == 2)
	{
		AfxMessageBox(_T("Zelena kocka"));

	}
	else 
	{
		AfxMessageBox(_T("Plava kocka"));

	}
	return *pointer;

}
