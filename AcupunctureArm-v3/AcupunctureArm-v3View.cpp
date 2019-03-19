
// AcupunctureArm-v3View.cpp : implementation of the CAcupunctureArmv3View class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "AcupunctureArm-v3.h"
#endif

#include "AcupunctureArm-v3Doc.h"
#include "AcupunctureArm-v3View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAcupunctureArmv3View

IMPLEMENT_DYNCREATE(CAcupunctureArmv3View, CView)

BEGIN_MESSAGE_MAP(CAcupunctureArmv3View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_WM_CREATE()
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MBUTTONDOWN()
	ON_WM_MBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CAcupunctureArmv3View construction/destruction

CAcupunctureArmv3View::CAcupunctureArmv3View()
{
	// TODO: add construction code here

}

CAcupunctureArmv3View::~CAcupunctureArmv3View()
{
}

BOOL CAcupunctureArmv3View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	cs.style |= WS_CLIPCHILDREN | WS_CLIPSIBLINGS;
	return CView::PreCreateWindow(cs);
}

// CAcupunctureArmv3View drawing

void CAcupunctureArmv3View::OnDraw(CDC* /*pDC*/)
{
	CAcupunctureArmv3Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	RenderScene();
	// TODO: add draw code for native data here
}


// CAcupunctureArmv3View printing

BOOL CAcupunctureArmv3View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CAcupunctureArmv3View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CAcupunctureArmv3View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CAcupunctureArmv3View diagnostics

#ifdef _DEBUG
void CAcupunctureArmv3View::AssertValid() const
{
	CView::AssertValid();
}

void CAcupunctureArmv3View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CAcupunctureArmv3Doc* CAcupunctureArmv3View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CAcupunctureArmv3Doc)));
	return (CAcupunctureArmv3Doc*)m_pDocument;
}
#endif //_DEBUG


// CAcupunctureArmv3View message handlers
BOOL CAcupunctureArmv3View::SetupPixelFormat()
{
	static PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR), // size of this pfd
		1,                                                     // version number
		PFD_DRAW_TO_WINDOW |           // support window
		PFD_SUPPORT_OPENGL |               // support OpenGL
		PFD_DOUBLEBUFFER,                     // double buffered
		PFD_TYPE_RGBA,                           // RGBA type
		24,                                                 // 24-bit color depth
		0, 0, 0, 0, 0, 0,                               // color bits ignored
		0,                                                   // no alpha buffer
		0,                                                   // shift bit ignored
		0,                                                   // no accumulation buffer
		0, 0, 0, 0,                                       // accum bits ignored
		32,                                                 // 32-bit z-buffer
		0,                                                   // no stencil buffer
		0,                                                   // no auxiliary buffer
		PFD_MAIN_PLANE,                         // main layer
		0,                                                   // reserved
		0, 0, 0                                            // layer masks ignored
	};

	int m_nPixelFormat = ::ChoosePixelFormat(m_pDC->GetSafeHdc(), &pfd);
	if (m_nPixelFormat == 0)
	{
		MessageBox(_T("ChoosePixelFormat failed."));
		return FALSE;
	}
	if (::SetPixelFormat(m_pDC->GetSafeHdc(), m_nPixelFormat, &pfd) == FALSE)
	{
		MessageBox(_T("SetPixelFormat failed."));
		return FALSE;
	}
	return TRUE;
}

BOOL CAcupunctureArmv3View::InitOpenGL()
{
	//Get a DC for the Client Area
	m_pDC = new CClientDC(this);
	//Failure to Get DC
	if (m_pDC == NULL)
	{
		MessageBox(_T("Error Obtaining DC"));
		return FALSE;
	}
	//Failure to set the pixel format
	if (!SetupPixelFormat())
	{
		return FALSE;
	}
	//Create Rendering Context
	m_hRC = ::wglCreateContext(m_pDC->GetSafeHdc());
	//Failure to Create Rendering Context
	if (m_hRC == 0)
	{
		MessageBox(_T("Error Creating RC"));
		return FALSE;
	}

	//Make the RC Current
	if (::wglMakeCurrent(m_pDC->GetSafeHdc(), m_hRC) == FALSE)
	{
		MessageBox(_T("Error making RC Current"));
		return FALSE;
	}

	// 启用阴影平滑
	::glShadeModel(GL_SMOOTH);
	//黑色背景
	::glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	//设置深度缓存
	::glClearDepth(1.0f);
	//启用深度测试
	::glEnable(GL_DEPTH_TEST);
	//所作深度测试的类型
	::glDepthFunc(GL_LEQUAL);
	//告诉系统对透视进行修正
	::glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	GLfloat ambientLight[] = { 0.01f, 0.01f, 0.01f, 1.0f };
	GLfloat diffuseLight[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	GLfloat lightPos[] = { 600.0f, 600.0f, 600.0f, 1.0f };

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);

	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	//	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND); // 打开混合
	glBlendFunc(GL_ONE, GL_SRC_ALPHA);
	glEnable(SMOOTH_GROUP);

	return TRUE;
}

void CAcupunctureArmv3View::OnDestroy()
{
	CView::OnDestroy();
	if (m_hRC)
	{
		//Make the RC non-current
		if (::wglMakeCurrent(NULL, NULL) == FALSE)
		{
			::MessageBox(NULL, _T("释放DC或RC失败。"), _T("关闭错误"), MB_OK | MB_ICONINFORMATION);
		}
		//Delete the rendering context
		if (::wglDeleteContext(m_hRC) == FALSE)
		{
			::MessageBox(NULL, _T("释放RC失败。"), _T("关闭错误"), MB_OK | MB_ICONINFORMATION);
		}
		m_hRC = NULL;
	}

	//Delete the DC
	if (m_pDC)
	{
		delete m_pDC;
	}
	//Set it to NULL
	m_pDC = NULL;

	KillTimer(1);
	// TODO: Add your message handler code here
}


void CAcupunctureArmv3View::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	Invalidate(FALSE);//添加定时器响应函数和场景更新函数
	CView::OnTimer(nIDEvent);
}


int CAcupunctureArmv3View::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	SetTimer(1, 10, NULL);
	if (!InitOpenGL())
	{
		::MessageBox(NULL, _T("初始化OpenGL失败!"), _T("错误"), MB_OK | MB_ICONEXCLAMATION);
		return -1;
	}
	// TODO:  Add your specialized creation code here
	m_triList.Init();
	if (m_triList.getNumObjects() > 0)
		m_triList.removeAllObjects();

	if (loader.Reader("3dModel/left_hand.3ds", &m_triList))
	{
		m_triList.doAfterMath();
	}
	else
	{
		::MessageBox(NULL, _T("加载3D模型失败!"), _T("错误"), MB_OK | MB_ICONEXCLAMATION);
		return -1;
	}


	camPos[0] = camPos[1] = camPos[2] = camRot[0] = camRot[1] = camRot[2] = 0.0f;
	camPos[2] = -100.0f; camRot[0] = 20.0f; camRot[1] = -20.0f;
	scenePos[0] = scenePos[1] = scenePos[2] = sceneRot[0] = sceneRot[1] = sceneRot[2] = 0.0f;
	mousePreviousPoint.x = mousePreviousPoint.y = 0;
	mouseLeftDown = mouseMiddleDown = mouseRightDown = FALSE;
	// TODO:  Add your specialized creation code here

	return 0;
}


BOOL CAcupunctureArmv3View::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default
	return TRUE;
//	return CView::OnEraseBkgnd(pDC);
}


void CAcupunctureArmv3View::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);
	if (cx <= 0 || cy <= 0)
	{
		return;
	}
	//选择投影矩阵
	::glMatrixMode(GL_PROJECTION);
	//重置投影矩阵
	::glLoadIdentity();
	//计算窗口的外观比例
	::gluPerspective(45.0f, (GLfloat)cx / (GLfloat)cy, 0.1f, 3.0*10e+11f);
	//设置模型观察矩阵
	::glMatrixMode(GL_MODELVIEW);
	//重置模型观察矩阵
	::glLoadIdentity();
	//设置当前的视口
	::glViewport(0, 0, cx, cy);
	// TODO: Add your message handler code here
}


void CAcupunctureArmv3View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	SetCapture();
	mouseLeftDown = TRUE;
	mousePreviousPoint.x = point.x;
	mousePreviousPoint.y = point.y;
	CView::OnLButtonDown(nFlags, point);
}


void CAcupunctureArmv3View::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	ReleaseCapture();
	mouseLeftDown = FALSE;
	SetSceneRot(0, (point.y - mousePreviousPoint.y), TRUE, TRUE);
	SetSceneRot(2, (point.x - mousePreviousPoint.x), TRUE, TRUE);
	CView::OnLButtonUp(nFlags, point);
}


void CAcupunctureArmv3View::OnMButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	ReleaseCapture();
	mouseMiddleDown = TRUE;
	mousePreviousPoint.x = point.x;
	mousePreviousPoint.y = point.y;
	CView::OnMButtonDown(nFlags, point);

//	TRACE("camRot[0]:%f,camRot[1]:%f,camRot[2]:%f,sceneRot[0]:%f,sceneRot[1]:%f,sceneRot[2]:%f\n", camRot[0], camRot[1], camRot[2], sceneRot[0], sceneRot[1], sceneRot[2]);
//	TRACE("camPos[0]:%f,camPos[1]:%f,camPos[2]:%f,scenePos[0]:%f,scenePos[1]:%f,scenePos[2]:%f\n", camPos[0], camPos[1], camPos[2], scenePos[0], scenePos[1], scenePos[2]);
}


void CAcupunctureArmv3View::OnMButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	ReleaseCapture();
	mouseMiddleDown = FALSE;
	SetCamPos(0, (point.x - mousePreviousPoint.x), TRUE, TRUE);
	SetCamPos(1, (point.y - mousePreviousPoint.y), TRUE, TRUE);
	CView::OnMButtonUp(nFlags, point);
}


void CAcupunctureArmv3View::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (mouseRightDown)
	{
		SetCamPos(2, -(point.y - mousePreviousPoint.y), TRUE, TRUE);
	}
	else if (mouseLeftDown)
	{
		SetSceneRot(0, (point.y - mousePreviousPoint.y), TRUE, TRUE);
		SetSceneRot(2, (point.x - mousePreviousPoint.x), TRUE, TRUE);
	}
	else if (mouseMiddleDown)
	{
		SetCamPos(0, (point.x - mousePreviousPoint.x), TRUE, TRUE);
		SetCamPos(1, -(point.y - mousePreviousPoint.y), TRUE, TRUE);
	}

	mousePreviousPoint.x = point.x;
	mousePreviousPoint.y = point.y;
	CView::OnMouseMove(nFlags, point);
}


void CAcupunctureArmv3View::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	SetCapture();
	mouseRightDown = TRUE;
	mousePreviousPoint.x = point.x;
	mousePreviousPoint.y = point.y;
	CView::OnRButtonDown(nFlags, point);

}


void CAcupunctureArmv3View::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	ReleaseCapture();
	mouseRightDown = FALSE;
	SetCamPos(2, (point.y - mousePreviousPoint.y), TRUE, TRUE);
	CView::OnRButtonUp(nFlags, point);
}


BOOL CAcupunctureArmv3View::RenderScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_ACCUM_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	/************************/
	glTranslatef(camPos[0], camPos[1], camPos[2]);
	glRotatef(camRot[0], 1.0F, 0.0F, 0.0F);
	glRotatef(camRot[1], 0.0F, 1.0F, 0.0F);
	glRotatef(camRot[2], 0.0F, 0.0F, 1.0F);


	glTranslatef(scenePos[0], scenePos[1], scenePos[2]);
	glRotatef(sceneRot[0], 1.0F, 0.0F, 0.0F);
	glRotatef(sceneRot[1], 0.0F, 1.0F, 0.0F);
	glRotatef(sceneRot[2], 0.0F, 0.0F, 1.0F);
	/*****************************/

	glTranslatef(0.0f, 0.0f, -6.0f);
	glRotatef(-90, 1, 0, 0);
	//	glRotatef(-90, 0, 0, 1);
	glRotatef(100, 0, 1, 0);
	glScalef(0.5f, 0.5f, 0.5f);
	//	m_triList.drawGL();

	if (CGlobal::force[0] > 0)
	{
		/*********************/
		camRot[0] = 20.0; camRot[1] = -20.0; camRot[2] = 0.0;
		sceneRot[0] = -73.0; sceneRot[1] = 0.0; sceneRot[2] = 59.0;
		camPos[0] = 0.0; camPos[1] = 1.0; camPos[2] = -9.040635;
		scenePos[0] = 0.0; scenePos[1] = 0.0; scenePos[2] = 0.0;
		/***************************/
		CGlobal::niddle_position[0] += CGlobal::velocity[0] * 0.001;
		glPushMatrix();
		glTranslatef(0.0, CGlobal::niddle_position[0], 0.0);
		m_triList.getObjectByName("niddle1")->drawGL();
		glPopMatrix();
		m_triList.getObjectByName("acupoint1")->drawGL();

	}

	if (CGlobal::force[1] >25.0)
	{
		/*********************/
		camRot[0] = 20.0; camRot[1] = -20.0; camRot[2] = 0.0;
		sceneRot[0] = -90.0; sceneRot[1] = 0.0; sceneRot[2] = 77.0;
		camPos[0] = 7.0; camPos[1] = 0.0; camPos[2] = -19.30096;
		scenePos[0] = 0.0; scenePos[1] = 0.0; scenePos[2] = 0.0;
		/***************************/
		CGlobal::niddle_position[1] += CGlobal::velocity[1] * 0.001;
		glPushMatrix();
		glTranslatef(0.0, CGlobal::niddle_position[1], 0.0);
		m_triList.getObjectByName("niddle2")->drawGL();
		glPopMatrix();
		m_triList.getObjectByName("acupoint2")->drawGL();

	}

	if (CGlobal::force[2] > 250)
	{
		/*********************/
		camRot[0] = 20.0; camRot[1] = -20.0; camRot[2] = 0.0;
		sceneRot[0] = -80.0; sceneRot[1] = 0.0; sceneRot[2] = 71.0;
		camPos[0] = -5.0; camPos[1] = 5.0; camPos[2] = -24.115597;
		scenePos[0] = 0.0; scenePos[1] = 0.0; scenePos[2] = 0.0;
		/***************************/
		CGlobal::niddle_position[2] += CGlobal::velocity[2] * 0.001;
		glPushMatrix();
		glTranslatef(0.0, CGlobal::niddle_position[2], 0.0);
		m_triList.getObjectByName("niddle3")->drawGL();
		glPopMatrix();
		m_triList.getObjectByName("acupoint3")->drawGL();

	}

	if (CGlobal::force[3] > 250)
	{
		/*********************/
		camRot[0] = 20.0; camRot[1] = -20.0; camRot[2] = 0.0;
		sceneRot[0] = -40.0; sceneRot[1] = 0.0; sceneRot[2] = 131.0;
		camPos[0] = -20.0; camPos[1] = -11.0; camPos[2] = -19.798136;
		scenePos[0] = 0.0; scenePos[1] = 0.0; scenePos[2] = 0.0;
		/***************************/
		CGlobal::niddle_position[3] += CGlobal::velocity[3] * 0.001;
		glPushMatrix();
		glTranslatef(0.0, CGlobal::niddle_position[3], 0.0);
		m_triList.getObjectByName("niddle4")->drawGL();
		glPopMatrix();
		m_triList.getObjectByName("acupoint4")->drawGL();

	}

	if (CGlobal::force[4] > 250)
	{
		/*********************/
		camRot[0] = 20.0; camRot[1] = -20.0; camRot[2] = 0.0;
		sceneRot[0] = 39.0; sceneRot[1] = 0.0; sceneRot[2] = 90.0;
		camPos[0] = -26.0; camPos[1] = -5.0; camPos[2] = -30.969498;
		scenePos[0] = 0.0; scenePos[1] = 0.0; scenePos[2] = 0.0;
		/***************************/
		CGlobal::niddle_position[4] -= CGlobal::velocity[4] * 0.001;
		glPushMatrix();
		glTranslatef(0.0, 0.0, CGlobal::niddle_position[4]);
		m_triList.getObjectByName("niddle5")->drawGL();
		glPopMatrix();
		m_triList.getObjectByName("acupoint5")->drawGL();

	}

	m_triList.getObjectByName("arm")->drawGL();


	SwapBuffers(wglGetCurrentDC());		//交互缓冲区

	return TRUE;
}

void CAcupunctureArmv3View::SetCamPos(int axis, int value, BOOL increment, BOOL apply)
{
	if (increment)
	{
		if (axis == 2)
		{
			camPos[axis] += (float)value*camPos[axis] / 100;
		}
		else
		{
			camPos[axis] += (float)value;
		}
	}
	else
	{
		camPos[axis] = (float)value / 2;
	}
	RenderScene();
}

void CAcupunctureArmv3View::SetSceneRot(int axis, int value, BOOL increment, BOOL apply)
{
	if (increment)
		sceneRot[axis] += (sceneRot[axis] >= 360) ? (-360 + value / 2) : value / 2;
	else
		sceneRot[axis] = (sceneRot[axis] >= 360) ? (-360 + value / 2) : value / 2;
	RenderScene();
}