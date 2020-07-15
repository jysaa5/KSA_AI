#include<iostream>

using namespace std;

int dist1, dist2;

unsigned char train_images[28 * 28 * 10000];
unsigned char test_images[28 * 28 * 10000];

unsigned char train_lbs_images[28 * 28 * 10000];
unsigned char test_lbs_images[28 * 28 * 10000];

unsigned char train_labels[10000];
unsigned char test_labels[10000];

unsigned char minDistIdx[10000];
unsigned char Lbs_minDistIdx[10000];

int CalDist(int test_idx, int train_idx) {
    for (int j = 0; j < 28 * 28; j++) {
        dist1 += (test_images[test_idx + j] - train_images[train_idx + j]) * (test_images[test_idx + j] - train_images[train_idx + j]);
    }
    return sqrt(dist1);

}

int Lbs_CalDist(int test_idx, int train_idx) {
    for (int j = 0; j < 28 * 28; j++) {
        dist2 += (test_lbs_images[test_idx + j] - train_lbs_images[train_idx + j]) * (test_lbs_images[test_idx + j] - train_lbs_images[train_idx + j]);
    }
    return sqrt(dist2);

}

int main() {

    FILE* train_fp;
    FILE* test_fp;

    FILE* train_label_fp;
    FILE* test_label_fp;

    fopen_s(&train_fp, "train-images.idx3-ubyte", "rb");
    fopen_s(&train_label_fp, "train-labels.idx1-ubyte", "rb");
    fopen_s(&test_fp, "t10k-images.idx3-ubyte", "rb");
    fopen_s(&test_label_fp, "t10k-labels.idx1-ubyte", "rb");

    fread(train_labels, 8, 1, train_label_fp);
    fread(train_labels, sizeof(train_labels), 1, train_label_fp);

    fread(train_images, 16, 1, train_fp);
    fread(train_images, sizeof(train_images), 1, train_fp);

    fread(test_labels, 8, 1, test_label_fp);
    fread(test_labels, sizeof(test_labels), 1, test_label_fp);

    fread(test_images, 16, 1, test_fp);
    fread(test_images, sizeof(test_images), 1, test_fp);

    fclose(train_label_fp);
    fclose(train_fp);
    fclose(test_label_fp);
    fclose(test_fp);

    for (int k = 0; k < 10000; k++) {
        for (int j = 1; j < 27; j++) {
            for (int i = 1; i < 27; i++) {

                int m = 0;
                unsigned char val1 = 0;
                unsigned char val2 = 0;

                for (int sj = -1; sj < 2; sj++) {
                    for (int si = -1; si < 2; si++) {
                        if (si != 0 && sj != 0) {
                            if (train_images[k * 28 * 28 + j * 28 + i] <= train_images[k * 28 * 28 + (j + sj) * 28 + i + si])
                                val1 |= (1 << m);
                            if (test_images[k * 28 * 28 + j * 28 + i] <= test_images[k * 28 * 28 + (j + sj) * 28 + i + si])
                                val2 |= (1 << m);
                        }
                        else if (si == 0 && sj == 0)
                            m--;
                        m++;
                    }
                }

                train_lbs_images[k * 28 * 28 + j * 28 + i] = val1;
                test_lbs_images[k * 28 * 28 + j * 28 + i] = val2;
            }
        }
    }

    for (int k = 0; k < 10000; k++) {
        int minDist1 = INT32_MAX;
        int minDist2 = INT32_MAX;

        for (int j = 0; j < 10000; j++) {
            dist1 = CalDist(k * 28 * 28, j * 28 * 28);
            dist2 = Lbs_CalDist(k * 28 * 28, j * 28 * 28);
            if (minDist1 > dist1) {
                minDist1 = dist1;
                minDistIdx[k] = train_labels[j];
            }
            if (minDist2 > dist2) {
                minDist2 = dist2;
                Lbs_minDistIdx[k] = train_labels[j];
            }
        }
    }

    int count1 = 0;
    int count2 = 0;

    for (int i = 0; i < 10000; i++) {
        if (minDistIdx[i] == test_labels[i]) {
            count1++;
        }
        if (Lbs_minDistIdx[i] == test_labels[i]) {
            count2++;
        }
    }

    cout << "AVG: " << (double)count1 / 10000 * 100 << "\n";
    cout << "AVG: " << (double)count2 / 10000 * 100 << "\n";

    return 0;
}