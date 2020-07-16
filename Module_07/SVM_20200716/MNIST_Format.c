#include <stdio.h>

unsigned char test_image[10000][28 * 28];
unsigned char train_image[10000][28 * 28];
unsigned char test_label[10000];
unsigned char train_label[10000];




int main()
{

    //파일 읽기
    FILE* test;
    FILE* test_idx;
    FILE* train;
    FILE* train_idx;
    FILE* out_test_file;
    FILE* out_train_file;

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


    //출력한 파일
    fopen_s(&out_test_file, "out_test_file.idx3-ubyte", "w");
    fopen_s(&out_train_file, "out_train_file.idx3-ubyte", "w");

    fclose(test);
    fclose(test_idx);
    fclose(train);
    fclose(train_idx);


    //test 파일 데이터 변환
    for (int k = 0; k < 10000; k++)
    {
        fprintf(out_test_file, "%d ", test_label[k]);
        for (int i = 0; i < 28 * 28; i++)
        {
            if (test_image[k][i])
                fprintf(out_test_file, "%d:%d ", i + 1, (int)test_image[k][i]);
        }
        fprintf(out_test_file, "\n");
    }

    //train 파일 데이터 변환
    for (int k = 0; k < 10000; k++)
    {
        fprintf(out_train_file, "%d ", train_label[k]);
        for (int i = 0; i < 28 * 28; i++)
        {
            if (train_image[k][i])
                fprintf(out_train_file, "%d:%d ", i + 1, (int)train_image[k][i]);
        }
        fprintf(out_train_file, "\n");
    }


    // 파일 닫기

    fclose(out_test_file);
    fclose(out_train_file);

    return 0;
}