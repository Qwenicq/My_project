/////////////////////////////////////////////////////////////////////////////
//
//	Copyright (c) 2022 <company name>
//
//	Module Name:
//		ResProp.cpp
//
//	Abstract:
//		Implementation of the resource extension property page classes.
//
//	Author:
//		<name> (<e-mail name>) Mmmm DD, 2022
//
//	Revision History:
//
//	Notes:
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Ê÷Ex.h"
#include "ResProp.h"
#include "ExtObj.h"
#include "DDxDDv.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyParamsPage property page
/////////////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNCREATE(CMyParamsPage, CBasePropertyPage)

/////////////////////////////////////////////////////////////////////////////
// Message Maps

BEGIN_MESSAGE_MAP(CMyParamsPage, CBasePropertyPage)
	//{{AFX_MSG_MAP(CMyParamsPage)
	//}}AFX_MSG_MAP
	// TODO: Modify the following lines to represent the data displayed on this page.
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
//++
//
//	CMyParamsPage::CMyParamsPage
//
//	Routine Description:
//		Default constructor.
//
//	Arguments:
//		None.
//
//	Return Value:
//		None.
//
//--
/////////////////////////////////////////////////////////////////////////////
CMyParamsPage::CMyParamsPage(void) : CBasePropertyPage(CMyParamsPage::IDD)
{
	// TODO: Modify the following lines to represent the data displayed on this page.
	//{{AFX_DATA_INIT(CMyParamsPage)
	//}}AFX_DATA_INIT

	// Setup the property array.
	{
	}  // Setup the property array

	m_iddPropertyPage = IDD_PP_MY_PARAMETERS;
	m_iddWizardPage = IDD_WIZ_MY_PARAMETERS;

}  //*** CMyParamsPage::CMyParamsPage()

/////////////////////////////////////////////////////////////////////////////
//++
//
//	CMyParamsPage::DoDataExchange
//
//	Routine Description:
//		Do data exchange between the dialog and the class.
//
//	Arguments:
//		pDX		[IN OUT] Data exchange object 
//
//	Return Value:
//		None.
//
//--
/////////////////////////////////////////////////////////////////////////////
void CMyParamsPage::DoDataExchange(CDataExchange * pDX)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Modify the following lines to represent the data displayed on this page.
	//{{AFX_DATA_MAP(CMyParamsPage)
	//}}AFX_DATA_MAP

	// Handle numeric parameters.
	if (!BBackPressed())
	{
	}  // if:  back button not pressed

	// TODO: Add any additional field validation here.
	if (pDX->m_bSaveAndValidate)
	{
		// Make sure all required fields are present.
		if (!BBackPressed())
		{
		}  // if:  back button not pressed
	}  // if:  saving data from dialog

	CBasePropertyPage::DoDataExchange(pDX);

}  //*** CMyParamsPage::DoDataExchange()

/////////////////////////////////////////////////////////////////////////////
//++
//
//	CMyParamsPage::OnInitDialog
//
//	Routine Description:
//		Handler for the WM_INITDIALOG message.
//
//	Arguments:
//		None.
//
//	Return Value:
//		TRUE		We need the focus to be set for us.
//		FALSE		We already set the focus to the proper control.
//
//--
/////////////////////////////////////////////////////////////////////////////
BOOL CMyParamsPage::OnInitDialog(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CBasePropertyPage::OnInitDialog();

	// TODO:
	// Limit the size of the text that can be entered in edit controls.

	return TRUE;	// return TRUE unless you set the focus to a control
					// EXCEPTION: OCX Property Pages should return FALSE

}  //*** CMyParamsPage::OnInitDialog()

/////////////////////////////////////////////////////////////////////////////
//++
//
//	CMyParamsPage::OnSetActive
//
//	Routine Description:
//		Handler for the PSN_SETACTIVE message.
//
//	Arguments:
//		None.
//
//	Return Value:
//		TRUE	Page successfully initialized.
//		FALSE	Page not initialized.
//
//--
/////////////////////////////////////////////////////////////////////////////
BOOL CMyParamsPage::OnSetActive(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// Enable/disable the Next/Finish button.
	if (BWizard())
		EnableNext(BAllRequiredFieldsPresent());

	return CBasePropertyPage::OnSetActive();

}  //*** CMyParamsPage::OnSetActive()

/////////////////////////////////////////////////////////////////////////////
//++
//
//	CMyParamsPage::OnChangeRequiredField
//
//	Routine Description:
//		Handler for the EN_CHANGE message on the Share name or Path edit
//		controls.
//
//	Arguments:
//		None.
//
//	Return Value:
//		None.
//
//--
/////////////////////////////////////////////////////////////////////////////
void CMyParamsPage::OnChangeRequiredField(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	OnChangeCtrl();

	if (BWizard())
		EnableNext(BAllRequiredFieldsPresent());

}  //*** CMyParamsPage::OnChangeRequiredField()

/////////////////////////////////////////////////////////////////////////////
//++
//
//	CMyParamsPage::BAllRequiredFieldsPresent
//
//	Routine Description:
//		Handler for the EN_CHANGE message on the Share name or Path edit
//		controls.
//
//	Arguments:
//		None.
//
//	Return Value:
//		None.
//
//--
/////////////////////////////////////////////////////////////////////////////
BOOL CMyParamsPage::BAllRequiredFieldsPresent(void) const
{
	return TRUE;

}  //*** CMyParamsPage::BAllRequiredFieldsPresent()
