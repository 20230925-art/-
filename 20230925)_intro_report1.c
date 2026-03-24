#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int scores[10];   // 학생 10명의 성적을 저장할 배열
    int sum = 0;
    double avg;
    
    // 난수 생성을 위한 시드 설정
    srand(time(NULL));

    // 반복문을 이용하여 난수로 성적 입력 및 합계 계산
    for (int i = 0; i < 10; i++) {
        scores[i] = rand() % 101;  // 0 ~ 100 사이 난수
        sum += scores[i];
    }

    // 평균 계산
    avg = sum / 10.0;

    // 결과 출력
    printf("학생 성적:\n");
    for (int i = 0; i < 10; i++) {
        printf("%d번째 학생: %d점\n", i + 1, scores[i]);
    }

    printf("\n총점: %d\n", sum);
    printf("평균 점수: %.2f\n", avg);

    return 0;
}
