//Download by http://www.NewXing.com
// GdiplusDemoFuns.h

#ifndef _GDIPLUS_DEMO_FUNS_H__
#define _GDIPLUS_DEMO_FUNS_H__

void  CreatePenFromBrush_Click();
void  DashStyle_Custom_Click();
void  Pen_Align_Click();
void  Pen_Tranform_Click();
void  Pen_LineCap_Click();
void  Pen_TransColor_Click();

//-------------------------------------------------------------
//txt1 = "画刷";

void  Brush_SolidBrush_Click();
void  Brush_FillVurve_Click();
void  Brush_HatchBrush_Click();
void  Brush_EnumAllStyle_Click();
void  Brush_SetRenderingOrigin_Click();
void  Brush_Texture_Click();
void  Brush_Texture_WrapMode_Click();
void  Brush_TextureTransform_Click();
void  Brush_GetTextureMatrix_Click();
void  Brush_LinearGradientBrush_Click();
void  Brush_LinearArrange_Click();
void  Brush_LinearInterpolation_Click();
void  Brush_LinearGradientMode_Click();
void  Brush_LinearAngle_Click();
void  Brush_LinearCustomize_Click();
void  Brush_LinearGradientBrush_BellShape_Click();
void  Brsuh_LinearGradientBrush_UsingGamma_Click();
void  Brush_PathGradientBrush_Star_Click();
void  Brush_PathGradientBrush_Star2_Click();
void  Brush_Using_MorePathGradientBrush_Click();
void  Brush_PathGradientBrush_WrapMode_Click();
void  Brush_PathGradientBrush_CenterPoint_Click();
void  Brush_PathGradientBrush_InterpolationColors_Click();
void  Brsuh_PathGradietBrush_Focus_Click();
void  Brush_PathGradientBrush_Transform_Click();

//-------------------------------------------------------------
//txt1 = "文本与字体";

void  Font_UsingFontInGDIPlus_Click();
void  Font_EnumAllFonts_Click();
void  Font_EnhanceFontDialog_Click();
void  Font_UsingTextRenderHint_Click();
void  Font_Privatefontcollection_Click();
void  Font_Privatefontcollection2_Click();
void  Font_IsStyleAvailable_Click();
void  Font_Size_Click();
void  Font_BaseLine_Click();
void  Font_DrawString_Click();
void  Font_MeasureString_Click();
void  Font_MeasureString2_Click();
void  Font_ColumnTextOut_Click();
void  Font_StirngTrimming_Click();
void  Font_TextOutClip_Click();
void  Font_MeasureCharacterRanges_Click();
void  Font_TextoutDirection_Click();
void  Font_TextAlignment_Click();
void  Font_TextAlignment2_Click();
void  Font_TextoutUsingTabs_Click();
void  Font_UsingTabs_Click();
void  Font_TextoutHotkeyPrefix_Click();
void  Font_TextoutShadow_Click();
void  Font_TextoutHashline_Click();
void  Font_TextoutTexture_Click();
void  Font_TextoutGradient_Click();

//-------------------------------------------------------------
//txt1 = "路径和区域";

void  Path_Construct_Click();
void  Path_AddLines_Click();
void  Path_CloseFigure_Click();
void  Path_FillPath_Click();
void  Path_AddSubPath_Click();
void  Path_GetSubPath_Click();
void  Path_GetPoints_Click();
void  Path_PathData_Click();
void  Path_ViewPointFLAG_Click();
void  Path_SubPathRange_Click();
void  Path_Flatten_Click();
void  Path_Warp_Click();
void  Path_Transform_Click();
void  Path_Widen_Click();
void  Path_WidenDemo_Click();
void  Region_FromPath_Click();
void  Region_Calculate_Click();
void  Region_GetRects_Click();

//-------------------------------------------------------------
//txt1 = "GDI+的坐标变换";

void  Transform_Click();
void  TranslateTransform_Click();
void  RotateTransform_Click();
void  DrawWatch_Click();
void  ScaleTransform_Click();
void  RectScale_Click();
void  FontRotate_Click();
void  Matrix_ListElements_Click_1();
void  MatrixPos_Click();
void  Martrix_Invert_Click();
void  Matrix_Multiply_Click();
void  Matrix_TransformPoints_Click();
void  Matrix_TransformPoints2_Click();
void  Matrix_TransformVectors_Click();
void  Matrix_RotateAt_Click();
void  Matrix_Shear_Click();
void  Matrix_TextoutShear_Click();
void  Matrix_ChangeFontHeight_Click();

//-------------------------------------------------------------
//txt1 = "GDI+的色彩变换";

void  ColorMatrix_Start_Click();
void  TranslateColor_Click();
void  ScaleColor_Click();
void  RotateColor_Click();
void  ColorShear_Click();
void  ColorRemap_Click();
void  SetRGBOutputChannel_Click();

//-------------------------------------------------------------
//txt1 = "图像的基本处理";

void  Metafile_Click();
void  CroppingAndScaling_Click();
void  UsingInterpolationMode_Click();
void  RotateFlip_Click();
void  ImageSkewing_Click();
void  Cubeimage_Click();
void  ThumbnailImage_Click();
void  Clone_Click();
void  Picturescale_Click();

//-------------------------------------------------------------
//txt1 = "图像色彩信息的调整";

void  ImageAttributesSetNoOp_Click();
void  SetColorMatrices_Click();
void  SetOutputChannelColorProfile_Click();
void  Gammaadjust_Click();
void  SetOutputChannel_Click();
void  Colorkey_Click();
void  Setthreshold_Click();
void  AdjustedPalette_Click();
void  SetWrapMode_Click();

//-------------------------------------------------------------
//txt1 = "图形的编码与解码";

void  ListAllImageEncoders_Click();
void  ListImageEncoder_Detail_Click();
void  ListImageDecoder_Click();
void  GetEncoderParameter_Click();
void  GetAllEncoderParameter_Click();
void  menuItem17_Click();
void  SaveBmp2tif_Click();
void  SaveBMP2JPG_Click();
void  TransformingJPEG_Click();
void  MultipleFrameImage_Click();
void  GetImageFromMultyFrame_Click();
void  QueryImage_Click();
void  SetProp_Click();

//-------------------------------------------------------------
//txt1 = "图形特技处理";

void  menuItem2_Click();
void  GrayScale_Click();
void  Inverse_Click();
void  Emboss_Click();
void  OnCanvas_Click();
void  OnWood_Click();
void  Flashligt_Click();
void  BlurAndSharpen_Click();

#endif //_GDIPLUS_DEMO_FUNS_H__