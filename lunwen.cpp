#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <wchar.h>
wchar_t* read_file(const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (!file) {
        perror("Error opening file");
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* buffer = (char*)malloc(file_size + 1);
    if (!buffer) {
        fclose(file);
        return NULL;
    }

    size_t bytes_read = fread(buffer, 1, file_size, file);
    buffer[bytes_read] = '\0';
    fclose(file);

    size_t wlen = mbstowcs(NULL, buffer, 0);
    if (wlen == (size_t)-1) {
        free(buffer);
        return NULL;
    }

    wchar_t* wbuffer = (wchar_t*)malloc((wlen + 1) * sizeof(wchar_t));
    if (!wbuffer) {
        free(buffer);
        return NULL;
    }

    mbstowcs(wbuffer, buffer, wlen + 1);
    free(buffer);
    return wbuffer;
}

int lcs(const wchar_t* text1, const wchar_t* text2) {
    int len1 = wcslen(text1);
    int len2 = wcslen(text2);

    int** dp = (int**)malloc((len1 + 1) * sizeof(int*));
    for (int i = 0; i <= len1; i++) {
        dp[i] = (int*)calloc(len2 + 1, sizeof(int));
    }

    for (int i = 1; i <= len1; i++) {
        for (int j = 1; j <= len2; j++) {
            if (text1[i - 1] == text2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            }
            else {
                dp[i][j] = dp[i - 1][j] > dp[i][j - 1] ? dp[i - 1][j] : dp[i][j - 1];
            }
        }
    }

    int result = dp[len1][len2];

    for (int i = 0; i <= len1; i++) {
        free(dp[i]);
    }
    free(dp);

    return result;
}

int main(){
    setlocale(LC_ALL, "");
    char path_buffer[256];

    printf("请输入原文文件路径: ");
    fgets(path_buffer, 256, stdin);
    path_buffer[strcspn(path_buffer, "\n")] = '\0';
    wchar_t* original = read_file(path_buffer);

    printf("请输入抄袭版文件路径: ");
    fgets(path_buffer, 256, stdin);
    path_buffer[strcspn(path_buffer, "\n")] = '\0';
    wchar_t* plagiarized = read_file(path_buffer);

    if (!original || !plagiarized) {
        fprintf(stderr, "Error reading input files\n");
        free(original);
        free(plagiarized);
        return 1;
    }

    int lcs_len = lcs(original, plagiarized);
    int len1 = wcslen(original);
    int len2 = wcslen(plagiarized);
    double similarity = (2.0 * lcs_len) / (len1 + len2) * 100;
     printf("请输入输出文件路径: ");
    fgets(path_buffer, 256, stdin);
    path_buffer[strcspn(path_buffer, "\n")] = '\0';
    FILE* output = fopen(path_buffer, "w");
    if (!output) {
        perror("Error opening output file");
        free(original);
        free(plagiarized);
        return 1;
    }

    fprintf(output, "%.2f%%", similarity);
    fclose(output);

    free(original);
    free(plagiarized);
    return 0;
}