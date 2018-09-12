
#include <fstream>
#include <iostream>
#include <string>
 #include <sstream> 
#include "opencv\cv.h"
#include "opencv\highgui.h"
using namespace cv;
using namespace std;
   extern int readDir(char *dirName, vector<string> &filesName);
int test17(int argc, char *argv[])  
{  

	string  dirName="G:/F/YOLO/yolo-v2/darknet-master/train-v/VOCdevkit/VOC2007/JPEGImages";
	string  drawpath="G:/F/YOLO/yolo-v2/darknet-master/train-v/imgDraw";
    vector<string> filesName;
	readDir((char*)dirName.c_str(),filesName);
	
	for(int i=0;i<filesName.size();i++)	
	{
		string imgPath=filesName[i];
		int pos=imgPath.find_last_of('/');
		int pos2=imgPath.find_first_of('.');
		string name1=imgPath.substr(pos+1,pos2-pos-1);
		string imgPath1=imgPath.substr(0,pos);
		 pos=imgPath1.find_last_of('/');

		 string labelPath=imgPath1.substr(0,pos)+"/labels/"+name1+".txt";

		Mat img=imread(imgPath.c_str());
		if(img.data==NULL)
		{
			printf("img.data null:%s\n",name1.c_str());
			system("pause");
			return 0;
		}
		int width=img.cols;int height=img.rows;
		

		
		fstream flabel;
		flabel.open(labelPath,ios::in);
		if (!flabel.is_open())
		{
			cout << "fimg 文件数据打开错误！"<< endl;
			system("pause");
			return false;
		}  
		int class1;	 float cenx;  float ceny;float cenw;float cenh;
		 flabel>>class1>>cenx>>ceny>>cenw>>cenh;
		 flabel.close();
		 Rect rt;rt.x=(cenx-cenw/2)*width;rt.y=(ceny-cenh/2)*height;
		 rt.width=cenw*width;rt.height=cenh*height;
		 rectangle(img,rt,Scalar(0,0,255));

		   string drawpath1=drawpath+"/"+name1+".jpg";

		 imwrite(drawpath1,img);
	}

	
	return 0;  
}  