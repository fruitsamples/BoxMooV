/*  window.h																				Michael Bishop - August 21 1996														Nick Thompson	(c)1994-96 Apple Computer Inc., All Rights Reserved								*/#ifndef _WINDOW_H_#define	_WINDOW_H_#include <QuickDraw.h>enum {	kWindowResID = 6347} ;	WindowPtr	Window_New(void) ;void		Window_Delete(WindowPtr theWindow) ;void		Window_Update( WindowPtr window );void		Window_Activate(WindowPtr theWindow, short activate);void		Window_DoContent (WindowPtr theWindow, EventRecord *event);WindowPtr	Window_GetNextWindow(WindowPtr theWindow);void		Window_DestroyAll(void);#endif