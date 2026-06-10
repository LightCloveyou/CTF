#include "account.h"

user* users;
int user_counts, user_size;

int account_register(user* new_account)
{
    if(find_account(new_account->username) >= 0)
        return -1;

    memcpy(&users[user_counts], new_account, sizeof(user));

    user_counts++;
    if(user_counts >= user_size)
        user_alloc();
    return 0;
}

int account_login(user *current_account, user *input_account)
{
    int idx = find_account(input_account->username);
    if(idx < 0)
        return -1;

    if(!memcmp(users[idx].password, input_account->password, PASSWORD_LEN))
    {
        memcpy(current_account->username, input_account->username, USERNAME_LEN);
        memcpy(current_account->password, input_account->password, PASSWORD_LEN);
        return 0;
    }

    return -1;
}

int account_logout(user *currrnt_account)
{
    memset(currrnt_account, 0, sizeof(user));
}

int account_delete(user *current_account, user *input_account)
{
    if(memcmp(current_account, input_account, sizeof(user)))
        return -1;

    int idx = find_account(input_account->username);

    memset(&users[idx], 0, sizeof(user));
    memcpy(&users[idx], &users[idx + 1], sizeof(user) * (user_counts - idx - 1));
    account_logout(current_account);

    user_counts--;
    return 0;
}

int account_rename(user *current_account, user *old_account, user *new_account)
{
    if(memcmp(current_account, old_account, sizeof(user)))
        return -1;

    int idx = find_account(new_account->username);
    if(idx >= 0)
        return -1;
    idx = find_account(old_account->username);
    
    memcpy(&users[idx], new_account, sizeof(user));
    memcpy(current_account, new_account, sizeof(user));
}

int find_account(char* username)
{
    for(int i = 0; i < user_counts; i++)
    {
        // printf("[Debug find]: user: %s account: %s\n", users[i].username, users[i].password);
        if(!memcmp(users[i].username, username, USERNAME_LEN))
            return i;
    }
    return -1;
}

user* get_account(user *account)
{
    int invalid;
    memset(account, 0, sizeof(user));
    mprintf("Please input username: ");
    do
    {
        invalid = 0;
        int username_size = read(client_fd, account->username, 32);
        for(int i = 0; i < username_size; i++)
        {
            if(account->username[i] == '\n' || account->username[i] == ' ')
            {
                account->username[i] = 0;
                break;
            }
            if(account->username[i] < '0' || account->username[i] > '\x7f')
            {
                mprintf("Invalid username.\nPlease input again: ");
                invalid = 1;
                break;
            }
        }
    } while(invalid);
    char password[PASSWORD_LEN];
    memset(password, 0, 32);
    mprintf("Please input password: ");
    read(client_fd, password, 32);
    mprintf("\n");

    int size = strlen(password);
    unsigned char passowrd_hashed[MD5_DIGEST_LENGTH];
    MD5((unsigned char*)password, size, passowrd_hashed);

    for (int i = 0; i < MD5_DIGEST_LENGTH; i++)
        sprintf(account->password + i * 2, "%02x", passowrd_hashed[i]);
    // printf("[Debug get]: user: %s account: %s\n", account->username, account->password);
    return account;
}

void user_alloc()
{
    user *new = malloc(sizeof(user) * user_size * 2);
    memset(new, 0, sizeof(user) * user_size * 2);
    memcpy(new, users, sizeof(user) * user_size);
    free(users);
    users = new;
    user_size *= 2;
}

void save_users()
{
    FILE* fd = fopen("user.db", "w");
    for(int i = 0; i < user_counts; i++)
       fprintf(fd, "%s %s\n", users[i].username, users[i].password);
    fclose(fd);
    return;
}