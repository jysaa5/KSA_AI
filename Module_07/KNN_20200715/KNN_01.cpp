#include <stdio.h>
#include <math.h>

unsigned char test_image[28 * 28 * 10000]; //image[10000][28 * 28], image[10000][28][28]
unsigned char train_image[28 * 28 * 10000];
unsigned char test_label[10000];
unsigned char train_label[10000];


double dist[10000 * 10000];
int minDistIdx[10000] = { 0 };
int count = 0;


//typedef struct idxDist 
//{
//   int index;
//   double dist;
//};



//double callDist(char* ptsi, char* ptri)
//{
//
//   int dist = 0;
//
//   
//   for (int j = 0; j < 28 * 28; j++)
//   {
//      dist += (ptsi[j] - ptri[j]) * (ptsi[j] - ptri[j]);
//   }
//   return sqrt(dist);
//}


void getDIstAll();
void getMinClass();
void getRecoRate();




int main()
{

    //fp = fopen_s(&fp, "t10k-images.idx3-ubyte", "rb"); // fopen_s

    //fread(test_image, 16, 1, fp); // 16byte 읽고 버리기
    //fread(test_image, sizeof(test_image), 1, fp); // 이미지 읽기




    FILE* fp;
    FILE* fpidx;
    FILE* tfp;
    FILE* tfpidx;




    fopen_s(&fp, "t10k-images.idx3-ubyte", "rb");
    fread(test_image, 16, 1, fp);
    fread(test_image, 28 * 28 * 10000, 1, fp);

    fopen_s(&fpidx, "t10k-labels.idx1-ubyte", "rb");
    fread(test_label, 8, 1, fpidx);
    fread(test_label, 10000, 1, fpidx);

    fopen_s(&tfp, "train-images.idx3-ubyte", "rb");
    fread(train_image, 16, 1, tfp);
    fread(train_image, 28 * 28 * 10000, 1, tfp);

    fopen_s(&tfpidx, "train-labels.idx1-ubyte", "rb");
    fread(train_label, 8, 1, tfpidx);
    fread(train_label, 10000, 1, tfpidx);






    getMinClass();
    getRecoRate();


    fclose(fp);
    fclose(fpidx);
    fclose(tfp);
    fclose(tfpidx);

    return 0;

}

void getDistAll()
{

    double temp = 0.0;
    int m = 0;
    int n = 0;
    int v = 0;

    for (m = 0; m < 10000; m++)
    {

        for (n = 0; n < 10000; n++)
        {
            for (v = 0; v < 28 * 28; v++) {
                //dist[i * j + j] = callDist(test_image[i * 28 * 28], train_image[j * 28 * 28]);
                temp += (test_image[m * 28 * 28 + v] - train_image[n * 28 * 28 + v]) * (test_image[m * 28 * 28 + v] - train_image[n * 28 * 28 + v]);

            }


            dist[m * 10000 + n] = sqrt(temp);

        }


        //printf_s("%d\n", m);
    }
}


void getMinClass() {

    double temp = 0;
    double minDist = 1e6;
    //double minDistArr[10000];
    //struct idxDist minDistArr[10000] ;


    getDistAll();


    for (int k = 0; k < 10000; k++) // 학습 데이터
    {

        minDist = 1e6;
        for (int j = 0; j < 10000; j++) // 테스트 데이터
        {
            temp = dist[k * 10000 + j];
            if (minDist > temp)
            {
                minDist = temp;
                //minDistArr[count] = temp;
                minDistIdx[k] = train_label[j]; // 최소 거리인 클래스 저장
                //count++;
            }
        }



    }
}


//int sorting()
//{
//   double minDistArr[10000] = { 0 };
//   double temp = 0.0;
//
//
//   
//   *minDistArr = getMinClass();
//
//   for (int i = 0; i < count; i++) {
//      for (int j = 0; j < count - i - 1; j++) {
//         if (minDistArr[j] > minDistArr[j + 1]) {
//            temp = minDistArr[j];
//            minDistArr[j] = minDistArr[j + 1];
//            minDistArr[j + 1] = temp;
//         }
//      }
//   }
//
//
//
//
//
//
//
//
//
//   return minDistArr;
//   
//}
//
//


void getRecoRate()
{

    double recoRate = 0.0;

    for (int i = 0; i < 10000; i++)
    {
        if (test_label[i] == minDistIdx[9999])
            recoRate += 0.01;
    }


    printf_s("정답률 : %lf", recoRate);
}