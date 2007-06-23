!Process class methodsFor: 'instance creation'!

on: aContext
    ^self new context: aContext; initialize; yourself
! !

!Process methodsFor: 'execution'!

initialize
    self suspend
!

context
    ^context
!

context: aContext
    context := aContext
!

suspend
    suspended := true.
    self isActive ifTrue: [Processor yield]
!

resume
    suspended := false.
    self isActive ifFalse: [Processor yield]
!

terminate
    self isActive
	ifTrue: [ Processor leaveTo: nil andAnswer: nil]
	ifFalse: [ context := nil ]
! !

!Process methodsFor: 'testing'!

isActive
    ^self == Processor activeProcess
! !