VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "cDatabase"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

Public Name As String
Public IdNo As Integer
Public formatTypeName    As String           'added 09242003
Public formatRecord As Integer               'added 09242003
Public noKeyFields As Integer                'added 09242003
Public firstDbFldNo As Integer                'added 09242003
Public lastDbFldNo As Integer                'added 09242003
Public deviceFilename As String              'added 09242003
Public creator As String                     'added 09242003
Public LocalOrGlobal           As String  '**added 04042004
Public LocalSource             As String  '**added 04042004

Public keyFieldTblNo As Integer     'added 02042004
Public Sub class_initialize()
   keyFieldTblNo = 0                'added 02042004
   
   Name = ""
   formatTypeName = ""                     'added 09242003
   formatRecord = 0                       'added 09242003
   noKeyFields = 0                         'added 09242003
   firstDbFldNo = 0                        'added 09242003
   lastDbFldNo = 0                         'added 09242003
   deviceFilename = ""                     'added 09242003
   creator = ""                            'added 09242003
   IdNo = 0
End Sub
