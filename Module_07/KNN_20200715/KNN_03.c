#include <stdio.h>
#include <math.h>

unsigned char test_image[28 * 28 * 10000];
unsigned char train_image[28 * 28 * 10000];
unsigned char test_label[10000];
unsigned char train_label[10000];

double dist[10000 * 10000];
int minDistIdx[10000];
int count = 0;
double dist_temp = 0;
int dist1, dist2;

void getDistAll();
void getMinClass();
void getRecoRate();
int CalDist();



int main()
{
    //���� �б�
    FILE* test;
    FILE* test_idx;
    FILE* train;
    FILE* train_idx;

    // �׽�Ʈ �̹���
    fopen_s(&test, "t10k-images.idx3-ubyte", "rb");
    fread(test_image, 16, 1, test);
    fread(test_image, 28 * 28 * 10000, 1, test);

    // �׽�Ʈ �̹��� �ε���
    fopen_s(&test_idx, "t10k-labels.idx1-ubyte", "rb");
    fread(test_label, 8, 1, test_idx);
    fread(test_label, 10000, 1, test_idx);

    // �н� �̹���
    fopen_s(&train, "train-images.idx3-ubyte", "rb");
    fread(train_image, 16, 1, train);
    fread(train_image, 28 * 28 * 10000, 1, train);

    // �н� �̹��� �ε���
    fopen_s(&train_idx, "train-labels.idx1-ubyte", "rb");
    fread(train_label, 8, 1, train_idx);
    fread(train_label, 10000, 1, train_idx);


    // ���� �ݱ�
    fclose(test);
    fclose(test_idx);
    fclose(train);
    fclose(train_idx);


    // �Լ� ȣ��
    getMinClass();
    getRecoRate();

    return 0;

}


int CalDist(int test_idx, int train_idx) {
    for (int j = 0; j < 28 * 28; j++) {
        dist1 += (test_image[test_idx + j] - train_image[train_idx + j]) * (test_image[test_idx + j] - train_image[train_idx + j]);
    }
    return sqrt(dist1);

}

void getDistAll()
{

    int m = 0;
    int n = 0;
    int v = 0;
    int num = 28 * 28;

    for (m = 0; m < 10000; m++)
    {

        for (n = 0; n < 10000; n++)
        {
            for (v = 0; v < 28 * 28; v++) {
                dist_temp += ((int)(test_image[m * num + v] - train_image[n * num + v])) * ((int)(test_image[m * num + v] - train_image[n * num + v]));
                dist[m * 10000 + n] = sqrt(dist_temp);
            }


            //dist[m * 10000 + n] = sqrt(dist_temp);

        }

        printf_s("%lf\n", dist[m * 10000 + n]);
        //printf_s("%d\n", m);
    }
}


void getMinClass() {

    double temp = 0;
    double minDist = 1e6;
    //double minDistArr[10000];
    //struct idxDist minDistArr[10000] ;


    //getDistAll();


    for (int k = 0; k < 10000; k++) // �н� ������
    {
       // dist1 = CalDist(k * 28 * 28, j * 28 * 28);
        minDist = 1e6;
        for (int j = 0; j < 10000; j++) // �׽�Ʈ ������
        {
            dist1 = CalDist(k * 28 * 28, j * 28 * 28);
           // temp = dist[k * 10000 + j];
            if (minDist > dist1)
            {
                minDist = dist1;
                //minDistArr[count] = temp;
                minDistIdx[k] = train_label[j]; // �ּ� �Ÿ��� Ŭ���� ����
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
    //double recoRate = 0;
    int recoRate = 0;

    for (int i = 0; i < 10000; i++)
    {
        if (test_label[i] == minDistIdx[i]) {
            recoRate++;
        }
    }


    //printf_s("����� : %lf", recoRate);
    printf_s("����� : %lf", (double)recoRate / 10000 * 100);
}