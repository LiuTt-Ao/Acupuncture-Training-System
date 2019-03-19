
// AcupunctureArmView.cpp : implementation of the CAcupunctureArmView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "AcupunctureArm.h"
#endif

#include "AcupunctureArmDoc.h"
#include "AcupunctureArmView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAcupunctureArmView

IMPLEMENT_DYNCREATE(CAcupunctureArmView, CView)

BEGIN_MESSAGE_MAP(CAcupunctureArmView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CAcupunctureArmView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_DESTROY()
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_TIMER()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MBUTTONDOWN()
	ON_WM_MBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()

// CAcupunctureArmView construction/destruction

CAcupunctureArmView::CAcupunctureArmView()
{
	// TODO: add construction code here

}

CAcupunctureArmView::~CAcupunctureArmView()
{
}

BOOL CAcupunctureArmView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	cs.style |= WS_CLIPCHILDREN | WS_CLIPSIBLINGS;

	return CView::PreCreateWindow(cs);
}

// CAcupunctureArmView drawing

void CAcupunctureArmView::OnDraw(CDC* /*pDC*/)
{
	CAcupunctureArmDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	RenderScene();
	// TODO: add draw code for native data here
	/*********************
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glColor3f(1.0f, 0.0f, 0.0f);
	glTranslatef(-1.5f, 0.0f, -6.0f);
	glBegin(GL_TRIANGLES);// 绘制三角形
		glVertex3f(1.0f, 1.0f, 1.0f);// 上顶点
		glVertex3f(0.0f, -1.0f, -1.0f);// 左下
		glVertex3f(2.0f, -1.0f, 0.0f);// 右下
	glEnd();
	SwapBuffers(wglGetCurrentDC());
	/******************/
}


// CAcupunctureArmView printing


void CAcupunctureArmView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CAcupunctureArmView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CAcupunctureArmView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CAcupunctureArmView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CAcupunctureArmView::OnRButtonUp(UINT nFlags , CPoint point)
{
	ReleaseCapture();
	mouseRightDown = FALSE;
	SetCamPos(2, (point.y - mousePreviousPoint.y), TRUE, TRUE);
	CView::OnRButtonUp(nFlags, point);
}

void CAcupunctureArmView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
//	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CAcupunctureArmView diagnostics

#ifdef _DEBUG
void CAcupunctureArmView::AssertValid() const
{
	CView::AssertValid();
}

void CAcupunctureArmView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CAcupunctureArmDoc* CAcupunctureArmView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CAcupunctureArmDoc)));
	return (CAcupunctureArmDoc*)m_pDocument;
}
#endif //_DEBUG


// CAcupunctureArmView message handlers


BOOL CAcupunctureArmView::SetupPixelFormat()
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


BOOL CAcupunctureArmView::InitOpenGL()
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

	GLfloat ambientLight[] = { 0.2f, 0.2f, 0.2f, 1.0f };
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
	glBlendFunc(GL_SRC_ALPHA, GL_DST_ALPHA);

	return TRUE;
}


void CAcupunctureArmView::OnDestroy()
{
	CView::OnDestroy();
	//Delete the RC
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
			::MessageBox(NULL, _T("释放RC失败。"),_T( "关闭错误"), MB_OK | MB_ICONINFORMATION);
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


int CAcupunctureArmView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here
	SetTimer(1, 10, NULL);

	if (!InitOpenGL())
	{
		::MessageBox(NULL, _T("初始化OpenGL失败!"), _T("错误"), MB_OK | MB_ICONEXCLAMATION);
		return -1;
	}

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

	obj = m_triList.getObjectByIndex(0);
	obj->setMaterial(FALSE);

	return 0;
}


void CAcupunctureArmView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
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
}


BOOL CAcupunctureArmView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default

	//return CView::OnEraseBkgnd(pDC);//将该句注释掉换成return true ;
	return TRUE;
}


BOOL CAcupunctureArmView::RenderScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_ACCUM_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(camPos[0], camPos[1], camPos[2]);
	glRotatef(camRot[0], 1.0F, 0.0F, 0.0F);
	glRotatef(camRot[1], 0.0F, 1.0F, 0.0F);
	glRotatef(camRot[2], 0.0F, 0.0F, 1.0F);


	glTranslatef(scenePos[0], scenePos[1], scenePos[2]);
	glRotatef(sceneRot[0], 1.0F, 0.0F, 0.0F);
	glRotatef(sceneRot[1], 0.0F, 1.0F, 0.0F);
	glRotatef(sceneRot[2], 0.0F, 0.0F, 1.0F);

	glTranslatef(0.0f, 0.0f, -6.0f);
	glRotatef(-90, 1, 0, 0);
//	glRotatef(-90, 0, 0, 1);
	glRotatef(100, 0, 1, 0);
	glScalef(0.5f, 0.5f, 0.5f);
	m_triList.drawGL();

	SwapBuffers(wglGetCurrentDC());		//交互缓冲区
	
	return TRUE;
}


void CAcupunctureArmView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	
	Invalidate(FALSE);//添加定时器响应函数和场景更新函数

	CView::OnTimer(nIDEvent);
}


void CAcupunctureArmView::SetCamPos(int axis, int value, BOOL increment, BOOL apply)
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

void CAcupunctureArmView::SetSceneRot(int axis, int value, BOOL increment, BOOL apply)
{
	if (increment)
		sceneRot[axis] += (sceneRot[axis] >= 360) ? (-360 + value / 2) : value / 2;
	else
		sceneRot[axis] = (sceneRot[axis] >= 360) ? (-360 + value / 2) : value / 2;
	RenderScene();
}

void CAcupunctureArmView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	SetCapture();
	mouseLeftDown = TRUE;
	mousePreviousPoint.x = point.x;
	mousePreviousPoint.y = point.y;
	obj->setMaterial(TRUE);
	CView::OnLButtonDown(nFlags, point);
}


void CAcupunctureArmView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	ReleaseCapture();
	mouseLeftDown = FALSE;
	SetSceneRot(0, (point.y - mousePreviousPoint.y), TRUE, TRUE);
	SetSceneRot(2, (point.x - mousePreviousPoint.x), TRUE, TRUE);
	obj->setMaterial(FALSE);
	CView::OnLButtonUp(nFlags, point);
}


void CAcupunctureArmView::OnMButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	ReleaseCapture();
	mouseMiddleDown = TRUE;
	mousePreviousPoint.x = point.x;
	mousePreviousPoint.y = point.y;
	CView::OnMButtonDown(nFlags, point);
}


void CAcupunctureArmView::OnMButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	ReleaseCapture();
	mouseMiddleDown = FALSE;
	SetCamPos(0, (point.x - mousePreviousPoint.x), TRUE, TRUE);
	SetCamPos(1, (point.y - mousePreviousPoint.y), TRUE, TRUE);
	CView::OnMButtonUp(nFlags, point);
}


void CAcupunctureArmView::OnMouseMove(UINT nFlags, CPoint point)
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


void CAcupunctureArmView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	SetCapture();
	mouseRightDown = TRUE;
	mousePreviousPoint.x = point.x;
	mousePreviousPoint.y = point.y;
	CView::OnRButtonDown(nFlags, point);
}
