
// AcupunctureArm-v2View.h : interface of the CAcupunctureArmv2View class
//

#pragma once

#include "Read3d\TriList.h"
#include "Read3d\TriObject.h"
#include "Read3d\ModelLoader.h"


class CAcupunctureArmv2View : public CView
{
protected: // create from serialization only
	CAcupunctureArmv2View();
	DECLARE_DYNCREATE(CAcupunctureArmv2View)

// Attributes
public:
	CAcupunctureArmv2Doc* GetDocument() const;

	HGLRC m_hRC;          //Rendering Context着色描述表
	CClientDC* m_pDC;     //Device Context设备描述表

	BOOL SetupPixelFormat();
	BOOL InitOpenGL();
	BOOL RenderScene();

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
	virtual ~CAcupunctureArmv2View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // debug version in AcupunctureArm-v2View.cpp
inline CAcupunctureArmv2Doc* CAcupunctureArmv2View::GetDocument() const
   { return reinterpret_cast<CAcupunctureArmv2Doc*>(m_pDocument); }
#endif

