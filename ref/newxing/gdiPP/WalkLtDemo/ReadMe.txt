
--2019/5/31 15:02--osu--
1. + git 
2. * MyDrawString(gc, "xd_v: 0.0.3", Font(L"Arial",12), SolidBrush(Color::Blue), Point(20, 240));


========================================================================
GDI+�������ʵ��Դ����(��UNICODE��VC++��)

version: 1.0.0	2007-9-16

	author:	Louyu.
	email: louyu@zju.edu.cn
	web site: http://www.walkgis.com

	�������Ϲ㷺�����ġ�GDI+�������ʵ��Դ���롱��ʹ�õ���C#���ԣ��ҷ�װ�˿�Դ����
��Դ������Ҫ�� ��Form1.cs�� �У��书�ܵ�ʵ����ʽ��.Net��MSDN������ͬ��

	���߶Ը�Դ�����������ֲ����VC�ķ� UNICODE �����½������޸ģ���Ҫ����

	1���ṩ��һ�� multibyte �� widechar ��ת���� CWideCharString
		ʵ�� char* �� WCHAR* ��ת������෽�����磺
		a) CWideCharString(char*) �õ� WCHAR*
		b) L"char* string" �õ� WCHAR*
		c) �ڷ�UNICODE�����£�CString(WCHAR*) �õ� char*

	2����ԭC#�е�Math��Shell�ȶ���ת��Ϊ��ͨ��VC�������綨���� rand_Next ��

	3����ԭC#�����е�new��ΪVC�����û�ָ��
		��������VC�ж�new�����غ�delete�ķ��ӵ������������ڴ�й©

	4��������һ��MyDrawString�������滻ԭ�����е� graphics.DrawString(...)
		������ԭC#������DrawString�Ĳ���˳������÷�ʽ
		���������� _MakeA_RGB ����

	5����Ϊ Image::Save Ҫ�󱣴���ļ����ô��ڣ�������ʾ�п��ܻᷴ��ִ��Save������
		�ṩ�� MyImageSave ���������ж��ļ��Ƿ���ڣ���������ɾ����Ȼ�� Save.

	6��Ϊ�����ܱ���ԭ����ķ���� CWalkLtDemo.cpp �� OnDraw(...) �������ṩһ��
		void DoGdiplusDemo(...) ������
		�ú����������������ʾ�����д�������Ҫ�Ļ�ͼ����Graphicsʵ����

	7�������˵����鿴�����������ˡ�GDI+������ʾ���͡���ǰ��ʾ��Դ���롱�˵���
		���ڹ���������������Ӧ��ť��

	8����������VC6��VC++.NET�н�������ȫ�Ĳ��ԡ�

	ע��������Ŀ¼�ṹΪ��
	../WalkLt					��Ŀ¼
		ReadMe.txt			���ļ�
	../WalkLt/Bin					ִ�г���Ŀ¼
	../WalkLt/Bin/gidplus_demo_data			��ʾ����
	../WalkLt/Include				Gdiplus*.hͷ�ļ�Ŀ¼
	../WalkLt/Lib					Gdiplus.lib������Ŀ¼
	../WalkLt/WalkLtDemo				vcԴ����Ŀ¼
		WalkLtDemo.dsw			vc6 ����(Workspace)
		WalkLtDemo.sln			vc++.net ����
	../WalkLt/WalkLtDemo/res			������ԴĿ¼

	˵����������ʹ�õ� gdiplus*.h �ж� Color �� Point �����������������ֱ�Ϊ��
		GdiPlusColor �� PointI
		Ϊ��MSDN�е� Color �� Point ��һ�£���WalkLtDemoHelp.h��ʹ���� typedef:
			typedef GdiPlusColor Color;
			typedef PointI Point;

	������Ŀ¼�ṹ��������CWalkLtDemoApp::InitInstance()��������ͼ�������ļ�����Ŀ¼
�����ã�SetCurrentDirectory()�����ı��˱���Ŀ¼�ṹ��ʹ���߿������޸ĸú�����
