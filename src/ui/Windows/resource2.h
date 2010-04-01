//{{NO_DEPENDENCIES}}

// Non-editable by VS2005

// Menus and Toolbars

/*

*** WARNING *** *** WARNING *** *** WARNING *** *** WARNING *** *** WARNING ***
*** WARNING *** *** WARNING *** *** WARNING *** *** WARNING *** *** WARNING ***
*** WARNING *** *** WARNING *** *** WARNING *** *** WARNING *** *** WARNING ***

Do NOT change the value of any resource used in a menu from V3.17 onwards.

*** WARNING *** *** WARNING *** *** WARNING *** *** WARNING *** *** WARNING ***
*** WARNING *** *** WARNING *** *** WARNING *** *** WARNING *** *** WARNING ***
*** WARNING *** *** WARNING *** *** WARNING *** *** WARNING *** *** WARNING ***

  These values may be in the user's config file, if they define their own
  shortcuts.

  You may delete an entry or add new ones with new IDs or change the order of
  menu items in any menu or move a menu item to a new menu,

  BUT THE VALUE FOR A PARTICULAR FUNCTION MUST NOT CHANGE
    e.g. ID_MENUITEM_OPEN must remain 32002
  (Otherwise, a user may be unpleasantly surprised, when his shortcut for, say,
   copying a password ends up deleting the current entry...)
*/

#define ID_MENUTOOLBAR_START            32000

// File menu
#define ID_FILEMENU                     32001
#define ID_MENUITEM_OPEN                32002
#define ID_MENUITEM_NEW                 32003
#define ID_MENUITEM_CLOSE               32004
#define ID_MENUITEM_SAVE                32005
#define ID_MENUITEM_SAVEAS              32006
#define ID_MENUITEM_MRUENTRY            32007
#define ID_MENUITEM_CLEAR_MRU           32008
#define ID_EXPORTMENU                   32009
#define ID_MENUITEM_EXPORT2PLAINTEXT    32010
#define ID_MENUITEM_EXPORT2OLD1XFORMAT  32011
#define ID_MENUITEM_EXPORT2V2FORMAT     32012
#define ID_MENUITEM_EXPORT2XML          32013
#define ID_IMPORTMENU                   32014
#define ID_MENUITEM_IMPORT_XML          32015
#define ID_MENUITEM_IMPORT_PLAINTEXT    32016
#define ID_MENUITEM_IMPORT_KEEPASS      32017
#define ID_MENUITEM_MERGE               32018
#define ID_MENUITEM_COMPARE             32019
#define ID_MENUITEM_PROPERTIES          32020
#define ID_MENUITEM_EXIT                32021
#define ID_MENUITEM_SYNCHRONIZE         32022

// Edit menu
#define ID_EDITMENU                     32050
#define ID_MENUITEM_ADD                 32051
#define ID_MENUITEM_EDIT                32052
#define ID_MENUITEM_VIEW                32053
#define ID_MENUITEM_GROUPENTER          32054
#define ID_MENUITEM_DELETE              32055
#define ID_MENUITEM_DELETEENTRY         32056
#define ID_MENUITEM_DELETEGROUP         32057
#define ID_MENUITEM_RENAME              32058
#define ID_MENUITEM_RENAMEGROUP         32059
#define ID_MENUITEM_RENAMEENTRY         32060
#define ID_MENUITEM_FIND                32061
#define ID_MENUITEM_FINDUP              32062
#define ID_MENUITEM_DUPLICATEENTRY      32063
#define ID_MENUITEM_ADDGROUP            32064
#define ID_MENUITEM_CLEARCLIPBOARD      32065
#define ID_MENUITEM_COPYPASSWORD        32066
#define ID_MENUITEM_PASSWORDSUBSET      32067
#define ID_MENUITEM_COPYUSERNAME        32068
#define ID_MENUITEM_COPYNOTESFLD        32069
#define ID_MENUITEM_COPYURL             32070
#define ID_MENUITEM_COPYEMAIL           32071
#define ID_MENUITEM_BROWSEURL           32072
#define ID_MENUITEM_BROWSEURLPLUS       32073
#define ID_MENUITEM_SENDEMAIL           32074
#define ID_MENUITEM_AUTOTYPE            32075
#define ID_MENUITEM_RUNCOMMAND          32076
#define ID_MENUITEM_CREATESHORTCUT      32077
#define ID_MENUITEM_GOTOBASEENTRY       32078
#define ID_MENUITEM_FINDELLIPSIS        32079
#define ID_MENUITEM_COPYRUNCOMMAND      32080
#define ID_MENUITEM_EDITBASEENTRY       32081
#define ID_MENUITEM_UNDO                32082
#define ID_MENUITEM_REDO                32083
#define ID_MENUITEM_EXPORTENT2PLAINTEXT 32084
#define ID_MENUITEM_EXPORTENT2XML       32085

// View menu
#define ID_VIEWMENU                     32101
#define ID_MENUITEM_LIST_VIEW           32102
#define ID_MENUITEM_TREE_VIEW           32103
#define ID_MENUITEM_NEW_TOOLBAR         32104
#define ID_MENUITEM_OLD_TOOLBAR         32105
#define ID_MENUITEM_SHOWHIDE_TOOLBAR    32106
#define ID_MENUITEM_SHOWHIDE_DRAGBAR    32107
#define ID_MENUITEM_SHOWFINDTOOLBAR     32108
#define ID_MENUITEM_EXPANDALL           32109
#define ID_MENUITEM_COLLAPSEALL         32110
#define ID_MENUITEM_REFRESH             32111
#define ID_FILTERMENU                   32112
#define ID_MENUITEM_EDITFILTER          32113
#define ID_MENUITEM_APPLYFILTER         32114
#define ID_MENUITEM_MANAGEFILTERS       32115
#define ID_CHANGEFONTMENU               32116
#define ID_MENUITEM_CHANGETREEFONT      32117
#define ID_MENUITEM_CHANGEPSWDFONT      32118
#define ID_REPORTSMENU                  32119
#define ID_MENUITEM_REPORT_COMPARE      32120
#define ID_MENUITEM_REPORT_FIND         32121
#define ID_MENUITEM_REPORT_IMPORTTEXT   32122
#define ID_MENUITEM_REPORT_IMPORTXML    32123
#define ID_MENUITEM_REPORT_MERGE        32124
#define ID_MENUITEM_REPORT_VALIDATE     32125
#define ID_MENUITEM_VKEYBOARDFONT       32126
#define ID_MENUITEM_SHOWHIDE_UNSAVED    32127
#define ID_MENUITEM_REPORT_SYNCHRONIZE  32128

// Manage menu
#define ID_MANAGEMENU                   32150
#define ID_MENUITEM_CHANGECOMBO         32151
#define ID_MENUITEM_BACKUPSAFE          32152
#define ID_MENUITEM_RESTORESAFE         32153
#define ID_MENUITEM_OPTIONS             32154
#define ID_MENUITEM_CUSTOMIZETOOLBAR    32155
#define ID_MENUITEM_VALIDATE            32156
#define ID_MENUITEM_GENERATEPASSWORD    32157

// Help menu
#define ID_HELPMENU                     32200
#define ID_MENUITEM_PWSAFE_WEBSITE      32201
#define ID_MENUITEM_ABOUT               32202
#define ID_MENUITEM_U3SHOP_WEBSITE      32203
#define ID_MENUITEM_HELP                32204

// Listview Header menu
#define ID_MENUITEM_COLUMNPICKER        32210
#define ID_MENUITEM_RESETCOLUMNS        32211

// OptionsShortcuts ListView header menu
#define ID_MENUITEM_RESETCOLUMNWIDTH    32215

// Compare Entry menu
#define ID_MENUITEM_COMPVIEWEDIT        32220
#define ID_MENUITEM_COPY_TO_ORIGINAL    32221
#define ID_MENUITEM_COPY_TO_COMPARISON  32222

// System Tray Menu
#define ID_MENUITEM_TRAYLOCK            32250
#define ID_MENUITEM_TRAYUNLOCK          32251
#define ID_MENUITEM_CLEARRECENTENTRIES  32252
#define ID_MENUITEM_MINIMIZE            32253
#define ID_MENUITEM_RESTORE             32254

// Main Toolbar - only those items not also menu items
// or only on mouse right-click popup menu
#define ID_TOOLBUTTON_LISTTREE          32260
#define ID_TOOLBUTTON_VIEWREPORTS       32261

// Right Mouse Drag
#define ID_MENUITEM_COPYHERE            32270
#define ID_MENUITEM_MOVEHERE            32271
#define ID_MENUITEM_RCREATESHORTCUT     32272
#define ID_MENUITEM_CANCEL              32273

#define ID_MENUITEM_RESETSHORTCUT       32290
#define ID_MENUITEM_REMOVESHORTCUT      32291

// Find Toolbar - also dummy menu for shortcuts
#define ID_FINDMENU                     32300
#define ID_TOOLBUTTON_CLOSEFIND         32301
#define ID_TOOLBUTTON_CLEARFIND         32302
#define ID_TOOLBUTTON_FINDEDITCTRL      32303
#define ID_TOOLBUTTON_FINDCASE          32304
#define ID_TOOLBUTTON_FINDCASE_I        32305
#define ID_TOOLBUTTON_FINDCASE_S        32306
#define ID_TOOLBUTTON_FINDADVANCED      32307
#define ID_TOOLBUTTON_FINDREPORT        32308
#define ID_TOOLBUTTON_FINDRESULTS       32309

#define ID_MENUTOOLBAR_END              32499

#define ID_FLC_CRITERIA                 32500
#define ID_FLC_ENABLE                   32501
#define ID_FLC_FIELD                    32502
#define ID_FLC_LOGIC                    32503
#define ID_FLC_SELECT                   32504
#define ID_FLC_DELETE                   32505
#define ID_FLC_INSERT                   32506
#define ID_FLC_PREVIOUS                 32507
#define ID_FLC_NEXT                     32508

// System menu
#define ID_SYSMENU_ALWAYSONTOP          33000

// Menu item ranges
#define ID_FILE_MRU_ENTRY1              33001
#define ID_FILE_MRU_ENTRYMAX            33020

#define ID_TRAYRECENT_ENTRY1            33101
#define ID_TRAYRECENT_ENTRYMAX          33125

#define ID_TRAYRECENT_ENTRY_HELP1       33126
#define ID_TRAYRECENT_ENTRY_HELP2       33150

#define ID_MENUITEM_TRAYAUTOTYPE1       33151
#define ID_MENUITEM_TRAYAUTOTYPEMAX     33175

#define ID_MENUITEM_TRAYBROWSE1         33176
#define ID_MENUITEM_TRAYBROWSEMAX       33200

#define ID_MENUITEM_TRAYDELETE1         33201
#define ID_MENUITEM_TRAYDELETEMAX       33225

#define ID_MENUITEM_TRAYCOPYNOTES1      33226
#define ID_MENUITEM_TRAYCOPYNOTESMAX    33250

#define ID_MENUITEM_TRAYCOPYPASSWORD1   33251
#define ID_MENUITEM_TRAYCOPYPASSWORDMAX 33275

#define ID_MENUITEM_TRAYCOPYUSERNAME1   33276
#define ID_MENUITEM_TRAYCOPYUSERNAMEMAX 33300

#define ID_MENUITEM_TRAYVIEWEDIT1       33301
#define ID_MENUITEM_TRAYVIEWEDITMAX     33325

#define ID_MENUITEM_TRAYCOPYURL1        33326
#define ID_MENUITEM_TRAYCOPYURLMAX      33350

#define ID_MENUITEM_TRAYRUNCMD1         33351
#define ID_MENUITEM_TRAYRUNCMDMAX       33375

#define ID_MENUITEM_TRAYBROWSEPLUS1     33376
#define ID_MENUITEM_TRAYBROWSEPLUSMAX   33400

#define ID_MENUITEM_TRAYCOPYEMAIL1      33401
#define ID_MENUITEM_TRAYCOPYEMAILMAX    33425

#define ID_MENUITEM_TRAYSENDEMAIL1      33426
#define ID_MENUITEM_TRAYSENDEMAILMAX    33450

// Following for CEditExtn context menu
// Really string constants, but "logically" they're menus...
#define IDS_MENUSTRING_UNDO        34100
#define IDS_MENUSTRING_CUT         34101
#define IDS_MENUSTRING_COPY        34102
#define IDS_MENUSTRING_PASTE       34103
#define IDS_MENUSTRING_DELETE      34104
#define IDS_MENUSTRING_SELECTALL   34105
#define IDS_MENUSTRING_SHOWVKB     34106
