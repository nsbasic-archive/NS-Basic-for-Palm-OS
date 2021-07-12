VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "CDataElement"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Attribute VB_Ext_KEY = "SavedWithClassBuilder" ,"Yes"
Attribute VB_Ext_KEY = "Top_Level" ,"Yes"
Option Explicit

'local variable(s) to hold property value(s)
Private mvarName As String
Private mvarLength As Integer
Private mvarDgt_Bef As Integer
Private mvarDgt_Aft As Integer
Private mvarKind As String
Private mvarCur_No_Values As Integer
Private mvarByteFlag As Byte
Private mvarByteFlag2 As Byte

Public max_no_values1 As Integer
Public max_no_values2 As Integer
Public max_no_values3 As Integer
Public tbl_no As Integer
Public LocalOrGlobal As String '"g"=global "l"=active local "x"=inactive local
Public LocalSource As String  'name of func/sub that defined local var
Public single_value As Variant
Public typedefFlag As Boolean
Public typedefName As String
Public isConstant As Boolean

Private Sub class_initialize()
   Name = ""
   Length = 0
   Dgt_Bef = 0
   Dgt_Aft = 0
   Kind = "u"
   Cur_No_Values = 0

   max_no_values1 = 1
   max_no_values2 = 0
   max_no_values3 = 0
   ByteFlag = &H0
   typedefFlag = False
   isConstant = False
'If compiler_debug Then
'sgBox "assigning de#=" + str(gtarget.DataCollection.count + 1)
'End If

'041801 MMD Handled by CProject now
'tbl_no = gtarget.DataCollection.count + 1

   tbl_no = 0
   LocalOrGlobal = "g"
End Sub

Public Property Let Cur_No_Values(ByVal vData As Integer)
   mvarCur_No_Values = vData
End Property

Public Property Get Cur_No_Values() As Integer
   Cur_No_Values = mvarCur_No_Values
End Property

Public Property Let Kind(ByVal vData As String)
   mvarKind = vData
End Property

Public Property Get Kind() As String
   Kind = mvarKind
End Property

Public Property Let Dgt_Aft(ByVal vData As Integer)
   mvarDgt_Aft = vData
End Property

Public Property Get Dgt_Aft() As Integer
   Dgt_Aft = mvarDgt_Aft
End Property

Public Property Let Dgt_Bef(ByVal vData As Integer)
   mvarDgt_Bef = vData
End Property

Public Property Get Dgt_Bef() As Integer
   Dgt_Bef = mvarDgt_Bef
End Property

Public Property Let Length(ByVal vData As Integer)
   mvarLength = vData
End Property

Public Property Get Length() As Integer
   Length = mvarLength
End Property

Public Property Let Name(ByVal vData As String)
   mvarName = vData
End Property

Public Property Get Name() As String
   Name = mvarName
End Property

Public Property Let ByteFlag(ByVal vData As Byte)
   mvarByteFlag = vData
End Property

Public Property Get ByteFlag() As Byte
   ByteFlag = mvarByteFlag
End Property

Public Property Let ByteFlag2(ByVal vData As Byte)
   mvarByteFlag2 = vData
End Property

Public Property Get ByteFlag2() As Byte
   ByteFlag2 = mvarByteFlag2
End Property
