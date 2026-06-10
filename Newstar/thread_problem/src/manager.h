#pragma once
#include <pthread.h>
#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <openssl/md5.h>
#include <signal.h>
#include "account.h"

extern __thread user temp;
extern __thread user current_account;
extern __thread int logged;
extern __thread int client_fd;


void manager_init();
void manager_menu();

void manager_register();
void manager_login();
void manager_rename();
void manager_logout();
void manager_delete();

void *account_manager();

