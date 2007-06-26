!Behavior methodsFor: 'accessing'!

name
    ^name
!

superclass
    ^superclass
!

printString
    ^self name asString
! !

!Behavior methodsFor: 'instance creation'!

basicNew
    <primitive: 'Behavior_new'>
	^self primitiveFailed
!

new
    <primitive: 'Behavior_new'>
	^self primitiveFailed
!

basicNew: anInteger
    <primitive: 'Behavior_newColon'>
	^self primitiveFailed
!

new: anInteger
    <primitive: 'Behavior_newColon'>
	^self primitiveFailed
! !

!Behavior methodsFor: 'enumerating'!

allSuperclassesDo: aBlock  
    "Invokes aBlock for all superclasses, both direct and indirect."
    | class superclass |
    class := self.
    [ superclass := class superclass.
      class := superclass.
      superclass notNil ]
	whileTrue: [ aBlock value: superclass ]
! !