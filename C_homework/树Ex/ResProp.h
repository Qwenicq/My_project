/////////////////////////////////////////////////////////////////////////////
//
//	Copyright (c) 2022 <company name>
//
//	Module Name:
//		ResProp.h
//
//	Abstract:
//		Definition of the resource extension property page classes.
//
//	Implementation File:
//		ResProp.cpp
//
//	Author:
//		<name> (<e-mail name>) Mmmm DD, 2022
//
//	Revision History:
//
//	Notes:
//
/////////////////////////////////////////////////////////////////////////////

#ifndef _RESPROP_H_
#define _RESPROP_H_

/////////////////////////////////////////////////////////////////////////////
// Include Files
/////////////////////////////////////////////////////////////////////////////

#ifndef _BASEPAGE_H_
#include "BasePage.h"	// for CBasePropertyPage
#endif

#ifndef _PROPLIST_H_
#include "PropList.h"	// for CObjectPropert
#endif

/////////////////////////////////////////////////////////////////////////////
// Forward Class Declarations
/////////////////////////////////////////////////////////////////////////////

class CMyParamsPage;

/////////////////////////////////////////////////////////////////////////////
// External Class Declarations
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
//
//	CMyParamsPage
//
//	Purpose:
//		Parameters page for resources.
//
/////////////////////////////////////////////////////////////////////////////

class CMyParamsPage : public CBasePropertyPage
{
	DECLARE_DYNCREATE(CMyParamsPage)

// Construction
public:
	CMyParamsPage(void);

// Dialog Data
	//{{AFX_DATA(CMyParamsPage)
	enum { IDD = IDD_PP_MY_PARAMETERS };
	//}}AFX_DATA

protected:

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CMyParamsPage)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

protected:
	virtual const CObjectProperty *	Pprops(void) const	{ return NULL; }
	virtual DWORD					Cprops(void) const	{ return 0; }

// Implementation
protected:
	BOOL	BAllRequiredFieldsPresent(void) const;

	// Generated message map functions
	//{{AFX_MSG(CMyParamsPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeRequiredField();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};  //*** class CMyParamsPage

/////////////////////////////////////////////////////////////////////////////

#endif // _RESPROP_H_
