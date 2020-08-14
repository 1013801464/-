#include <atlimage.h>
#include <vector>
#include <iostream>
#include <string>
#include <io.h>

using namespace std;


bool ResizePicture(CString strSource, CString strTarget)
{
	int WIDTH = 500;		// 最大宽度
	int HEIGHT = 500;		// 最大高度
	CImage oldimg;
	CImage newimg;
	oldimg.Load(strSource);
	if (oldimg.IsNull())
		return false;
	int nWidth = 0;
	int nHeight = 0;

	nWidth = oldimg.GetWidth();
	nHeight = oldimg.GetHeight();

	if (nWidth > WIDTH || nHeight > HEIGHT)
	{
		double dRatio = nWidth * 1.0 / nHeight;
		if (nWidth > nHeight)
		{
			nWidth = WIDTH;
			nHeight = (int)(nWidth / dRatio);
		}
		else
		{
			nHeight = HEIGHT;
			nWidth = (int)(nHeight * dRatio);
		}
	}

	if (!newimg.CreateEx(nWidth, nHeight, 24, BI_RGB))
	{
		oldimg.Destroy();
		return false;
	}

	int nPreMode = ::SetStretchBltMode(newimg.GetDC(), HALFTONE);
	newimg.ReleaseDC();
	oldimg.Draw(newimg.GetDC(), 0, 0, nWidth, nHeight, 0, 0, oldimg.GetWidth(), oldimg.GetHeight());
	newimg.ReleaseDC();
	::SetBrushOrgEx(newimg.GetDC(), 0, 0, NULL);
	newimg.ReleaseDC();
	::SetStretchBltMode(newimg.GetDC(), nPreMode);
	newimg.ReleaseDC();

	newimg.Save(strTarget);
	newimg.Destroy();
	oldimg.Destroy();

	return true;
}

bool ResizePicture2(CString strSource, CString strTarget)
{
	int WIDTH = 200;
	int HEIGHT = 200;
	CImage oldimg;
	CImage newimg;
	oldimg.Load(strSource);
	if (oldimg.IsNull())
		return false;
	int nWidth = 0;
	int nHeight = 0;

	nWidth = oldimg.GetWidth();
	nHeight = oldimg.GetHeight();

	if (nWidth > WIDTH || nHeight > HEIGHT)
	{
		double dRatio = nWidth * 1.0 / nHeight;
		if (nWidth > nHeight)
		{
			nWidth = WIDTH;
			nHeight = (int)(nWidth / dRatio);
		}
		else
		{
			nHeight = HEIGHT;
			nWidth = (int)(nHeight * dRatio);
		}
	}

	if (!newimg.CreateEx(WIDTH, HEIGHT, 24, BI_RGB))
	{
		oldimg.Destroy();
		return false;
	}
	RECT rect = { 0,0,WIDTH,HEIGHT };
	HBRUSH hb = ::CreateSolidBrush(RGB(49, 77, 121));
	::FillRect(newimg.GetDC(), &rect, hb);
	newimg.ReleaseDC();
	int nPreMode = ::SetStretchBltMode(newimg.GetDC(), HALFTONE);
	newimg.ReleaseDC();
	oldimg.Draw(newimg.GetDC(), (WIDTH - nWidth) / 2, (HEIGHT - nHeight) / 2, nWidth, nHeight, 0, 0, oldimg.GetWidth(), oldimg.GetHeight());
	newimg.ReleaseDC();
	::SetBrushOrgEx(newimg.GetDC(), 0, 0, NULL);
	newimg.ReleaseDC();
	::SetStretchBltMode(newimg.GetDC(), nPreMode);
	newimg.ReleaseDC();

	newimg.Save(strTarget);
	newimg.Destroy();
	oldimg.Destroy();
	::DeleteObject(hb);

	return true;
}

char source_dir_path[256];
char target_dir_path[256];
vector<string> files;

void getFiles(string path, string path2, vector<string>& files)
{
	//文件句柄  
	long   hFile = 0;
	//文件信息  
	struct _finddata_t fileinfo;
	string p, p2;
	if ((hFile = _findfirst(p.assign(path).append(path2).append("*").c_str(), &fileinfo)) != -1)
	{
		do
		{
			//如果是目录,迭代之  
			//如果不是,加入列表  
			if ((fileinfo.attrib &  _A_SUBDIR))
			{
				//if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
				//	getFiles(p.assign(path).append("\\"), p2.assign(fileinfo.name).append("\\"), files);
			}
			else
			{
				files.push_back(p.assign(path2).append(fileinfo.name));  //这一行可以给出相对路径
																		 //files.push_back(p.assign(fileinfo.name) );  //这一行可以给出文件名 
			}
		} while (_findnext(hFile, &fileinfo) == 0);
		_findclose(hFile);
	}
}

// 判断字符串是否以xxx结尾
bool endsWith(string s, string sub) {
	return s.rfind(sub) == (s.length() - sub.length()) ? 1 : 0;
}

int main() {
	cout << "Source Folder:" << endl;
	cin.getline(source_dir_path, 256);
	cout << "Destination Folder:" << endl;
	cin.getline(target_dir_path, 256);

	// 修改字符串类型, 然后为路径路径追加 '\'
	string sourceDirPath(source_dir_path);
	if (sourceDirPath[sourceDirPath.length() - 1] != '\\') {
		sourceDirPath.append("\\");
	}
	string targetDirPath(target_dir_path);
	if (targetDirPath[targetDirPath.length() - 1] != '\\') {
		targetDirPath.append("\\");
	}

	// 获取源路径下的所有文件  
	vector<string> files;
	getFiles(sourceDirPath, "", files);
	char str[30];
	int size = files.size();
	for (int i = 0; i < size; i++)
	{
		if (!endsWith(files[i], ".png") && !endsWith(files[i], ".bmp") && !endsWith(files[i], ".jpg") && !endsWith(files[i], ".jpeg")
			&& !endsWith(files[i], ".PNG") && !endsWith(files[i], ".BMP") && !endsWith(files[i], ".JPG") && !endsWith(files[i], ".JPEG")) {
			cout << "  ignore  : " << files[i] << endl;
			continue;
		}
		string full_source_path;
		string full_target_path;
		full_source_path.assign(sourceDirPath);
		full_source_path.append(files[i]);
		full_target_path.assign(targetDirPath);
		full_target_path.append(files[i]);
		// 修改bmp和png的文件名后缀
		if (endsWith(files[i], ".png") || endsWith(files[i], ".bmp") || endsWith(files[i], ".PNG") || endsWith(files[i], ".BMP") || endsWith(files[i], ".JPG")) {
			full_target_path[full_target_path.length() - 3] = 'j';
			full_target_path[full_target_path.length() - 2] = 'p';
			full_target_path[full_target_path.length() - 1] = 'g';
		}
		cout << "processing: " << sourceDirPath << files[i].c_str() << endl;
		ResizePicture2(CString(full_source_path.data()), CString(full_target_path.data()));
		cout << "    ----> " << full_target_path << endl;
	}
	return 0;
}