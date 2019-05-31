
--2019/5/31 15:02--osu--
1. + git 
2. * MyDrawString(gc, "xd_v: 0.0.3", Font(L"Arial",12), SolidBrush(Color::Blue), Point(20, 240));


========================================================================
GDI+程序设计实例源代码(非UNICODE，VC++版)

version: 1.0.0	2007-9-16

	author:	Louyu.
	email: louyu@zju.edu.cn
	web site: http://www.walkgis.com

	在网络上广泛流传的“GDI+程序设计实例源代码”中使用的是C#语言，且封装了开源对象，
其源代码主要在 “Form1.cs” 中，其功能的实现形式与.Net的MSDN帮助不同。

	作者对该源代码进行了移植，在VC的非 UNICODE 环境下进行了修改，主要处理：

	1、提供了一个 multibyte 与 widechar 的转化类 CWideCharString
		实现 char* 与 WCHAR* 的转换有许多方法，如：
		a) CWideCharString(char*) 得到 WCHAR*
		b) L"char* string" 得到 WCHAR*
		c) 在非UNICODE环境下，CString(WCHAR*) 得到 char*

	2、将原C#中的Math、Shell等对象转换为普通的VC函数，如定义了 rand_Next 等

	3、将原C#代码中的new改为VC的引用或指针
		避免了在VC中对new的重载和delete的繁杂调用所带来的内存泄漏

	4、定义了一组MyDrawString函数，替换原代码中的 graphics.DrawString(...)
		保持了原C#代码中DrawString的参数顺序和引用方式
		增加了两个 _MakeA_RGB 函数

	5、因为 Image::Save 要求保存的文件不得存在，而在演示中可能会反复执行Save，所以
		提供了 MyImageSave 函数，先判断文件是否存在，若存在则删除，然后 Save.

	6、为尽可能保持原代码的风格，在 CWalkLtDemo.cpp 的 OnDraw(...) 函数中提供一个
		void DoGdiplusDemo(...) 函数，
		该函数负责向各功能演示函数中传递所需要的绘图区和Graphics实例。

	7、在主菜单“查看”项下增加了“GDI+功能演示”和“当前演示的源代码”菜单，
		并在工具条上增加了相应按钮。

	8、程序已在VC6和VC++.NET中进行了完全的测试。

	注：本例的目录结构为：
	../WalkLt					主目录
		ReadMe.txt			本文件
	../WalkLt/Bin					执行程序目录
	../WalkLt/Bin/gidplus_demo_data			演示数据
	../WalkLt/Include				Gdiplus*.h头文件目录
	../WalkLt/Lib					Gdiplus.lib函数库目录
	../WalkLt/WalkLtDemo				vc源代码目录
		WalkLtDemo.dsw			vc6 环境(Workspace)
		WalkLtDemo.sln			vc++.net 环境
	../WalkLt/WalkLtDemo/res			样例资源目录

	说明：本例中使用的 gdiplus*.h 中对 Color 和 Point 进行了重新声明，分别为：
		GdiPlusColor 和 PointI
		为与MSDN中的 Color 和 Point 相一致，在WalkLtDemoHelp.h中使用了 typedef:
			typedef GdiPlusColor Color;
			typedef PointI Point;

	按本例目录结构，作者在CWalkLtDemoApp::InitInstance()中增加了图像样例文件所在目录
的设置：SetCurrentDirectory()，若改变了本例目录结构，使用者可自行修改该函数。
