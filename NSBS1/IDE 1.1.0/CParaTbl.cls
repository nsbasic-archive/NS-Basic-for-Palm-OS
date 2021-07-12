VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "CParaTbl"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Attribute VB_Ext_KEY = "SavedWithClassBuilder" ,"Yes"
Attribute VB_Ext_KEY = "Top_Level" ,"Yes"
Option Explicit

Public typ As String
Public func_de_no As Integer
Public name_ptr As String
Public tbl_no As Integer
Public defined As Integer
Public moduleId As Integer
Public offset As Long
Public ptype As String  's=sub l=label
Public argCount As Integer
Public defBy As String

Private Sub class_initialize()
   tbl_no = 0
   name_ptr = ""
   defined = 0
   offset = 0
   defBy = ""
   argCount = -1
   ptype = ""
   moduleId = thisModuleId 'id of mod being compiled
End Sub
