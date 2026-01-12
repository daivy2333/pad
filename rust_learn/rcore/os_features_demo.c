
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <signal.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <string.h>

// 共享数据结构
typedef struct {
    int counter;
    pthread_mutex_t mutex;
} SharedData;

// 全局共享数据指针
SharedData *shared_data;
// 全局文件描述符
int log_file;

// 异步信号处理函数
void async_handler(int signum) {
    time_t now;
    char time_str[50];

    time(&now);
    strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", localtime(&now));

    // 持久性：将异步事件记录到文件
    char log_msg[100];
    snprintf(log_msg, sizeof(log_msg), "[%s] 异步信号 %d 被捕获\n", time_str, signum);

    write(log_file, log_msg, strlen(log_msg));
    printf("%s", log_msg);
}

// 并发性：线程1函数 - 增加计数器
void* thread1_func(void* arg) {
    for (int i = 0; i < 10; i++) {
        // 共享性：访问共享内存中的数据
        pthread_mutex_lock(&shared_data->mutex);
        shared_data->counter++;
        printf("线程1: 计数器增加到 %d\n", shared_data->counter);

        // 持久性：将状态写入文件
        char log_msg[50];
        snprintf(log_msg, sizeof(log_msg), "线程1: 计数器增加到 %d\n", shared_data->counter);
        write(log_file, log_msg, strlen(log_msg));

        pthread_mutex_unlock(&shared_data->mutex);
        sleep(1);
    }
    return NULL;
}

// 并发性：线程2函数 - 减少计数器
void* thread2_func(void* arg) {
    for (int i = 0; i < 10; i++) {
        // 共享性：访问共享内存中的数据
        pthread_mutex_lock(&shared_data->mutex);
        shared_data->counter--;
        printf("线程2: 计数器减少到 %d\n", shared_data->counter);

        // 持久性：将状态写入文件
        char log_msg[50];
        snprintf(log_msg, sizeof(log_msg), "线程2: 计数器减少到 %d\n", shared_data->counter);
        write(log_file, log_msg, strlen(log_msg));

        pthread_mutex_unlock(&shared_data->mutex);
        sleep(1);
    }
    return NULL;
}

int main() {
    pthread_t thread1, thread2;

    // 持久性：创建日志文件
    log_file = open("os_features_log.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (log_file == -1) {
        perror("无法打开日志文件");
        exit(EXIT_FAILURE);
    }

    // 共享性：创建共享内存区域
    shared_data = (SharedData*)mmap(NULL, sizeof(SharedData), 
                                    PROT_READ | PROT_WRITE, 
                                    MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    if (shared_data == MAP_FAILED) {
        perror("无法创建共享内存");
        close(log_file);
        exit(EXIT_FAILURE);
    }

    // 初始化共享数据和互斥锁
    shared_data->counter = 0;
    pthread_mutex_init(&shared_data->mutex, NULL);

    // 异步性：设置信号处理
    signal(SIGUSR1, async_handler);
    signal(SIGUSR2, async_handler);

    // 持久性：记录程序开始
    char start_msg[100];
    time_t now;
    time(&now);
    strftime(start_msg, sizeof(start_msg), "程序开始于: %s", ctime(&now));
    write(log_file, start_msg, strlen(start_msg));
    printf("%s", start_msg);
    printf("程序PID: %d\n", getpid());
    printf("可以使用以下命令发送异步信号:\n");
    printf("  kill -USR1 %d\n", getpid());
    printf("  kill -USR2 %d\n", getpid());

    // 并发性：创建两个线程
    if (pthread_create(&thread1, NULL, thread1_func, NULL) != 0) {
        perror("无法创建线程1");
        exit(EXIT_FAILURE);
    }

    if (pthread_create(&thread2, NULL, thread2_func, NULL) != 0) {
        perror("无法创建线程2");
        exit(EXIT_FAILURE);
    }

    // 等待线程完成
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    // 持久性：记录程序结束
    time_t end_now;
    char end_msg[100];
    time(&end_now);
    strftime(end_msg, sizeof(end_msg), "程序结束于: %s", ctime(&end_now));
    write(log_file, end_msg, strlen(end_msg));
    printf("%s", end_msg);

    // 清理资源
    pthread_mutex_destroy(&shared_data->mutex);
    munmap(shared_data, sizeof(SharedData));
    close(log_file);

    printf("程序完成。日志已保存到 os_features_log.txt\n");
    return 0;
}
