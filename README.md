## TMAKE

tmake is a simple program for the purpose of speeding up the setup of some working spaces.
Using tmake you can make project templates and quickly add them to your next project.

## Usage

You can use the program in the following three ways:

```
tmake <flag>
```
where the flags are:
* -h, for help.
* -l, for listing the templates.

Current directory use:
```
tmake <template_name>
```

Path use:
```
tmake <template_name> <path>
```

For slightly more info, use the -h flag.
## Example Template

```
<program_path>/templates/c:
incl  main

<program_path>/templates/c/incl:

<program_path>/templates/c/main:
main.c
```
where main.c has
```C
int main(int argc, char * argv)
{
    return 0;
}
```