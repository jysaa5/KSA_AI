#include <stdio.h>
#include <math.h>

// 학습: 1만 개, 테스트: 1만 개

unsigned char test_image[28 * 28 * 10000];
unsigned char train_image[28 * 28 * 10000];
unsigned char test_label[10000];
unsigned char train_label[10000];

//double dist[10000 * 10000];
int minDistIdx[10000];
unsigned char Lbp_minDistIdx[10000];


unsigned char train_lbp_image[28 * 28 * 10000];
unsigned char test_lbp_image[28 * 28 * 10000];


int count = 0;
double dist_temp = 0;
int dist1, dist2;


// 함수
void getDistAll();
void getMinClass();
void getRecoRate();
int CalDist();
int LBP_CalDist();


int main()
{
    //파일 읽기
    FILE* test;
    FILE* test_idx;
    FILE* train;
    FILE* train_idx;

    // 테스트 이미지
    fopen_s(&test, "t10k-images.idx3-ubyte", "rb");
    fread(test_image, 16, 1, test);
    fread(test_image, 28 * 28 * 10000, 1, test);

    // 테스트 이미지 인덱스
    fopen_s(&test_idx, "t10k-labels.idx1-ubyte", "rb");
    fread(test_label, 8, 1, test_idx);
    fread(test_label, 10000, 1, test_idx);

    // 학습 이미지
    fopen_s(&train, "train-images.idx3-ubyte", "rb");
    fread(train_image, 16, 1, train);
    fread(train_image, 28 * 28 * 10000, 1, train);

    // 학습 이미지 인덱스
    fopen_s(&train_idx, "train-labels.idx1-ubyte", "rb");
    fread(train_label, 8, 1, train_idx);
    fread(train_label, 10000, 1, train_idx);


    // 파일 닫기
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

                train_lbp_image[k * 28 * 28 + j * 28 + i] = val1;
                test_lbp_image[k * 28 * 28 + j * 28 + i] = val2;
            }
        }
    }



    // 함수 호출
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
        dist2 += (test_lbp_image[test_idx + j] - train_lbp_image[train_idx + j]) * (test_lbp_image[test_idx + j] - train_lbp_image[train_idx + j]);
    }
    return sqrt(dist2);

}



void getMinClass() {

    double temp = 0;
    double minDist1 = 1e6;
    double minDist2 = 1e6;


    for (int k = 0; k < 10000; k++) // 학습 데이터
    {
        minDist1 = 1e6;
        minDist2 = 1e6;
        for (int j = 0; j < 10000; j++) // 테스트 데이터
        {
            dist1 = CalDist(k * 28 * 28, j * 28 * 28);
            dist2 = LBP_CalDist(k * 28 * 28, j * 28 * 28);
            if (minDist1 > dist1)
            {
                minDist1 = dist1;
                minDistIdx[k] = train_label[j]; // 최소 거리인 클래스 저장
            }

            if (minDist2 > dist2)
            {
                minDist2 = dist2;
                Lbp_minDistIdx[k] = train_label[j]; // 최소 거리인 클래스 저장

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

        if (test_label[i] == Lbp_minDistIdx[i]) {
            recoRate2++;
        }
    }


    printf_s("K-NN 정답률 : %lf\n", (double)recoRate1 / 10000 * 100);
    printf_s("LBP 정답률 : %lf\n", (double)recoRate2 / 10000 * 100);
}