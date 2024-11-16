#include <stdio.h>
#include <stdlib.h>

// maxSeq 函数的原型声明
size_t maxSeq(int * array, size_t n);

// 测试函数，用于检查 `maxSeq` 函数的结果
void doTest(int * array, size_t n, size_t expected) {
    size_t result = maxSeq(array, n);
    if (result != expected) {
        printf("Test failed: maxSeq(");
        if (array == NULL) {
            printf("NULL");
        } else {
            printf("{");
            for (size_t i = 0; i < n; i++) {
                printf("%d", array[i]);
                if (i < n - 1) {
                    printf(", ");
                }
            }
            printf("}");
        }
        printf(", %zu) expected %zu, but got %zu\n", n, expected, result);
        exit(EXIT_FAILURE);
    }
}

// 主函数，包含所有的测试用例
int main(void) {
    // 测试用例 1: 空数组
    int * array1 = NULL;
    doTest(array1, 0, 0);

    // 测试用例 2: 只有一个元素的数组
    int array2[] = {5};
    doTest(array2, 1, 1);

    // 测试用例 3: 严格递增的数组
    int array3[] = {1, 2, 3, 4, 5};
    doTest(array3, 5, 5);

    // 测试用例 4: 严格递减的数组
    int array4[] = {5, 4, 3, 2, 1};
    doTest(array4, 5, 1);

    // 测试用例 5: 混合增加和减少的数组
    int array5[] = {1, 3, 2, 4, 6, 1, 7};
    doTest(array5, 7, 3);  // 最长递增子序列是 [2, 4, 6]

    // 测试用例 6: 所有元素相同
    int array6[] = {4, 4, 4, 4};
    doTest(array6, 4, 1);

    // 测试用例 7: 含有负数的数组
    int array7[] = {-3, -2, -1, 0, 1};
    doTest(array7, 5, 5);

    // 测试用例 8: 重复值与递增的组合
    int array8[] = {1, 2, 2, 3, 4};
    doTest(array8, 5, 3);  // 最长递增子序列是 [2, 3, 4]

    // 测试用例 9: 交替增加和减少的数组
    int array9[] = {1, 3, 2, 5, 4, 6};
    doTest(array9, 6, 2);  // 最长递增子序列是 [2, 5, 6]

    // 如果所有测试都通过
    printf("All tests passed successfully.\n");
    return EXIT_SUCCESS;
}


