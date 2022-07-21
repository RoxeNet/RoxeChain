#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <sys/prctl.h>
#include <sys/stat.h>


int g_child = -1;

static int GetPid(char* buf)
{
    char* p1 = NULL;
    while (*buf != '\0') {
        if (p1 == NULL && *buf >= '1' && *buf <= '9')
           p1 = buf;

        if (p1) {
            if (*buf == ' ') {
                *buf = '\0';
                break;
            }
        }
        buf++;
    }

    if (p1) {
        return atoi(p1);
    }
    return -1;
}

int WDExistsProcess(const char *name)
{
    FILE* fp;
    int ret = -1;

    char buf[1024];
    char cmd[256];
    sprintf(cmd, "ps -ef | grep \"%s\" | grep -v \"grep\"", name);
    fp = popen(cmd, "r");

    if (NULL == fp) {
        ret = 0;
        printf("system errr line:%d\n", __LINE__);
    }
    else
    {
        while (fgets(buf, sizeof(buf), fp) != NULL) {
	   // printf("%s\n", buf);

            if (strstr(buf, name)) {
                ret = GetPid(buf);
                break;
            }
        }
    }
    pclose(fp);
    return ret;
}

void WDGetCurDir(char* dir, int size)
{
    readlink("/proc/self/exe", dir, size);
    char* p = strrchr(dir, '/');
    if (p == 0 || p == dir) {
        printf("get path error!\n");
        return;
    }
    *p = '\0';
}

static void Proc(const char* pgname, char* shortname, char** param, int param_count)
{
    int ret, status;	
   
    int count = param_count; 
    char path[256];
    WDGetCurDir(path, sizeof(path));
    char param1[] = "--replay-blockchain"; 
    char param2[] = "--hard-replay-blockchain"; 

    while (1) {
	pid_t pid = fork();
	if (pid < 0) {
            printf("fork error=%s\n", strerror(errno));
	    sleep(5);
	    continue;
	}
        
	if (pid == 0) {
	    char szStderr[320];
	    char szStdout[320];
	    snprintf(szStdout, sizeof(szStdout), "%s/stdout.txt", path);  
            snprintf(szStderr, sizeof(szStderr), "%s/stderr.txt", path);

	    FILE* pout = freopen(szStdout, "w+", stdout);
            FILE* perr = freopen(szStderr, "w+", stderr);
	    
	    execvp(pgname, param);

	    fclose(pout);
	    fclose(perr);
	    exit(-1);	
	}

        if (pid > 0) {
            g_child = pid;

	    status = 0;	
	    ret = waitpid(pid, &status, 0);

	    char file[256];
	    snprintf(file, sizeof(file), "%s/stderr.txt", path);
	  
	    int flag = -1; 
	    FILE* pFile = fopen(file, "rb");
	    if (pFile) {
	       	flag = -2;

	        fseek(pFile, 0, SEEK_END);
	        int64_t len = ftell(pFile);
		fseek(pFile, len - 1024, SEEK_SET);
		
		char buf[2048];
                if (0 != fread(buf, 1, sizeof(buf), pFile)) {
	            flag = -3;		

                    if (strstr(buf, "replay required")) {
                        param[count] = param1;
                        param[count + 1] = param2;
			count += 2;
			flag = 1;
		    }
		    else {
			flag = -4;    
		        if (count - 2 == param_count) {
			    flag = 0;	
                            param[param_count] = NULL;
			    param[param_count + 1] = NULL;
		        }		
		    }
	        }
	        fclose(pFile);
	    }
	    else {
                flag = -10;
	    }

	    printf("error: flag=%d pid %d exit ret=%d status=%d\n", flag, pid, ret, status);
	    sleep(10);
	}	
    }
}

static int ParseArgv(char* param, char* buf, char** arr, int arr_max)
{
    char* p1;	
    char* p = param;
    while(*p == ' ') {
        p++;
    }
    
    int j;
    int n = 0;
    int k = 0;
    
    while (k < arr_max && *p != ']' && *p != '\0') {
	p1 = p;
        j = 0;

	while(*p != ' ' && *p != ']') {
            p++;
	    j++;
        }
        *p++ = '\0';
	j += 1;

        memcpy(&buf[n], p1, j);
	arr[k++] = &buf[n];
	n += j;

        while(*p == ' ') {
            p++;
        }
    }
    return k;
}

void on_signal(int sig)
{
    switch (sig)
    {
	case SIGKILL:
	case SIGINT:
	case SIGTERM:
        {
            kill(g_child, 15);
	    sleep(3);
            exit(0); 
	}
	break;

	default:
	    break;
    }
}

void SetupSign()
{
    struct sigaction sigact;
    memset(&sigact, 0, sizeof(struct sigaction));
    sigact.sa_handler = on_signal;
    sigemptyset(&sigact.sa_mask);

    signal(SIGPIPE, SIG_IGN);
    sigaction(SIGINT, &sigact, NULL);
    sigaction(SIGTERM, &sigact, NULL);
    sigaction(SIGCHLD, &sigact, NULL);
}


//The first parameter is the program name
//The second parameter is divided by '[   ]'
//for example watchapp ls '[ls -al]'


int main(int argc, char* argv[])
{
    if (argc == 3) {
	char* pgname = argv[1];
	char* param = argv[2];
        
	if (param[0] != '[') {
            printf("Parameter missing '['\n");		
            return -2;
	}
        
	int n = strlen(param);
        if (param[n -1] != ']') {
            printf("Parameter missing ']'\n");		
            return -3;		
	}

        char dir[512];
        WDGetCurDir(dir, sizeof(dir));
       
	char exe[256];
	snprintf(exe, sizeof(exe), "%s/%s", dir, pgname);

	char buf[4096];
	char* out_param[100];
	memset(out_param, 0, sizeof(char*) * 100);
        
	int out_param_count = ParseArgv(param + 1, buf, out_param, 100);

#if 0
        FILE* pf = fopen("./err.log", "w");
        printf("%s  %s\n", exe, pgname);

        fwrite(exe, 1, strlen(exe), pf);  
	int i = 0;	
        while (i < 100 && out[i] != 0) {
            printf(" %s\n", out[i]);

	    fwrite(out[i], 1, strlen(out[i]), pf);
	    i++;
        }
        fclose(pf);	
#endif    
	SetupSign();

    	Proc(exe, pgname, out_param, out_param_count);
	return 0;
    }

    printf("Parameter error\n");    
    return -1;
}



