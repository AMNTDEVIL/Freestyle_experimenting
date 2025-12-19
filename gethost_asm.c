#include <stdio.h>
#include <sys/sysinfo.h>
#include<unistd.h>
#include<string.h>
int main() {
    struct sysinfo info;
    char hostname[256];
    if(gethostname(hostname,sizeof(hostname))==0){
        printf("Hostname:%s\n",hostname);
    }
    else{
        perror("failed to fetch hostname");
        return -1;
    }
    if (sysinfo(&info) != 0) {
        perror("sysinfo failed");
        return 1;
    }

    // Apply mem_unit (almost always 1 on modern systems)
    unsigned long unit = info.mem_unit;

unsigned long long total_ram  = (unsigned long long)info.totalram * unit;
    unsigned long long free_ram   = (unsigned long long)info.freeram   * unit;
    unsigned long total_swap = info.totalswap * unit;
    unsigned long free_swap  = info.freeswap  * unit;

    // Convert to GB for nice display
    double total_ram_gb  = total_ram  / (1024.0 * 1024.0 * 1024.0);
    double free_ram_gb   = free_ram   / (1024.0 * 1024.0 * 1024.0);
    double total_swap_gb = total_swap / (1024.0 * 1024.0 * 1024.0);
    double free_swap_gb  = free_swap  / (1024.0 * 1024.0 * 1024.0);

    printf("=== Memory Information ===\n");
    printf("Total RAM         : %.2f GB\n", total_ram_gb);
    printf("Free RAM (MemFree): %.2f GB\n", free_ram_gb);

    // Get MemAvailable (the number that actually matters)
    FILE *fp = fopen("/proc/meminfo", "r");
    unsigned long mem_available_kb = 0;
    if (fp) {
        char line[256];
        while (fgets(line, sizeof(line), fp)) {
            if (sscanf(line, "MemAvailable: %lu kB", &mem_available_kb) == 1)
                break;
        }
        fclose(fp);
    }
    if (mem_available_kb > 0) {
        double avail_gb = mem_available_kb / (1024.0 * 1024.0);
        printf("Available RAM     : %.2f GB\n", avail_gb);
    }

    // Swap information
    printf("\n");
    if (total_swap == 0) {
        printf("Swap memory       : No swap configured\n");
    } else {
        printf("Total Swap        : %.2f GB\n", total_swap_gb);
        printf("Free Swap         : %.2f GB\n", free_swap_gb);
        printf("Used Swap         : %.2f GB\n", (total_swap_gb - free_swap_gb));
    }
    FILE *cpu_fp = fopen("/proc/cpuinfo", "r");
    if (cpu_fp) {
        char line[256];
        printf("\n=== CPU Information ===\n");
       int printed_model = 0, printed_vendor = 0, printed_cores = 0;

while (fgets(line, sizeof(line), cpu_fp)) {
    if (!printed_model && strncmp(line, "model name", 10) == 0) {
        printf("%s", line);
        printed_model = 1;
    }
    else if (!printed_vendor && strncmp(line, "vendor_id", 9) == 0) {
        printf("%s", line);
        printed_vendor = 1;
    }
    else if (!printed_cores && strncmp(line, "cpu cores", 9) == 0) {
        printf("%s", line);
        printed_cores = 1;
    }
}

        fclose(cpu_fp);
    }
    return 0;
}