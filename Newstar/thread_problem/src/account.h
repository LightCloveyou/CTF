#pragma once
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <stdarg.h>
#include <openssl/md5.h>

#define USERNAME_LEN 32
#define PASSWORD_LEN 32

#define USERFILE "user.db"

typedef struct user
{
    char password[USERNAME_LEN + 1];
    char username[PASSWORD_LEN + 1];
}user;

extern user* users;
extern int user_counts;
extern int user_size;
extern __thread int client_fd;
// pthread_mutex_t lock;

int mprintf(const char *fmt, ...);
void account_menu();
user* get_account(user *account);
int account_register(user* new_account);
int account_login(user *current_account, user *input_account);
int account_logout(user *currrnt_account);
int account_delete(user *current_account, user *input_account);
int account_rename(user *current_account, user *old_account, user *new_account);
int find_account(char* username);
void user_alloc();
void save_users();