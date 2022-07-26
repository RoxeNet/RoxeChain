#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>
#include <stdlib.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>


typedef struct TChar
{
    int len;
    char buf[0];
} Tchar;

typedef struct TAddr
{
    char host[96];
    int port;
} TAddr;

typedef struct TArrAddr
{
    int count;
    TAddr arr[0];
} TArrAddr;

static char g_producer[64];
static int g_isproducer = 0;
static int g_ismainnet = 0;

static char g_main_url[256];
static char g_test_url[256];
char* g_producer_url = NULL;

char* g_home = NULL;


int WDCopyFile(char* file, char* bakfile)
{
    FILE* pFile = fopen(file, "rb");
    if (pFile == NULL) {
        printf("error read %s line:%d\n", file, __LINE__);
        return -1;	
    }

    FILE* pBakFile = fopen(bakfile, "wb");
    if (pBakFile == NULL) {
	fclose(pFile);    
        printf("error write %s line:%d\n", bakfile, __LINE__);
        return -2;
    }

    char buf[4096];
    int n = 0;
    while (!feof(pFile)) {
       n = fread(buf, 1, sizeof(buf), pFile);
       if (n > 0)
           fwrite(buf, 1, n, pBakFile);
       else
	   break;    
    }

    fclose(pFile);
    fclose(pBakFile);
    return 0;
}

int WDExec(const char* cmd, Tchar** out_line, int line_num)
{
    FILE* pFile = popen(cmd, "r");
    if (!pFile) {
	printf("error exec %s line:%d\n", cmd, __LINE__);    
        return -1;
    }
    char line[1024];
    int i = 0;
    int len;
    memset(line, 0, sizeof(line));

    while (i < line_num && fgets(line, sizeof(line), pFile) != NULL) {
       	len = strlen(line);
	len --;    

	if (len > 0) {
           // printf("%s\n", line);
            
	    line[len] = '\0';
            if (out_line[i]->len > len)	
	        strcpy(out_line[i]->buf, line);
	    else
	        return -100;
	}
        else {
            return -101;
	}	

	i++;
        memset(line, 0, sizeof(line));
    }

    pclose(pFile);
    return 0;
}

int RunApp(const char* pgname, char** param)
{
    pid_t pid = fork();
    if (pid < 0) {
        printf("fork error=%s\n", strerror(errno));
        return -1;
    }

    if (pid == 0) {
	setsid();   
        umask(0);
       
#if 0	
        FILE* pf = fopen("./runa.log", "w");	
     	fwrite (pgname, 1, strlen(pgname), pf);
	int i = 0;
	while(param[i] != NULL) {
           fwrite(param[i], 1, strlen(param[i]), pf);
           i++;
	}
        fclose(pf);	
#endif
	execvp(pgname, param);
    }

    return 0;
}

int WDFileExists(const char* filename)
{
    if (access(filename, 0) != 0) {
        return -1;
    }
    return 0;
}

int GetKey(char* pub, char* priv)
{
    Tchar* out_line[2];

    out_line[0] = (Tchar*)malloc(256);
    out_line[0]->len = 256;
    out_line[1] = (Tchar*)malloc(256);
    out_line[1]->len = 256;

    int line_num = 2;

    #define DEF_CLEAN()\
        free(out_line[0]);\
        free(out_line[1])

    if (0 != WDExec("./clroxe create key --to-console", out_line, line_num)) {
	DEF_CLEAN();
	printf("WDExec error\n");
	return -1;
    }
    
    const char* p1 = "Private key:";
    char* pt = strstr(out_line[0]->buf, p1);
    if (pt == NULL) {
	DEF_CLEAN();    
	printf("parse %s error line:%d\n", p1, __LINE__);
        return -2;
    }
   
    int len = strlen(p1);
    while (pt[len] == ' ') {
        len++;
    }

    strcpy(priv, &pt[len]);

    const char* p2 = "Public key:";
    pt = strstr(out_line[1]->buf, p2);
    if (pt == NULL) {
	DEF_CLEAN();    
	printf("parse %s error line:%d\n", p2, __LINE__);
        return -3;
    }

    len = strlen(p2);
    while (pt[len] == ' ') {
        len++;
    }

    strcpy(pub, &pt[len]);

    DEF_CLEAN();
    return 0;
}


int GetWallet(char* wallet, char* key)
{
    int ok = 0;
    char* cmd = "./clroxe wallet create --to-console 2>&1";

    FILE* pFile = popen(cmd, "r");
    if (!pFile) {
	printf("error exec %s line:%d\n", cmd, __LINE__);    
        return -1;
    }
    char line[1024];
    strcpy(wallet, "default");

    char fullname[128];
    sprintf(fullname, "Creating wallet: %s", wallet);
    int flag = 0;

    while (fgets(line, sizeof(line), pFile) != NULL) {
       	if (strstr(line, "Wallet already exists")) {
            pclose(pFile);
            return -10;
	}
	if (flag == 0) {
            if (strstr(line, fullname))
	        flag =1;
	}
	if (flag == 1 && line[0] == '"') {
            int len = strlen(line);
            len -= 3; 
	    memcpy(key, &line[1], len);
	    key[len] = '\0';
	    ok = 1;
	    break;   
	}
    }
    
    pclose(pFile);
    return ok == 1 ? 0 : -4;
}

int WDUnlockWallet(char* wallet, char* wallet_pass)
{
    int ret = -1;
    char cmd[1024];
    snprintf(cmd, sizeof(cmd), "./clroxe wallet unlock -n %s --password %s 2>&1", wallet, wallet_pass);

    FILE* pFile = popen(cmd, "r");
    if (!pFile) {
        printf("error exec %s line:%d\n", cmd, __LINE__);
        return ret;
    }
  
    char flag[128];
    snprintf(flag, sizeof(flag), "Unlocked: %s", wallet);

    char line[1024];
    while (fgets(line, sizeof(line), pFile) != NULL) {
        if (strstr(line, flag) == line) {
            ret = 0;
            break;
        }

        if (strstr(line, "Already unlocked")) {
            ret = 0;
            break;
        }
    }

    fclose(pFile);
    return ret;
}


int WDImportPriv(char* wallet, char* priv)
{
    int ret = -1;
    char cmd[1024];
    snprintf(cmd, sizeof(cmd), "./clroxe wallet import -n %s --private-key %s 2>&1", wallet, priv);

    FILE* pFile = popen(cmd, "r");
    if (!pFile) {
        printf("error exec %s line:%d\n", cmd, __LINE__);
        return ret;
    }
  
    char line[1024]; 
    while (fgets(line, sizeof(line), pFile) != NULL) {
        if (strstr(line, "Key already exists")) {
	   // printf("%s\n", line);
            ret = 0;
	    break;
        }
	 
	if (strstr(line, "Error")) {
            printf("%s", line);
	    break; 
	}
        
	if (strstr(line, "imported private key for:")) {
            ret = 0;
	    break;
	}
    }

    fclose(pFile);
    return ret;
}

int WDRegProducer(char* url, char* producer, char* pub)
{
    int ret = -1;
    char cmd[1024];
    snprintf(cmd, sizeof(cmd), "./clroxe -u %s system regproducer %s %s -p %s@active 2>&1", url, producer, pub, producer);

    FILE* pFile = popen(cmd, "r");
    if (!pFile) {
        printf("error exec %s line:%d\n", cmd, __LINE__);
        return ret;
    }

    char line[1024];
    while (fgets(line, sizeof(line), pFile) != NULL) {
        if (strstr(line, "executed transaction:")) {
	    ret = 0;
	    break;
        }
	printf("%s", line);
    }
    fclose(pFile);
    if (ret != 0) {
       	printf("%s\n", cmd);    
    }
    return ret;
}

int WDUnRegProducer(char* url, char* producer)
{
    int ret = -1;
    char cmd[1024];
    snprintf(cmd, sizeof(cmd), "./clroxe -u %s system unregprod %s -p %s  2>&1", url, producer, producer);
    printf("%s\n", cmd);

    FILE* pFile = popen(cmd, "r");
    if (!pFile) {
        printf("error exec %s line:%d\n", cmd, __LINE__);
        return ret;
    }

    char line[1024];
    while (fgets(line, sizeof(line), pFile) != NULL) {
        if (strstr(line, "executed transaction:")) {
            ret = 0;
            break;
        }
        printf("%s", line);
    }
    fclose(pFile);
    return ret;
}

int WDCheckProducer(char* url, char* producer, int showcmd)
{
    int ret = -1;
    char cmd[1024];
    snprintf(cmd, sizeof(cmd), "./clroxe -u %s system listproducers 2>&1", url);
    if (showcmd == 1)
        printf("%s\n", cmd);	    

    FILE* pFile = popen(cmd, "r");
    if (!pFile) {
        printf("error exec %s line:%d\n", cmd, __LINE__);
        return ret;
    }

    int n = 0;
    char line[1024];
    while (fgets(line, sizeof(line), pFile) != NULL) {
        if (strstr(line, "Producer") == line) {
	    n = 1;
	    continue;
        }
	if (n == 1) {
            if (line == strstr(line, producer)) {
               ret = 0;
	       break;
	    }	    
        }
    }
    fclose(pFile);
    if (ret != 0 && showcmd == 0) {
        printf("%s\n", cmd);
    }
    return ret;
}

int WDStrExists(char* line, char** bufs, int* lens, int bufs_len)
{
    for (int i = 0; i < bufs_len; i++) {	
        if (0 == strncmp(line, bufs[i], lens[i]))
            return 1; 	    
    }
    return 0;
}

int WDCombineFile(const char* tmpfile, const char* def_conf, char* key, const char* file)
{
    FILE* pTmpfile = fopen(tmpfile, "rb");
    if (pTmpfile == NULL) {
        printf("not found %s line:%d\n", tmpfile, __LINE__);
	return -1;
    }   

    FILE* pDefconf = fopen(def_conf, "rb");
    if (pDefconf == NULL) {
	fclose(pTmpfile);    
        printf("not found %s line:%d\n", def_conf, __LINE__);
        return -2;
    }

    FILE* pFile = fopen(file, "wb");
    if (pFile == NULL) {
        fclose(pTmpfile);
        fclose(pDefconf);
        printf("write file error %s line:%d\n", file, __LINE__);
        return -3;
    }
    
    #define DEF_COMB_CLEAN()\
        fclose(pTmpfile);\
        fclose(pDefconf);\
        fclose(pFile)

    //----------
    const int K = 100;
    char* bufs[K];
    int lens[K];
    int bufs_len = 0;
    memset(bufs, 0, sizeof(bufs));
    
    int i = 0;
    int len;    
    char line[1024];
    while (NULL != fgets(line, sizeof(line), pDefconf)) {
        if (line[0] == '#')
            continue;
        if (strstr(line, "is-mainnet"))
	    continue;	
        if (strstr(line, "is-producer")) 
            continue;
        
	if (strstr(line, "test_url"))
            continue;
        if (strstr(line, "main_url"))
            continue;

        if (line == strstr(line, "main-p2p-peer-address")) {
            if (g_ismainnet == 1){
		len = strlen(line) - 5;
                fwrite(&line[5], 1, len, pFile);
            }
	    continue;
	}

        if (line == strstr(line, "test-p2p-peer-address")) {
            if (g_ismainnet == 0){ 
		len = strlen(line) - 5;
                fwrite(&line[5], 1, len, pFile);
	    }
	    continue;
	}

	len = strlen(line);
        fwrite(line, 1, len, pFile);

	char* p = malloc(128);
	memcpy(p, line, 127);

        char* p1 = strstr(p, " ");
	if (!p1) {
            p1 = strstr(p, "=");
	}
        
	if (p1 != NULL && i < K) {
	    *p1 = '\0';	
            lens[i] = p1 - p;		
            bufs[i] = p;
	    i++;
	}
    }
    bufs_len = i;

    //------------
    char key_buf[2048];
    int size = sprintf(key_buf, "%s\n", key);
    fwrite(key_buf, 1, size, pFile);

    int n;
   
    while (NULL != fgets(line, sizeof(line), pTmpfile)) {
        if (line[0] == '#')
            continue; 	       
        
        if (0 == WDStrExists(line, bufs, lens, bufs_len)) {
            n = strlen(line);
            fwrite(line, 1, n, pFile);
        }
    }
    
    for (int i = 0; i < bufs_len; i++) {
        free(bufs[i]);
    }

    DEF_COMB_CLEAN(); 

    return 0;
}

int WDReadUserInfo(const char* user_file, char* account)
{
    FILE* pFile = fopen(user_file, "rb");
    if (pFile == NULL) {
        printf("read file error %s line:%d\n", user_file, __LINE__);
        return -1;
    }
    char buf[1024];
    if (fgets(buf, sizeof(buf), pFile) != NULL) {
        char* p = strstr(buf, "account:"); 
        if (p != buf) {
            fclose(pFile);		
            return -2;
	}
        p += 8;
        int l = strlen(p);
        p[l - 1] = '\0';
	
	strncpy(account, p, 64);
	fclose(pFile);
	return 0;
    }
    fclose(pFile);
    return -3;
}

int WDCreateUserInfo(char* producer,const char* userfile, const char* wallet_file, const char* user_file)
{
    FILE* pFile = fopen(user_file, "wb");
    if (pFile == NULL) {
        printf("write file error %s line:%d\n", user_file, __LINE__);
        return -1;
    }

    FILE* pUserFile = fopen(userfile, "rb");
    if (pUserFile == NULL) {
        fclose(pFile);
        printf("not found %s line:%d\n", userfile, __LINE__);
        return -2;
    }

    FILE* pWalletFile = fopen(wallet_file, "rb");
    if (pWalletFile == NULL) {
        fclose(pFile);
	fclose(pUserFile);
        printf("not found %s line:%d\n", wallet_file, __LINE__);
        return -3;
    }

    char name[128];
    int len = sprintf(name, "account:%s\n", producer);
    fwrite(name, 1, len, pFile);

    char buf[4096];
    len = fread(buf, 1, sizeof(buf), pUserFile);
    fwrite(buf, 1, len, pFile);

    len = fread(buf, 1, sizeof(buf), pWalletFile);
    fwrite(buf, 1, len, pFile);

    fclose(pFile);
    fclose(pUserFile);
    fclose(pWalletFile);
    
    return 0;
}

int WDSaveKey(const char* filename, char* priv,  char* pub)
{
    FILE* pFile = fopen(filename, "wb");
    if (pFile == NULL)
       return -1;

    char buf[256];
    int n = snprintf(buf, sizeof(buf), "priv:%s\n", priv);
    fwrite(buf, 1, n, pFile);  

    n = snprintf(buf, sizeof(buf), "pub:%s\n", pub);
    fwrite(buf, 1, n, pFile);

    fclose(pFile);   

    return 0; 
}

int WDReadKey(const char* filename, char* priv,  char* pub)
{
    if (WDFileExists(filename) != 0)
        return -1;

    FILE* pFile = fopen(filename, "rb");
    if (pFile == NULL)
        return -2;

    int m;
    int k = 0;
    char* p;
    char buf[256];

    while (!feof(pFile)) {
        p = fgets(buf, sizeof(buf), pFile);
        if (p) {
	    p = strstr( buf, "priv:");     
            if (p) {
	        k++;	   
                p += 5;
                m = strlen(p);
                p[m - 1] = '\0';

	        strcpy(priv, p);
	        continue;
	    } 

            p = strstr( buf, "pub:");
	    if (p) {
	        k++;
                p += 4;
                m = strlen(p);
                p[m - 1] = '\0';

                strcpy(pub, p);
	        continue;
            }
        }
    }

    fclose(pFile);
    int ret = k > 1 ? 0: -3;

    return ret;
}


int WDReadWallet(const char* filename, char* wallet,  char* key)
{
    if (WDFileExists(filename) != 0)
        return -1;

    FILE* pFile = fopen(filename, "rb");
    if (pFile == NULL)
        return -2;

    int m = 0;
    int k = 0;
    char* p = NULL;
    char buf[1024];

    while (fgets(buf, sizeof(buf), pFile) != NULL) {
	if (k == 2)
	    break;

        p = strstr(buf, "wallet:");
	if (p) {
	    k++;	
            p += 7;
            m = strlen(p);
            p[m - 1] = '\0';
            strcpy(wallet, p);
	    continue;
	}

	p = strstr(buf, "key:");
        if (p) {
            k++;
            p += 4;
            m = strlen(p);
            p[m - 1] = '\0';
            strcpy(key, p);
            continue;
        }
    }
   
    if (k == 2)
	return 0;
    return -3;    
}

int WDSaveWallet(const char* filename, char* wallet,  char* key)
{
    FILE* pFile = fopen(filename, "w");
    if (pFile == NULL)
        return -2;

    char buf[1024];
    int n = sprintf(buf, "wallet:%s\n", wallet);
    fwrite(buf, 1, n, pFile);

    n = sprintf(buf, "key:%s\n", key);
    fwrite(buf, 1, n, pFile);
    fclose(pFile);
    return 0;
}


int WDBuildGeneFile(int type, const char* filename)
{

   const char* testbuf ="{\n\
   \"initial_timestamp\": \"2020-05-22T08:11:08.888\",\n\
   \"initial_key\": \"ROXE69GFtEZywjksKAv6oEJ2RfSPo5ShvJKa4v2nQZzaeDoUAr8Xn4\",\n\
   \"initial_configuration\": {\n \
   \"max_block_net_usage\": 1048576,\n \
   \"target_block_net_usage_pct\": 1000,\n\
    \"max_transaction_net_usage\": 524288,\n\
    \"base_per_transaction_net_usage\": 12,\n\
    \"net_usage_leeway\": 500,\n\
    \"context_free_discount_net_usage_num\": 20,\n\
    \"context_free_discount_net_usage_den\": 100,\n\
    \"max_block_cpu_usage\": 200000,\n\
    \"target_block_cpu_usage_pct\": 1000,\n\
    \"max_transaction_cpu_usage\": 150000,\n\
    \"min_transaction_cpu_usage\": 100,\n\
    \"max_transaction_lifetime\": 3600,\n\
    \"deferred_trx_expiration_window\": 600,\n\
    \"max_transaction_delay\": 3888000,\n\
    \"max_inline_action_size\": 4096,\n\
    \"max_inline_action_depth\": 4,\n\
    \"max_authority_depth\": 6\n\
   }\n\
   }";

   const char* buf ="{\n\
    \"initial_timestamp\": \"2020-05-22T08:11:08.888\",\n\
    \"initial_key\": \"ROXE8MBBU6zdAFHXFb8235Qg5u3LSJvg2VzbjfqEpXTEc5asGe6XZH\",\n\
    \"initial_configuration\": {\n\
    \"max_block_net_usage\": 1048576,\n\
    \"target_block_net_usage_pct\": 1000,\n\
    \"max_transaction_net_usage\": 524288,\n\
    \"base_per_transaction_net_usage\": 12,\n\
    \"net_usage_leeway\": 500,\n\
    \"context_free_discount_net_usage_num\": 20,\n\
    \"context_free_discount_net_usage_den\": 100,\n\
    \"max_block_cpu_usage\": 200000,\n\
    \"target_block_cpu_usage_pct\": 1000,\n\
    \"max_transaction_cpu_usage\": 150000,\n\
    \"min_transaction_cpu_usage\": 100,\n\
    \"max_transaction_lifetime\": 3600,\n\
    \"deferred_trx_expiration_window\": 600,\n\
    \"max_transaction_delay\": 3888000,\n\
    \"max_inline_action_size\": 4096,\n\
    \"max_inline_action_depth\": 4,\n\
    \"max_authority_depth\": 6\n\
   }\n\
   }";

    const char* p;
    int len;

    if (type == 0) {
        p = testbuf;
    }
    else {
        p = buf;
    }
    len = strlen(p);
    
    FILE* pFile = fopen(filename, "wb");
    if (pFile == NULL) {
        printf("error write %s line:%d\n", filename, __LINE__);
	return -1;
    }
    fwrite(p, 1, len, pFile);

    fclose(pFile);

    printf("build (%s) genesis.json ok\n", (type == 0? "testnet" : "mainnet"));
    return 0;
}

int Name2Addr(const char*name, in_addr_t* pAddr)
{
    struct hostent * hp;
    if (isdigit((int)(*name)))
        *pAddr = inet_addr(name);
    else
    {
       hp = gethostbyname(name);
       if (hp == NULL)
          return -1;
       memcpy((char*)pAddr, hp->h_addr_list[0], hp->h_length);
    }
    return 0;
}

int SetSendTimeout(int sockFd, int timeout_s)
{
    struct timeval loSndTimeo = {timeout_s, 0};
    if (setsockopt(sockFd, SOL_SOCKET, SO_SNDTIMEO, (char*)&loSndTimeo, sizeof(loSndTimeo)) == -1)
        return -1;
    return 0;
}

int Connect(const char* host, int port)
{
    int sockFd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockFd < 1) {
        printf("socket err=%s line:%d\n", strerror(errno), __LINE__);
	return -1;    
    }
    
    if (0 != SetSendTimeout(sockFd, 10)) {
	printf("SetSendTimeout err=%s line:%d\n", strerror(errno), __LINE__);    
        return -1;
    }

    struct sockaddr_in svr_addr;
    if (Name2Addr(host, &svr_addr.sin_addr.s_addr) == -1)
    {
	close(sockFd);    
        printf("Name2Addr err=%s %s:%d line:%d\n", strerror(errno), host, port, __LINE__);
        return -2;
    }
    svr_addr.sin_family = AF_INET;
    svr_addr.sin_port = htons(port);

    int liRet = connect(sockFd, (struct sockaddr*)&svr_addr, sizeof(svr_addr));
    if (liRet == -1)
    {
        close(sockFd);	    
        printf("connect err=%s %s:%d line:%d\n", strerror(errno), host, port, __LINE__);
        return -3;
    }
    close(sockFd);
    return 0;
}

int IsUsedPort(int port)
{
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    inet_pton(AF_INET, "0.0.0.0", &addr.sin_addr);
     
    if (bind(fd, (struct sockaddr*)&addr, sizeof(struct sockaddr_in)) < 0) {
	close(fd);    
	return 1;
    }
    close(fd);
    return 0;
}

int ParseAddr(char* p, const char* pl, TAddr* pAddr)
{
    int len = strlen(pl);
    char* p1 = p + len;

    while (*p1 == ' ' || *p1 == '=') {
        p1++;
    }
    
    p = p1;

    while (*p1 != '\n') {
       	if (*p1 == ' ' || *p1 == ':')
            break; 
        p1++;
    }

    if (p != p1) {
        *p1 = '\0';
        strncpy(pAddr->host, p, 96);
    }
    else {
        return -1;
    }

    p = p1 + 1;
    while (*p == ' '){
	p++;    
    }

    pAddr->port = atoi(p);

    return 0;
}

int WDCheckNet(TArrAddr** plisten, TArrAddr** peer)
{
    int n = (*plisten)->count;
    TAddr* pAddr = NULL;
    for (int i = 0; i < n; i++) {
	 pAddr = &(*plisten)->arr[i];    
         if (1 == IsUsedPort(pAddr->port)) {
             printf("\033[1m\033[40;33mport %d isused \033[0m line:%d\n", pAddr->port, __LINE__);
             return -1;		 
	 }
    }

    n = (*peer)->count;
    for (int i = 0; i < n; i++) {
	pAddr = &(*peer)->arr[i];
        if (0 != Connect(pAddr->host, pAddr->port)) {
            printf("\033[1m\033[40;33merror connect %s:%d\n\033[0m", pAddr->host, pAddr->port);
	    return -2;	
        }
    } 
    return 0;
}

int WDParseLine(char* line, const char* flag, char* out, int out_size)
{
     char* p = strstr(line, flag);
     if (p != line) {
         return -1;
     }

     p += strlen(flag);
     while (*p == ' ' || *p == '=') {
         p++;
     }
     int i = strlen(p);
     if (i > 1) {
         *(p + i - 1) = '\0';
         strncpy(out, p, out_size);
	 return 0;
     }

     return -2;
}

int WDParseDefconf(const char* filename, TArrAddr** plisten, TArrAddr** test_peer, TArrAddr** main_peer)
{
    FILE* pFile = fopen(filename, "rb");
    if (!pFile) {
        printf("error open %s line:%d\n", filename, __LINE__);
        return -1;
    }

    int listen_max = 32;
    int listen_num = 0;
    *plisten = (TArrAddr*)malloc(sizeof(TAddr) * listen_max + sizeof(int));
    if (plisten == NULL) {
	fclose(pFile);    
        printf("malloc error line:%d\n", __LINE__);
	return -2;
    } 

    int peer_max = 128;
    int test_peer_num = 0;
    int main_peer_num = 0;

    *test_peer = (TArrAddr*)malloc(sizeof(TAddr) * peer_max + sizeof(int));
    if (test_peer == NULL) {
	fclose(pFile);    
	free(plisten);    
        printf("malloc error line:%d\n", __LINE__);
        return -3;
    } 

    *main_peer = (TArrAddr*)malloc(sizeof(TAddr) * peer_max + sizeof(int));
    if (main_peer == NULL) {
        fclose(pFile);
        free(plisten);
	free(*test_peer);
        printf("malloc error line:%d\n", __LINE__);
        return -3;
    }


    char line[1024];
    char* p;
    memset(line, 0, sizeof(line));

    const char* svr1 = "http-server-address";
    const char* svr2 = "p2p-listen-endpoint";
    const char* pl; 
    const char* test_peerfmt = "test-p2p-peer-address";
    const char* main_peerfmt = "main-p2p-peer-address";

    char out[128];

    while (fgets(line, sizeof(line), pFile) != NULL) {
        pl = svr1;
	p = strstr(line, pl);

	if (p == NULL) {
            pl = svr2;		
            p = strstr(line, pl);
	}

        if (p == line) {
	    if (listen_num >= listen_max) {
	        fclose(pFile);	   
                printf(" listen num over line:%d\n", __LINE__);
	        return -1;
	    }
	    TAddr* pAddr = &(*plisten)->arr[listen_num];
            if (0 != ParseAddr(p, pl, pAddr)) {
                printf(" error %s line:%d\n", line, __LINE__);
	        return -2; 	
	    }
	    else {
	        listen_num++;
	    }
            continue;
	}

        p = strstr(line, test_peerfmt);
        if (p == line) {
            if (test_peer_num >= listen_max) {
	        fclose(pFile);	    
                printf(" peer num over line:%d\n", __LINE__);
                return -2;
            }
		
            TAddr* pAddr = &(*test_peer)->arr[test_peer_num];
            if (0 != ParseAddr(p, test_peerfmt, pAddr)) {
                printf(" error %s line:%d\n", line, __LINE__);
                return -2;
            }
            else {
		test_peer_num++;
            }
            continue;
	}

	p = strstr(line, main_peerfmt);
        if (p == line) {
            if (main_peer_num >= listen_max) {
                fclose(pFile);
                printf(" peer num over line:%d\n", __LINE__);
                return -2;
            }

            TAddr* pAddr = &(*main_peer)->arr[main_peer_num];
            if (0 != ParseAddr(p, main_peerfmt, pAddr)) {
                printf(" error %s line:%d\n", line, __LINE__);
                return -2;
            }
            else {
                main_peer_num++;
            }
            continue;
        }

	if (0 == WDParseLine(line, "is-mainnet", out, 16)) {
            g_ismainnet = strcmp(out, "true") == 0 ? 1 : 0;
            continue;
        }
       
        if (0 == WDParseLine(line, "is-producer", out, 16)) {
            g_isproducer = strcmp(out, "true") == 0 ? 1 : 0;
            continue;
	}

        if (0 == WDParseLine(line, "test_url", out, 128)) {
            strncpy(g_test_url, out, sizeof(g_test_url)); 
	    continue;
        }

	if (0 == WDParseLine(line, "main_url", out, 128)) {
            strncpy(g_main_url, out, sizeof(g_main_url));
            continue;
        }


        if (0 == WDParseLine(line, "producer-name", g_producer, 64)) {
            continue;
        }
    }

    fclose(pFile);
    (*plisten)->count = listen_num;
    (*test_peer)->count = test_peer_num;
    (*main_peer)->count = main_peer_num;

    return 0; 
}

void WDFree(TArrAddr* plisten, TArrAddr* test_peer, TArrAddr* main_peer)
{
    free(plisten);
    free(test_peer);
    free(main_peer);
}

int GetPid(char* buf)
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
            if (strstr(buf, name)) {
                ret = GetPid(buf);  
	        break;
	    }
        }
    }
    pclose(fp);
    return ret;
}

int WDExistsProc(const char *name)
{   
    int found = 0;    

    FILE* fp;
    
    char buf[1024];
    char cmd[256];
    sprintf(cmd, "ps -ef | grep \"%s\" | grep -v \"grep\"", name);
    fp = popen(cmd, "r");
  
    if (NULL == fp) {   
        found = -1;
	printf("system errr line:%d\n", __LINE__);
    }
    else
    { 
	char* p1 = NULL;    
	while (fgets(buf, sizeof(buf), fp) != NULL) {
            p1 = strstr(buf, name);
	    --p1;

	    while (p1 != buf) {
               if (*p1 == 'p') {
                   break;
	       }
	       if (*p1 >= '0' && *p1 <= '9') {
		   found = 1;
	           break;	   
	       }
	       --p1;
	    }
	    if (found == 1)
		 break;
        }
    }
    pclose(fp);
    return found;
}


void WDCheckStatus(const char* file)
{
    FILE* pFile = fopen(file, "rb");
    if (!pFile) {
        printf("error open %s line:%d\n", file, __LINE__);
        return;
    }

    fseek(pFile, 0, SEEK_END);
    int pos = ftell(pFile);
    pos -= 256;
    fseek(pFile, pos, 0);

    char buf[2048];
    char* p;

    char out[256];
    int64_t n = 0;
    int len = 0;
    int size = 0;

    char sync1[] = "data syn complete";
    char sync2[] = "data sync ...";
    char* sync = sync2;

    printf("....        \n");
    fflush(stdout);
    
    while(1) {
        if (feof(pFile)) {
            pos = ftell(pFile);           
            pos -= 512;
            fseek(pFile, pos, 0);
            continue;
        }

	memset(buf, 0, sizeof(buf));
	size = fread(buf, 1, sizeof(buf) -1, pFile);

	if (size > 0) {
            p = strstr(buf, "#");
	    if (p) {
	        n = atoll(p+1);    
                len = sprintf(out, "block num: %ld", n);
	    }
            
	    p = strstr(buf, "latency: ");
            if (p) {
	        p += 9;
	        n = atoll(p);	 

		len += sprintf(&out[len], " latency: %ld ms", n);
		sync = n <= (int64_t)1000 ? sync1 : sync2;
	    }
             
	    if (p) {
                printf("\033[1A");
		printf("\033[K");
                printf("\033[1m\033[40;33m%s status: %s\n\033[0m", out, sync);       
		fflush(stdout);
	    }	     
	}
	sleep(1);
    }

    fclose(pFile);
}

int WDParseUrl(char* url, char* host, int* port)
{
    //http://testnet.rocpro.me:18888
    if (url == NULL || url[0] == '\0')
        return -1;
    
    char* p1 = url;

    p1 = strstr(url, "//");
    if (p1) {
        p1 += 2;
    }

    while (p1 && *p1 == ' ') 
        p1++;

    while (p1 && (*p1 != ' ' && *p1 != ':')) {
        *host++ = *p1++; 
    }
    *host = '\0';
    
    while (p1 && (*p1 == ':' || *p1 == ' '))
        p1++;	    

    *port = atoi(p1);
   
    return 0;
}

int WDTestUrl(char* url)
{
    char host[64];
    int port;

    if (0 != WDParseUrl(url, host, &port)) {
        printf("\033[1m\033[40;33murl %s error\n\033[0m", url);
        return -1;
    }

    int ret = Connect(host, port);
    if (ret != 0) {
        printf("\033[1m\033[40;33mconnect %s error\n\033[0m", url);
        return -2;
    }
    return 0;
}


void Usge()
{
    printf("Usage: roxe  [param]\n");
    printf("   ./roxe                    start nodroxe\n");
    printf("   ./roxe  -stop             stop nodroxe\n");
    printf("   ./roxe  -status           view nodroxe data synchronization progress\n");
    printf("   ./roxe  -unsuper          unregister producer\n");    
    printf("   ./roxe  -prod             view producer\n");
}


#define  DEF_START  1

int main(int argc, char* argv[])
{
    if (argc > 1) {
	char* p = argv[1];    
	int ok = 0;
        if (strstr(p, "-stop") == p)
            ok++;
        if (strstr(p, "-status") == p)
	    ok++;	
	if (strstr(p, "-unsuper") == p)
            ok++;
        if (strstr(p, "-prod") == p)
	    ok++;   	

        if (ok == 0) {
            Usge();
	    return 0;
	}	
    }    

    if (argc == 2 && (0 == strcmp(argv[1], "-h") || 0 == strcmp(argv[1], "-help")) ) {
        Usge();
       	return 0;    
    }
    g_home = getenv("HOME");

    char dir[512];
    readlink("/proc/self/exe", dir, sizeof(dir));
    char* p = strrchr(dir, '/');
    if (p == 0 || p == dir) {
        printf("\033[1m\033[40;33mget path error!\033[0m\n");
        return 0;
    }
    *p = '\0';

 
    if (argc == 2 && 0 == strcmp(argv[1], "-status")) {
        printf("\n      ====== View nodroxe synchronize data ======\n");	
        char file[256];
        sprintf(file, "%s/stderr.txt", dir);
        WDCheckStatus(file); 

	return 0;    
    }

    if (argc == 2 && 0 == strcmp(argv[1], "-stop")) {
        int pid = WDExistsProcess("watchapp nodroxe");
        if (pid > 0) {
            printf("Are you sure you want to kill nodroxe? Please enter y or n\ninput: ");
	    char ch = getchar();
	    if (ch == 'y') {
                char cmd[64];
	        sprintf(cmd, "kill %d", pid);
	        system(cmd);
	    }
	}
        else {
            printf("\033[1m\033[40;33mnodroxe is not running\n\n\033[0m");
	}	
	return 0;    
    }
    printf("\n      ====== Configure and start nodroxe ======\n");	


    memset(g_producer, 0 , sizeof(g_producer));

    char dat_path[1024];
    snprintf(dat_path, sizeof(dat_path), "%s/dat", dir);
    if (0 != WDFileExists(dat_path)) {
        if (0 != mkdir(dat_path, 0644)) {
            printf("\033[1m\033[40;33mcreate dir %s error\033[0m\n", dat_path);
	    return 0;
	}
    } 
    
    //-- exists run nodroxe --------0----------

    if (argc == 1) {
        int exists = WDExistsProc("nodroxe");
        if (exists == 1) {
            printf("\033[1m\033[40;33mnodroxe is already running\n\n\033[0m");
            return 0;
        }
    }
   
    //------ 1 ----------
    // read user.txt 
    char g_priv[256];
    char pub[256];
   
    char userfile[1024]; 
    snprintf(userfile, sizeof(userfile), "%s/key.dat", dat_path);

    int ret = WDReadKey(userfile, g_priv, pub);
    if (ret != 0) {
        if (0 != GetKey(pub, g_priv)) {
	    printf("\033[1m\033[40;33mGetKey error\033[0m\n");    
            return 0;
        }
        WDSaveKey(userfile, g_priv, pub);
    }
    else {
        printf("read public key ok\n");
    }

    //------- 2 -------
    char key[1024];
    snprintf(key, sizeof(key), "signature-provider=%s=KEY:%s\n", pub, g_priv);
   
    char def_conf[1024];
    snprintf(def_conf, sizeof(def_conf), "%s/def-conf.ini", dir);        
    ret = WDFileExists(def_conf);

    if (ret != 0) {
label_2:
        //wait def-conf.ini
	printf("\033[1m\033[40;33mProvide the public key \"%s\" to the administrator\033[0m\n", pub);
        printf("Wait for The administrator gives \033[1m\033[40;33m\"def-conf.ini\" \033[0mto the \"%s\"\n", dir);

	int j = 0;
	printf(" =");
	do {
	    j++; 	
            ret = WDFileExists(def_conf);
            sleep(1);
	    if (j < 20) {
	        printf(" =");
	        fflush(stdout);
	    }
	    else {
                printf("\n");
                j = 0;
                printf("\033[1A");
                printf("\033[K");
		printf(" =");
	    }
	} while (ret != 0);
	printf("\n");
    }

    // ------  3 -------------- 
    //check net
    TArrAddr* plisten;
    TArrAddr* peer = NULL;
    TArrAddr* test_peer = NULL;
    TArrAddr* main_peer = NULL;

    if (0 != WDParseDefconf(def_conf, &plisten, &test_peer, &main_peer)) {
        printf("\033[1m\033[40;33mParseDefconf error\033[0m\n");
	return 0;    
    }
   
    if (g_isproducer == 1 &&  g_producer[0] == '\0') {
        goto label_2;
    }
    peer = g_ismainnet == 1 ? main_peer : test_peer;

    //--  check url-----------------
    if (g_ismainnet == 1)
        g_producer_url = g_main_url;
    else
        g_producer_url = g_test_url;

    ret = WDTestUrl(g_producer_url);
    if (ret != 0)
        return 0;
    printf("\ncheck peer url ok\n");

    //-------- producer-----
    if (argc == 2 && strstr(argv[1], "-prod")) {
        ret = WDCheckProducer(g_producer_url, g_producer, 1);
        if (ret != 0) {
            printf("\033[1m\033[40;33mProducer %s does not exist\n\033[0m", g_producer);
        }
	else {
            printf("\033[1m\033[40;33mProducer %s exist\n\033[0m", g_producer);
	}
        return 0; 	    
    }

   //----------unsuper------- 
    if (argc == 2 && strstr(argv[1], "-unsuper")) {
        char wallet[64];
        char wallet_key[256];
        char wallet_file[1024];
        snprintf(wallet_file, sizeof(wallet_file), "%s/wallet.dat", dat_path);

	ret = WDCheckProducer(g_producer_url, g_producer, 0);
        if (ret != 0) {
            printf("\033[1m\033[40;33mProducer %s does not exist\n\033[0m", g_producer);
	    return 0;
	}

        ret = WDReadWallet(wallet_file, wallet, wallet_key);
        if (ret == 0) {
	    ret = WDUnlockWallet(wallet, wallet_key);
            if (ret == 0) {
                 ret = WDUnRegProducer(g_producer_url, g_producer);
	    }
	}
        if (ret == 0)
	    printf("\033[1m\033[40;33m\nUnRegProducer %s ok\n\033[0m", g_producer);  	
	else
	    printf("\033[1m\033[40;33m\nUnRegProducer %s error\n\033[0m", g_producer);  	
	return 0;    
    }

    //-------4------------------ 
    printf("check net connect ....\n");
    if (0 != WDCheckNet(&plisten, &peer)) {
	WDFree(plisten, test_peer, main_peer);    
        printf("\033[1m\033[40;33mcheck net connect error\033[0m\n");
        return 0;
    }
    WDFree(plisten, test_peer, main_peer);
    printf("check net connect ok\n\n");
   

    //--------- 5 ---------------
    //build genesis.json
    char jsonfile[1024];
    snprintf(jsonfile, sizeof(jsonfile), "%s/genesis.json", dir);
    WDBuildGeneFile(g_ismainnet, jsonfile);

    //---------- 6 --------------
    //build config.ini
    char tmpfile[1024];
    snprintf(tmpfile, sizeof(tmpfile), "%s/config.ini-template", dir);

    char file[1024];
    snprintf(file, sizeof(file), "%s/config.ini", dir);

    if (WDFileExists(tmpfile) != 0) {
        printf("not found %s\n", tmpfile);
        return 0;
    }

    //combine file
    if (0 != WDCombineFile(tmpfile, def_conf, key, file)) {
        printf("\033[1m\033[40;33merror WDCombineFile\033[0m\n");
	return 0;
    }
    printf("build config.ini ok\n");

    //------------ 7 --------------
    // run nodroxe , kroxed 
  
    printf("\nstart nodroxe...\n");
    
    char roxe_param[1024];
    snprintf(roxe_param, sizeof(roxe_param),
    "[nodroxe --data-dir %s/node --genesis-json %s/genesis.json --config-dir %s]", dir, dir, dir);
  
    char* param_1[4] = {"watchapp", "nodroxe", NULL, NULL};  
    param_1[2] = roxe_param;

  //  printf("%s\n", param_1[2]);
    
    char run_buf[256];
    snprintf(run_buf, sizeof(run_buf), "%s/watchapp", dir);
    RunApp(run_buf, param_1);

    int num = 0;
    do {
        int ok = WDExistsProc("nodroxe");
        if (ok == 1) {
            printf("start nodroxe ok\n\n");		
            break;
        }
	sleep(3);

	num++;
	if (num > 10) {
            printf("\033[1m\033[40;33m start nodroxe error \033[0m\n\n"); 
	    return 0;	
	}
    } while(1);


    //--create wallet --------8-------
    ret = 0;
    char g_wallet[64];
    char g_wallet_key[256];
    char wallet_file[1024];
    snprintf(wallet_file, sizeof(wallet_file), "%s/wallet.dat", dat_path);

    ret = WDReadWallet(wallet_file, g_wallet, g_wallet_key);
    if (ret != 0) {
label_WL_1:  
      	ret = GetWallet(g_wallet, g_wallet_key);
	if (ret == 0) {
            ret = WDSaveWallet(wallet_file, g_wallet, g_wallet_key);
	}
	else if (ret == -10) {
            const char* fname = "/roxe-wallet/default.wallet"; 		
            char wall_name[128];
	    sprintf(wall_name, "%s%s", g_home, fname);
	    
	    char wall_name2[128];
	    int sec = time(0); 
	    sprintf(wall_name2, "%s%s-%d", g_home, fname, sec);
	    if (0 != rename(wall_name, wall_name2)) {
                printf("\033[1m\033[40;33mcreate wallet error!\n\033[0m");
		return 0;
	    } 
	    goto label_WL_1;
	}

        if (ret != 0) {
           printf("\033[32mcreate wallet error!\033[0m\n");
           return 0;
        }
    }
    else {
        printf("read wallet ok\n"); 
        ret = WDUnlockWallet(g_wallet, g_wallet_key);
        if (ret != 0) {
            printf("\033[32mcreate wallet error!\033[0m\n"); 
	    return 0;
        }
    }
  
    //--------9--------- 
    char user_file[1024];
    snprintf(user_file, sizeof(user_file), "%s/user.info", dir);

    if (WDFileExists(user_file) != 0) {
        WDCreateUserInfo(g_producer, userfile, wallet_file, user_file);         
    }
    else {
	char account[64];    
        int r = WDReadUserInfo(user_file, account);
        if (r != 0 || strcmp(g_producer, account) != 0) {
            WDCreateUserInfo(g_producer, userfile, wallet_file, user_file);
	}
    }
    printf("\033[1m\n\033[40;33m \"%s\" the file that users need to keep!\033[0m\n", user_file);

    //----import key -----9--------------
    ret = WDImportPriv(g_wallet, g_priv);
    if (ret == 0) {
        printf("\nimport account private key succeeded ok\n");
    }
    else {
        printf("\n\n");
    }

    sleep(6);
    do {
        ret = Connect("0.0.0.0", 18888);
        if (ret != 0) {
	   sleep(5);
	}	   
    } while (ret != 0);
    //printf("connect port %d ok\n", 18888);

    //-----10 ---------
    if (g_isproducer == 1) {
        ret = WDRegProducer(g_producer_url, g_producer, pub); 
        if (ret != 0) {
            printf("\033[31mregistered producer error\033[0m\n\n");
	    return 0;
	}

	do {
	    ret = WDCheckProducer(g_producer_url, g_producer, 2);
	    if (ret != 0)
	        sleep(2);	    
	} while (ret != 0);

	if (ret == 0) {
	    printf("\nsuccessfully registered producer ok\n");
        }
    }

    printf("\n      ====== program execution completed! ======\n\n");
    return 0;
}
