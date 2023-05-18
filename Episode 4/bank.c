#include <stdio.h>
typedef struct client
{
    int num;
    int service_time;
    int servicing_flag;
    int wait_time;
} client;
int cur_client_num;
int window_num;
int total_client_num;
int get_wait_num(client *client_list)
{
    int i = 0;
    int wait_num = 0;
    int cnt = 0;
    for (i = 0; cnt < cur_client_num; i++)
    {
        if (client_list[i].servicing_flag == 0)
        {
            wait_num++;
        }
        if (client_list[i].servicing_flag != -1)
        {
            cnt++;
        }
    }
    return wait_num;
}
void is_window_add(client *client_list)
{
    int wait_num = get_wait_num(client_list);
    if (window_num == 3)
    {
        if (wait_num >= 21 && wait_num < 28)
        {
            window_num++;
        }
        else if (wait_num >= 28)
        {
            window_num += 2;
        }
    }
    else if (window_num == 4)
    {
        if (wait_num >= 28)
        {
            window_num++;
        }
    }
}
int get_next_term_window_num(client *client_list)
{
    int wait_num = get_wait_num(client_list);
    if (window_num == 5)
    {
        if (wait_num < 35)
        {
            return 4;
        }
        else
        {
            return 5;
        }
    }
    else if (window_num == 4)
    {
        if (wait_num < 28)
        {
            return 3;
        }
        else
        {
            return 4;
        }
    }
    else if (window_num == 3)
    {
        return 3;
    }
}
void client_status(client *client_list, int client_add_flag)
{
    int i = 0;
    int servicing_num = 0;
    int cnt = 0;
    if (client_add_flag == 1)
    {
        is_window_add(client_list);
    }
    cnt = 0;
    for (i = 0; cnt < cur_client_num; i++)
    {
        if (client_list[i].servicing_flag == 1)
        {
            servicing_num++;
        }
        if (client_list[i].servicing_flag != -1)
        {
            cnt++;
        }
    }
    if (servicing_num < window_num)
    {
        int arragement_num = window_num - servicing_num;
        cnt = 0;
        for (i = 0; cnt < cur_client_num && arragement_num > 0 && i < total_client_num; i++)
        {
            if (client_list[i].servicing_flag == 0)
            {
                client_list[i].servicing_flag = 1;
                arragement_num--;
            }
            if (client_list[i].servicing_flag != -1)
            {
                cnt++;
            }
        }
    }
    int tmp_cur_client_num = cur_client_num;
    cnt = 0;
    for (i = 0; cnt < tmp_cur_client_num; i++)
    {
        if (client_list[i].servicing_flag == 1)
        {
            client_list[i].service_time--;
            if (client_list[i].service_time == 0)
            {
                client_list[i].servicing_flag = -1;
                cur_client_num--;
            }
        }
        if (client_list[i].servicing_flag != -1)
        {
            cnt++;
        }
    }
    cnt = 0;
    for (i = 0; cnt < cur_client_num; i++)
    {
        if (client_list[i].servicing_flag == 0)
        {
            client_list[i].wait_time++;
        }
        if (client_list[i].servicing_flag != -1)
        {
            cnt++;
        }
    }
}
int main()
{
    int time_term = 0;
    scanf("%d", &time_term);
    int i = 0;
    int client_num[20] = {0};
    for (i = 0; i < time_term; i++)
    {
        scanf("%d", &client_num[i]);
        total_client_num += client_num[i];
    }
    client client_list[100] = {0};
    for (i = 0; i < total_client_num; i++)
    {
        client_list[i].num = i + 1;
        int service_type = 0;
        scanf("%d", &service_type);
        switch (service_type)
        {
        case 1:
            client_list[i].service_time = 1;
            break;
        case 2:
            client_list[i].service_time = 2;
            break;
        case 3:
            client_list[i].service_time = 3;
            break;
        default:
            break;
        }
    }
    int client_add_flag = 0;
    window_num = 3;

    for (i = 0; i < time_term; i++)
    {
        client_add_flag = 1;
        cur_client_num += client_num[i];
        client_status(client_list, client_add_flag);
        window_num = get_next_term_window_num(client_list);
    }
    client_add_flag = 0;
    while (cur_client_num > 0)
    {
        client_status(client_list, client_add_flag);
        window_num = get_next_term_window_num(client_list);
    }
    for (i = 0; i < total_client_num; i++)
    {
        printf("%d : %d\n", client_list[i].num, client_list[i].wait_time);
    }
    return 0;
}