/*  main.c																																								  This is BoxPaint, a sample app designed to show how getting UV data from  a pick object can be used to draw on a texture. This app does not have		  graceful error handling - it's purpose is to demonstrate UV picking.																																							  Michael Bishop - August 21 1996													  Nick Thompson  Robert Dierkes																				  (c)1994-96 Apple Computer Inc., All Rights Reserved								*//*  system headers */#include <Devices.h>#include <Dialogs.h>#include <DiskInit.h>#include <Events.h>#include <Fonts.h>#include <Menus.h>#include <PictUtils.h>#include <QDOffScreen.h>#include <QuickDraw.h>#include <SegLoad.h>#include <StandardFile.h>#include <TextEdit.h>#include	"BoxPaint_main.h"#include	"BoxPaint_utility.h"#include	"BoxPaint_menu.h"#include	"BoxMooV_window.h"#include	"BoxMooV_event.h"#include	"BoxMooV_document.h"/* -------------------------------------------------------------------------------------------** function prototypes*/static void InitToolbox( void ) ;static void Main_EventLoop( void ) ;static void	Main_Init( short mBarResourceID, short numMoremasters);static void	Main_Destroy( void );/* -------------------------------------------------------------------------------------------** Global Variables*/Boolean 		gQuitFlag 		= false ;Boolean			gForeground		= true ;short			gTicks			= 1 ;/* -------------------------------------------------------------------------------------------**  main() **  entry point for the application, initialize the toolbox, initialize QuickDraw 3D **  and enter the main event loop.  On exit from the main event loop, we want to call **  the QuickDraw 3D exit function to clean up QuickDraw 3d. */void main( void ) {	Main_Init( kMBARResID, 5 ) ;			/* initialise the toolbox, load our menubar */	Main_EventLoop() ;		/* tear down any we allocated */	Main_Destroy() ;			/* and bail */	ExitToShell() ;}/*	-------------------------------------------------------------------------------------------**	Main_Init**	Initialize our environment, pass in the mbar resource ID, and also the number of calls **	to make to moremasters*/void Main_Init( short mBarResourceID, short numMoremasters){	Handle		menuBar = nil;	short		loopCounter ;	TQ3Status	myStatus ;		MaxApplZone() ;		/* max out the apps heap */		for( loopCounter = 0; loopCounter < numMoremasters ; loopCounter++ )		MoreMasters() ;			InitToolbox() ;		/* initialize anything else we need to */		/* init QuickDraw 3D, open a connection to the QuickDraw 3D library */	myStatus = Q3Initialize();	if ( myStatus == kQ3Failure )		DebugStr("\pQ3Initialize returned failure.");					/*  initialize application globals */		gQuitFlag = false;	gForeground = true;	gTicks		= 1;	/* load the application menu bar */		menuBar = GetNewMBar( mBarResourceID );	/* Read menus into menu bar, MBAR res id is 128 */		if ( menuBar == nil )		 ExitToShell();						/* if we dont have it then quit - your app */		 									/* needs a dialog here */ 	SetMenuBar(menuBar);					/* Install menus */	DisposHandle(menuBar);		AddResMenu(GetMHandle(mApple), 'DRVR');	/* Add DA names to Apple menu, ID 128 */	Menu_Adjust() ;	DrawMenuBar();}void Main_Destroy( void ){	Window_DestroyAll();	Q3Exit() ;}/*	--------------------------------------------------------------------**	InitToolbox**	Initialize the toolbox managers*/void InitToolbox( void ){		InitGraf( &qd.thePort );	InitFonts();	InitWindows();	InitCursor();	InitDialogs( nil ) ;	FlushEvents( everyEvent, 0 ) ;}/*	--------------------------------------------------------------------**	Main_EventLoop**	The heart of the app. Handles all interaction*/void Main_EventLoop(){	EventRecord 	theEvent;	WindowPtr   	theWindow;	short       	thePart;	Rect        	screenRect;	Point			aPoint = {100, 100};	Boolean			eventPresent = false;	while( !gQuitFlag )	{		eventPresent = WaitNextEvent( everyEvent, &theEvent, gTicks, nil );				if (eventPresent == true)		{			switch (theEvent.what) {				case mouseDown:									thePart = FindWindow( theEvent.where, &theWindow ) ;										switch( thePart ) {						case inMenuBar: 							Menu_Adjust() ;							Menu_HandleCommand(MenuSelect(theEvent.where));							break;												case inDrag:							screenRect = (**GetGrayRgn()).rgnBBox;							DragWindow( theWindow, theEvent.where, &screenRect );							break ;											case inContent:							if (theWindow != FrontWindow())								SelectWindow( theWindow );							Window_DoContent(theWindow, &theEvent);							break ;											case inGoAway:							if (TrackGoAway( theWindow, theEvent.where )) {								Document_Delete( Document_GetFromWindow(theWindow) ) ;							}							break ;													default:							break ;					}					break ;																	case updateEvt:									theWindow = (WindowPtr)theEvent.message;					Window_Update( theWindow ) ;					break ;									case keyDown:				case autoKey:					Event_HandleKeyPress(&theEvent);					break;									case diskEvt:					if ( Utility_HiWrd(theEvent.message) != noErr ) 						(void) DIBadMount(aPoint, theEvent.message);					break;									case osEvt:					Event_DoOSEvent(theEvent);					break;				case activateEvt:					break;			}		}		else {				Event_DoNull();		/* Handle the Null Event */		}	}}/*	--------------------------------------------------------------------**	Main_DoAbout**	Display the About Box*/void Main_DoAbout( void ){	short				itemHit ;		itemHit = Alert ( 128, nil ) ;}