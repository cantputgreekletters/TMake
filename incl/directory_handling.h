#if !defined(__DIRECTORY_HANDLING_H__)
#define __DIRECTORY_HANDLING_H__

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>

#define bool int
#define true 1
#define false 0

char exe_path[PATH_MAX];

char templates_path[PATH_MAX];

bool init_program()
{
    ssize_t len = readlink("/proc/self/exe", exe_path, sizeof(exe_path) - 1);

    if(len == -1)
    {
        printf("Could not init program.\n");
        return false;
    }

    exe_path[len] = '\0';

    char * last_slash = strrchr(exe_path, '/');
    if(last_slash)
    {
        *last_slash = '\0';
    }

    int result = snprintf(templates_path, sizeof(templates_path), "%s/templates/", exe_path);

    if (result < 0 || (size_t)result >= sizeof(templates_path))
    {
        printf("Templates path is too long.\n");
        return false;
    }
    return true;
}

void list_directory(char * path)
{
    DIR * dir = opendir(path);
    if(dir == NULL)
    {
        printf("Error: Could not open directory %s.\n", path);
        return;
    }

    struct dirent * entry;

    while ((entry = readdir(dir)) != NULL)
    {
        if(strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) continue;
        printf("%s\n", entry->d_name);
    }
    
    closedir(dir);
}

void make_template(char * template_name, char * target_path)
{
    char command[4096];
    int result = snprintf(command, sizeof(command), "cp -r \"%s%s/.\" \"%s\"", templates_path, template_name, target_path);
    if (result < 0 || (size_t)result >= sizeof(command))
    {
        printf("Command path is too long.\n");
        return;
    }
    
    result = system(command);
    
    if(result == -1)
    {
        printf("Failed to call command\n");
        return;
    }

    printf("Made template \"%s\" to: %s\n", template_name, target_path);
}

bool exists_template(char * name)
{
    const char * path = templates_path;
    DIR * dir = opendir(path);
    if(dir == NULL)
    {
        printf("Error: Could not open directory %s.\n", path);
        return false;
    }

    struct dirent * entry;
    
    bool val = false;
    while ((entry = readdir(dir)) != NULL)
    {
        if(strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) continue;
        if(strcmp(name, entry->d_name) == 0)
        {
            val = true;
            break;
        }
    }
    
    closedir(dir);

    return val;
}

#endif // __DIRECTORY_HANDLING_H__
