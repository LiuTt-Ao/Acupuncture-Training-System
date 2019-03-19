
// AcupunctureArmView.h : interface of the CAcupunctureArmView class
//

#pragma once

#include "Read3d\TriList.h"
#include "Read3d\TriObject.h"
#include "Read3d\ModelLoader.h"


class CAcupunctureArmView : public CView
{
protected: // create from serialization only
	CAcupunctureArmView();
	DECLARE_DYNCREATE(CAcupunctureArmView)

// Attributes
public:
	CAcupunctureArmDoc* GetDocument() const;

	HGLRC m_hRC;          //Rendering Context着色描述表
	CClientDC* m_pDC;     //Device Context设备描述表

	CTriList    m_triList;  //3d model
	ModelLoader loader; 
	CTriObject* obj;

	float camRot[3], sceneRot[3], camPos[3], scenePos[3];
	BOOL mouseRightDown, mouseLeftDown, mouseMiddleDown;
	CPoint mousePreviousPoint;

// Operations
public:
	void SetSceneRot(int axis, int value, BOOL increment, BOOL apply);
	void SetCamPos(int axis, int value, BOOL increment, BOOL apply);

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CAcupunctureArmView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	BOOL SetupPixelFormat();
	BOOL InitOpenGL();
	afx_msg void OnDestroy();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	BOOL RenderScene();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // debug version in AcupunctureArmView.cpp
inline CAcupunctureArmDoc* CAcupunctureArmView::GetDocument() const
   { return reinterpret_cast<CAcupunctureArmDoc*>(m_pDocument); }
#endif

