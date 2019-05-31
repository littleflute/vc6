//Download by http://www.NewXing.com
/**************************************************************************\
*
* Copyright (c) 1998-2001, Microsoft Corp.  All Rights Reserved.
*
* Module Name:
*
*   GdiplusColorMatrix.h
*
* Abstract:
*
*  GDI+ GdiPlusColor Matrix object, used with Graphics.DrawImage
*
\**************************************************************************/

#ifndef _GDIPLUSCOLORMATRIX_H
#define _GDIPLUSCOLORMATRIX_H

//----------------------------------------------------------------------------
// GdiPlusColor matrix
//----------------------------------------------------------------------------

struct ColorMatrix
{
    REAL m[5][5];
};

//----------------------------------------------------------------------------
// GdiPlusColor Matrix flags
//----------------------------------------------------------------------------

enum ColorMatrixFlags
{
    ColorMatrixFlagsDefault   = 0,
    ColorMatrixFlagsSkipGrays = 1,
    ColorMatrixFlagsAltGray   = 2
};

//----------------------------------------------------------------------------
// GdiPlusColor Adjust Type
//----------------------------------------------------------------------------

enum ColorAdjustType
{
    ColorAdjustTypeDefault,
    ColorAdjustTypeBitmap,
    ColorAdjustTypeBrush,
    ColorAdjustTypePen,
    ColorAdjustTypeText,
    ColorAdjustTypeCount,
    ColorAdjustTypeAny      // Reserved
};

//----------------------------------------------------------------------------
// GdiPlusColor Map
//----------------------------------------------------------------------------

struct ColorMap
{
    GdiPlusColor oldColor;
    GdiPlusColor newColor;
};

#endif
