"
Copyright (c) 2007 Rahul
This file is part of Smalltalk YX.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the 'Software'), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell   
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
  
The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.
   
THE SOFTWARE IS PROVIDED 'AS IS', WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,  
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER    
DEALINGS IN THE SOFTWARE.
"

X11XEvent subclass: #XEvent
        instanceVariableNames: ''
        classVariableNames: ''!

!XEvent class methodsFor: 'instance creation'!

create
    ^self handle: (self primX11XEventCreate).
! !

!XEvent methodsFor: 'access'!
xkey
    ^X11XKeyEvent handle: (self primXEventXkey).
!

xmotion
    ^X11XMotionEvent handle: (self primXEventXmotion).
!

xbutton
    ^X11XButtonEvent handle: (self primXEventXbutton).
! !

!XEvent methodsFor: 'finalization'!

finalize
    self delete.
! !

