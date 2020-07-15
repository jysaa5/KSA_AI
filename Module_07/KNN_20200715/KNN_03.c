#include <stdio.h>
#include <math.h>

unsigned char test_image[28 * 28 * 10000];
unsigned char train_image[28 * 28 * 10000];
unsigned char test_label[10000];
unsigned char train_label[10000];

//double dist[10000 * 10000];
int minDistIdx[10000];
unsigned char Lbs_minDistIdx[10000];


unsigned char train_lbs_image[28 * 28 * 10000];
unsigned char test_lbs_image[28 * 28 * 10000];


int count = 0;
double dist_temp = 0;
int dist1, dist2;


// �Լ�
void getDistAll();
void getMinClass();
void getRecoRate();
int CalDist();
int LBP_CalDist();


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



    // LBP
    for (int k = 0; k < 10000; k++) {
        for (int j = 1; j < 27; j++) {
            for (int i = 1; i < 27; i++) {

                int m = 0;
                unsigned char val1 = 0;
                unsigned char val2 = 0;

                for (int sj = -1; sj < 2; sj++) {
                    for (int si = -1; si < 2; si++) {
                        if (si != 0 && sj != 0) {
                            if (train_image[k * 28 * 28 + j * 28 + i] <= train_image[k * 28 * 28 + (j + sj) * 28 + i + si])
                                val1 |= (1 << m);
                            if (test_image[k * 28 * 28 + j * 28 + i] <= test_image[k * 28 * 28 + (j + sj) * 28 + i + si])
                                val2 |= (1 << m);
                        }
                        else if (si == 0 && sj == 0)
                        {
                            m--;
                        }
                        m++;
                    }
                }

                train_lbs_image[k * 28 * 28 + j * 28 + i] = val1;
                test_lbs_image[k * 28 * 28 + j * 28 + i] = val2;
            }
        }
    }



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


int LBP_CalDist(int test_idx, int train_idx) {
    for (int j = 0; j < 28 * 28; j++) {
        dist2 += (test_lbs_image[test_idx + j] - train_lbs_image[train_idx + j]) * (test_lbs_image[test_idx + j] - train_lbs_image[train_idx + j]);
    }
    return sqrt(dist2);

}



void getMinClass() {

    double temp = 0;
    double minDist = 1e6;


    for (int k = 0; k < 10000; k++) // �н� ������
    {
        minDist = 1e6;
        for (int j = 0; j < 10000; j++) // �׽�Ʈ ������
        {
            dist1 = CalDist(k * 28 * 28, j * 28 * 28);
            dist2 = LBP_CalDist(k * 28 * 28, j * 28 * 28);
            if (minDist > dist1)
            {
                minDist = dist1;
                minDistIdx[k] = train_label[j]; // �ּ� �Ÿ��� Ŭ���� ����
            }

            if (minDist > dist2)
            {
                minDist = dist2;
                Lbs_minDistIdx[k] = train_label[j]; // �ּ� �Ÿ��� Ŭ���� ����

            }
        }



    }
}

void getRecoRate()
{
    int recoRate1 = 0;
    int recoRate2 = 0;

    for (int i = 0; i < 10000; i++)
    {
        if (test_label[i] == minDistIdx[i]) {
            recoRate1++;
        }

        if (test_label[i] == Lbs_minDistIdx[i]) {
            recoRate2++;
        }
    }

    //printf_s("����� : %lf", recoRate);
    printf_s("K-NN ����� : %lf", (double)recoRate1 / 10000 * 100);
    printf_s("LBP ����� : %lf", (double)recoRate2 / 10000 * 100);
}