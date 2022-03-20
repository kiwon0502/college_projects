#include <iostream>
#include <cstring>
#include <cstdlib>
using namespace std;

typedef struct {
    int time;
    int pid = -1;
    char code_name[20];
} Instruction;

typedef struct {
    int inst_num;
    int index = 0;
    int** set;
} Code;

int main(int argc, char* argv[]) {
    // scheduling functions
    const char* fcfs = "fcfs";                                      // 1
    const char* rr = "rr";                                          // 2
    const char* sjf_sim = "sjf-simple";                             // 3
    const char* sjf_exp = "sjf-exponential";                        // 4
    // paging algorithms
    const char* fifo = "fifo";                                      // 1
    const char* lru = "lru";                                        // 2
    const char* lru_sam = "lru-sampled";                            // 3
    const char* lfu = "lfu";                                        // 4
    const char* mfu = "mfu";                                        // 5
    const char* optimal = "optimal";                                // 6
    // directory
    const char* dir_default = "/home/giwon/Desktop/OS_hw/A3/";
    char* input_default;
    strcpy(input_default, dir_default);
    strcat(input_default, "input");

    // values for execution options
    char* sched = new char[20];
    char* page = new char[20];
    char* dir = new char[100];
    int sc, pg, di;
    int len;

    // values for input file
    int totalEventNum, vmemSize, pmemSize, pageSize;
    Instruction* inst;
    Code* code;
    int code_num;

    // input execution options
    switch(argc) {
        case 1:
            strcpy(sched, fcfs);
            strcpy(page, fifo);
            strcpy(dir, dir_default);
            break;
        case 2:
            len = strlen(argv[1]);
            switch(argv[1][1]) {
                case 's':
                    strncpy(sched, argv[1]+7, len-6);
                    break;
                case 'p':
                    strncpy(page, argv[1]+6, len-5);
                    break;
                case 'd':
                    strncpy(dir, argv[1]+5, len-4);
                    break;
                default:
                    cout<<"Wrong execution options"<<endl;
                    return 0;
            }
            break;
        case 3:
            len = strlen(argv[1]);
            switch(argv[1][1]) {
                case 's':
                    strncpy(sched, argv[1]+7, len-6);
                    break;
                case 'p':
                    strncpy(page, argv[1]+6, len-5);
                    break;
                case 'd':
                    strncpy(dir, argv[1]+5, len-4);
                    break;
                default:
                    cout<<"Wrong execution options"<<endl;
                    return 0;
            }
            len = strlen(argv[2]);
            switch(argv[2][1]) {
                case 's':
                    strncpy(sched, argv[2]+7, len-6);
                    break;
                case 'p':
                    strncpy(page, argv[2]+6, len-5);
                    break;
                case 'd':
                    strncpy(dir, argv[2]+5, len-4);
                    break;
                default:
                    cout<<"Wrong execution options"<<endl;
                    return 0;
            }
            break;
        case 4:
            len = strlen(argv[1]);
            switch(argv[1][1]) {
                case 's':
                    strncpy(sched, argv[1]+7, len-6);
                    break;
                case 'p':
                    strncpy(page, argv[1]+6, len-5);
                    break;
                case 'd':
                    strncpy(dir, argv[1]+5, len-4);
                    break;
                default:
                    cout<<"Wrong execution options"<<endl;
                    return 0;
            }
            len = strlen(argv[2]);
            switch(argv[2][1]) {
                case 's':
                    strncpy(sched, argv[2]+7, len-6);
                    break;
                case 'p':
                    strncpy(page, argv[2]+6, len-5);
                    break;
                case 'd':
                    strncpy(dir, argv[2]+5, len-4);
                    break;
                default:
                    cout<<"Wrong execution options"<<endl;
                    return 0;
            }
            len = strlen(argv[3]);
            switch(argv[3][1]) {
                case 's':
                    strncpy(sched, argv[3]+7, len-6);
                    break;
                case 'p':
                    strncpy(page, argv[3]+6, len-5);
                    break;
                case 'd':
                    strncpy(dir, argv[3]+5, len-4);
                    break;
                default:
                    cout<<"Wrong execution options"<<endl;
                    return 0;
            }
            break;
        default:
            cout<<"Wrong execution options"<<endl;
            return 0;
    }

    if (!strcmp(sched, fcfs)) sc = 1;
    else if (!strcmp(sched, rr)) sc = 2;
    else if (!strcmp(sched, sjf_sim)) sc = 3;
    else if (!strcmp(sched, sjf_exp)) sc = 4;

    if (!strcmp(page, fifo)) pg = 1;
    else if (!strcmp(page, lru)) pg = 2;
    else if (!strcmp(page, lru_sam)) pg = 3;
    else if (!strcmp(page, lfu)) pg = 4;
    else if (!strcmp(page, mfu)) pg = 5;
    else if (!strcmp(page, optimal)) pg = 6;

    FILE* in = fopen(dir, "r");
    if (in == NULL) {
        cout<<"INPUT is not opened"<<endl;
    }
    else {
        fscanf(in, "%d\t%d\t%d\t%d\n", &totalEventNum, &vmemSize, &pmemSize, &pageSize);
        cout<<totalEventNum<<" "<<vmemSize<<" "<<pmemSize<<" "<<pageSize<<endl;
        //
        inst = new Instruction[totalEventNum];
        for(int i=0; i<totalEventNum; i++) {
            fscanf(in, "%d\t%s", &inst[i].time, inst[i].code_name);
            if(!strcmp(inst[i].code_name, "INPUT")) {
                fscanf(in, "\t%d\n", &inst[i].pid);
            }
            else {
                fscanf(in, "\n");
            }
        }
    }
    fclose(in);

    for (int i=0; i<totalEventNum; i++) {
        if (inst[i].pid == -1) code_num++;
    }
    
    code = new Code[code_num];
    for(int i=0; i<code_num; i++) {
        FILE* fid = fopen(dir, "r");

        if (fid == NULL) {
            cout<<"INPUT is not opened"<<endl;
        }
        else {
            fscanf(fid, "%d\n", &code[i].inst_num);
            code[i].set = new int*[code[i].inst_num];
            for(int j=0; j<code[i].inst_num; j++) {
                (code[i].set)[j] = new int[2];
            }
            for(int j=0; j<code[i].inst_num; j++) {
                fscanf(fid, "%d\t%d", code[i].set[0], code[i].set[1]);
            }
        }
        fclose(fid);
    }

    return 0;
}