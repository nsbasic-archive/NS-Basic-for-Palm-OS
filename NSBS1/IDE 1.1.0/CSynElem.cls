VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "CSynElem"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Attribute VB_Ext_KEY = "SavedWithClassBuilder" ,"Yes"
Attribute VB_Ext_KEY = "Top_Level" ,"Yes"
Option Explicit

Public mvarPrev As CSynElem
Public mvarNxt As CSynElem
Public posInInput As Long
Public de_no As Integer
Public sub1 As Integer
Public sub2 As Integer
Public sub3 As Integer
Public maj As String
Public term As String
Public termin As String
Public termType As Integer

Public Property Set Prev(ByVal c As CSynElem)
    Set mvarPrev = c
End Property

Public Property Get Prev()
   Set Prev = mvarPrev
End Property

Public Property Set Nxt(ByVal c As CSynElem)
    Set mvarNxt = c
End Property

Public Property Get Nxt()
   Set Nxt = mvarNxt
End Property
