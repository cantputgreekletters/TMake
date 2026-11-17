#include "directory_handling.h"


#define test_path "./test/"

int main(int argc, char * argv[])
{
    if(argc == 1)
    {
        printf("Template name was not given..\n");
        return -1;
    }

    if(! init_program())
    {
        return -1;
    }
    char * template_name = argv[1];

    if(strcmp(template_name, "-l") == 0 )
    {
        list_directory(templates_path);
        return 0;
    }else if(strcmp(template_name, "-h") == 0)
    {
        printf(
            "tmake -l, lists all the available templates\n."
            "tmake -h, help\n."
            "tmake <template_name>, adds the selected template to your current path\n."
            "tmake <template_name> <path>, adds the selected template to the given path\n.");
        return 0;
    }

    if(! exists_template(template_name))
    {
        printf("Template name \"%s\" was not found..\n", template_name);
        return -1;
    }

    if(argc == 3)
    {
        char * path = argv[2];
        make_template(argv[1], path);
    } else if(argc < 3)
    {
        char path[PATH_MAX];

        if(getcwd(path, sizeof(path)) == NULL)
        {
            printf("Could not get current directory\n");
            return -1;
        }

        char * path_end = strrchr(path, '\0');
        if(path_end)
        {
            *path_end = '/';
            *(path_end + 1) = '\0';
        }
        make_template(argv[1], path);
    }
    

    return 0;
}