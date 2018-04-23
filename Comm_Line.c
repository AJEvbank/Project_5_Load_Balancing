#ifndef COMM_LINE

#define COMM_LINE

#include "main.h"

void CommLineArgs(int argc,
                  char ** argv,
                  int *seed,
                  long double *max_num,
                  int *n,
                  int *print,
                  long double *epsilon,
                  long double *min_num
                 )
{
  *seed = SEED; *max_num = MAX_NUM; *n = N; *print = PRINT, *epsilon = EPSILON, *min_num = MIN_NUM;
  static char * SHORT = "";
	static struct option OPTS[] =
																{
                                  {"seed",required_argument,0,'s'},
																	{"max_num",required_argument,0,'m'},
                                  {"n",required_argument,0,'n'},
                                  {"epsilon",required_argument,0,'e'},
                                  {"min_num",required_argument,0,'i'},
                                  {"print",no_argument,0,'p'},
																	{0,0,0,0}
																};
	int ch;
	int opt_index = 0;
	while(1)
	{
		ch = getopt_long_only(argc,argv,SHORT,OPTS,&opt_index);

    if (ch == -1)
		{
			break;
		}

    switch(ch)
    {
      case 's':
                if(isNumber(optarg))
                {
                  *seed = atoi(optarg);
                }
                else
                {
                  *seed = SEED;
                }
                break;
      case 'm':
                if(isNumber(optarg))
                {
                  *max_num = strtold(optarg, NULL);
                }
                else
                {
                  *max_num = MAX_NUM;
                }
                break;
    case 'i':
              if(isNumber(optarg))
              {
                *min_num = strtold(optarg, NULL);
              }
              else
              {
                *min_num = MIN_NUM;
              }
              break;
      case 'n':
                if(isNumber(optarg))
                {
                  *n = atoi(optarg);
                }
                else
                {
                  *n = N;
                }
                break;
      case 'p':
                *print = 1;
                break;
      case 'e':
                if(isNumber(optarg))
                {
                  *epsilon = strtold(optarg, NULL);
                }
                else
                {
                  *epsilon = EPSILON;
                }
                break;
      default:
                printf("default case\n");
                break;
    }
  }

}

int isNumber(const char * str)
{
	int i;
	int len = strlen(str);
	char ch;
	enum isNumStates state = INITIAL;
	if (len > 0)
	{
		for (i = 0; i < len; i++)
		{
			ch = str[i];
			switch (state)
			{
			case INITIAL:
			{
				if (ch == '-' || ch == '+')
				{
					state = PLUSORMINUS;
				}
				else if (ch == '0')
				{
					state = ZERO;
				}
				else if (isdigit(ch))
				{
					state = NUMBER;
				}
				else
				{
					state = ERROR;
				}
				break;
			}

			case PLUSORMINUS:
			{
				if (ch == '0')
				{
					state = ZERO;
				}
				else if (isdigit(ch))
				{
					state = NUMBER;
				}
				else
				{
					state = ERROR;
				}
				break;
			}

			case ZERO:
			{
				if (ch == '.')
				{
					state = DECIMAL;
				}
				else
				{
					state = ERROR;
				}
				break;
			}

			case NUMBER:
			{
				if (isdigit(ch))
				{
					state = NUMBER;
				}
				else if (ch == '.')
				{
					state = DECIMAL;
				}
				else
				{
					state = ERROR;
				}
				break;
			}

			case DECIMAL:
			{
				if (isdigit(ch))
				{
					state = DECIMAL;
				}
				else
				{
					state = ERROR;
				}
				break;
			}

			case ERROR:
			{
				return 0;
				break;
			}

			default:
			{
				printf("default in isNumber: %d \n", (int)state);
				return 0;
				break;
			}

			}
		}
		return 1;
	}
	else
	{
		return 0;
	}
}



#endif
