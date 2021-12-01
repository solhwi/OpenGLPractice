
// OpenGLView.cpp: COpenGLView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "OpenGL.h"
#endif

#include "OpenGLDoc.h"
#include "OpenGLView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// COpenGLView

IMPLEMENT_DYNCREATE(COpenGLView, CView)

BEGIN_MESSAGE_MAP(COpenGLView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &COpenGLView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_WM_KEYDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()

// COpenGLView 생성/소멸

COpenGLView::COpenGLView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

COpenGLView::~COpenGLView()
{
}

BOOL COpenGLView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// COpenGLView 그리기

bool COpenGLView::SetDevicePixelFormat(HDC hdc)
{
	int pixelformat;

	PIXELFORMATDESCRIPTOR pfd = {
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_GENERIC_FORMAT | PFD_DOUBLEBUFFER | PFD_TYPE_RGBA,
		32,
		0, 0, 0, 0, 0, 0,
		8,
		0,
		8,
		0, 0, 0, 0,
		16,
		0, 0,
		PFD_MAIN_PLANE,
		0, 0, 0, 0
	};

	if ((pixelformat = ChoosePixelFormat(hdc, &pfd)) == FALSE)
	{
		MessageBox(LPCTSTR(L"ChoosePixelFormat Failed"), LPCTSTR(L"Error"), MB_OK);
		return false;
	}

	if (SetPixelFormat(hdc, pixelformat, &pfd) == FALSE)
	{
		MessageBox(LPCTSTR(L"SetPixelFormat Failed"), LPCTSTR(L"Error"), MB_OK);
		return false;
	}

	return true;
}

void COpenGLView::InitGL()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	m_b511065.Initialize();
}

void COpenGLView::ResizeGLScene(GLsizei width, GLsizei height)
{
	if (height == 0) height = 1;

	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 1000.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void COpenGLView::DrawGLScene() 
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 원래 있는 거
	glLoadIdentity(); // 원래 있는 거

	gluLookAt(m_b511065.posX, m_b511065.posY, m_b511065.posZ, m_b511065.locationX, m_b511065.locationY, m_b511065.locationZ, 0.f, 1.f, 0.f);

	if (m_b511065.cameraMode == 1)
	{
		glRotated(-m_b511065.rotationX, 1, 0, 0); // 카메라를 돌릴 것이기 때문에 반대 방향
		glRotated(-m_b511065.rotationY, 0, 1, 0);

		m_b511065.DrawStars(); // 별 그리기
		m_b511065.DrawSphere(); // 비행체 그리기
	}
	else if (m_b511065.cameraMode == 2)
	{
		glTranslated(m_b511065.locationX, m_b511065.locationY, m_b511065.locationZ + m_b511065.speed); // 비행기는 이동
		m_b511065.SetLocation(m_b511065.locationX, m_b511065.locationY, m_b511065.locationZ + m_b511065.speed); // 이동한 만큼 위치 갱신
 		m_b511065.SetCameraPos(m_b511065.locationX, m_b511065.locationY + 2, m_b511065.locationZ - 5); // 카메라 위치 갱신
		
		m_b511065.DrawSphere(); // 비행기 그리기

		glTranslated(-m_b511065.locationX, -m_b511065.locationY, -(m_b511065.locationZ + m_b511065.speed)); // 별은 이동하지 않으며,
		glRotated(m_b511065.rotationX, 1, 0, 0); // 별을 카메라의 반대 방향대로 회전시킴
		glRotated(m_b511065.rotationY, 0, 1, 0);

		m_b511065.DrawStars(); // 별 그리기
	}

	//m_b511065.Light(); // 광원 
	//m_b511065.Spotlight(); // 스포트라이트

	SwapBuffers(m_hDC);
}

void COpenGLView::OnDraw(CDC* /*pDC*/)
{
	COpenGLDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	DrawGLScene();
	Invalidate(false);
	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// COpenGLView 인쇄


void COpenGLView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL COpenGLView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void COpenGLView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void COpenGLView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

void COpenGLView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void COpenGLView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// COpenGLView 진단

#ifdef _DEBUG
void COpenGLView::AssertValid() const
{
	CView::AssertValid();
}

void COpenGLView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

COpenGLDoc* COpenGLView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(COpenGLDoc)));
	return (COpenGLDoc*)m_pDocument;
}
#endif //_DEBUG


// COpenGLView 메시지 처리기


int COpenGLView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	m_hDC = GetDC()->m_hDC;

	if (!SetDevicePixelFormat(m_hDC)) return -1;

	m_hGLRC = wglCreateContext(m_hDC);
	wglMakeCurrent(m_hDC, m_hGLRC);

	InitGL();

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.

	return 0;
}


void COpenGLView::OnDestroy()
{
	CView::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.

	m_b511065.Destroy();

	wglMakeCurrent(m_hDC, NULL);
	wglDeleteContext(m_hGLRC);
}


void COpenGLView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);
	ResizeGLScene(cx, cy);
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}


void COpenGLView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	switch (nChar)
	{
	case '1': // 카메라가 Z축에서 원점을 바라보도록 설정
		m_b511065.ChangeCameraMode(1);
		break;

	case '2': // 카메라가 비행기를 후방(약간 위)에서 바라보도록 설정
		m_b511065.ChangeCameraMode(2);
		break;
	}

	if (m_b511065.cameraMode == 1) 
	{
		m_b511065.SetCameraPos(0, 0, 2);

		switch (nChar)
		{
		case 'W': // 카메라를 x축 기준으로 +회전
			m_b511065.SetCameraRotateX(3);
			break;

		case 'A': // 카메라를 y축 기준으로 -회전
			m_b511065.SetCameraRotateY(-3);
			break;

		case 'S': // 카메라를 x축 기준으로 -회전
			m_b511065.SetCameraRotateX(-3);
			break;

		case 'D': // 카메라를 y축 기준으로 +회전
			m_b511065.SetCameraRotateY(3);
			break;
		}
	}
	else if (m_b511065.cameraMode == 2)
	{
		switch (nChar)
		{
		case VK_ADD:
			m_b511065.speed += 0.01;
			break;

		case VK_SUBTRACT:
			m_b511065.speed -= 0.01;
			break;
		}

	}

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


void COpenGLView::OnMouseMove(UINT nFlags, CPoint point)
{
	// 이동한 정도에 따라 카메라의 위치를 변화시킨다.

	if (m_b511065.isCameraRotate)
	{
		m_b511065.CameraMove(point);
	}

	CView::OnMouseMove(nFlags, point);
}


void COpenGLView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// 이 때의 포지션을 기억한다.
	m_b511065.startPoint = point;
	m_b511065.isCameraRotate = true;
	CView::OnLButtonDown(nFlags, point);
}


void COpenGLView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// 이동을 멈춘다.
	m_b511065.isCameraRotate = false;
	CView::OnLButtonUp(nFlags, point);
}
