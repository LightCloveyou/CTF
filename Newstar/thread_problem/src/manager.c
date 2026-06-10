#include "manager.h"

__thread user temp;
__thread user current_account;
__thread int logged;
__thread int client_fd;

int mprintf(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    int ret = vdprintf(client_fd, fmt, args);
    va_end(args);
    return ret;
}


void manager_menu()
{
    if(!logged)
    {
        mprintf("1. Register\n");
        mprintf("2. Login\n");
        mprintf("3. Exit\n");
    }
    else
    {
        mprintf("Current account: %s\n", current_account.username);
        mprintf("1. Rename\n");
        mprintf("2. Logout\n");
        mprintf("3. Logoff\n");
        mprintf("4. Readflag\n");
    }
    mprintf("Please select your operation: ");
}

void manager_init()
{
    user_counts = 0;
    user_size = 20;
    users = malloc(user_size * sizeof(user));
    char username[USERNAME_LEN + 1], password[PASSWORD_LEN + 1];
    memset(username, 0, sizeof(username));
    memset(password, 0, sizeof(password));
    memset(users, 0, sizeof(user) * user_size);

    FILE* fd = fopen(USERFILE, "r");

    while(fscanf(fd, "%33s%33s", username, password) == 2)
    {
        memcpy(users[user_counts].username, username, USERNAME_LEN);
        memcpy(users[user_counts].password, password, PASSWORD_LEN);
        memset(username, 0, sizeof(username));
        memset(password, 0, sizeof(password));
        user_counts++;
        if(user_counts >= user_size)
            user_alloc();
    }
    fclose(fd);
    setbuf(stdin, 0);
    setbuf(stdout, 0);
    setbuf(stderr, 0);

}

void manager_register()
{
    int success = account_register(get_account(&temp));
    if(success < 0)
    {
        mprintf("Register failed!\n");
    }
}

void manager_login()
{
    int success = account_login(&current_account, get_account(&temp));
    if(success < 0)
    {
        mprintf("Login failed!\n");
        return;
    }
    logged = 1;
}

void manager_rename()
{
    user old_account, new_account;
    mprintf("Please input current account information.\n");
    get_account(&old_account);
    mprintf("Please input new account information.\n");
    get_account(&new_account);
    int success = account_rename(&current_account, &old_account, &new_account);
    if(success < 0)
        mprintf("Rename failed!\n");
}

void manager_logout()
{
    account_logout(&current_account);
    logged = 0;
}

void manager_delete()
{
    mprintf("Please check current account information.\n");
    int success = account_delete(&current_account, get_account(&temp));
    if(success < 0)
    {
        mprintf("Delete failed!\n");
        return;
    }
    logged = 0;
}

void get_flag()
{
    if(strcmp(current_account.username, "root"))
    {
        mprintf("You are not admin!\n");
        return;
    }
    int fd = open("/flag", O_RDONLY);
    char flag[0x100];
    read(fd, flag, 0x100);
    mprintf("flag: %s", flag);
}

void *account_manager()
{  
    signal(SIGPIPE, pthread_exit);

    int choice;
    char buf[16];
    memset(&temp, 0, sizeof(user));
    memset(&current_account, 0, sizeof(user));

    memcpy(temp.username, "root", 4);
    memcpy(temp.password, "8b53d2e57d1e8c67e994ef866c30571a", 32);
    account_register(&temp);

    mprintf("Welcode to 小明's account manager system!\n");
    while (1)
    {
        manager_menu();
        
        memset(buf, 0, 16);
        read(client_fd, buf, 15);
        choice = atoi(buf);
        if(!logged)
        {
            switch (choice)
            {
            case 1:
                manager_register();
                break;
            case 2:
                manager_login();
                break;
            case 3:
                save_users();
                return NULL;
                break;
            }
        }
        else
        {
            switch (choice)
            {
            case 1:
                manager_rename();
                break;
            case 2:
                manager_logout();
                break;
            case 3:
                manager_delete();
                break;
            case 4:
                get_flag();
                break;
            default:
                break;
            }
        }
    }
}

