
#include <gl\gl.H>
#include <gl\glu.H>
#include <gl\glut.H>
#include <gl\glaux.H>
#include "OpenGLDoc.h"

#pragma once

#pragma comment(lib, "OPENGL32.LIB")
#pragma comment(lib, "GLAUX.LIB")
#pragma comment(lib, "GLUT32.LIB")
#pragma comment(lib, "GLU32.LIB")

// OpenGLView.h: COpenGLView 클래스의 인터페이스

class COpenGLView : public CView
{
protected: // serialization에서만 만들어집니다.
	COpenGLView() noexcept;
	DECLARE_DYNCREATE(COpenGLView)

// 특성입니다.
public:
	COpenGLDoc* GetDocument() const;

// 작업입니다.
public:
	HDC m_hDC;
	HGLRC m_hGLRC;
	B511065 m_b511065;

public:
	bool SetDevicePixelFormat(HDC hdc);
	void InitGL();
	void ResizeGLScene(GLsizei width, GLsizei height);
	void DrawGLScene();

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~COpenGLView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // OpenGLView.cpp의 디버그 버전
inline COpenGLDoc* COpenGLView::GetDocument() const
   { return reinterpret_cast<COpenGLDoc*>(m_pDocument); }
#endif

