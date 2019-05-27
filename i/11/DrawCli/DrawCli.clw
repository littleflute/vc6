; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CDrawView
LastTemplate=CPropertyPage
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "DrawCli.h"
LastPage=0

ClassCount=7
Class1=CDrawApp
Class2=CDrawDoc
Class3=CDrawView
Class4=CMainFrame

ResourceCount=7
Resource1=ID_POPUP_MENU
Resource2=IDR_MAINFRAME
Resource3=IDR_DRAW_TOOLBAR
Resource4=IDD_ABOUTBOX
Resource5=IDR_DRAWCLTYPE_CNTR_IP
Resource6=IDR_DRAWCLTYPE
Class5=CSplitFrame
Class6=CAboutDlg
Class7=CRectDlg
Resource7=IDD_PROP_RECT

[CLS:CDrawApp]
Type=0
HeaderFile=DrawCli.h
ImplementationFile=DrawCli.cpp
Filter=N

[CLS:CDrawDoc]
Type=0
HeaderFile=DrawDoc.h
ImplementationFile=DrawDoc.cpp
Filter=N
BaseClass=COleDocument
VirtualFilter=ODC
LastObject=CDrawDoc

[CLS:CDrawView]
Type=0
HeaderFile=DrawVw.h
ImplementationFile=DrawVw.cpp
Filter=C
BaseClass=CScrollView
VirtualFilter=VWC
LastObject=ID_EDIT_SELECT_ALL


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
BaseClass=CMDIFrameWnd
VirtualFilter=fWC
LastObject=CMainFrame


[CLS:CSplitFrame]
Type=0
HeaderFile=SplitFrm.h
ImplementationFile=SplitFrm.cpp
Filter=M


[CLS:CAboutDlg]
Type=0
HeaderFile=DrawCli.cpp
ImplementationFile=DrawCli.cpp
Filter=D
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_PRINT_SETUP
Command4=ID_FILE_MRU_FILE1
Command5=ID_APP_EXIT
Command6=ID_VIEW_TOOLBAR
Command7=ID_VIEW_STATUS_BAR
Command8=ID_HELP_FINDER
Command9=ID_APP_ABOUT
CommandCount=9

[TB:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
Command8=ID_APP_ABOUT
Command9=ID_CONTEXT_HELP
CommandCount=9

[MNU:IDR_DRAWCLTYPE]
Type=1
Class=CDrawView
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_CLOSE
Command4=ID_FILE_SAVE
Command5=ID_FILE_SAVE_AS
Command6=ID_FILE_PRINT
Command7=ID_FILE_PRINT_PREVIEW
Command8=ID_FILE_PRINT_SETUP
Command9=ID_FILE_MRU_FILE1
Command10=ID_APP_EXIT
Command11=ID_EDIT_UNDO
Command12=ID_EDIT_CUT
Command13=ID_EDIT_COPY
Command14=ID_EDIT_PASTE
Command15=ID_EDIT_CLEAR
Command16=ID_EDIT_PASTE_SPECIAL
Command17=ID_EDIT_SELECT_ALL
Command18=ID_EDIT_PROPERTIES
Command19=ID_OLE_INSERT_NEW
Command20=ID_OLE_EDIT_LINKS
Command21=ID_OLE_VERB_FIRST
Command22=ID_VIEW_PAPERCOLOR
Command23=ID_VIEW_GRID
Command24=ID_VIEW_SHOWOBJECTS
Command25=ID_VIEW_TOOLBAR
Command26=ID_VIEW_STATUS_BAR
Command27=ID_VIEW_DRAWTOOLBAR
Command28=ID_WINDOW_NEW
Command29=ID_WINDOW_CASCADE
Command30=ID_WINDOW_TILE_HORZ
Command31=ID_WINDOW_ARRANGE
Command32=ID_OBJECT_LINECOLOR
Command33=ID_OBJECT_FILLCOLOR
Command34=ID_OBJECT_MOVETOFRONT
Command35=ID_OBJECT_MOVETOBACK
Command36=ID_OBJECT_MOVEFORWARD
Command37=ID_OBJECT_MOVEBACK
Command38=ID_HELP_FINDER
Command39=ID_APP_ABOUT
CommandCount=39

[MNU:IDR_DRAWCLTYPE_CNTR_IP]
Type=1
Class=CDrawView
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_CLOSE
Command4=ID_FILE_SAVE
Command5=ID_FILE_SAVE_AS
Command6=ID_FILE_PRINT
Command7=ID_FILE_PRINT_PREVIEW
Command8=ID_FILE_PRINT_SETUP
Command9=ID_FILE_MRU_FILE1
Command10=ID_APP_EXIT
Command11=ID_WINDOW_NEW
Command12=ID_WINDOW_CASCADE
Command13=ID_WINDOW_TILE_HORZ
Command14=ID_WINDOW_ARRANGE
CommandCount=14

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
Command15=ID_CONTEXT_HELP
Command16=ID_HELP
Command17=ID_CANCEL_EDIT_CNTR
CommandCount=17

[ACL:IDR_DRAWCLTYPE_CNTR_IP]
Type=1
Class=CDrawView
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_NEXT_PANE
Command6=ID_PREV_PANE
Command7=ID_CONTEXT_HELP
Command8=ID_HELP
Command9=ID_CANCEL_EDIT_CNTR
CommandCount=9

[DLG:IDD_PROP_RECT]
Type=1
Class=CRectDlg
ControlCount=10
Control1=IDC_STATIC,static,1342308352
Control2=IDC_WEIGHT,edit,1350631552
Control3=IDC_SPIN1,msctls_updown32,1342177302
Control4=IDC_LINECOLOR_BUTTON,button,1342242816
Control5=IDC_LINECOLOR,static,1342181387
Control6=IDC_STATIC,button,1342177287
Control7=IDC_NOFILL,button,1342242819
Control8=IDC_FILLCOLOR_BUTTON,button,1342242816
Control9=IDC_FILLCOLOR,static,1342181387
Control10=IDC_STATIC,button,1342177287

[MNU:ID_POPUP_MENU]
Type=1
Class=?
CommandCount=0

[TB:IDR_DRAW_TOOLBAR]
Type=1
Class=?
Command1=ID_DRAW_SELECT
Command2=ID_DRAW_LINE
Command3=ID_DRAW_RECT
Command4=ID_DRAW_ROUNDRECT
Command5=ID_DRAW_ELLIPSE
Command6=ID_DRAW_CIRCLE
Command7=ID_OBJECT_MOVETOFRONT
Command8=ID_OBJECT_MOVETOBACK
Command9=ID_OBJECT_MOVEFORWARD
Command10=ID_OBJECT_MOVEBACK
Command11=ID_OBJECT_LINECOLOR
Command12=ID_OBJECT_FILLCOLOR
Command13=ID_OBJECT_TEXTCOLOR
CommandCount=13

[CLS:CRectDlg]
Type=0
HeaderFile=RectDlg.h
ImplementationFile=RectDlg.cpp
BaseClass=CPropertyPage
Filter=D
LastObject=CRectDlg
VirtualFilter=idWC

