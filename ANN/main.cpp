#include <iostream>
#include <fstream>
#include <time.h>
#include <math.h>
#include <stdlib.h>
#include <cstring>
#include "image.h"
using namespace std;

double **d_InputHiddenWeight;	        //输入、隐藏层权值矩阵
double **d_HiddenOutputWeight;	        //隐藏、输出层权值矩阵
IMAGE *imageTrainSet;		//训练图片集
IMAGE *imageTestSet;		//测试图片集
#define IMAGE_WIDTH 32			///图片宽度
#define IMAGE_HEIGHT 30			///图片像素
#define TRAIN_IMAGE_AMOUNT 277		///训练样本数量
#define TEST_IMAGE_AMOUNT 139		///测试样本数量
#define NETWORK_INPUT_AMOUNT 960	///输入层数量
#define NETWORK_HIDDEN_AMOUNT 4	///隐藏层单元数量
#define NETWORK_OUTPUT_AMOUNT 4 	///输出层单元数量
#define PUSH_VALUE 0.3			///冲击量
#define SPEED_VALUE 0.3			///训练速率
#define TRAIN_TIMES 500			///训练次数
#define random(x) (rand()x%)

void buildNetwork();						///建立神经网络拓扑
void getTrainData();						///读取训练数据
void getTestData();						///读取测试数据
void backPropagte(IMAGE * trainSet, double speed,int times);	///反向传播训练网络
void testNetwork(IMAGE * testSet,double &rate);		///测试准确率
IMAGE openImage(char *  filename);


void buildNetwork(){
  //生成网络权值矩阵
  d_InputHiddenWeight = new double *[NETWORK_INPUT_AMOUNT];
    for(int i=0;i<NETWORK_INPUT_AMOUNT;i++)
      d_InputHiddenWeight[i] = new double [NETWORK_HIDDEN_AMOUNT];
  d_HiddenOutputWeight = new double *[NETWORK_HIDDEN_AMOUNT];
    for(int i=0;i<NETWORK_HIDDEN_AMOUNT;i++)
      d_HiddenOutputWeight[i] = new double [NETWORK_OUTPUT_AMOUNT];
    
  //设置随机因子
  srand((int)time(0));
  
  //生成随机权值（-0.5～0.5）
  for(int i=0;i<NETWORK_INPUT_AMOUNT;i++)
    for(int j=0;j<NETWORK_HIDDEN_AMOUNT;j++)
      d_InputHiddenWeight[i][j] = (random(100)-50)/1000;
  for(int i=0;i<NETWORK_HIDDEN_AMOUNT;i++)
    for(int j=0;j<NETWORK_OUTPUT_AMOUNT;j++)
      d_HiddenOutputWeight[i][j] = (random(100)-50)/1000;
}
void getTrainData(){	
  ifstream input("train.txt");
  char * path;
  int size = sizeof(path);
  char *path_2 = new char[size];
  imageTrainSet = new IMAGE[TRAIN_IMAGE_AMOUNT];
  for(int i=0;i<TRAIN_IMAGE_AMOUNT;i++){
    ///afs/cs/project/theo-8/faceimages/faces/kawamura/kawamura_straight_happy_open_4.pgm
    char letter;
    char letters[150]={0};
    for(int j=0;j<150;j++){
      input>>letter;
      if(j>10&&letters[j-2]=='p'&&letters[j-1]=='g'&&letter=='m'){
	letters[j]='m';
	letters[j+1]='\0';
	break;
      }
      else
	letters[j]=letter;
    }
//    input>>path;
    char *p;
    p = strtok(letters,"/");
    for(int u=0;u<6;u++)
      p = strtok(NULL,"/");
    char *name = p;
    p = strtok(NULL,"/");
    char *state = p;
    for(int u=0;u<4;u++)
      p = strtok(NULL,"/");
    
    string newName(name);
    string newState(state);
    p = strtok(state,"_");
    p = strtok(NULL,"_");
    char *direct = p;
    p = strtok(NULL,"_");
    p = strtok(NULL,"_");
    char *glass = p;

    string filename = "/home/snooze/projects/ANN/build/faces/"+newName+"/"+newState;
    char *filename_char =  const_cast<char*>(filename.c_str());
    double * target = new double[NETWORK_OUTPUT_AMOUNT];
    for(int p=0;p<NETWORK_OUTPUT_AMOUNT;p++)
      target[p]=0;
    string direct_2(direct);
    string glass_2(glass);
    if(direct_2 == "straight"){
      target[0]=1;
      //target[1]=target[2]=target[3]=0.1;
    }
    if(direct_2 == "up"){
      target[1]=1;
    //  target[0]=target[2]=target[3]=0.1;
    }
    if(direct_2 == "left"){
      target[2]=1;
   //   target[1]=target[0]=target[3]=0.1;
    }
    if(direct_2 == "right"){
      target[3]=1;
   //   target[1]=target[0]=target[2]=0.1;
    }
//    if(glass_2 == "open") target[4]=1;
//    if(glass_2 == "sunglasses") target[5]=1;
    imageTrainSet[i] =  openImage(filename_char);
    imageTrainSet[i].target = target;
  }
  input.close();
}
void getTestData(){
  ifstream input("test1.txt");
  char * path;
  int size = sizeof(path);
  char *path_2 = new char[size];
  imageTestSet = new IMAGE[TEST_IMAGE_AMOUNT];
  for(int i=0;i<TEST_IMAGE_AMOUNT;i++){
    ///afs/cs/project/theo-8/faceimages/faces/kawamura/kawamura_straight_happy_open_4.pgm
    char letter;
    char letters[150];
    for(int j=0;j<150;j++){
      input>>letter;
      if(j>10&&letters[j-2]=='p'&&letters[j-1]=='g'&&letter=='m'){
	letters[j]='m';
	letters[j+1]='\0';
	break;
      }
	
      else{
	letters[j]=letter;
      }
    }
//    input>>path;
    char *p;
    p = strtok(letters,"/");
    for(int t=0;t<6;t++)
      p = strtok(NULL,"/");
    char *name = p;
    p = strtok(NULL,"/");
    char *state = p;
    for(int t=0;t<4;t++)
      p = strtok(NULL,"/");

    string a(name);
    string b(state);
    p = strtok(state,"_");
    p = strtok(NULL,"_");
    char *direct = p;
    p = strtok(NULL,"_");
    p = strtok(NULL,"_");
    char *glass = p;

    string filename = "/home/snooze/projects/ANN/build/faces/"+a+"/"+b;
    char *filename_char =  const_cast<char*>(filename.c_str());
    double * target = new double[NETWORK_OUTPUT_AMOUNT];
    for(int p=0;p<NETWORK_OUTPUT_AMOUNT;p++)
      target[p]=0;
    string direct_2(direct);
    string glass_2(glass);
    if(direct_2 == "straight")
      target[0]=1;
    if(direct_2 == "up")
      target[1]=1;
    if(direct_2 == "left")
      target[2]=1;
    if(direct_2 == "right")
      target[3]=1;
//    if(glass_2=="open")
 //     target[4] = 1;
//    if(glass_2 == "sunglasses")
 //     target[5]=1;
    imageTestSet[i] =  openImage(filename_char);
    imageTestSet[i].target = target;
  }
  input.close();
}	
void testNetwork(IMAGE * testSet,double &rate){
  int count=0;///计算成功次数
  int testAmount = TEST_IMAGE_AMOUNT;
  double *hiddenValue = new double [NETWORK_HIDDEN_AMOUNT];	//隐藏层的输出值
  double *outputValue = new double [NETWORK_OUTPUT_AMOUNT];	//输出层的输出值
  for(int i=0;i<testAmount;i++){
    //每一个训练样例,计算隐藏层输出
    for(int k=0;k<NETWORK_HIDDEN_AMOUNT;k++){
		//每一个隐藏层单元
		for(int p=0;p<NETWORK_INPUT_AMOUNT;p++){
			//每一个像素
			hiddenValue[k] += testSet[i].data[p]*d_InputHiddenWeight[p][k];
		}
		hiddenValue[k] = 1/(1+exp(-(hiddenValue[k])));
	}
  //每一个训练样例，计算输出层输出
	for(int k=0;k<NETWORK_OUTPUT_AMOUNT;k++){
		//每一个输出层单元
		for(int p=0;p<NETWORK_HIDDEN_AMOUNT;p++){
			//每一个隐藏层单元
			outputValue[k] += hiddenValue[p]*d_HiddenOutputWeight[p][k];
		}
		outputValue[k] = 1/(1+exp(-(outputValue[k])));
	}
	//返回最大的方向
	double max1,max2;
	int flag1=-1,flag2=-1,flag3=-1,flag4=-1;
	///*
	if(outputValue[0]>outputValue[1]){max1 = outputValue[0];flag1 = 0;}
	else{max1 = outputValue[1];flag1=1;}
	if(max1>outputValue[2]);
	else{max1 = outputValue[2];flag1=2;}
	if(max1>outputValue[3]);
	else{max1 = outputValue[3];flag1=3;}
	///
	if(testSet[i].target[0]>testSet[i].target[1]){max2 = outputValue[0];flag2 = 0;}
	else{max2 = testSet[i].target[1];flag2=1;}
	if(max2>testSet[i].target[2]);
	else{max2 = testSet[i].target[2];flag2=2;}
	if(max2>testSet[i].target[3]);
	else{max2 =  testSet[i].target[3];flag2=3;}
	///
//	flag3=(outputValue[4]>outputValue[5])?4:5;
//	flag4=(testSet[i].target[4]>testSet[i].target[5])?4:5;
	//cout<<flag1<<"("<<flag2<<")"<<endl;
//	if(flag1 == flag2&&flag3==flag4)
	if(flag1 == flag2)
	    count++;
	
  }
  rate=((double)count)/((double)TEST_IMAGE_AMOUNT);///最终成功率
  //cout<<"rate="<<rate<<endl;
  
}
void backPropagte(IMAGE * trainSet, double speed, int times, double push){
	buildNetwork();
	int trainAmount = TRAIN_IMAGE_AMOUNT;
	for(int j=0;j<times;j++){//训练次数
		double *hiddenValue = new double [NETWORK_HIDDEN_AMOUNT];	//隐藏层的输出值
		double *outputValue = new double [NETWORK_OUTPUT_AMOUNT];	//输出层的输出值
		double *hiddenError = new double [NETWORK_HIDDEN_AMOUNT];	//隐藏层的误差
		double *outputError = new double [NETWORK_OUTPUT_AMOUNT];	//输出层的误差
		for(int i=0;i<trainAmount;i++){
			//每一个训练样例,计算隐藏层输出
			for(int k=0;k<NETWORK_HIDDEN_AMOUNT;k++){
				//每一个隐藏层单元
				for(int p=0;p<NETWORK_INPUT_AMOUNT;p++){
					//每一个像素
					hiddenValue[k] += trainSet[i].data[p]*d_InputHiddenWeight[p][k];
				}
				hiddenValue[k] = 1/(1+exp(-(hiddenValue[k])));
			}
			//每一个训练样例，计算输出层输出
			for(int k=0;k<NETWORK_OUTPUT_AMOUNT;k++){
				//每一个输出层单元
				for(int p=0;p<NETWORK_HIDDEN_AMOUNT;p++){
					//每一个隐藏层单元
					outputValue[k] += hiddenValue[p]*d_HiddenOutputWeight[p][k];
				}
				outputValue[k] = 1/(1+exp(-(outputValue[k])));
			}
			//每一个训练样例，计算输出层误差
			for(int k=0;k<NETWORK_OUTPUT_AMOUNT;k++)
				outputError[k] = outputValue[k]*(1-outputValue[k])*(trainSet[i].target[k]-outputValue[k]);
			//每一个训练样例，计算隐藏层误差
			for(int h=0;h<NETWORK_HIDDEN_AMOUNT;h++){
				double temp = 0;
				for(int k=0;k<NETWORK_OUTPUT_AMOUNT;k++)
					temp += d_HiddenOutputWeight[h][k]*outputError[k];
				hiddenError[h] = hiddenValue[h]*(1-hiddenValue[h])*temp;
			}
			//更新隐藏层的权值
			double temp1=0,temp2=0;
			for(int k=0;k<NETWORK_INPUT_AMOUNT;k++)
				for(int p=0;p<NETWORK_HIDDEN_AMOUNT;p++){
				  //      d_InputHiddenWeight[k][p]*=0.999;////项
					d_InputHiddenWeight[k][p] = d_InputHiddenWeight[k][p] + speed*hiddenError[p]*trainSet[i].data[k]+push*temp1;
					temp1 = speed*hiddenError[p]*trainSet[i].data[k];
				}
			//更新输出层的权值
			for(int k=0;k<NETWORK_HIDDEN_AMOUNT;k++)
				for(int p=0;p<NETWORK_OUTPUT_AMOUNT;p++){
				//	d_HiddenOutputWeight[k][p]*=0.999;///
					d_HiddenOutputWeight[k][p] = d_HiddenOutputWeight[k][p] + speed*outputError[p]*hiddenValue[k]+push*temp2;
					temp2 = speed*outputError[p]*hiddenValue[k];
				}

		}
	}
	
}
IMAGE openImage(char  *filename){
  IMAGE image;
  FILE *pgm;
  char line[512], intbuf[100], ch;
  int type, nc, nr, maxval, i, j, k, found;

  if ((pgm = fopen(filename, "r")) == NULL) {
    printf("IMGOPEN: Couldn't open '%s'\n", filename);
    return image;
  }

 // new->name = img_basename(filename);

  /*** Scan pnm type information, expecting P5 ***/
  fgets(line, 511, pgm);
  sscanf(line, "P%d", &type);
  if (type != 5 && type != 2) {
    printf("IMGOPEN: Only handles pgm files (type P5 or P2)\n");
    fclose(pgm);
    return image;
  }

  /*** Get dimensions of pgm ***/
  fgets(line, 511, pgm);
  sscanf(line, "%d %d", &nc, &nr);
  image.row = nr;
  image.col = nc;

  /*** Get maxval ***/
  fgets(line, 511, pgm);
  sscanf(line, "%d", &maxval);
  if (maxval > 255) {
    printf("IMGOPEN: Only handles pgm files of 8 bits or less\n");
    fclose(pgm);
    return image;
  }

  //new->data = (int *) malloc ((unsigned) (nr * nc * sizeof(int)));
  image.data = new double[nr*nc];
  if (image.data == NULL) {
    printf("IMGOPEN: Couldn't allocate space for image data\n");
    fclose(pgm);
    return image;
  }

  if (type == 5) {

    for (i = 0; i < nr; i++) {
      for (j = 0; j < nc; j++) {
       // img_setpixel(new, i, j, fgetc(pgm));
	image.data[i*nc+j] = ((double)fgetc(pgm))/255;
      }
    }

  } else if (type == 2) {

    for (i = 0; i < nr; i++) {
      for (j = 0; j < nc; j++) {

        k = 0;  found = 0;
        while (!found) {
          ch = (char) fgetc(pgm);
          if (ch >= '0' && ch <= '9') {
            intbuf[k] = ch;  k++;
  	  } else {
            if (k != 0) {
              intbuf[k] = '\0';
              found = 1;
	    }
	  }
	}
      }
    }

  } else {
    printf("IMGOPEN: Fatal impossible error\n");
    fclose(pgm);
    return image;
  }

  fclose(pgm);
  return image;
}

int main(){
  ofstream output("result.txt");
    double accuracyRate[30];
    double timeCost[30];
    
    for(int i = 0;i<30;i++){
      double rate;
      int times = i*50;
      time_t start,end;
      double cost;
      time(&start);
      cout<<"Start loading training & testing data......."<<endl;
      getTrainData();
      getTestData();
      cout<<"Loading complete."<<endl;
    /* for(int i=0;i<277;i++)
	cout<<imageTrainSet[i].col<<" "<<imageTrainSet[i].data[2]<<endl;
      cout<<"!!!!!!!!!!!!!!!!"<<endl;
      for(int i=0;i<100;i++)
	cout<<imageTestSet[i].col<<" "<<imageTestSet[i].data[2]<<endl;*/
      cout<<"Start training......."<<endl;
      backPropagte(imageTrainSet,SPEED_VALUE,times,PUSH_VALUE);
      cout<<"Training complete."<<endl;
      cout<<"Success Rate："<<endl;
      testNetwork(imageTestSet , rate);
      cout<<"Rate="<<rate<<endl;
      time(&end);
      cost=difftime(end,start); 
      cout<<"Time Consume:"<<cost<<"s"<<endl;
      accuracyRate[i] = rate;
      timeCost[i] = cost;
      ///打印输出结果
      output<<times<<" ";
      output<<accuracyRate[i]<<" ";
      output<<timeCost[i]<<" ";
      output<<endl;
    }
    
    

    output.close();
    
//    TestNetwork();
	//readImage("12.pgm");
	system("pause");
}






