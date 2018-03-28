#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#include <string>
#include <vector>
#include <sys/inotify.h>
#include <limits.h>
#include <pthread.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <algorithm>
#include <map>

#define FIFO_NAME "dhcpclient"
#define BUFF_LENGTH 32

void DhcpClientConfigure(void)
{
    int ret;
    FILE *out_stream;
    char out_line[1024] = "";
    char option[256] = "";
    char buf_udhcpc_pid[10] = {0};
    char vendor_class_value[] = "SMRML3-1-RM";
    const char* path_udhcpc_pid = "/var/run/udhcpc.pid";
    std::string commands;
    std::string out_data;

    int fd = open(path_udhcpc_pid, O_RDONLY|O_CREAT);
    if (fd == -1)
    {
        printf("%s(): open failed, file: %s, error = %d, err_str = %s!\n", __FUNCTION__, path_udhcpc_pid, errno, strerror(errno)); fflush(stdout);
        return; 
    }
    read(fd, buf_udhcpc_pid, sizeof(buf_udhcpc_pid));

    if (buf_udhcpc_pid[0] != '\0')
    {
        std::string udhcpc_pid_str = buf_udhcpc_pid;
        printf("%s, udhcpc pid = %s\n", __FUNCTION__, buf_udhcpc_pid);

        commands = "kill -9 ";
        commands.append(udhcpc_pid_str);
        ret = system(commands.c_str());

        printf("%s(), udhcpc process already exits, kill it! Commands = %s\n", __FUNCTION__, commands.c_str());
        commands.erase();
    }
    else
    {
        printf("%s(), udhcpc process didn't started \n", __FUNCTION__);
    }

    option[0] = 60;
    option[1] = sizeof(vendor_class_value) -1;

    strcpy(option+2, vendor_class_value);
    printf("%s(), option = %s\n", __FUNCTION__, option+2);

    std::string vendor_value(option+2, option[1]);
    printf("%s(), vendor_value = %s\n", __FUNCTION__, vendor_value.c_str());

    commands = "udhcpc -i eth1 -t 1 -T 2 -n -R -p /var/run/udhcpc.pid -V ";
    commands.append(vendor_value);
    printf("%s(), commands = %s\n", __FUNCTION__, commands.c_str());
    
    ret = system(commands.c_str());

    memset(out_line, 0, sizeof(out_line));
    out_stream = popen(commands.c_str(), "r");
    if (NULL == out_stream)
    {
        printf("popen failed!!!");    
    }
    while (fgets(out_line, sizeof(out_line), out_stream) != NULL)
    {
        if (out_line[strlen(out_line) -1] == '\n')
            //out_line[strlen(out_line) -1] = '\0'; 
        out_data.append(out_line);
    }
    ret = pclose(out_stream);
    printf("Commands output......\n%s\n", out_data.c_str());

}

void DhcpRelease(void)
{
    int ret;
    char buf_udhcpc_pid[10] = {0};
    std::string commands = "kill -USR2 ";
    const char* path_udhcpc_pid = "/var/run/udhcpc.pid";
    
    int fd = open(path_udhcpc_pid, O_RDONLY|O_CREAT);
    if (fd == -1)
    {
        printf("%s(): open failed, file: %s, error = %d, err_str = %s!\n", __FUNCTION__, path_udhcpc_pid, errno, strerror(errno)); fflush(stdout);
        return; 
    }

    read(fd, buf_udhcpc_pid, sizeof(buf_udhcpc_pid));

    if (buf_udhcpc_pid[0] == '\0')
    {
        printf("%s(), udhcpc pid is NULL, process maybe don't started!!!\n", __FUNCTION__);
    }

    std::string udhcpc_pid_str = buf_udhcpc_pid;
    printf("%s(), udhcpc pid = %s\n", __FUNCTION__, udhcpc_pid_str.c_str());fflush(stdout);
    commands.append(udhcpc_pid_str);

    printf("%s(), commands = %s\n", __FUNCTION__, commands.c_str());fflush(stdout);

    ret = system("ifconfig -a");
    ret = system(commands.c_str());
    sleep(2);
    ret = system("ifconfig -a");
}

void *DhcpClientMonitorByInotify(void* arg)
{
    (void)arg;
    char *p = NULL;
    char buf[1024];
    int num_read;
    int inotify_fd, wd;
    struct inotify_event *event;

    inotify_fd = inotify_init();
    if (inotify_fd == -1)
    {
    
    }

    wd = inotify_add_watch(inotify_fd, "/var/run/dhcpc_result.txt", IN_CLOSE_WRITE);

    while(1)
    {
        num_read = read(inotify_fd, buf, sizeof(buf));

        if (num_read == -1)
        {
        
        }
        if (num_read == 0)
        {
        
        }
        for (p = buf; p < buf+num_read;)
        {
            event = (struct inotify_event *)p;
            
            printf("%s(), wd = %2d\n", __FUNCTION__, event->wd);
            printf("%s(), mask = ", __FUNCTION__);
            if (event->mask & IN_ACCESS) printf("IN_ACCESS");
            if (event->mask & IN_ATTRIB) printf("IN_ATTRIB");
            if (event->mask & IN_CLOSE_NOWRITE) printf("IN_CLOSE_NOWRITE");
            if (event->mask & IN_CLOSE_WRITE) printf("IN_CLOSE_WRITE");
            if (event->mask & IN_CREATE) printf("IN_CREATE");
            if (event->mask & IN_DELETE) printf("IN_DELETE");
            if (event->mask & IN_DELETE_SELF) printf("IN_DELETE_SELF");
            if (event->mask & IN_IGNORED) printf("IN_IGNORED");
            if (event->mask & IN_ISDIR) printf("IN_ISDIR");
            if (event->mask & IN_MODIFY) printf("IN_MODIFY");
            if (event->mask & IN_MOVE_SELF) printf("IN_MOVE_SELF");
            if (event->mask & IN_MOVED_FROM) printf("IN_MOVED_FROM");
            if (event->mask & IN_MOVED_TO) printf("IN_MOVED_TO");
            if (event->mask & IN_OPEN) printf("IN_OPEN");
            if (event->mask & IN_Q_OVERFLOW) printf("IN_Q_OVERFLOW");
            if (event->mask & IN_UNMOUNT) printf("IN_UNMOUNT");

            printf("\n");

            p += sizeof(struct inotify_event) + event->len;
        }
    }

}


void *DhcpClientMonitorByFIFO(void* arg)
{
    (void)arg;
    int fd;
    int num_data;
    char buf[BUFF_LENGTH];
    std::string fifo_data_once;
    std::string fifo_data_all;

    memset(buf, 0, sizeof(buf));

    if (mkfifo(FIFO_NAME, 0666) == -1)
    {
        printf("%s(): FIFO create failed, error = %d, err_str = %s!\n", __FUNCTION__, errno, strerror(errno)); fflush(stdout);
    }

    while(1)
    {
        printf("open...\n");fflush(stdout);
        fd = open(FIFO_NAME, O_RDONLY);
        if (fd == -1)
        {
            printf("%s(): FIFO open failed, error = %d, err_str = %s!\n", __FUNCTION__, errno, strerror(errno)); fflush(stdout);
        }

        while(1)
        {
            printf("read...\n");fflush(stdout);
            num_data = read(fd, buf, sizeof(buf));
            if (num_data == -1)
            {

            }
            if (num_data == 0)
            {
                printf("FIFO data receive done! all:\n%s\n\n\n", fifo_data_all.c_str());fflush(stdout);
                close(fd);
                fifo_data_all.erase();
                break;
            }

            fifo_data_once = buf;
            fifo_data_all.append(fifo_data_once);
            printf("fifo data once:%s\n",fifo_data_once.c_str());fflush(stdout);
            memset(buf, 0, sizeof(buf));
        }
    }

    return 0;

}

void DhcpClientMonitor(void)
{
    int fd;
    int num_data;
    char buf[BUFF_LENGTH];

    memset(buf, 0, sizeof(buf));

    if (mkfifo(FIFO_NAME, 0666) == -1)
    {
        printf("%s(): FIFO create failed, error = %d, err_str = %s!\n", __FUNCTION__, errno, strerror(errno)); fflush(stdout);
    }

    while(1)
    {
        printf("open...\n");fflush(stdout);
        fd = open(FIFO_NAME, O_RDONLY);
        if (fd == -1)
        {
            printf("%s(): FIFO open failed, error = %d, err_str = %s!\n", __FUNCTION__, errno, strerror(errno)); fflush(stdout);
        }

        while(1)
        {
            printf("read...\n");fflush(stdout);
            num_data = read(fd, buf, sizeof(buf));
            if (num_data == -1)
            {

            }
            if (num_data == 0)
            {
                printf("Script done, data is NULL!\n\n\n");fflush(stdout);
                close(fd);
                break;
            }

            printf("fifo data:%s\n", buf);fflush(stdout);
            memset(buf, 0, sizeof(buf));
        }
    }

}
void StringFind()
{
    std::string eth_data = "ip=192.168.254.12 siaddr=192.168.254.99 router=192.168.254.1";
    //std::string::size_type ip_pos_start = eth_data.find("ip");
    //std::string::size_type ip_pos_end = eth_data.find(" ", ip_pos_start+1);

    //printf("%s ip start:%ld, ip end:%ld\n", __PRETTY_FUNCTION__, ip_pos_start, ip_pos_end);
    std::map<std::string, std::string> server_config;

    std::string::iterator p1 = std::find(eth_data.begin(), eth_data.end(), '=');
    std::string::iterator p2 = std::find(p1, eth_data.end(), ' ');
    std::string IP(p1 + 1, p2); 
    server_config["IP"] = IP;
    printf("%s IP: %s\n", __PRETTY_FUNCTION__, server_config["IP"].c_str());

    std::string::iterator p3 = std::find(p2, eth_data.end(), '=');
    std::string::iterator p4 = std::find(p3, eth_data.end(), ' ');

    std::string siaddr(p3 + 1, p4); 
    server_config["siaddr"] = siaddr;
    printf("%s IP: %s, %s\n", __PRETTY_FUNCTION__, server_config["IP"].c_str(), server_config["siaddr"].c_str());

    //std::string IP(eth_data.begin()+ip_pos_start+3, eth_data.begin()+ip_pos_end-1); 
    //printf("%s IP: %s\n", __PRETTY_FUNCTION__, IP.c_str());
}

int main(int argc, char* argv[])
{
    int ret;
    pthread_t id;          // identifer for new thread

    DhcpClientMonitor();

    ret = pthread_create(&id, NULL, DhcpClientMonitorByFIFO, NULL);
    if (ret != 0)
    {
        printf("%s(): thread create failed\n", __PRETTY_FUNCTION__);
        return -1;
    }
    pthread_join(id, NULL);    // block self and wait for thread id0 stop(call pthread_exit() )
    sleep(2);

    DhcpClientConfigure();
    DhcpRelease();

    StringFind();

    return 0;
}






