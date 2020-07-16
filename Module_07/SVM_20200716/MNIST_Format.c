#include <stdio.h>

unsigned char test_image[10000][28 * 28];
unsigned char train_image[10000][28 * 28];
unsigned char test_label[10000];
unsigned char train_label[10000];




int main()
{

    //���� �б�
    FILE* test;
    FILE* test_idx;
    FILE* train;
    FILE* train_idx;
    FILE* out_test_file;
    FILE* out_train_file;

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


    //����� ����
    fopen_s(&out_test_file, "out_test_file.idx3-ubyte", "w");
    fopen_s(&out_train_file, "out_train_file.idx3-ubyte", "w");

    fclose(test);
    fclose(test_idx);
    fclose(train);
    fclose(train_idx);


    //test ���� ������ ��ȯ
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

    //train ���� ������ ��ȯ
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


    // ���� �ݱ�

    fclose(out_test_file);
    fclose(out_train_file);

    return 0;
}