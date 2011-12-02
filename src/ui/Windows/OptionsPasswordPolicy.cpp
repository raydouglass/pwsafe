/*
* Copyright (c) 2003-2011 Rony Shapiro <ronys@users.sourceforge.net>.
* All rights reserved. Use of the code is allowed under the
* Artistic License 2.0 terms, as specified in the LICENSE file
* distributed with this code, or available from
* http://www.opensource.org/licenses/artistic-license-2.0.php
*/
// OptionsPasswordPolicy.cpp : implementation file
//

#include "stdafx.h"
#include "passwordsafe.h"
#include "GeneralMsgBox.h"
#include "DboxMain.h"
#include "ThisMfcApp.h"    // For Help
#include "Options_PropertySheet.h"

#include "core/PWCharPool.h"
#include "core/PwsPlatform.h"
#include "core/PWSprefs.h"

#if defined(POCKET_PC)
#include "pocketpc/resource.h"
#else
#include "resource.h"
#include "resource3.h"  // String resources
#endif

#include "OptionsPasswordPolicy.h" // Must be after resource.h

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COptionsPasswordPolicy property page

IMPLEMENT_DYNAMIC(COptionsPasswordPolicy, COptions_PropertyPage)

const UINT COptionsPasswordPolicy::nonHex[COptionsPasswordPolicy::N_NOHEX] = {
  IDC_USELOWERCASE, IDC_USEUPPERCASE, IDC_USEDIGITS,
  IDC_USESYMBOLS, IDC_EASYVISION, IDC_PRONOUNCEABLE};

const UINT COptionsPasswordPolicy::LenTxts[COptionsPasswordPolicy::N_HEX_LENGTHS * 2] = {
  IDC_STATIC_LC1, IDC_STATIC_LC2, IDC_STATIC_UC1, IDC_STATIC_UC2,
  IDC_STATIC_DG1, IDC_STATIC_DG2, IDC_STATIC_SY1, IDC_STATIC_SY2};

const UINT COptionsPasswordPolicy::nonHexLengths[COptionsPasswordPolicy::N_HEX_LENGTHS] = {
  IDC_MINLOWERLENGTH, IDC_MINUPPERLENGTH, IDC_MINDIGITLENGTH, IDC_MINSYMBOLLENGTH};

const UINT COptionsPasswordPolicy::nonHexLengthSpins[COptionsPasswordPolicy::N_HEX_LENGTHS] = {
  IDC_SPINLOWERCASE, IDC_SPINUPPERCASE, IDC_SPINDIGITS, IDC_SPINSYMBOLS};

COptionsPasswordPolicy::COptionsPasswordPolicy(CWnd *pParent,
                                               st_Opt_master_data *pOPTMD)
  : COptions_PropertyPage(pParent,
                          COptionsPasswordPolicy::IDD, COptionsPasswordPolicy::IDD_SHORT,
                          pOPTMD),
  m_password(L""), m_UseNamedPolicy(FALSE)
{
  m_Symbols = M_Symbols();
  m_PWUseLowercase = M_PWUseLowercase();
  m_PWUseUppercase = M_PWUseUppercase();
  m_PWUseDigits = M_PWUseDigits();
  m_PWUseSymbols = M_PWUseSymbols();
  m_PWUseHexdigits = M_PWUseHexdigits();
  m_PWEasyVision = M_PWEasyVision();
  m_PWMakePronounceable = M_PWMakePronounceable();
  m_PWDefaultLength = M_PWDefaultLength();
  m_PWDigitMinLength = M_PWDigitMinLength();
  m_PWLowerMinLength = M_PWLowerMinLength();
  m_PWSymbolMinLength = M_PWSymbolMinLength();
  m_PWUpperMinLength = M_PWUpperMinLength();
  m_UseOwnSymbols = M_UseOwnSymbols();

  // These must be in the same order as their respective Control IDs
  // in COptionsPasswordPolicy::nonHex
  pnonHex[0] = &m_PWUseLowercase;
  pnonHex[1] = &m_PWUseUppercase;
  pnonHex[2] = &m_PWUseDigits;
  pnonHex[3] = &m_PWUseSymbols;
  pnonHex[4] = &m_PWEasyVision;
  pnonHex[5] = &m_PWMakePronounceable;
}

COptionsPasswordPolicy::~COptionsPasswordPolicy()
{
}

void COptionsPasswordPolicy::DoDataExchange(CDataExchange* pDX)
{
  COptions_PropertyPage::DoDataExchange(pDX);

  //{{AFX_DATA_MAP(COptionsPasswordPolicy)
  DDX_Text(pDX, IDC_DEFPWLENGTH, m_PWDefaultLength);
  DDX_Text(pDX, IDC_MINDIGITLENGTH, m_PWDigitMinLength);
  DDX_Text(pDX, IDC_MINLOWERLENGTH, m_PWLowerMinLength);
  DDX_Text(pDX, IDC_MINSYMBOLLENGTH, m_PWSymbolMinLength);
  DDX_Text(pDX, IDC_MINUPPERLENGTH, m_PWUpperMinLength);
  DDX_Check(pDX, IDC_USELOWERCASE, m_PWUseLowercase);
  DDX_Check(pDX, IDC_USEUPPERCASE, m_PWUseUppercase);
  DDX_Check(pDX, IDC_USEDIGITS, m_PWUseDigits);
  DDX_Check(pDX, IDC_USESYMBOLS, m_PWUseSymbols);
  DDX_Check(pDX, IDC_EASYVISION, m_PWEasyVision);
  DDX_Check(pDX, IDC_USEHEXDIGITS, m_PWUseHexdigits);
  DDX_Check(pDX, IDC_PRONOUNCEABLE, m_PWMakePronounceable);
  DDX_Check(pDX, IDC_USENAMED_POLICY, m_UseNamedPolicy);
  
  DDX_Radio(pDX, IDC_USEDEFAULTSYMBOLS, m_UseOwnSymbols);
  DDX_Control(pDX, IDC_OWNSYMBOLS, (CEdit&)m_SymbolsEdit);

  // Because we can show the generated password when used from Mangage->Generate
  DDX_Control(pDX, IDC_PASSWORD, m_ex_password);

  DDX_Control(pDX,  IDC_USELOWERCASE, m_chkbox[0]);
  DDX_Control(pDX,  IDC_USEUPPERCASE, m_chkbox[1]);
  DDX_Control(pDX,  IDC_USEDIGITS, m_chkbox[2]);
  DDX_Control(pDX,  IDC_USESYMBOLS, m_chkbox[3]);
  DDX_Control(pDX,  IDC_EASYVISION, m_chkbox[4]);
  DDX_Control(pDX,  IDC_PRONOUNCEABLE, m_chkbox[5]);
  DDX_Control(pDX,  IDC_USEHEXDIGITS, m_chkbox[6]);
  DDX_Control(pDX,  IDC_USEDEFAULTSYMBOLS, m_radiobtn[0]);
  DDX_Control(pDX,  IDC_USEOWNSYMBOLS, m_radiobtn[1]);

  if (M_uicaller() != IDS_OPTIONS) {
    DDX_Control(pDX, IDC_POLICYNAME, m_PolicyNameEdit);
    DDX_Control(pDX, IDC_POLICYLIST, m_cbxPolicyNames);
  }
  //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(COptionsPasswordPolicy, COptions_PropertyPage)
  //{{AFX_MSG_MAP(COptionsPasswordPolicy)
  ON_WM_CTLCOLOR()
  ON_BN_CLICKED(ID_HELP, OnHelp)

  ON_BN_CLICKED(IDC_USEHEXDIGITS, OnUseHexdigits)
  ON_BN_CLICKED(IDC_USELOWERCASE, OnUseLowerCase)
  ON_BN_CLICKED(IDC_USEUPPERCASE, OnUseUpperCase)
  ON_BN_CLICKED(IDC_USEDIGITS, OnUseDigits)
  ON_BN_CLICKED(IDC_USESYMBOLS, OnUseSymbols)
  ON_BN_CLICKED(IDC_EASYVISION, OnEasyVision)
  ON_BN_CLICKED(IDC_PRONOUNCEABLE, OnMakePronounceable)

  // Because we can show the generated password when used from Mangage->Generate
  ON_BN_CLICKED(IDC_GENERATEPASSWORD, OnGeneratePassword)
  ON_BN_CLICKED(IDC_COPYPASSWORD, OnCopyPassword)
  ON_EN_CHANGE(IDC_PASSWORD, OnENChangePassword)

  ON_BN_CLICKED(IDC_USEDEFAULTSYMBOLS, OnSymbols)
  ON_BN_CLICKED(IDC_USEOWNSYMBOLS, OnSymbols)

  ON_BN_CLICKED(IDC_USENAMED_POLICY, OnUseNamedPolicy)

  ON_EN_KILLFOCUS(IDC_POLICYNAME, OnENChangePolicyName)

  ON_CBN_SELCHANGE(IDC_POLICYLIST, OnNamesComboChanged)

  ON_MESSAGE(PSM_QUERYSIBLINGS, OnQuerySiblings)
  //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COptionsPasswordPolicy message handlers

BOOL COptionsPasswordPolicy::OnInitDialog() 
{
  COptions_PropertyPage::OnInitDialog();

  if (M_uicaller() == IDS_OPTIONS) {
    for (int i = 0; i < 7; i++) {
      m_chkbox[i].SetTextColour(CR_DATABASE_OPTIONS);
    }
    for (int i = 0; i < 2; i++) {
      m_radiobtn[i].SetTextColour(CR_DATABASE_OPTIONS);
      m_radiobtn[i].SetType(BS_AUTORADIOBUTTON);
    }
  }

  switch (M_uicaller()) {
    case IDS_OPTIONS:
      // These are only used in Manage -> Generate Password or Add/Edit Policy names
      GetDlgItem(IDC_GENERATEPASSWORD)->EnableWindow(FALSE);
      GetDlgItem(IDC_GENERATEPASSWORD)->ShowWindow(SW_HIDE);
      GetDlgItem(IDC_COPYPASSWORD)->EnableWindow(FALSE);
      GetDlgItem(IDC_COPYPASSWORD)->ShowWindow(SW_HIDE);
      GetDlgItem(IDC_PASSWORD)->EnableWindow(FALSE);
      GetDlgItem(IDC_PASSWORD)->ShowWindow(SW_HIDE);
      GetDlgItem(IDC_POLICYNAME)->EnableWindow(FALSE);
      GetDlgItem(IDC_POLICYNAME)->ShowWindow(SW_HIDE);
      GetDlgItem(IDC_POLICYLIST)->EnableWindow(FALSE);
      GetDlgItem(IDC_POLICYLIST)->ShowWindow(SW_HIDE);
      GetDlgItem(IDC_USENAMED_POLICY)->EnableWindow(FALSE);
      GetDlgItem(IDC_USENAMED_POLICY)->ShowWindow(SW_HIDE);
      GetDlgItem(IDC_STATIC_NAMEDPOLICY)->ShowWindow(SW_HIDE);
      break;
    case IDS_GENERATEPASSWORD:
    {
      // These are only used in Manage -> Add/Edit Policy names
      GetDlgItem(IDC_POLICYNAME)->EnableWindow(FALSE);
      GetDlgItem(IDC_POLICYNAME)->ShowWindow(SW_HIDE);

      // Used to generate passwords - list only enabled if checkbox set
      GetDlgItem(IDC_POLICYLIST)->EnableWindow(FALSE);
      GetDlgItem(IDC_POLICYLIST)->ShowWindow(SW_SHOW);
      GetDlgItem(IDC_USENAMED_POLICY)->EnableWindow(TRUE);
      GetDlgItem(IDC_USENAMED_POLICY)->ShowWindow(SW_SHOW);
      GetDlgItem(IDC_STATIC_NAMEDPOLICY)->ShowWindow(SW_HIDE);

      // Populate the combo box
      m_cbxPolicyNames.ResetContent();

      // Get all password policy names
      std::vector<std::wstring> vNames;
      M_pDbx()->GetPolicyNames(vNames);

      // Add Default
      CString cs_text(MAKEINTRESOURCE(IDS_DATABASE_DEFAULT));
      m_cbxPolicyNames.AddString(cs_text);

      for (std::vector<std::wstring>::iterator iter = vNames.begin();
           iter != vNames.end(); ++iter) {
        m_cbxPolicyNames.AddString(iter->c_str());
      }

      // Centre the OK button & change its text
      RECT rc, rcOK;
      CWnd *pOK = m_options_psh->GetDlgItem(IDOK);

      m_options_psh->GetClientRect(&rc);
      pOK->GetWindowRect(&rcOK);
      m_options_psh->ScreenToClient(&rcOK);
      int top = rcOK.top;
      pOK->GetClientRect(&rcOK);
      int left = (rc.right - rcOK.right) / 2;
      pOK->MoveWindow(left, top, rcOK.right, rcOK.bottom);

      CString cs_close(MAKEINTRESOURCE(IDS_CLOSE));
      pOK->SetWindowText(cs_close);

      // Hide the Cancel button
      m_options_psh->GetDlgItem(IDCANCEL)->EnableWindow(FALSE);
      m_options_psh->GetDlgItem(IDCANCEL)->ShowWindow(SW_HIDE);

      ApplyPasswordFont(GetDlgItem(IDC_PASSWORD));
      m_ex_password.SetSecure(false);
      // Remove password character so that the password is displayed
      m_ex_password.SetPasswordChar(0);
      break;
    }
    case IDS_PSWDPOLICY:
      // These are only used in Manage -> Generate Password
      GetDlgItem(IDC_GENERATEPASSWORD)->EnableWindow(FALSE);
      GetDlgItem(IDC_GENERATEPASSWORD)->ShowWindow(SW_HIDE);
      GetDlgItem(IDC_COPYPASSWORD)->EnableWindow(FALSE);
      GetDlgItem(IDC_COPYPASSWORD)->ShowWindow(SW_HIDE);
      GetDlgItem(IDC_PASSWORD)->EnableWindow(FALSE);
      GetDlgItem(IDC_PASSWORD)->ShowWindow(SW_HIDE);
      GetDlgItem(IDC_POLICYLIST)->EnableWindow(FALSE);
      GetDlgItem(IDC_POLICYLIST)->ShowWindow(SW_HIDE);
      GetDlgItem(IDC_USENAMED_POLICY)->EnableWindow(FALSE);
      GetDlgItem(IDC_USENAMED_POLICY)->ShowWindow(SW_HIDE);
      GetDlgItem(IDC_STATIC_NAMEDPOLICY)->ShowWindow(SW_SHOW);

      if (!m_policyname.IsEmpty() && m_iter->second.usecount > 0) {
        // Cannot edit the policy 'Name' if it is present and use count > 0
        m_PolicyNameEdit.SetReadOnly(TRUE);
      }

      m_PolicyNameEdit.SetWindowText(m_policyname);
      // Max. length of policy name is 255 - only 2 hex digits used for length
      // in database header
      m_PolicyNameEdit.SetLimitText(255);
      break;
  }

  CSpinButtonCtrl *pspin  = (CSpinButtonCtrl *)GetDlgItem(IDC_PWLENSPIN);
  CSpinButtonCtrl *pspinD = (CSpinButtonCtrl *)GetDlgItem(IDC_SPINDIGITS);
  CSpinButtonCtrl *pspinL = (CSpinButtonCtrl *)GetDlgItem(IDC_SPINLOWERCASE);
  CSpinButtonCtrl *pspinS = (CSpinButtonCtrl *)GetDlgItem(IDC_SPINSYMBOLS);
  CSpinButtonCtrl *pspinU = (CSpinButtonCtrl *)GetDlgItem(IDC_SPINUPPERCASE);

  pspin->SetBuddy(GetDlgItem(IDC_DEFPWLENGTH));
  pspin->SetRange(4, 1024);
  pspin->SetBase(10);
  pspin->SetPos(m_PWDefaultLength);

  pspinD->SetBuddy(GetDlgItem(IDC_MINDIGITLENGTH));
  pspinD->SetRange(0, 1024);
  pspinD->SetBase(10);
  pspinD->SetPos(m_PWDigitMinLength);

  pspinL->SetBuddy(GetDlgItem(IDC_MINLOWERLENGTH));
  pspinL->SetRange(0, 1024);
  pspinL->SetBase(10);
  pspinL->SetPos(m_PWLowerMinLength);

  pspinS->SetBuddy(GetDlgItem(IDC_MINSYMBOLLENGTH));
  pspinS->SetRange(0, 1024);
  pspinS->SetBase(10);
  pspinS->SetPos(m_PWSymbolMinLength);

  pspinU->SetBuddy(GetDlgItem(IDC_MINUPPERLENGTH));
  pspinU->SetRange(0, 1024);
  pspinU->SetBase(10);
  pspinU->SetPos(m_PWUpperMinLength);

  m_save[SAVE_LOWERCASE] = m_PWUseLowercase;
  m_save[SAVE_UPPERCASE] = m_PWUseUppercase;
  m_save[SAVE_DIGITS] = m_PWUseDigits;
  m_save[SAVE_SYMBOLS] = m_PWUseSymbols;
  m_save[SAVE_EASYVISION] = m_PWEasyVision;
  m_save[SAVE_PRONOUNCEABLE] = m_PWMakePronounceable;

  if (m_PWUseLowercase == TRUE && m_PWLowerMinLength == 0)
    M_PWLowerMinLength() = m_PWLowerMinLength = 1;
  if (m_PWUseUppercase == TRUE && m_PWUpperMinLength == 0)
    M_PWUpperMinLength() = m_PWUpperMinLength = 1;
  if (m_PWUseDigits == TRUE && m_PWDigitMinLength == 0)
    M_PWDigitMinLength() = m_PWDigitMinLength = 1;
  if (m_PWUseSymbols == TRUE && m_PWSymbolMinLength == 0)
    M_PWSymbolMinLength() = m_PWSymbolMinLength = 1;

  m_savelen[SAVE_LOWERCASE] = m_PWLowerMinLength;
  m_savelen[SAVE_UPPERCASE] = m_PWUpperMinLength;
  m_savelen[SAVE_DIGITS] = m_PWDigitMinLength;
  m_savelen[SAVE_SYMBOLS] = m_PWSymbolMinLength;

  // Set up the correct controls (enabled/disabled)
  do_hex(m_PWUseHexdigits == TRUE);
  do_easyorpronounceable(m_PWEasyVision == TRUE || m_PWMakePronounceable == TRUE);

  stringT st_symbols;
  CPasswordCharPool::GetDefaultSymbols(st_symbols);

  GetDlgItem(IDC_STATIC_DEFAULTSYMBOLS)->SetWindowText(st_symbols.c_str());
  m_SymbolsEdit.SetWindowText(m_Symbols);

  GetDlgItem(IDC_USEDEFAULTSYMBOLS)->EnableWindow(m_PWUseSymbols);
  GetDlgItem(IDC_USEOWNSYMBOLS)->EnableWindow(m_PWUseSymbols);
  GetDlgItem(IDC_OWNSYMBOLS)->EnableWindow((m_PWUseSymbols == TRUE && m_UseOwnSymbols == OWN_SYMBOLS) ? TRUE : FALSE);

  return TRUE;
}

LRESULT COptionsPasswordPolicy::OnQuerySiblings(WPARAM wParam, LPARAM )
{
  if (M_uicaller() == IDS_GENERATEPASSWORD)
    return 0L;

  if (UpdateData(TRUE) == FALSE)
    return 1L;

  if (wParam == PP_UPDATE_VARIABLES && Validate() == FALSE)
    return 1L;

  // Get symbol string from Edit control
  m_SymbolsEdit.GetWindowText(m_Symbols);

  // Have any of my fields been changed?
  switch (wParam) {
    case PP_DATA_CHANGED:
      if (M_uicaller() == IDS_PSWDPOLICY)
        return 0L;
      if (M_PWDefaultLength()     != m_PWDefaultLength     ||
          M_PWUseLowercase()      != m_PWUseLowercase      ||
          (m_PWUseLowercase       == TRUE &&
           M_PWLowerMinLength()   != m_PWLowerMinLength)   ||
          M_PWUseUppercase()      != m_PWUseUppercase      ||
          (m_PWUseUppercase       == TRUE &&
           M_PWUpperMinLength()   != m_PWUpperMinLength)   ||
          M_PWUseDigits()         != m_PWUseDigits         ||
          (m_PWUseDigits          == TRUE &&
           M_PWDigitMinLength()   != m_PWDigitMinLength)   ||
          M_PWUseSymbols()        != m_PWUseSymbols        ||
          (m_PWUseSymbols          = TRUE &&
           M_PWSymbolMinLength()  != m_PWSymbolMinLength)  ||
          M_PWEasyVision()        != m_PWEasyVision        ||
          M_PWUseHexdigits()      != m_PWUseHexdigits      ||
          M_PWMakePronounceable() != m_PWMakePronounceable ||
          M_UseOwnSymbols()       != m_UseOwnSymbols       ||
          (M_UseOwnSymbols()      == OWN_SYMBOLS &&
           M_Symbols()            != m_Symbols))
        return 1L;
      break;
    case PP_UPDATE_VARIABLES:
      // Since OnOK calls OnApply after we need to verify and/or
      // copy data into the entry - we do it ourselfs here first
      if (OnApply() == FALSE)
        return 1L;
      if (M_uicaller() == IDS_PSWDPOLICY)
        UpdatePasswordPolicy();
  }
  return 0L;
}

BOOL COptionsPasswordPolicy::OnApply()
{
  UpdateData(TRUE);

  M_Symbols() = m_Symbols;
  M_PWUseLowercase() = m_PWUseLowercase;
  M_PWUseUppercase() = m_PWUseUppercase;
  M_PWUseDigits() = m_PWUseDigits;
  M_PWUseSymbols() = m_PWUseSymbols;
  M_PWUseHexdigits() = m_PWUseHexdigits;
  M_PWEasyVision() = m_PWEasyVision;
  M_PWMakePronounceable() = m_PWMakePronounceable;
  M_PWDefaultLength() = m_PWDefaultLength;
  M_PWDigitMinLength() = m_PWDigitMinLength;
  M_PWLowerMinLength() = m_PWLowerMinLength;
  M_PWSymbolMinLength() = m_PWSymbolMinLength;
  M_PWUpperMinLength() = m_PWUpperMinLength;
  M_UseOwnSymbols() = m_UseOwnSymbols;

  return COptions_PropertyPage::OnApply();
}

BOOL COptionsPasswordPolicy::PreTranslateMessage(MSG* pMsg)
{
  if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_F1) {
    PostMessage(WM_COMMAND, MAKELONG(ID_HELP, BN_CLICKED), NULL);
    return TRUE;
  }

  return COptions_PropertyPage::PreTranslateMessage(pMsg);
}

BOOL COptionsPasswordPolicy::OnKillActive()
{
  if (Validate() == FALSE)
    return FALSE;

  return COptions_PropertyPage::OnKillActive();
}

void COptionsPasswordPolicy::OnHelp()
{
  CString cs_HelpTopic;
  cs_HelpTopic = app.GetHelpFileName() + L"::/html/password_policies.html";
  HtmlHelp(DWORD_PTR((LPCWSTR)cs_HelpTopic), HH_DISPLAY_TOPIC);
}

void COptionsPasswordPolicy::SetPolicyData(st_PSWDPolicy &st_pp,
                                           CString &policyname,
                                           PSWDPolicyMap &MapPSWDPLC)
{
  // Only called for Password Policies
  if (M_uicaller() != IDS_PSWDPOLICY)
    return;

  m_default_st_pp = st_pp;
  m_MapPSWDPLC = MapPSWDPLC;
  m_policyname = m_oldpolicyname = policyname;
  m_iter = m_policyname.IsEmpty() ? m_MapPSWDPLC.end() :
                                    m_MapPSWDPLC.find(StringX((LPCWSTR)m_policyname));

  // Check the find worked above - if PolicyName not empty, it must be in the map!
  if (!m_policyname.IsEmpty())
    ASSERT(m_iter != m_MapPSWDPLC.end());

  // If New, use default values; otherwise use this policy's values
  st_PSWDPolicy xst_pp = m_policyname.IsEmpty() ? m_default_st_pp : m_iter->second;
  
  m_PWUseLowercase = M_PWUseLowercase() =
    (xst_pp.pwp.flags & PWSprefs::PWPolicyUseLowercase) == 
                       PWSprefs::PWPolicyUseLowercase;
  m_PWUseUppercase = M_PWUseUppercase() =
    (xst_pp.pwp.flags & PWSprefs::PWPolicyUseUppercase) == 
                       PWSprefs::PWPolicyUseUppercase;
  m_PWUseDigits = M_PWUseDigits() =
    (xst_pp.pwp.flags & PWSprefs::PWPolicyUseDigits) == 
                       PWSprefs::PWPolicyUseDigits;
  m_PWUseSymbols = M_PWUseSymbols() =
    (xst_pp.pwp.flags & PWSprefs::PWPolicyUseSymbols) == 
                       PWSprefs::PWPolicyUseSymbols;
  m_PWUseHexdigits = M_PWUseHexdigits() =
    (xst_pp.pwp.flags & PWSprefs::PWPolicyUseHexDigits) == 
                       PWSprefs::PWPolicyUseHexDigits;
  m_PWEasyVision = M_PWEasyVision() =
    (xst_pp.pwp.flags & PWSprefs::PWPolicyUseEasyVision) == 
                       PWSprefs::PWPolicyUseEasyVision;
  m_PWMakePronounceable = M_PWMakePronounceable() =
    (xst_pp.pwp.flags & PWSprefs::PWPolicyMakePronounceable) == 
                       PWSprefs::PWPolicyMakePronounceable;
  m_PWDefaultLength = M_PWDefaultLength() = xst_pp.pwp.length;
  m_PWDigitMinLength = M_PWDigitMinLength() = xst_pp.pwp.digitminlength;
  m_PWLowerMinLength = M_PWLowerMinLength() = xst_pp.pwp.lowerminlength;
  m_PWSymbolMinLength = M_PWSymbolMinLength() = xst_pp.pwp.symbolminlength;
  m_PWUpperMinLength = M_PWUpperMinLength() = xst_pp.pwp.upperminlength;
 
  CString cs_symbols = xst_pp.symbols.c_str();
  m_Symbols = M_Symbols() = cs_symbols;
  m_UseOwnSymbols = M_UseOwnSymbols() = cs_symbols.IsEmpty() ? DEFAULT_SYMBOLS : OWN_SYMBOLS;
}

void COptionsPasswordPolicy::OnNamesComboChanged()
{
  UpdateData(TRUE);

  int index = m_cbxPolicyNames.GetCurSel();
  m_cbxPolicyNames.GetLBText(index, m_policyname);
}

void COptionsPasswordPolicy::do_hex(const bool bHex)
{
  CString cs_value;
  int i;
  if (bHex) {
    // true means enable hex, save state for possible re-enable
    // Disable non-hex controls
    for (i = 0; i < N_NOHEX; i++) {
      UINT id = nonHex[i];
      m_save[i] = ((CButton*)GetDlgItem(id))->GetCheck();
      ((CButton*)GetDlgItem(id))->SetCheck(BST_UNCHECKED);
      GetDlgItem(id)->EnableWindow(FALSE);
      (*pnonHex[i]) = 0; // zero variable - otherwise Hexcheck wont work
    }

    for (i = 0; i < N_HEX_LENGTHS; i++) {
      UINT id = nonHexLengths[i];
      GetDlgItem(id)->SetWindowText(L"0");
      GetDlgItem(id)->EnableWindow(FALSE);

      GetDlgItem(nonHexLengthSpins[i])->EnableWindow(FALSE);
      GetDlgItem(LenTxts[i * 2])->EnableWindow(FALSE);
      GetDlgItem(LenTxts[i * 2 + 1])->EnableWindow(FALSE);
    }

    GetDlgItem(IDC_USEDEFAULTSYMBOLS)->EnableWindow(FALSE);
    GetDlgItem(IDC_USEOWNSYMBOLS)->EnableWindow(FALSE);
    GetDlgItem(IDC_STATIC_DEFAULTSYMBOLS)->EnableWindow(FALSE);
    GetDlgItem(IDC_OWNSYMBOLS)->EnableWindow(FALSE);

    m_savelen[SAVE_LOWERCASE] = m_PWLowerMinLength;
    m_savelen[SAVE_UPPERCASE] = m_PWUpperMinLength;
    m_savelen[SAVE_DIGITS] = m_PWDigitMinLength;
    m_savelen[SAVE_SYMBOLS] = m_PWSymbolMinLength;
  } else {
    // non-hex, restore state
    // Enable non-hex controls and restore checked state
    for (i = 0; i < N_NOHEX; i++) {
      UINT id = nonHex[i];
      GetDlgItem(id)->EnableWindow(TRUE);
      ((CButton*)GetDlgItem(id))->SetCheck(m_save[i]);
      (*pnonHex[i]) = m_save[i]; // Restore variable
    }

    for (i = 0; i < N_HEX_LENGTHS; i++) {
      UINT id = nonHexLengths[i];
      cs_value.Format(L"%d", m_savelen[i]);
      GetDlgItem(id)->SetWindowText(cs_value);
      GetDlgItem(id)->EnableWindow(m_save[i]);
      GetDlgItem(nonHexLengthSpins[i])->EnableWindow(m_save[i]);
      GetDlgItem(LenTxts[i * 2])->EnableWindow(m_save[i]);
      GetDlgItem(LenTxts[i * 2 + 1])->EnableWindow(m_save[i]);
    }

    BOOL bEnable = (IsDlgButtonChecked(IDC_USESYMBOLS) == BST_CHECKED &&
                   m_PWEasyVision == FALSE && m_PWMakePronounceable == FALSE) ? TRUE : FALSE;
    GetDlgItem(IDC_USEDEFAULTSYMBOLS)->EnableWindow(bEnable);
    GetDlgItem(IDC_USEOWNSYMBOLS)->EnableWindow(bEnable);
    GetDlgItem(IDC_STATIC_DEFAULTSYMBOLS)->EnableWindow(bEnable);
    GetDlgItem(IDC_OWNSYMBOLS)->EnableWindow((bEnable == TRUE && m_UseOwnSymbols == OWN_SYMBOLS) ?
                                             TRUE : FALSE);

    m_PWLowerMinLength = m_savelen[SAVE_LOWERCASE];
    m_PWUpperMinLength = m_savelen[SAVE_UPPERCASE];
    m_PWDigitMinLength = m_savelen[SAVE_DIGITS];
    m_PWSymbolMinLength = m_savelen[SAVE_SYMBOLS];
  }
}

void COptionsPasswordPolicy::do_easyorpronounceable(const bool bSet)
{
  // Can't have minimum lengths!
  if ((m_PWEasyVision == TRUE  || m_PWMakePronounceable == TRUE) &&
      (m_PWDigitMinLength > 1  || m_PWLowerMinLength > 1 || 
       m_PWSymbolMinLength > 1 || m_PWUpperMinLength > 1)) {
    CGeneralMsgBox gmb;
    gmb.AfxMessageBox(IDS_CANTSPECIFYMINNUMBER);
  }

  CString cs_value;
  int i;
  if (bSet) {
    for (i = 0; i < N_HEX_LENGTHS; i++) {
      GetDlgItem(nonHexLengths[i])->ShowWindow(SW_HIDE);
      GetDlgItem(nonHexLengthSpins[i])->ShowWindow(SW_HIDE);
      GetDlgItem(LenTxts[2 * i])->ShowWindow(SW_HIDE);
      GetDlgItem(LenTxts[2 * i + 1])->ShowWindow(SW_HIDE);
    }

    GetDlgItem(IDC_USEDEFAULTSYMBOLS)->EnableWindow(FALSE);
    GetDlgItem(IDC_USEOWNSYMBOLS)->EnableWindow(FALSE);
    GetDlgItem(IDC_STATIC_DEFAULTSYMBOLS)->EnableWindow((IsDlgButtonChecked(IDC_USESYMBOLS) == BST_CHECKED) ? TRUE : FALSE);
    GetDlgItem(IDC_OWNSYMBOLS)->EnableWindow(FALSE);

    m_savelen[SAVE_LOWERCASE] = m_PWLowerMinLength;
    m_savelen[SAVE_UPPERCASE] = m_PWUpperMinLength;
    m_savelen[SAVE_DIGITS] = m_PWDigitMinLength;
    m_savelen[SAVE_SYMBOLS] = m_PWSymbolMinLength;
  } else {
    for (i = 0; i < N_HEX_LENGTHS; i++) {
      GetDlgItem(nonHexLengths[i])->ShowWindow(SW_SHOW);
      GetDlgItem(nonHexLengthSpins[i])->ShowWindow(SW_SHOW);
      GetDlgItem(LenTxts[2 * i])->ShowWindow(SW_SHOW);
      GetDlgItem(LenTxts[2 * i + 1])->ShowWindow(SW_SHOW);
    }

    BOOL bEnable = (IsDlgButtonChecked(IDC_USESYMBOLS) == BST_CHECKED) ? TRUE : FALSE;
    GetDlgItem(IDC_USEDEFAULTSYMBOLS)->EnableWindow(bEnable);
    GetDlgItem(IDC_USEOWNSYMBOLS)->EnableWindow(bEnable);
    GetDlgItem(IDC_STATIC_DEFAULTSYMBOLS)->EnableWindow(bEnable);
    GetDlgItem(IDC_OWNSYMBOLS)->EnableWindow((bEnable == TRUE && m_UseOwnSymbols == OWN_SYMBOLS) ?
                                             TRUE : FALSE);

    m_PWLowerMinLength = m_savelen[SAVE_LOWERCASE];
    m_PWUpperMinLength = m_savelen[SAVE_UPPERCASE];
    m_PWDigitMinLength = m_savelen[SAVE_DIGITS];
    m_PWSymbolMinLength = m_savelen[SAVE_SYMBOLS];
  }
}

void COptionsPasswordPolicy::OnUseLowerCase() 
{
  UpdateData(TRUE);
  BOOL bChecked = (IsDlgButtonChecked(IDC_USELOWERCASE) == BST_CHECKED) ? TRUE : FALSE;

  GetDlgItem(IDC_MINLOWERLENGTH)->EnableWindow(bChecked);
  GetDlgItem(IDC_SPINLOWERCASE)->EnableWindow(bChecked);
  GetDlgItem(IDC_STATIC_LC1)->EnableWindow(bChecked);
  GetDlgItem(IDC_STATIC_LC2)->EnableWindow(bChecked);
  m_PWLowerMinLength = bChecked;  // Based on FALSE=0 & TRUE=1
  UpdateData(FALSE);
}

void COptionsPasswordPolicy::OnUseUpperCase() 
{
  UpdateData(TRUE);
  BOOL bChecked = (IsDlgButtonChecked(IDC_USEUPPERCASE) == BST_CHECKED) ? TRUE : FALSE;

  GetDlgItem(IDC_MINUPPERLENGTH)->EnableWindow(bChecked);
  GetDlgItem(IDC_SPINUPPERCASE)->EnableWindow(bChecked);
  GetDlgItem(IDC_STATIC_UC1)->EnableWindow(bChecked);
  GetDlgItem(IDC_STATIC_UC2)->EnableWindow(bChecked);
  m_PWUpperMinLength = bChecked;  // Based on FALSE=0 & TRUE=1
  UpdateData(FALSE);
}

void COptionsPasswordPolicy::OnUseDigits() 
{
  UpdateData(TRUE);
  BOOL bChecked = (IsDlgButtonChecked(IDC_USEDIGITS) == BST_CHECKED) ? TRUE : FALSE;

  GetDlgItem(IDC_MINDIGITLENGTH)->EnableWindow(bChecked);
  GetDlgItem(IDC_SPINDIGITS)->EnableWindow(bChecked);
  GetDlgItem(IDC_STATIC_DG1)->EnableWindow(bChecked);
  GetDlgItem(IDC_STATIC_DG2)->EnableWindow(bChecked);
  m_PWDigitMinLength = bChecked;  // Based on FALSE=0 & TRUE=1
  UpdateData(FALSE);
}

void COptionsPasswordPolicy::OnUseSymbols() 
{
  UpdateData(TRUE);

  BOOL bChecked = (IsDlgButtonChecked(IDC_USESYMBOLS) == BST_CHECKED &&
                   m_PWEasyVision == FALSE && m_PWMakePronounceable == FALSE) ? TRUE : FALSE;

  GetDlgItem(IDC_MINSYMBOLLENGTH)->EnableWindow(bChecked);
  GetDlgItem(IDC_SPINSYMBOLS)->EnableWindow(bChecked);
  GetDlgItem(IDC_STATIC_SY1)->EnableWindow(bChecked);
  GetDlgItem(IDC_STATIC_SY2)->EnableWindow(bChecked);

  GetDlgItem(IDC_USEDEFAULTSYMBOLS)->EnableWindow(bChecked);
  GetDlgItem(IDC_USEOWNSYMBOLS)->EnableWindow(bChecked);
  GetDlgItem(IDC_STATIC_DEFAULTSYMBOLS)->EnableWindow((IsDlgButtonChecked(IDC_USESYMBOLS) == BST_CHECKED) ? TRUE : FALSE);
  GetDlgItem(IDC_OWNSYMBOLS)->EnableWindow((bChecked == TRUE && m_UseOwnSymbols == OWN_SYMBOLS) ? TRUE : FALSE);

  m_PWSymbolMinLength = bChecked;  // Based on FALSE=0 & TRUE=1
  UpdateData(FALSE);
}

void COptionsPasswordPolicy::OnUseHexdigits() 
{
  UpdateData(TRUE);
  do_hex(IsDlgButtonChecked(IDC_USEHEXDIGITS) == BST_CHECKED);
  // Do not use UpdateData(FALSE) here or
  // all the good work in "do_hex" will be undone
}

void COptionsPasswordPolicy::OnEasyVision() 
{
  UpdateData(TRUE);

  if (m_PWEasyVision && m_PWMakePronounceable) {
    CGeneralMsgBox gmb;
    ((CButton*)GetDlgItem(IDC_EASYVISION))->SetCheck(FALSE);
    gmb.AfxMessageBox(IDS_PROVISMUTUALLYEXCL);
    m_PWEasyVision = FALSE;
  }

  const bool bChecked = (IsDlgButtonChecked(IDC_EASYVISION) == BST_CHECKED);

  do_easyorpronounceable(bChecked);
  // Do not use UpdateData(FALSE) here or
  // all the good work in "do_easyorpronounceable" will be undone
}

void COptionsPasswordPolicy::OnMakePronounceable() 
{
  UpdateData(TRUE);

  if (m_PWEasyVision && m_PWMakePronounceable) {
    CGeneralMsgBox gmb;
    ((CButton*)GetDlgItem(IDC_PRONOUNCEABLE))->SetCheck(FALSE);
    gmb.AfxMessageBox(IDS_PROVISMUTUALLYEXCL);
    m_PWMakePronounceable = FALSE;
  }

  const bool bChecked = (IsDlgButtonChecked(IDC_PRONOUNCEABLE) == BST_CHECKED);

  do_easyorpronounceable(bChecked);
  // Do not use UpdateData(FALSE) here or
  // all the good work in "do_easyorpronounceable" will be undone
}

void COptionsPasswordPolicy::OnSymbols()
{
  m_UseOwnSymbols = ((CButton *)GetDlgItem(IDC_USEDEFAULTSYMBOLS))->GetCheck() == BST_CHECKED ?
                        DEFAULT_SYMBOLS : OWN_SYMBOLS;

  GetDlgItem(IDC_OWNSYMBOLS)->EnableWindow(m_UseOwnSymbols == DEFAULT_SYMBOLS ? FALSE : TRUE);
  if (m_UseOwnSymbols == OWN_SYMBOLS)
    GetDlgItem(IDC_OWNSYMBOLS)->SetFocus();
}

BOOL COptionsPasswordPolicy::Validate()
{
  CGeneralMsgBox gmb;
  // Check that options, as set, are valid.
  if (m_PWUseHexdigits &&
     (m_PWUseLowercase || m_PWUseUppercase || m_PWUseDigits ||
      m_PWUseSymbols || m_PWEasyVision || m_PWMakePronounceable)) {
    gmb.AfxMessageBox(IDS_HEXMUTUALLYEXCL);
    return FALSE;
  }

  if (m_PWUseHexdigits) {
    if (m_PWDefaultLength % 2 != 0) {
      gmb.AfxMessageBox(IDS_HEXMUSTBEEVEN);
      return FALSE;
    }
  } else
  if (!m_PWUseLowercase && !m_PWUseUppercase &&
      !m_PWUseDigits && !m_PWUseSymbols) {
    gmb.AfxMessageBox(IDS_MUSTHAVEONEOPTION);
    return FALSE;
  }

  if ((m_PWDefaultLength < 4) || (m_PWDefaultLength > 1024)) {
    gmb.AfxMessageBox(IDS_DEFAULTPWLENGTH);
    ((CEdit*)GetDlgItem(IDC_DEFPWLENGTH))->SetFocus();
    return FALSE;
  }

  if (!(m_PWUseHexdigits || m_PWEasyVision || m_PWMakePronounceable) &&
      (m_PWDigitMinLength + m_PWLowerMinLength + 
       m_PWSymbolMinLength + m_PWUpperMinLength) > m_PWDefaultLength) {
    gmb.AfxMessageBox(IDS_DEFAULTPWLENGTHTOOSMALL);
    ((CEdit*)GetDlgItem(IDC_DEFPWLENGTH))->SetFocus();
    return FALSE;
  }

  if ((m_PWUseHexdigits || m_PWEasyVision || m_PWMakePronounceable))
    m_PWDigitMinLength = m_PWLowerMinLength = 
       m_PWSymbolMinLength = m_PWUpperMinLength = 1;

  if (M_uicaller() == IDS_PSWDPOLICY) {
    if (m_policyname.IsEmpty() || 
         (m_policyname != m_oldpolicyname && !VerifyPolicynameUnique(m_policyname))) {
      gmb.AfxMessageBox(IDS_INVALIDPOLICYNAME);
      ((CEdit*)GetDlgItem(IDC_POLICYNAME))->SetFocus();
      return FALSE;
    }
  }
 
  //End check
  return TRUE;
}

void COptionsPasswordPolicy::OnGeneratePassword()
{
  UpdateData(TRUE);

  // Use common validation
  if (Validate() == FALSE)
    return;

  PWPolicy pwp;
  stringT st_symbols;

  pwp.Empty();

  if (m_UseNamedPolicy == BST_UNCHECKED) {
    if (m_PWUseLowercase == TRUE)
      pwp.flags |= PWSprefs::PWPolicyUseLowercase;
    if (m_PWUseUppercase == TRUE)
      pwp.flags |= PWSprefs::PWPolicyUseUppercase;
    if (m_PWUseDigits == TRUE)
      pwp.flags |= PWSprefs::PWPolicyUseDigits;
    if (m_PWUseSymbols == TRUE)
      pwp.flags |= PWSprefs::PWPolicyUseSymbols;
    if (m_PWUseHexdigits == TRUE)
      pwp.flags |= PWSprefs::PWPolicyUseHexDigits;
    if (m_PWEasyVision == TRUE)
      pwp.flags |= PWSprefs::PWPolicyUseEasyVision;
    if (m_PWMakePronounceable == TRUE)
      pwp.flags |= PWSprefs::PWPolicyMakePronounceable;
    pwp.length = m_PWDefaultLength;
    pwp.digitminlength = m_PWDigitMinLength;
    pwp.lowerminlength = m_PWLowerMinLength;
    pwp.symbolminlength = m_PWSymbolMinLength;
    pwp.upperminlength = m_PWUpperMinLength;
  
    if (m_UseOwnSymbols == OWN_SYMBOLS) {
      m_SymbolsEdit.GetWindowText(m_Symbols);
      st_symbols = LPCWSTR(m_Symbols);
    } else
      CPasswordCharPool::GetDefaultSymbols(st_symbols);
  } else {
    st_PSWDPolicy st_pp;
    StringX sxPolicyName(m_policyname);
    M_pDbx()->GetPolicyFromName(sxPolicyName, st_pp);

    pwp = st_pp.pwp;
    if (st_pp.symbols.empty()) {
      CPasswordCharPool::GetDefaultSymbols(st_symbols);
    } else {
      st_symbols = st_pp.symbols.c_str();
    }
  }

  StringX passwd;
  M_pDbx()->MakeRandomPassword(passwd, pwp, st_symbols.c_str(), false);
  m_password = passwd.c_str();
  m_ex_password.SetWindowText(m_password);
  m_ex_password.Invalidate();
  UpdateData(FALSE);
}

void COptionsPasswordPolicy::OnCopyPassword()
{
  UpdateData(TRUE);

  M_pDbx()->SetClipboardData(m_password);
  M_pDbx()->UpdateLastClipboardAction(CItemData::PASSWORD);
}

void COptionsPasswordPolicy::OnENChangePassword()
{
  UpdateData(TRUE);

  m_ex_password.GetWindowText((CString &)m_password);
}

void COptionsPasswordPolicy::OnENChangePolicyName()
{
  UpdateData(TRUE);

  m_PolicyNameEdit.GetWindowText((CString &)m_policyname);
}

void COptionsPasswordPolicy::OnUseNamedPolicy()
{
  BOOL bEnable = ((CButton *)GetDlgItem(IDC_USENAMED_POLICY))->GetCheck() == BST_CHECKED ?
                           TRUE : FALSE;

  GetDlgItem(IDC_POLICYLIST)->EnableWindow(bEnable);
}

HBRUSH COptionsPasswordPolicy::OnCtlColor(CDC *pDC, CWnd *pWnd, UINT nCtlColor)
{
  // Database preferences - associated static text
  HBRUSH hbr = CPWPropertyPage::OnCtlColor(pDC, pWnd, nCtlColor);

  if (M_uicaller() != IDS_OPTIONS)
    return hbr;

  switch (pWnd->GetDlgCtrlID()) {
    case IDC_STATIC_PSWDLENGTH:
    case IDC_STATIC_LC1:
    case IDC_STATIC_LC2:
    case IDC_STATIC_UC1:
    case IDC_STATIC_UC2:
    case IDC_STATIC_DG1:
    case IDC_STATIC_DG2:
    case IDC_STATIC_SY1:
    case IDC_STATIC_SY2:
      pDC->SetTextColor(CR_DATABASE_OPTIONS);
      pDC->SetBkMode(TRANSPARENT);
      break;
  }

  return hbr;
}

void COptionsPasswordPolicy::UpdatePasswordPolicy()
{
  ASSERT(!m_policyname.IsEmpty());

  st_PSWDPolicy st_pp;
  st_pp.pwp.flags = 0;
  if (M_PWUseLowercase() == TRUE)
    st_pp.pwp.flags |= PWSprefs::PWPolicyUseLowercase;
  if (M_PWUseUppercase() == TRUE)
    st_pp.pwp.flags |= PWSprefs::PWPolicyUseUppercase;
  if (M_PWUseDigits() == TRUE)
    st_pp.pwp.flags |= PWSprefs::PWPolicyUseDigits;
  if (M_PWUseSymbols() == TRUE)
    st_pp.pwp.flags |= PWSprefs::PWPolicyUseSymbols;
  if (M_PWUseHexdigits() == TRUE)
    st_pp.pwp.flags |= PWSprefs::PWPolicyUseHexDigits;
  if (M_PWEasyVision() == TRUE)
    st_pp.pwp.flags |= PWSprefs::PWPolicyUseEasyVision;
  if (M_PWMakePronounceable() == TRUE)
    st_pp.pwp.flags |= PWSprefs::PWPolicyMakePronounceable;
  
  st_pp.pwp.length = M_PWDefaultLength();
  st_pp.pwp.digitminlength = M_PWDigitMinLength();
  st_pp.pwp.lowerminlength = M_PWLowerMinLength();
  st_pp.pwp.symbolminlength = M_PWSymbolMinLength();
  st_pp.pwp.upperminlength = M_PWUpperMinLength();

  st_pp.symbols = (M_PWUseSymbols() == TRUE && M_UseOwnSymbols() == OWN_SYMBOLS) ?
                         m_Symbols : L"";

  StringX sxPolicyName(m_policyname), sx_OldPolicyName(m_oldpolicyname);
  if (!m_oldpolicyname.IsEmpty() && m_policyname != m_oldpolicyname) {
    // Delete old policy using old name
    PSWDPolicyMapIter iter = m_MapPSWDPLC.find(sx_OldPolicyName);
    if (iter != m_MapPSWDPLC.end())
      m_MapPSWDPLC.erase(iter);
  }

  // Insert the new name
  m_MapPSWDPLC[sxPolicyName] = st_pp;
}
